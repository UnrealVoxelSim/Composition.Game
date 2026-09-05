#include "UnrealVoxelSim/Composition/Game.h"

#include "UnrealVoxelSim/Ecs/EnTT/Registry.h"
#include "UnrealVoxelSim/Events/Api/IPublisher.h"
#include "UnrealVoxelSim/Events/InMemory/Channel.h"
#include "UnrealVoxelSim/Forest/Generation/Generator.h"
#include "UnrealVoxelSim/Movement/Voxel/Controller.h"
#include "UnrealVoxelSim/Navigation/Voxel/Follower.h"
#include "UnrealVoxelSim/Navigation/Voxel/Planner.h"
#include "UnrealVoxelSim/Navigation/Voxel/SolidEnvironment.h"
#include "UnrealVoxelSim/Navigation/Voxel/SolidInvalidation.h"
#include "UnrealVoxelSim/Simulation/FixedStep/Controller.h"
#include "UnrealVoxelSim/Simulation/Pipeline/Pipeline.h"
#include "UnrealVoxelSim/Spatial/Index/Voxel/Chunked/Index.h"
#include "UnrealVoxelSim/Trees/Api/Species.h"
#include "UnrealVoxelSim/Trees/Api/StandardSpecies.h"
#include "UnrealVoxelSim/Trees/Controller.h"
#include "UnrealVoxelSim/Voxel/Chunked/Field.h"
#include "UnrealVoxelSim/Voxel/Solid/Api/Changed.h"
#include "UnrealVoxelSim/Voxel/Solid/Controller.h"
#include "UnrealVoxelSim/Voxel/Solid/Api/StandardMaterials.h"

#include <array>
#include <stdexcept>
#include <vector>

namespace UnrealVoxelSim::Composition {
Game::Game(
    const GameConfiguration configuration,
    const std::span<const Voxel::Solid::Api::MaterialTraversal> materials,
    const std::span<const Movement::Api::GroundedProfile> movementProfiles,
    const std::span<const Voxel::Api::Region> navigationPreparation,
    Profiling::Api::IRecorder &profiling) {
  if (!configuration.Bounds.IsValid() ||
      !configuration.RegistryScope.IsValid()) {
    throw std::invalid_argument{
        "Game composition requires valid world bounds and registry scope."};
  }

  m_Field = std::make_unique<Voxel::Chunked::Field>(configuration.Bounds);
  auto solidChanges =
      std::make_unique<Events::InMemory::Channel<Voxel::Solid::Api::Changed>>();
  auto &solidChangePublisher =
      static_cast<Events::Api::IPublisher<Voxel::Solid::Api::Changed> &>(
          *solidChanges);
  std::vector<Voxel::Solid::Api::MaterialId> materialIds;
  materialIds.reserve(materials.size());
  for (const auto &material : materials) {
    materialIds.push_back(material.Material);
  }
  m_Solids = std::make_unique<Voxel::Solid::Controller>(
      *m_Field, *m_Field, *m_Field, materialIds, std::move(solidChanges),
      solidChangePublisher);

  m_Entities =
      std::make_unique<Ecs::EnTT::Registry>(configuration.RegistryScope);
  m_VoxelEntityIndex = std::make_unique<
      Spatial::Index::Voxel::Chunked::Index<Ecs::Api::EntityId>>();
  const std::array treeSpecies{
      Trees::Api::Species{Trees::Api::StandardSpecies::Oak,
                          Voxel::Solid::Api::StandardMaterials::Trunk,
                          Voxel::Solid::Api::StandardMaterials::Leaves}};
  m_Trees = std::make_unique<Trees::Controller>(
      Trees::Controller::Access{*m_Entities}, *m_VoxelEntityIndex,
      *m_VoxelEntityIndex, *m_Solids, *m_Solids, *m_Solids,
      m_Solids->Changes(), treeSpecies);
  const std::array forestGroundMaterials{
      Voxel::Solid::Api::StandardMaterials::Dirt,
      Voxel::Solid::Api::StandardMaterials::Grass,
      Voxel::Solid::Api::StandardMaterials::Stone};
  m_Forests = std::make_unique<Forest::Generation::Generator>(
      *m_Solids, *m_Trees, forestGroundMaterials);
  m_Movement = std::make_unique<Movement::Voxel::Controller>(
      Movement::Voxel::Controller::Access{*m_Entities}, *m_Solids,
      movementProfiles, materials);
  m_NavigationEnvironment =
      std::make_unique<Navigation::Voxel::SolidEnvironment>(*m_Field, *m_Solids,
                                                            materials);
  m_Planner = std::make_unique<Navigation::Voxel::Planner>(
      *m_NavigationEnvironment, movementProfiles, profiling,
      configuration.PlannerExpansionsPerTick,
      configuration.PlannerMaximumExpansionsPerRequest,
      configuration.ReachabilityExpansionsPerTick,
      configuration.NavigationTileBuildsPerStep,
      configuration.NavigationComponentCellsPerTick);
  m_Planner->Prepare(navigationPreparation);
  m_Navigation = std::make_unique<Navigation::Voxel::Follower>(
      Navigation::Voxel::Follower::Access{*m_Entities}, *m_Planner, *m_Movement,
      movementProfiles);
  m_NavigationInvalidation =
      std::make_unique<Navigation::Voxel::SolidInvalidation>(
          m_Solids->Changes(), *m_Planner);

  const std::array<Simulation::Api::IStepParticipant *, 4> participants{
      m_Trees.get(), m_Planner.get(), m_Navigation.get(), m_Movement.get()};
  m_Pipeline = std::make_unique<Simulation::Pipeline::Pipeline>(participants);
  m_Simulation =
      std::make_unique<Simulation::FixedStep::Controller>(*m_Pipeline);
}

Game::~Game() = default;

const Voxel::Api::IBounds &Game::GetVoxelWorldBoundsProvider() const noexcept {
  return *m_Field;
}

const Voxel::Solid::Api::IReader &Game::GetSolidVoxelsReader() const noexcept {
  return *m_Solids;
}

const Voxel::Solid::Api::IRegionReader &
Game::GetSolidVoxelsRegionReader() const noexcept {
  return *m_Solids;
}

Voxel::Solid::Api::IChangeSource &Game::GetSolidVoxelsChangeSource() noexcept {
  return m_Solids->Changes();
}

Voxel::Solid::Api::IPlacer &Game::GetSolidVoxelPlacer() noexcept {
  return *m_Solids;
}

Voxel::Solid::Api::IRemover &Game::GetSolidVoxelRemover() noexcept {
  return *m_Solids;
}
Movement::Api::IIntentReceiver &Game::GetMovementIntentReceiver() noexcept {
  return *m_Movement;
}

Navigation::Api::INavigation &Game::GetNavigation() noexcept {
  return *m_Navigation;
}

Trees::Api::IPlanter &Game::GetTreePlanter() noexcept { return *m_Trees; }

Trees::Api::IRemover &Game::GetTreeRemover() noexcept { return *m_Trees; }

Forest::Generation::Api::IGenerator &Game::GetForestGenerator() noexcept {
  return *m_Forests;
}

Simulation::Api::IPacer &Game::GetSimulationPacer() noexcept {
  return *m_Simulation;
}
Simulation::Api::IStepper &Game::GetSimulationStepper() noexcept {
  return *m_Simulation;
}

Ecs::EnTT::Registry &Game::GetEcsRegistry() noexcept { return *m_Entities; }

const Ecs::EnTT::Registry &Game::GetEcsRegistry() const noexcept {
  return *m_Entities;
}

void Game::SetPreDomainParticipants(
    const std::span<Simulation::Api::IStepParticipant *const> participants) {
  if (m_Simulation->CurrentTick() != Simulation::Api::TickIndex{}) {
    throw std::logic_error{
        "Simulation participants cannot change after the first tick."};
  }
  std::vector<Simulation::Api::IStepParticipant *> ordered(participants.begin(),
                                                           participants.end());
  ordered.push_back(m_Trees.get());
  ordered.push_back(m_Planner.get());
  ordered.push_back(m_Navigation.get());
  ordered.push_back(m_Movement.get());
  m_Pipeline->SetParticipants(ordered);
}
} // namespace UnrealVoxelSim::Composition
