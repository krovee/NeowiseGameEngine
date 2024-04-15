#include "Engine/VulkanRHI/API/vulkan_core.h"
#include <Base/DynamicLibrary.h>
#include <Engine/VulkanRHI/VulkanAdapter.h>


namespace Neowise {
    CRHIVulkanAdapter::CRHIVulkanAdapter(VkInstance instance) : CRHIAdapterInterface(E_RHI_BACKEND_VULKAN) {
        
        auto vk = CDynamicLibrary::load(NW_VK_LIBRARY_NAME);
        PFN_vkGetInstanceProcAddr getInstanceProcAddr = 
            vk->getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
        
        enumeratePhysicalDevices = 
            reinterpret_cast<PFN_vkEnumeratePhysicalDevices>(
                getInstanceProcAddr(instance, "vkEnumeratePhysicalDevices")
            );
        
        if (!pickPhysicalDevice(instance)) {
            NW_ASSERT(false, "Failed to create vulkan adapter since there's no physical device to pick!");
        }
    }

    CRHIVulkanAdapter::~CRHIVulkanAdapter() {

    }

    bool CRHIVulkanAdapter::pickPhysicalDevice(VkInstance instance) {
        
        TUint32 physicalDevicesCount = 0;
        RHIVKFN(enumeratePhysicalDevices(instance, &physicalDevicesCount, nullptr), 
            "Failed to enumerate vulkan physical devices!");
        
        // 
        constexpr TUint kMaxPhysicalDevices = 8;
        CStaticVector<VkPhysicalDevice, 8> physicalDevices(physicalDevicesCount);

        return true;
    }
}
