# Install script for directory: C:/Software/GitHub/UnrealVoxelSim/Composition.Game

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/install/windows-msvc-debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/windows-msvc-debug/_deps/uvsbuild-build/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/windows-msvc-debug/_deps/unrealvoxelsim.events.inmemory-build/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/windows-msvc-debug/_deps/unrealvoxelsim.ecs.api-build/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/windows-msvc-debug/_deps/unrealvoxelsim.ecs.entt-build/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/windows-msvc-debug/_deps/unrealvoxelsim.forest.generation.api-build/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/windows-msvc-debug/_deps/unrealvoxelsim.forest.generation-build/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/windows-msvc-debug/_deps/unrealvoxelsim.movement.api-build/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/windows-msvc-debug/_deps/unrealvoxelsim.movement.voxel-build/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/windows-msvc-debug/_deps/unrealvoxelsim.navigation.api-build/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/windows-msvc-debug/_deps/unrealvoxelsim.navigation.voxel-build/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/windows-msvc-debug/_deps/unrealvoxelsim.simulation.fixedstep-build/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/windows-msvc-debug/_deps/unrealvoxelsim.simulation.pipeline-build/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/windows-msvc-debug/_deps/unrealvoxelsim.spatial.index.voxel.api-build/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/windows-msvc-debug/_deps/unrealvoxelsim.spatial.index.voxel.chunked-build/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/windows-msvc-debug/_deps/unrealvoxelsim.trees-build/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/windows-msvc-debug/_deps/unrealvoxelsim.voxel.chunked-build/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/windows-msvc-debug/_deps/unrealvoxelsim.voxel.solid-build/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/windows-msvc-debug/src/cmake_install.cmake")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/windows-msvc-debug/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Software/GitHub/UnrealVoxelSim/Composition.Game/o/windows-msvc-debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
