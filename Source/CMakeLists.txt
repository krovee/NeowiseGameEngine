
## CMake 3.28 is modern enough to be main version
## to compile and build Neowise Engine project.
cmake_minimum_required(VERSION 3.27)

## Set project name as 'Neowise' and specify C++.
project(Neowise CXX)

## Set language standard version
set(CMAKE_CXX_STANDARD 20)

## Include external cmake file.
include(Include.cmake)

## Sometimes when you run configuration on CMake,
## CMAKE_BUILD_TYPE will be empty, which defines
## undefined behaviour in our code. So, guard code
## from this state and force to accept Debug mode
## if CMAKE_BUILD_TYPE is empty.
guard_build_type("Debug")

## Initialize compiler-dependent variables.
initialize_compilers()

## Find and initialize VulkanSDK
initialize_vulkan_sdk()

## Setup PREPROCESSOR_DEFINITIONS variable to create
## required macro definitions for compilation.
set(PREPROCESSOR_DEFINITIONS)

## Enable AVX instructions on compiler-dependent level.
enable_compiler_features()

## Enable warnings check.
enable_warnings()

## Setup for Debug compilation...
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    log("Configuring Debug...")
    list(APPEND PREPROCESSOR_DEFINITIONS _DEBUG)
endif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")

## Setup for Debug compilation...
if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    log("Configuring Release...")
    list(APPEND PREPROCESSOR_DEFINITIONS NDEBUG)
endif("${CMAKE_BUILD_TYPE}" STREQUAL "Release")

## Setup for Debug compilation...
if("${CMAKE_BUILD_TYPE}" STREQUAL "Ship")
    log("Configuring Shiping...")
    list(APPEND PREPROCESSOR_DEFINITIONS NDEBUG NW_SHIP_BUILD)
endif("${CMAKE_BUILD_TYPE}" STREQUAL "Ship")

## ENGINE CONFIGURATION:
list(APPEND ENGINE_DEFINITIONS ${PREPROCESSOR_DEFINITIONS} ENGINE_EXPORTS)

## Inlcude path.
include_directories("Engine/Public" ${Vulkan_INCLUDE_DIRS})
## Sources path.
set(ENGINE_SOURCE_PREFIX "Engine/Private")

# Create a list of sources:
set(
    ENGINE_SOURCES

    # BASE
    ${ENGINE_SOURCE_PREFIX}/Base/Memory/AllocatorPolicyBase.cpp
    ${ENGINE_SOURCE_PREFIX}/Base/Memory/FixedHeapAllocatorPolicy.cpp
    ${ENGINE_SOURCE_PREFIX}/Base/Allocators.cpp
    ${ENGINE_SOURCE_PREFIX}/Base/BuildVersion.cpp
    ${ENGINE_SOURCE_PREFIX}/Base/CRC.cpp
    ${ENGINE_SOURCE_PREFIX}/Base/Diagnostics.cpp
    ${ENGINE_SOURCE_PREFIX}/Base/DynamicLibrary.cpp
    ${ENGINE_SOURCE_PREFIX}/Base/Hash.cpp
    ${ENGINE_SOURCE_PREFIX}/Base/MD5.cpp
    ${ENGINE_SOURCE_PREFIX}/Base/MemoryUtilities.cpp
    ${ENGINE_SOURCE_PREFIX}/Base/String.cpp
    ${ENGINE_SOURCE_PREFIX}/Base/StringUtils.cpp
    ${ENGINE_SOURCE_PREFIX}/Base/StringView.cpp
    ${ENGINE_SOURCE_PREFIX}/Base/Thread.cpp
    ${ENGINE_SOURCE_PREFIX}/Base/TimePoint.cpp
    ${ENGINE_SOURCE_PREFIX}/Base/UUID.cpp

    # ENGINE/RENDERER
    
    # ENGINE/RHI
    ${ENGINE_SOURCE_PREFIX}/Engine/RHI/RHI.cpp
    
    # ENGINE/VULKANRHI
    ${ENGINE_SOURCE_PREFIX}/Engine/VulkanRHI/Common.cpp
    ${ENGINE_SOURCE_PREFIX}/Engine/VulkanRHI/DynamicProvider.cpp

    # ENGINE/EVENTS
    ${ENGINE_SOURCE_PREFIX}/Engine/Events/Bus.cpp
    ${ENGINE_SOURCE_PREFIX}/Engine/Events/EngineEvents.cpp
    
    # ENGINE
    ${ENGINE_SOURCE_PREFIX}/Engine/Application.cpp
    ${ENGINE_SOURCE_PREFIX}/Engine/BaseWindow.cpp
    ${ENGINE_SOURCE_PREFIX}/Engine/EngineBoot.cpp
    ${ENGINE_SOURCE_PREFIX}/Engine/EngineGlobals.cpp
    ${ENGINE_SOURCE_PREFIX}/Engine/EngineLoop.cpp
    ${ENGINE_SOURCE_PREFIX}/Engine/GameRuntimeApplication.cpp
    ${ENGINE_SOURCE_PREFIX}/Engine/RenderThread.cpp

    # INPUT
    ${ENGINE_SOURCE_PREFIX}/Input/InputDevice.cpp
    ${ENGINE_SOURCE_PREFIX}/Input/InputSystem.cpp
    ${ENGINE_SOURCE_PREFIX}/Input/KeyboardInputDevice.cpp
    ${ENGINE_SOURCE_PREFIX}/Input/Keycode.cpp
    ${ENGINE_SOURCE_PREFIX}/Input/MouseInputDevice.cpp

    # LAUNCH
    ${ENGINE_SOURCE_PREFIX}/Launch/SecureMain.cpp

    # MATH
    ${ENGINE_SOURCE_PREFIX}/Math/Half.cpp
    ${ENGINE_SOURCE_PREFIX}/Math/Matrix3.cpp
    ${ENGINE_SOURCE_PREFIX}/Math/Matrix4.cpp
    ${ENGINE_SOURCE_PREFIX}/Math/MatrixFunctions.cpp
    ${ENGINE_SOURCE_PREFIX}/Math/Packed.cpp
    ${ENGINE_SOURCE_PREFIX}/Math/Projection.cpp
    ${ENGINE_SOURCE_PREFIX}/Math/Quaternion.cpp
    ${ENGINE_SOURCE_PREFIX}/Math/Scalar.cpp
    ${ENGINE_SOURCE_PREFIX}/Math/Transform.cpp
    ${ENGINE_SOURCE_PREFIX}/Math/Vector2.cpp
    ${ENGINE_SOURCE_PREFIX}/Math/Vector3.cpp
    ${ENGINE_SOURCE_PREFIX}/Math/Vector4.cpp
    ${ENGINE_SOURCE_PREFIX}/Math/VectorFunctions.cpp

    # PLATFORM/NULL
    ${ENGINE_SOURCE_PREFIX}/Platform/Null/NullPlatformConsole.cpp
    ${ENGINE_SOURCE_PREFIX}/Platform/Null/NullPlatformKeyboard.cpp
    ${ENGINE_SOURCE_PREFIX}/Platform/Null/NullPlatformMemory.cpp
    ${ENGINE_SOURCE_PREFIX}/Platform/Null/NullPlatformSystemClock.cpp
    ${ENGINE_SOURCE_PREFIX}/Platform/Null/NullPlatformWindow.cpp
)

if (WIN32)
    list(
        APPEND 
        ENGINE_SOURCES

        # PLATFORM/WINDOWS
        ${ENGINE_SOURCE_PREFIX}/Platform/Windows/WindowsBase.cpp
        ${ENGINE_SOURCE_PREFIX}/Platform/Windows/WindowsPlatformAssert.cpp
        ${ENGINE_SOURCE_PREFIX}/Platform/Windows/WindowsPlatformConsole.cpp
        ${ENGINE_SOURCE_PREFIX}/Platform/Windows/WindowsPlatformFilesystem.cpp
        ${ENGINE_SOURCE_PREFIX}/Platform/Windows/WindowsPlatformKeyboard.cpp
        ${ENGINE_SOURCE_PREFIX}/Platform/Windows/WindowsPlatformMemory.cpp
        ${ENGINE_SOURCE_PREFIX}/Platform/Windows/WindowsPlatformMutexLock.cpp
        ${ENGINE_SOURCE_PREFIX}/Platform/Windows/WindowsPlatformSystemClock.cpp
        ${ENGINE_SOURCE_PREFIX}/Platform/Windows/WindowsPlatformThread.cpp
        ${ENGINE_SOURCE_PREFIX}/Platform/Windows/WindowsPlatformWindow.cpp
    )
endif ()

if (LINUX)
    list(
        APPEND
        ENGINE_SOURCES 

        # PLATFORM/LINUX
        ${ENGINE_SOURCE_PREFIX}/Platform/Linux/LinuxBase.cpp
        ${ENGINE_SOURCE_PREFIX}/Platform/Linux/LinuxPlatformAssert.cpp
        ${ENGINE_SOURCE_PREFIX}/Platform/Linux/LinuxPlatformConsole.cpp
        ${ENGINE_SOURCE_PREFIX}/Platform/Linux/LinuxPlatformDynamicLibrary.cpp
        ${ENGINE_SOURCE_PREFIX}/Platform/Linux/LinuxPlatformKeyboard.cpp
        ${ENGINE_SOURCE_PREFIX}/Platform/Linux/LinuxPlatformMemory.cpp
        ${ENGINE_SOURCE_PREFIX}/Platform/Linux/LinuxPlatformMutexLock.cpp
        ${ENGINE_SOURCE_PREFIX}/Platform/Linux/LinuxPlatformSystemClock.cpp
        ${ENGINE_SOURCE_PREFIX}/Platform/Linux/LinuxPlatformThread.cpp
        ${ENGINE_SOURCE_PREFIX}/Platform/Linux/LinuxPlatformWindow.cpp
    )
endif ()

## Create engine's dynamic library
add_library(NeowiseEngine SHARED ${ENGINE_SOURCES})
target_populate_compile_definitions(NeowiseEngine ENGINE_DEFINITIONS)
target_compile_definitions(NeowiseEngine PRIVATE ENGINE_EXPORTS)
target_link_os_dependent_libraries(NeowiseEngine)

## APPLICATION CONFIGURATION:
list(APPEND APPLICATION_DEFINITIONS ${PREPROCESSOR_DEFINITIONS})

## Inlcude path.
include_directories("Engine/Public" ${Vulkan_INCLUDE_DIRS})
## Sources path.
set(APPLICATION_SOURCE_PREFIX "Application/Private")

# Create a list of sources:
set(
    APPLICATION_SOURCES

    ${APPLICATION_SOURCE_PREFIX}/Launch/WinMain.cpp
    ${APPLICATION_SOURCE_PREFIX}/Launch/LinuxMain.cpp
)

## Create application's executable
add_executable(Application WIN32 ${APPLICATION_SOURCES})
target_populate_compile_definitions(Application APPLICATION_DEFINITIONS)
target_link_libraries(Application PRIVATE NeowiseEngine)
