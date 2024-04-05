#pragma once

#include <Engine/VulkanRHI/Common.h>
#include <Engine/RHI/RHIAdapter.h>

namespace Neowise {

    class NW_API CRHIVulkanAdapter : public CRHIAdapterInterface {
    public:
        ~CRHIVulkanAdapter() override;
        CRHIVulkanAdapter(VkInstance instance);

    private:
        PFN_vkEnumeratePhysicalDevices              enumeratePhysicalDevices = nullptr;
        PFN_vkGetPhysicalDeviceProperties           getPhysicalDeviceProperties = nullptr;
        PFN_vkGetPhysicalDeviceFeatures             getPhysicalDeviceFeatures = nullptr;
        PFN_vkEnumerateDeviceExtensionProperties    enumerateDeviceExtensionProperties = nullptr;
        PFN_vkEnumerateDeviceLayerProperties        enumerateDeviceLayerProperties = nullptr;
        PFN_vkCreateDevice                          createDevice = nullptr;
        PFN_vkDestroyDevice                         destroyDevice = nullptr;

        bool pickPhysicalDevice(VkInstance instance);
    private:
        VkDevice device = VK_NULL_HANDLE;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkPhysicalDeviceFeatures2 physicalDeviceFeatures = {};
        VkPhysicalDeviceMeshShaderFeaturesEXT meshShaderFeatures = {};
        VkPhysicalDeviceMeshShaderPropertiesEXT meshShaderProperties = {};
    };

}
