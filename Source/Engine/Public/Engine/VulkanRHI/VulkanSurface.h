#pragma once

#include <Engine/VulkanRHI/Common.h>
#include <Engine/RHI/RHISurface.h>
#include <Engine/RHI/RHI.h>

namespace Neowise {

    class NW_API CRHIVulkanSurface : public CRHISurfaceInterface {
    public:
        ~CRHIVulkanSurface() override;
        CRHIVulkanSurface() = default;
        
        CRHIVulkanSurface(VkInstance _instance, VkSurfaceKHR _surface);

        VkSurfaceKHR getSurface() const;

        TBool getPhysicalDeviceSupport(VkPhysicalDevice pd, TUint32 queueIdx, VkBool32* pSupported) const;
        TBool getPhysicalDeviceCapabilities(VkPhysicalDevice pd, VkSurfaceCapabilitiesKHR* pSurfaceCaps) const;
        TBool getPhysicalDeviceFormats(VkPhysicalDevice pd, TUint32* pCount, VkSurfaceFormatKHR* pFormats) const;
        TBool getPhysicalDevicePresentModes(VkPhysicalDevice pd, TUint32* pCount, VkPresentModeKHR* pModes) const;
    private:
        VkInstance      instance = VK_NULL_HANDLE;
        VkSurfaceKHR    surface = VK_NULL_HANDLE;

        PFN_vkDestroySurfaceKHR                         destroySurfaceKHR = nullptr;
        PFN_vkGetPhysicalDeviceSurfaceSupportKHR        getPhysicalDeviceSurfaceSupportKHR = nullptr;
        PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR   getPhysicalDeviceSurfaceCapabilitiesKHR = nullptr;
        PFN_vkGetPhysicalDeviceSurfaceFormatsKHR        getPhysicalDeviceSurfaceFormatsKHR = nullptr;
        PFN_vkGetPhysicalDeviceSurfacePresentModesKHR   getPhysicalDeviceSurfacePresentModesKHR = nullptr;
    };

}
