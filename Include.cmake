## Include.cmake
## External cmake file to define some useful macros
## and utilities.

## log(MSG) <- macro to print standard CMake-like message.
macro(log MSG)
    message("-- " ${MSG})
endmacro(log)

macro(fatal MSG)
    message(FATAL_ERROR "-- " ${MSG})
endmacro(fatal)

macro(error MSG)
    message(SEND_ERROR "-- " ${MSG})
endmacro(error)

macro(warn MSG)
    message(WARNING "-- " ${MSG})
endmacro(warn)

macro(guard_build_type DEFAULT_BUILD_TYPE)
    if ("${DEFAULT_BUILD_TYPE}" STREQUAL "")
        error("Failed to call guard_build_type() with empty default build type!")
    endif ()

    if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
        set(CMAKE_BUILD_TYPE ${DEFAULT_BUILD_TYPE})
    endif ()
endmacro(guard_build_type)

macro(initialize_compilers)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_DEFINITION_PREFIX "-D")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_CXX_DEFINITION_PREFIX "/D")
    endif()
endmacro(initialize_compilers)

macro(target_populate_compile_definitions TARGET_NAME DEFS)
    list(LENGTH ${DEFS} DEFS_COUNT)
    if (NOT "${DEFS_COUNT}" STREQUAL "0")
        foreach(DEF IN LISTS ${DEFS})
            target_compile_definitions(${TARGET_NAME} PRIVATE "${CMAKE_CXX_DEFINITION_PREFIX}${DEF}") 
        endforeach(DEF IN LISTS ${DEFS})
    endif (NOT "${DEFS_COUNT}" STREQUAL "0")
endmacro(target_populate_compile_definitions TARGET_NAME DEFS)

macro(add_native_executable APPNAME SRCS)
    if (WIN32)
        add_executable(${APPNAME} WIN32 ${SRCS})
    elseif (UNIX)
        add_executable(${APPNAME} ${SRCS})
    endif ()
    
endmacro(add_native_executable APPNAME)

macro(initialize_vulkan_sdk)
    find_package(Vulkan REQUIRED)
endmacro(initialize_vulkan_sdk)
