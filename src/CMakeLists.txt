add_library(
    ${PROJECT_NAME}
    UnrealVoxelSim/Composition/Game.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/public>"
        "$<INSTALL_INTERFACE:include>"
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        UnrealVoxelSim.Ecs.Api
        UnrealVoxelSim.Forest.Generation.Api
        UnrealVoxelSim.Movement.Api
        UnrealVoxelSim.Navigation.Api
        UnrealVoxelSim.Profiling.Api
        UnrealVoxelSim.Simulation.Api
        UnrealVoxelSim.Trees.Api
        UnrealVoxelSim.Voxel.Api
        UnrealVoxelSim.Voxel.Solid.Api
    PRIVATE
        UnrealVoxelSim.Events.InMemory
        UnrealVoxelSim.Ecs.EnTT
        UnrealVoxelSim.Forest.Generation
        UnrealVoxelSim.Movement.Voxel
        UnrealVoxelSim.Navigation.Voxel
        UnrealVoxelSim.Simulation.FixedStep
        UnrealVoxelSim.Simulation.Pipeline
        UnrealVoxelSim.Spatial.Index.Voxel.Chunked
        UnrealVoxelSim.Trees
        UnrealVoxelSim.Voxel.Chunked
        UnrealVoxelSim.Voxel.Solid
)

if(UNREALVOXELSIM_ENABLE_PROFILING)
    target_compile_definitions(${PROJECT_NAME} PRIVATE UNREALVOXELSIM_PROFILING_ENABLED=1)
endif()

UnrealVoxelSimConfigureTarget(${PROJECT_NAME})
