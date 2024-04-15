#pragma once

/**
* Convert any x-literal into c string.
*/
#ifndef NW_STRINGIFY
#	define NW_STRINGIFY(x) #x
#endif//NW_STRINGIFY

/**
 * 
*/
#ifndef NW_UNUSED
#   define NW_UNUSED(x) (void)x
#endif//NW_UNUSED

/**
* Everything in x will be placed during all build 
* types except for shipped code. 
*/
#ifndef NW_NONSHIP_CODE
#   define NW_NONSHIP_CODE(x) x
#endif//NW_NONSHIP_CODE

/**
* Definitions of handy macros to determine build 
* type in compile time in a 'standard' way.
*/

#ifdef  _DEBUG
#   define NW_BUILD_TYPE_DEBUG 1
#else
#   define NW_BUILD_TYPE_DEBUG 0
#endif//_DEBUG

#if defined(NDEBUG) && !defined(NW_SHIP_BUILD)
#   define NW_BUILD_TYPE_RELEASE 1
#else
#   define NW_BUILD_TYPE_RELEASE 0
#endif//NDEBUG

#ifdef NW_SHIP_BUILD
#   define NW_BUILD_TYPE_SHIP 1
#else
#   define NW_BUILD_TYPE_SHIP 0
#endif//NW_SHIP_BUILD

#ifndef NW_BUILD_TYPE
#   define NW_BUILD_TYPE (NW_BUILD_TYPE_DEBUG | NW_BUILD_TYPE_RELEASE | NW_BUILD_TYPE_SHIP)
#endif//NW_BUILD_TYPE

#if NW_BUILD_TYPE == NW_BUILD_TYPE_SHIP
#   undef  NW_NONSHIP_CODE
#   define NW_NONSHIP_CODE(x)
#endif

/**
* Helpers for min/max comparison and clamp.
*/

#ifndef NW_MIN
#   define NW_MIN(a, b) ((a) < (b) ? (a) : (b))
#endif//NW_MIN

#ifndef NW_MAX
#   define NW_MAX(a, b) ((a) < (b) ? (b) : (a))
#endif//NW_MAX

#ifndef NW_CLAMP
#   define NW_CLAMP(x, _min, _max) NW_MIN(NW_MAX(x, _min), _max)
#endif//NW_CLAMP

/**
* Macros for endianness definition.
*/

#ifndef NW_LITTLE_ENDIAN
#   if (0x00000000ffffffff >> 31) == 1
#       define NW_LITTLE_ENDIAN 1
#   else
#       define NW_LITTLE_ENDIAN 0
#   endif
#endif//NW_LITTLE_ENDIAN

#ifndef NW_BIG_ENDIAN
#   if (0xffffffff0000000 >> 31) == 1
#       define NW_BIG_ENDIAN 1
#   else
#       define NW_BIG_ENDIAN 0
#   endif
#endif//NW_BIG_ENDIAN

#if     NW_BIG_ENDIAN
#   error "This code is expected to be compiled on a little endian machine only!"
#endif//NW_BIG_ENDIAN

/**
* Macros to identify operating system which compiles this code.
*/

#ifndef NW_OS_TYPE_WIN32
#   ifdef _WIN32
#       define NW_OS_TYPE_WIN32 1
#   else
#       define NW_OS_TYPE_WIN32 0
#   endif
#endif//NW_OS_TYPE_WIN32

#ifndef NW_OS_TYPE_LINUX
#   ifdef __linux__
#       define NW_OS_TYPE_LINUX 1
#   else
#       define NW_OS_TYPE_LINUX 0
#   endif
#endif//NW_OS_TYPE_LINUX

/* 
* NW_API macro defined to export functions, objects from
* engine code over to application code base and being able
* to link against it.
*/

#ifdef ENGINE_EXPORTS
#   if NW_OS_TYPE_WIN32
#	    define NW_API __declspec(dllexport)
#   elif NW_OS_TYPE_LINUX
#       define NW_API __attribute__ ((visibility ("default")))
#   endif//NW_OS_TYPE_WIN32 || NW_OS_TYPE_LINUX
#else
#   if NW_OS_TYPE_WIN32
#       define NW_API __declspec(dllimport)
#   elif NW_OS_TYPE_LINUX
#       define NW_API __attribute__ ((visibility ("default")))
#   endif//NW_OS_TYPE_WIN32 || NW_OS_TYPE_LINUX
#endif//ENGINE_EXPORTS

#ifndef __VA_SELECT
#   define __VA_SELECT_CAT(x, y)        x ## y
#   define __VA_SELECT_IMPL(name, num)  __VA_SELECT_CAT(__ ## name ## _, num)
#   define __VA_SELECT_GET_COUNT(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, count, ...) count 
#   ifdef NW_OS_TYPE_WIN32
#       define __VA_SELECT_VA_SIZE(...) __VA_SELECT_GET_COUNT(__VA_ARGS__, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)
#   else
#       define __VA_SELECT_VA_SIZE(...) __VA_SELECT_GET_COUNT(__VA_ARGS__, 0, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#   endif//NW_OS_TYPE_WIN32
#   define __VA_SELECT(name, ...)       __VA_SELECT_IMPL(name, __VA_SELECT_VA_SIZE(__VA_ARGS__) ) (__VA_ARGS__)
#endif//__VA_SELECT

/**
 * Helper macro to concatenate variable count of tokens into one
 */
#ifndef NW_CONCAT
# define NW_CONCAT(...) __VA_SELECT(NW_CONCAT, __VA_ARGS__)

// Implementation:
# define __NW_CONCAT_15(__1, __2, __3, __4, __5, __6, __7, __8, __9, __10, __11, __12, __13, __14, __15)  __1 ## __2 ## __3 ## __4 ## __5 ## __6 ## __7 ## __8 ## __9 ## __10 ## __11 ## __12 ## __13 ## __14 ## __15
# define __NW_CONCAT_14(__1, __2, __3, __4, __5, __6, __7, __8, __9, __10, __11, __12, __13, __14)        __1 ## __2 ## __3 ## __4 ## __5 ## __6 ## __7 ## __8 ## __9 ## __10 ## __11 ## __12 ## __13 ## __14 
# define __NW_CONCAT_13(__1, __2, __3, __4, __5, __6, __7, __8, __9, __10, __11, __12, __13)              __1 ## __2 ## __3 ## __4 ## __5 ## __6 ## __7 ## __8 ## __9 ## __10 ## __11 ## __12 ## __13 
# define __NW_CONCAT_12(__1, __2, __3, __4, __5, __6, __7, __8, __9, __10, __11, __12)                    __1 ## __2 ## __3 ## __4 ## __5 ## __6 ## __7 ## __8 ## __9 ## __10 ## __11 ## __12 
# define __NW_CONCAT_11(__1, __2, __3, __4, __5, __6, __7, __8, __9, __10, __11)                          __1 ## __2 ## __3 ## __4 ## __5 ## __6 ## __7 ## __8 ## __9 ## __10 ## __11
# define __NW_CONCAT_10(__1, __2, __3, __4, __5, __6, __7, __8, __9, __10)                                __1 ## __2 ## __3 ## __4 ## __5 ## __6 ## __7 ## __8 ## __9 ## __10
# define __NW_CONCAT_9(__1, __2, __3, __4, __5, __6, __7, __8, __9)                                       __1 ## __2 ## __3 ## __4 ## __5 ## __6 ## __7 ## __8 ## __9
# define __NW_CONCAT_8(__1, __2, __3, __4, __5, __6, __7, __8)                                            __1 ## __2 ## __3 ## __4 ## __5 ## __6 ## __7 ## __8
# define __NW_CONCAT_7(__1, __2, __3, __4, __5, __6, __7)                                                 __1 ## __2 ## __3 ## __4 ## __5 ## __6 ## __7
# define __NW_CONCAT_6(__1, __2, __3, __4, __5, __6)                                                      __1 ## __2 ## __3 ## __4 ## __5 ## __6
# define __NW_CONCAT_5(__1, __2, __3, __4, __5)                                                           __1 ## __2 ## __3 ## __4 ## __5
# define __NW_CONCAT_4(__1, __2, __3, __4)                                                                __1 ## __2 ## __3 ## __4
# define __NW_CONCAT_3(__1, __2, __3)                                                                     __1 ## __2 ## __3
# define __NW_CONCAT_2(__1, __2)                                                                          __1 ## __2
# define __NW_CONCAT_1(__1)                                                                               __1
# define __NW_CONCAT_0( )
#endif//NW_CONCAT
