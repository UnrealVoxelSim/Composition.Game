#pragma once

#include "UnrealVoxelSim/Ecs/Api/RegistryScopeId.h"
#include "UnrealVoxelSim/Forest/Generation/Api/IGenerator.h"
#include "UnrealVoxelSim/Movement/Api/GroundedProfile.h"
#include "UnrealVoxelSim/Movement/Api/IIntentReceiver.h"
#include "UnrealVoxelSim/Navigation/Api/INavigation.h"
#include "UnrealVoxelSim/Profiling/Api/IRecorder.h"
#include "UnrealVoxelSim/Simulation/Api/IPacer.h"
#include "UnrealVoxelSim/Simulation/Api/IStepParticipant.h"
#include "UnrealVoxelSim/Simulation/Api/IStepper.h"
#include "UnrealVoxelSim/Trees/Api/IPlanter.h"
#include "UnrealVoxelSim/Trees/Api/IRemover.h"
#include "UnrealVoxelSim/Voxel/Api/IBounds.h"
#include "UnrealVoxelSim/Voxel/Api/Region.h"
#include "UnrealVoxelSim/Voxel/Solid/Api/IChangeSource.h"
#include "UnrealVoxelSim/Voxel/Solid/Api/IPlacer.h"
#include "UnrealVoxelSim/Voxel/Solid/Api/IReader.h"
#include "UnrealVoxelSim/Voxel/Solid/Api/IRegionReader.h"
#include "UnrealVoxelSim/Voxel/Solid/Api/IRemover.h"
#include "UnrealVoxelSim/Voxel/Solid/Api/MaterialId.h"
#include "UnrealVoxelSim/Voxel/Solid/Api/MaterialTraversal.h"

#include <cstddef>
#include <memory>
#include <span>

namespace UnrealVoxelSim::Ecs::EnTT {
class Registry;
}

namespace UnrealVoxelSim::Movement::Voxel {
class Controller;
}

namespace UnrealVoxelSim::Forest::Generation {
class Generator;
}

namespace UnrealVoxelSim::Spatial::Index::Voxel::Chunked {
template<typename TValue>
class Index;
}

namespace UnrealVoxelSim::Trees {
class Controller;
}

namespace UnrealVoxelSim::Navigation::Voxel {
class Follower;
}

namespace UnrealVoxelSim::Navigation::Voxel {
class Planner;
class SolidEnvironment;
class SolidInvalidation;
} // namespace UnrealVoxelSim::Navigation::Voxel

namespace UnrealVoxelSim::Simulation::FixedStep {
class Controller;
}

namespace UnrealVoxelSim::Simulation::Pipeline {
class Pipeline;
}

namespace UnrealVoxelSim::Voxel::Chunked {
class Field;
}

namespace UnrealVoxelSim::Voxel::Solid {
class Controller;
}

namespace UnrealVoxelSim::Composition {
struct GameConfiguration final {
  Voxel::Api::Region Bounds;
  Ecs::Api::RegistryScopeId RegistryScope{1};
  std::size_t PlannerExpansionsPerTick{768};
  std::size_t PlannerMaximumExpansionsPerRequest{65'536};
  std::size_t ReachabilityExpansionsPerTick{32};
  std::size_t NavigationTileBuildsPerStep{16};
  std::size_t NavigationComponentCellsPerTick{256};
};

class Game final {
public:
  Game(GameConfiguration configuration,
       std::span<const Voxel::Solid::Api::MaterialTraversal> materials,
       std::span<const Movement::Api::GroundedProfile> movementProfiles,
       std::span<const Voxel::Api::Region> navigationPreparation,
       Profiling::Api::IRecorder &profiling);
  ~Game();

  Game(const Game &) = delete;
  Game &operator=(const Game &) = delete;
  Game(Game &&) = delete;
  Game &operator=(Game &&) = delete;

  [[nodiscard]] const Voxel::Api::IBounds &
  GetVoxelWorldBoundsProvider() const noexcept;
  [[nodiscard]] const Voxel::Solid::Api::IReader &
  GetSolidVoxelsReader() const noexcept;
  [[nodiscard]] const Voxel::Solid::Api::IRegionReader &
  GetSolidVoxelsRegionReader() const noexcept;
  [[nodiscard]] Voxel::Solid::Api::IChangeSource &
  GetSolidVoxelsChangeSource() noexcept;
  [[nodiscard]] Voxel::Solid::Api::IPlacer &GetSolidVoxelPlacer() noexcept;
  [[nodiscard]] Voxel::Solid::Api::IRemover &GetSolidVoxelRemover() noexcept;
  [[nodiscard]] Movement::Api::IIntentReceiver &
  GetMovementIntentReceiver() noexcept;
  [[nodiscard]] Navigation::Api::INavigation &GetNavigation() noexcept;
  [[nodiscard]] Trees::Api::IPlanter &GetTreePlanter() noexcept;
  [[nodiscard]] Trees::Api::IRemover &GetTreeRemover() noexcept;
  [[nodiscard]] Forest::Generation::Api::IGenerator &GetForestGenerator() noexcept;
  [[nodiscard]] Simulation::Api::IPacer &GetSimulationPacer() noexcept;
  [[nodiscard]] Simulation::Api::IStepper &GetSimulationStepper() noexcept;

  // Application/world composition uses this only to construct
  // capability-limited ECS participants.
  [[nodiscard]] Ecs::EnTT::Registry &GetEcsRegistry() noexcept;
  [[nodiscard]] const Ecs::EnTT::Registry &GetEcsRegistry() const noexcept;
  void SetPreDomainParticipants(
      std::span<Simulation::Api::IStepParticipant *const> participants);

private:
  // TODO Is there any reason to keep these classes in heap?
  std::unique_ptr<Voxel::Chunked::Field> m_Field;
  std::unique_ptr<Voxel::Solid::Controller> m_Solids;
  std::unique_ptr<Ecs::EnTT::Registry> m_Entities;
  std::unique_ptr<Spatial::Index::Voxel::Chunked::Index<Ecs::Api::EntityId>> m_VoxelEntityIndex;
  std::unique_ptr<Trees::Controller> m_Trees;
  std::unique_ptr<Forest::Generation::Generator> m_Forests;
  std::unique_ptr<Movement::Voxel::Controller> m_Movement;
  std::unique_ptr<Navigation::Voxel::SolidEnvironment> m_NavigationEnvironment;
  std::unique_ptr<Navigation::Voxel::Planner> m_Planner;
  std::unique_ptr<Navigation::Voxel::Follower> m_Navigation;
  std::unique_ptr<Navigation::Voxel::SolidInvalidation>
      m_NavigationInvalidation;
  std::unique_ptr<Simulation::Pipeline::Pipeline> m_Pipeline;
  std::unique_ptr<Simulation::FixedStep::Controller> m_Simulation;
};
} // namespace UnrealVoxelSim::Composition
