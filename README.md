# UnrealVoxelSim.Composition.Game

Platform-independent application composition root for the core simulation domains. It owns the concrete ECS, voxel,
movement, navigation, event, pipeline, and fixed-step implementations and exposes domain API views to outer
application/world composition.

The core deterministic order is voxel topology/planning, following, then movement. An outer world composer may prepend
explicit simulation participants before the first tick without transferring their policy or ownership into this module.
Local domain calls and events remain synchronous. The composition object is never injected into a domain system.

This module contains no world catalog, terrain generation, pawns, population policy, presentation state, or runtime
statistics. Those belong to platform adapters or dedicated world-building modules.
