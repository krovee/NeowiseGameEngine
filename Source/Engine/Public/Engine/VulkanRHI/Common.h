#pragma once

#include <Engine/RHI/RHI.h>

#define VK_NO_PROTOTYPES
#include <Engine/VulkanRHI/API/vk_platform.h>
#include <Engine/VulkanRHI/API/vulkan_core.h>

namespace Neowise {
    /** 
    * 
    */
    struct RHIVKUtil {
        /** 
        * Returns true ONLY when result is equals vk::Result::eSuccess.
        */
        static bool isSuccess(const VkResult result);

        /** 
        * Returns true if result is semi-successful (e.g. VK_SUBOPTIMAL).
        */
        static bool isValid(const VkResult result);

        /** 
        * 
        */
        static void errorLog(const CString msg, const TUint line, const CStringView file, const CStringView fn);

        /** 
        * Returns reflected string of a reslult.
        */
        static CStringView toString(const VkResult result);

        /**
         * Gets an access to list of required instance extensions.
         */
        static const CVector<const char*>& getRequiredInstanceExtensions();
        
        /**
         * 
         */
        static const CVector<const char*>& getRequiredInstanceLayers();
    };

#ifndef RHIVKFN
#	define RHIVKFN2(fn, line, msg, ...)																								\
{																																	\
    const auto NW_CONCAT(result_on_line_, line) = fn; if (!RHIVKUtil::isSuccess(NW_CONCAT(result_on_line_, line))) {				\
        CString msgbuf;																												\
        CStringBuilder ms(msgbuf);																									\
        ms << RHIVKUtil::toString(NW_CONCAT(result_on_line_, line)) << msg << "" __VA_ARGS__ ;										\
        RHIVKUtil::errorLog(msgbuf, line, __FILE__, __FUNCTION__);																	\
    }																																\
}

#	define RHIVKFN(fn, msg, ...) RHIVKFN2(fn, __LINE__, msg, __VA_ARGS__)
#endif

#if NW_BUILD_TYPE == NW_BUILD_TYPE_SHIP
#	undef  RHIVKFN
#	define RHIVKFN(fn, msg, ...) { (void)fn; }
#endif

#ifndef NW_VK_LIBRARY_NAME
#	if NW_OS_TYPE_WIN32
#		define NW_VK_LIBRARY_NAME "vulkan-1.dll"
#	elif NW_OS_TYPE_LINUX
#		define NW_VK_LIBRARY_NAME "libvulkan.so.1"
#	endif
#endif

}
