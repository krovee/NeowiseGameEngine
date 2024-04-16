#pragma once

#include <Engine/VulkanRHI/Common.h>
#include <Engine/RHI/RHIAdapter.h>

namespace Neowise {
    class CRHIVulkanSurface;

    class NW_API CRHIVulkanAdapter : public CRHIAdapterInterface {
    public:
        ~CRHIVulkanAdapter() override;
        CRHIVulkanAdapter(const SRHIAdapterSpecification& specs, VkInstance instance);
        CRHIVulkanAdapter(const SRHIAdapterSpecification& specs, VkInstance instance, const CRHIVulkanSurface* pSurface);

        CStringView getName() const override;
        IRHISwapchain createSwapchain(const SRHISwapchainSpecification& specs, const IRHISurface& surface, const IRHISwapchain& oldSwapchain) override;

        VkDevice getDevice() const;
        VkPhysicalDevice getGPU() const;
    private:
        PFN_vkEnumeratePhysicalDevices              enumeratePhysicalDevices = nullptr;
        PFN_vkGetPhysicalDeviceProperties2          getPhysicalDeviceProperties2 = nullptr;
        PFN_vkGetPhysicalDeviceFeatures2            getPhysicalDeviceFeatures2 = nullptr;
        PFN_vkEnumerateDeviceExtensionProperties    enumerateDeviceExtensionProperties = nullptr;
        PFN_vkEnumerateDeviceLayerProperties        enumerateDeviceLayerProperties = nullptr;
        PFN_vkGetPhysicalDeviceQueueFamilyProperties getPhysicalDeviceQueueFamilyProperties = nullptr;
        PFN_vkGetPhysicalDeviceMemoryProperties     getPhysicalDeviceMemoryProperties = nullptr;
        PFN_vkCreateDevice                          createDevice = nullptr;
        PFN_vkDestroyDevice                         destroyDevice = nullptr;
        PFN_vkCreateSwapchainKHR                    createSwapchainKHR = nullptr;
        PFN_vkDestroySwapchainKHR                   destroySwapchainKHR = nullptr;
        PFN_vkGetSwapchainImagesKHR                 getSwapchainImagesKHR = nullptr;
        PFN_vkCreateImageView                       createImageView = nullptr;
        PFN_vkDestroyImageView                      destroyImageView = nullptr;

        TBool pickPhysicalDevice(const SRHIAdapterSpecification& specs, VkInstance instance);
        TBool pickPhysicalDeviceWithSurfaceSupport(const SRHIAdapterSpecification& specs, VkInstance instance, const CRHIVulkanSurface* pSurface);

        PhysicalDeviceSet getPhysicalDeviceSet(VkPhysicalDevice pd, const CRHIVulkanSurface* pSurface = nullptr) const;
        QueueFamilyInfo getPhysicalDeviceQueueFamilyInfo(VkPhysicalDevice pd, const CRHIVulkanSurface* pSurface = nullptr) const;
        SwapchainSupportInfo getPhysicalDeviceSwapchainSupportInfo(VkPhysicalDevice pd, const CRHIVulkanSurface* pSurface) const;
    private:
        CString gpuName = { "<unknownGPU>" };
        VkDevice device = VK_NULL_HANDLE;
        QueueFamilyInfo queueFamilyInfo = {};
        SwapchainSupportInfo swapchainSupportInfo = {};
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkPhysicalDeviceFeatures2 physicalDeviceFeatures = {};
        VkPhysicalDeviceProperties2 physicalDeviceProperties = {};
        VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = {};
        VkPhysicalDeviceMeshShaderFeaturesEXT meshShaderFeatures = {};
        VkPhysicalDeviceMeshShaderPropertiesEXT meshShaderProperties = {};
    };

}
