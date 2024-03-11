#pragma once

#include <Engine/RHI/RHI.h>

#include <vulkan/vulkan.hpp>

namespace Neowise {
	/** 
	* 
	*/
	struct RHIVKUtil {
		/** 
		* Returns true ONLY when result is equals vk::Result::eSuccess.
		*/
		static bool isSuccess(const vk::Result result);

		/** 
		* Returns true if result is semi-successful (e.g. VK_SUBOPTIMAL).
		*/
		static bool isValid(const vk::Result result);

		/** 
		* 
		*/
		static void errorLog(const CString msg, const uint line, const CStringView file, const CStringView fn);

		/** 
		* Returns reflected string of a reslult.
		*/
		static CStringView toString(const vk::Result result);
	};

#ifndef RHIVKFN
#	define RHIVKFN2(fn, line, msg, ...)																								\
{																																	\
	const auto NW_CONCAT(result_on_line_, line) = fn; if (!RHIVKUtil::isSuccess(NW_CONCAT(result_on_line_, line))) {				\
		CString msgbuf;																												\
		CStringBuilder ms(msgbuf);																										\
		ms << RHIVKUtil::toString(NW_CONCAT(result_on_line_, line)) << msg << "" __VA_ARGS__;																									\
		RHIVKUtil::errorLog(msgbuf, line, __FILE__, __FUNCTION__);																		\
	}																																\
}

#	define RHIVKFN(fn, msg, ...) RHIVKFN2(fn, __LINE__, msg, __VA_ARGS__)
#endif

#if NW_BUILD_TYPE == NW_BUILD_TYPE_SHIP
#	undef  RHIVKFN
#	define RHIVKFN(fn, msg, ...) { (void)fn; }
#endif

}
