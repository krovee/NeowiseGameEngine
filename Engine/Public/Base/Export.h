#pragma once

/* 
* NW_API macro defined to export functions, objects from
* engine code over to application code base and being able
* to link against it.
*/

#if defined(_DLL)
#	define NW_API __declspec(dllexport)
#else
#	define NW_API __declspec(dllimport)
#endif
