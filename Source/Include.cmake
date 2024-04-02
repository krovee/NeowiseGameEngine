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
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
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

macro(enable_compiler_features)
    if (WIN32)
        add_compile_options(/arch:AVX /Ot /GS- /sdl- /fp:fast /GR- /permissive- /Gr)
    else ()
        add_compile_options(-mstackrealign -ffp-model=fast -march=x86-64-v3 -fno-exceptions -fno-rtti)
    endif ()
endmacro(enable_compiler_features)

macro(enable_warnings)
    if (WIN32)
        add_compile_options(/WX)
    else ()
        add_compile_options(-Wall -Wextra)
    endif ()
endmacro(enable_warnings)

macro(target_link_os_dependent_libraries TARGETNAME)
    set(LINKLIBS)

    if (LINUX)
        find_package(X11 REQUIRED)
        list(APPEND LINKLIBS ${X11_X11_xcb_LIB} ${X11_X11_LIB})
    endif (LINUX)
    

    target_link_libraries(${TARGETNAME} PRIVATE ${LINKLIBS})
endmacro(target_link_os_dependent_libraries TARGETNAME)


