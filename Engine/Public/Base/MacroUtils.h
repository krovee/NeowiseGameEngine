#pragma once

/**
* Convert any x-literal into c string.
*/
#ifndef NW_STRINGIFY
#	define NW_STRINGIFY(x) #x
#endif

/**
* Helper for concatenation.
*/
#ifndef NW_CONCAT2
#	define NW_CONCAT2(x, y) x ## y
#endif

/**
* Concatenate x and y.
*/
#ifndef NW_CONCAT
#	define NW_CONCAT(x, y) NW_CONCAT2(x, y)
#endif

/**
 * 
*/
#ifndef NW_UNUSED
#   define NW_UNUSED(x) (void)x
#endif 

/**
* Everything in x will be placed during all build 
* types except for shipped code. 
*/
#ifndef NW_NONSHIP_CODE
#	define NW_NONSHIP_CODE(x) x
#endif 

/**
* Definitions of handy macros to determine build 
* type in compile time in a 'standard' way.
*/

#ifdef  _DEBUG
#	define NW_BUILD_TYPE_DEBUG 0xdeb
#else
#	define NW_BUILD_TYPE_DEBUG 0
#endif

#if defined NDEBUG && !defined(NW_SHIP_BUILD)
#	define NW_BUILD_TYPE_RELEASE 0x7e1
#else
#	define NW_BUILD_TYPE_RELEASE 0
#endif

#ifdef NW_SHIP_BUILD
#	define NW_BUILD_TYPE_SHIP 0x517
#else
#	define NW_BUILD_TYPE_SHIP 0
#endif

#ifndef NW_BUILD_TYPE
#	define NW_BUILD_TYPE (NW_BUILD_TYPE_DEBUG | NW_BUILD_TYPE_RELEASE | NW_BUILD_TYPE_SHIP)
#endif

#if NW_BUILD_TYPE == NW_BUILD_TYPE_SHIP
#	undef  NW_NONSHIP_CODE
#	define NW_NONSHIP_CODE(x)
#endif

/**
* Helpers for min/max comparison and clamp.
*/

#ifndef NW_MIN
#	define NW_MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef NW_MAX
#	define NW_MAX(a, b) ((a) < (b) ? (b) : (a))
#endif

#ifndef NW_CLAMP
#	define NW_CLAMP(x, _min, _max) NW_MIN(NW_MAX(x, _min), _max)
#endif

/**
* Macros for endianness definition.
*/

#ifndef NW_LITTLE_ENDIAN
#	if (0x00000000ffffffff >> 31) == 1
#		define NW_LITTLE_ENDIAN 1
#	else
#		define NW_LITTLE_ENDIAN 0
#	endif
#endif

#ifndef NW_BIG_ENDIAN
#	if (0xffffffff0000000 >> 31) == 1
#		define NW_BIG_ENDIAN 1
#	else
#		define NW_BIG_ENDIAN 0
#	endif
#endif

#if NW_BIG_ENDIAN
#	error "This code is expected to be compiled on a little endian machine only!"
#endif

/**
* Macros to identify operating system which compiles this code.
*/

#ifndef NW_OS_TYPE_WIN32
#	ifdef _WIN32
#		define NW_OS_TYPE_WIN32 1
#	else
#		define NW_OS_TYPE_WIN32 0
#	endif
#endif

#ifndef NW_OS_TYPE_LINUX
#	ifdef __linux__
#		define NW_OS_TYPE_LINUX 1
#	else
#		define NW_OS_TYPE_LINUX 0
#	endif
#endif

/* 
* NW_API macro defined to export functions, objects from
* engine code over to application code base and being able
* to link against it.
*/

#ifdef ENGINE_EXPORTS
#   if NW_OS_TYPE_WIN32
#	    define NW_API __declspec(dllexport)
#   elif NW_OS_TYPE_LINUX
#	    define NW_API __attribute__ ((visibility ("default")))
#   endif
#else
#   if NW_OS_TYPE_WIN32
#	    define NW_API __declspec(dllimport)
#   elif NW_OS_TYPE_LINUX
#	    define NW_API __attribute__ ((visibility ("default")))
#   endif
#endif
