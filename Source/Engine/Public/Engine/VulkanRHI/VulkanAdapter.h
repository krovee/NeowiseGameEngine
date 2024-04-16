#pragma once

#include <Engine/VulkanRHI/Common.h>
#include <Engine/RHI/RHIAdapter.h>

namespace Neowise {
    class CRHIVulkanSurface;

    struct QueueFamilyInfo {
        TOptional<TUint32> graphicsIdx = nullopt;
        TOptional<TUint32> transferIdx = nullopt;
        TOptional<TUint32> presentIdx = nullopt;
        TOptional<TUint32> computeIdx = nullopt;

        inline TBool complete() const {
            return graphicsIdx && computeIdx && transferIdx && presentIdx;
        }
    };

    struct PhysicalDeviceSet {
        TDouble score = {};
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        CString name = { "<unknownGPU>" };
        QueueFamilyInfo queueFamilyInfo = {};
        VkPhysicalDeviceProperties2 properties2 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2, &meshShaderProps };
        VkPhysicalDeviceFeatures2 features2 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2, &features12 };
        VkPhysicalDeviceMeshShaderFeaturesEXT meshShaderExt = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_EXT };
        VkPhysicalDeviceMeshShaderPropertiesEXT meshShaderProps = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_EXT };
        VkPhysicalDeviceVulkan13Features features13 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES, &meshShaderExt };
        VkPhysicalDeviceVulkan12Features features12 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES, &features13 };
        VkPhysicalDeviceMemoryProperties memory = {};
    };

    class NW_API CRHIVulkanAdapter : public CRHIAdapterInterface {
    public:
        ~CRHIVulkanAdapter() override;
        CRHIVulkanAdapter(const SRHIAdapterSpecification& specs, VkInstance instance);
        CRHIVulkanAdapter(const SRHIAdapterSpecification& specs, VkInstance instance, const CRHIVulkanSurface* pSurface);

        CStringView getName() const override;
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

        TBool pickPhysicalDevice(const SRHIAdapterSpecification& specs, VkInstance instance);
        TBool pickPhysicalDeviceWithSurfaceSupport(const SRHIAdapterSpecification& specs, VkInstance instance, const CRHIVulkanSurface* pSurface);

        PhysicalDeviceSet getPhysicalDeviceSet(VkPhysicalDevice pd, const CRHIVulkanSurface* pSurface = nullptr) const;
        QueueFamilyInfo getPhysicalDeviceQueueFamilyInfo(VkPhysicalDevice pd, const CRHIVulkanSurface* pSurface = nullptr) const;
    private:
        CString gpuName = { "<unknownGPU>" };
        VkDevice device = VK_NULL_HANDLE;
        QueueFamilyInfo queueFamilyInfo = {};
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkPhysicalDeviceFeatures2 physicalDeviceFeatures = {};
        VkPhysicalDeviceProperties2 physicalDeviceProperties = {};
        VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = {};
        VkPhysicalDeviceMeshShaderFeaturesEXT meshShaderFeatures = {};
        VkPhysicalDeviceMeshShaderPropertiesEXT meshShaderProperties = {};
    };

}
