#include "Engine/VulkanRHI/API/vulkan_core.h"
#include <Engine/VulkanRHI/VulkanAdapter.h>
#include <Engine/VulkanRHI/VulkanSurface.h>
#include <Base/DynamicLibrary.h>


namespace Neowise {
    CRHIVulkanAdapter::CRHIVulkanAdapter(const SRHIAdapterSpecification& specs, VkInstance instance) : CRHIAdapterInterface(E_RHI_BACKEND_VULKAN) {
        
        {
            auto vk = CDynamicLibrary::load(NW_VK_LIBRARY_NAME);
            PFN_vkGetInstanceProcAddr getInstanceProcAddr = 
                vk->getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
            
            enumeratePhysicalDevices = 
                reinterpret_cast<PFN_vkEnumeratePhysicalDevices>(
                    getInstanceProcAddr(instance, "vkEnumeratePhysicalDevices")
                );
            getPhysicalDeviceProperties2 = 
                reinterpret_cast<PFN_vkGetPhysicalDeviceProperties2>(
                    getInstanceProcAddr(instance, "vkGetPhysicalDeviceProperties2")
                );
            getPhysicalDeviceFeatures2 = 
                reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures2>(
                    getInstanceProcAddr(instance, "vkGetPhysicalDeviceFeatures2")
                );
            enumerateDeviceExtensionProperties = 
                reinterpret_cast<PFN_vkEnumerateDeviceExtensionProperties>(
                    getInstanceProcAddr(instance, "vkEnumerateDeviceExtensionProperties")
                );
            enumerateDeviceLayerProperties = 
                reinterpret_cast<PFN_vkEnumerateDeviceLayerProperties>(
                    getInstanceProcAddr(instance, "vkEnumerateDeviceLayerProperties")
                );
            getPhysicalDeviceMemoryProperties = 
                reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties>(
                    getInstanceProcAddr(instance, "vkGetPhysicalDeviceMemoryProperties")
                );
            getPhysicalDeviceQueueFamilyProperties = 
                reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties>(
                    getInstanceProcAddr(instance, "vkGetPhysicalDeviceQueueFamilyProperties")
                );
            createDevice = 
                reinterpret_cast<PFN_vkCreateDevice>(
                    getInstanceProcAddr(instance, "vkCreateDevice")
                );
            destroyDevice = 
                reinterpret_cast<PFN_vkDestroyDevice>(
                    getInstanceProcAddr(instance, "vkDestroyDevice")
                );
        }
        
        if (!pickPhysicalDevice(specs, instance)) {
            NW_ASSERT(kFalse, "Failed to create vulkan adapter since there's no physical device to pick!");
        }
    }

    Neowise::CRHIVulkanAdapter::CRHIVulkanAdapter(const SRHIAdapterSpecification& specs, VkInstance instance, const CRHIVulkanSurface *pSurface): CRHIAdapterInterface(E_RHI_BACKEND_VULKAN) {

        {
            auto vk = CDynamicLibrary::load(NW_VK_LIBRARY_NAME);
            PFN_vkGetInstanceProcAddr getInstanceProcAddr = 
                vk->getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
            
            enumeratePhysicalDevices = 
                reinterpret_cast<PFN_vkEnumeratePhysicalDevices>(
                    getInstanceProcAddr(instance, "vkEnumeratePhysicalDevices")
                );
            getPhysicalDeviceProperties2 = 
                reinterpret_cast<PFN_vkGetPhysicalDeviceProperties2>(
                    getInstanceProcAddr(instance, "vkGetPhysicalDeviceProperties2")
                );
            getPhysicalDeviceFeatures2 = 
                reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures2>(
                    getInstanceProcAddr(instance, "vkGetPhysicalDeviceFeatures2")
                );
            enumerateDeviceExtensionProperties = 
                reinterpret_cast<PFN_vkEnumerateDeviceExtensionProperties>(
                    getInstanceProcAddr(instance, "vkEnumerateDeviceExtensionProperties")
                );
            enumerateDeviceLayerProperties = 
                reinterpret_cast<PFN_vkEnumerateDeviceLayerProperties>(
                    getInstanceProcAddr(instance, "vkEnumerateDeviceLayerProperties")
                );
            getPhysicalDeviceMemoryProperties = 
                reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties>(
                    getInstanceProcAddr(instance, "vkGetPhysicalDeviceMemoryProperties")
                );
            getPhysicalDeviceQueueFamilyProperties = 
                reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties>(
                    getInstanceProcAddr(instance, "vkGetPhysicalDeviceQueueFamilyProperties")
                );
            createDevice = 
                reinterpret_cast<PFN_vkCreateDevice>(
                    getInstanceProcAddr(instance, "vkCreateDevice")
                );
            destroyDevice = 
                reinterpret_cast<PFN_vkDestroyDevice>(
                    getInstanceProcAddr(instance, "vkDestroyDevice")
                );
        }

        if (!pickPhysicalDeviceWithSurfaceSupport(specs, instance, pSurface)) {
            NW_ASSERT(kFalse, "Failed to create vulkan adapter since there's no physical device to pick!");
        }
    }

    CStringView Neowise::CRHIVulkanAdapter::getName() const {
        return gpuName;
    }

    CRHIVulkanAdapter::~CRHIVulkanAdapter() {

    }

    TBool CRHIVulkanAdapter::pickPhysicalDevice(const SRHIAdapterSpecification& specs, VkInstance instance) {
        
        TUint32 physicalDevicesCount = 0;
        RHIVKFN(enumeratePhysicalDevices(instance, &physicalDevicesCount, nullptr), 
            "Failed to enumerate vulkan physical devices!");
        
        // Hope your machine don't have 8 GPUs, because if it has so you're in trouble..
        constexpr TUint kMaxPhysicalDevices = 8;
        TStaticVector<VkPhysicalDevice, 8> physicalDevices(physicalDevicesCount);
        enumeratePhysicalDevices(instance, &physicalDevicesCount, physicalDevices.data());

        TStaticVector<PhysicalDeviceSet, 8> sets = {};

        for (const auto pd : physicalDevices) {
            sets.emplace(getPhysicalDeviceSet(pd));
        }

        quickSort(sets.data(), sets.size(), 0, 
        [](const PhysicalDeviceSet& a, const PhysicalDeviceSet& b) -> TBool {
            return a.score < b.score;
        });

        auto bestSet = sets.front();
        bool found = false;
        TUint idx = 0;
        while (idx <= sets.size()) {
            if (found) 
                break;

            if (specs.required.meshShading && !(bestSet.meshShaderExt.meshShader)) {
                bestSet = sets[++idx];
                continue;
            }

            if (specs.required.dynamicRendering && !(bestSet.features13.dynamicRendering)) {
                bestSet = sets[++idx];
                continue;
            }

            if (specs.required.advancedSync && !(bestSet.features13.synchronization2)) {
                bestSet = sets[++idx];
                continue;
            }

            if (specs.required.advancedIndexing && !(bestSet.features12.descriptorIndexing)) {
                bestSet = sets[++idx];
                continue;
            }

            if (specs.required.openAddressing && !(bestSet.features12.bufferDeviceAddress)) {
                bestSet = sets[++idx];
                continue;
            }

            // If we got here and satisfied all checks - we found the best set! ^^
            found = true;
        }

        if (!found) {
            GDiag << "Failed to choose suitable GPU for rendering!\n";
            return kFalse;
        }

        physicalDevice = bestSet.physicalDevice;
        physicalDeviceFeatures = bestSet.features2;
        meshShaderFeatures = bestSet.meshShaderExt;
        meshShaderProperties = bestSet.meshShaderProps;
        physicalDeviceMemoryProperties = bestSet.memory;
        physicalDeviceProperties = bestSet.properties2;
        gpuName = bestSet.name;

        VkDeviceCreateInfo deviceCI = { VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO };
        

        return kTrue;
    }

    TBool CRHIVulkanAdapter::pickPhysicalDeviceWithSurfaceSupport(
                                                        const SRHIAdapterSpecification& specs, 
                                                        VkInstance instance, 
                                                        const CRHIVulkanSurface *pSurface) 
    {
        TUint32 physicalDevicesCount = 0;
        RHIVKFN(enumeratePhysicalDevices(instance, &physicalDevicesCount, nullptr), 
            "Failed to enumerate vulkan physical devices!");
        
        // Hope your machine don't have 8 GPUs, because if it has so you're in trouble..
        constexpr TUint kMaxPhysicalDevices = 8;
        TStaticVector<VkPhysicalDevice, 8> physicalDevices(physicalDevicesCount);
        enumeratePhysicalDevices(instance, &physicalDevicesCount, physicalDevices.data());

        TStaticVector<PhysicalDeviceSet, 8> sets = {};

        for (const auto pd : physicalDevices) {
            sets.emplace(getPhysicalDeviceSet(pd, pSurface));
        }

        quickSort(sets.data(), sets.size(), 0, 
        [](const PhysicalDeviceSet& a, const PhysicalDeviceSet& b) -> TBool {
            return a.score < b.score;
        });

        auto bestSet = sets.front();
        bool found = false;
        TUint idx = 0;
        while (idx <= sets.size()) {
            if (found) 
                break;

            if (specs.required.meshShading && !(bestSet.meshShaderExt.meshShader)) {
                bestSet = sets[++idx];
                continue;
            }

            if (specs.required.dynamicRendering && !(bestSet.features13.dynamicRendering)) {
                bestSet = sets[++idx];
                continue;
            }

            if (specs.required.advancedSync && !(bestSet.features13.synchronization2)) {
                bestSet = sets[++idx];
                continue;
            }

            if (specs.required.advancedIndexing && !(bestSet.features12.descriptorIndexing)) {
                bestSet = sets[++idx];
                continue;
            }

            if (specs.required.openAddressing && !(bestSet.features12.bufferDeviceAddress)) {
                bestSet = sets[++idx];
                continue;
            }

            if (!bestSet.queueFamilyInfo.complete()) {
                bestSet = sets[++idx];
                continue;
            }

            // If we got here and satisfied all checks - we found the best set! ^^
            found = true;
        }

        if (!found) {
            GDiag << "Failed to choose suitable GPU for rendering!\n";
            return kFalse;
        }

        physicalDevice = bestSet.physicalDevice;
        physicalDeviceFeatures = bestSet.features2;
        meshShaderFeatures = bestSet.meshShaderExt;
        meshShaderProperties = bestSet.meshShaderProps;
        physicalDeviceMemoryProperties = bestSet.memory;
        physicalDeviceProperties = bestSet.properties2;
        queueFamilyInfo = bestSet.queueFamilyInfo;
        gpuName = bestSet.name;

        VkDeviceCreateInfo deviceCI = { VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO };
        
        TStaticVector<VkDeviceQueueCreateInfo, 4> queuesCI = {4, VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO};
        

        return kTrue;
    }

    PhysicalDeviceSet CRHIVulkanAdapter::getPhysicalDeviceSet(VkPhysicalDevice pd, const CRHIVulkanSurface* pSurface) const {
        PhysicalDeviceSet set = { 1, pd };
        
        getPhysicalDeviceProperties2(pd, &set.properties2);
        getPhysicalDeviceFeatures2(pd, &set.features2);
        getPhysicalDeviceMemoryProperties(pd, &set.memory);

        {   // score API versions + etc.
            auto vals = (TUint32*)&set.properties2.properties;
            constexpr auto valsCount = 4;
            for (TUint i = 0; i < valsCount; ++i) {
                // Append to score: apiVersion, driverVersion, vendorID, deviceID
                set.score += vals[i];
            }
        }

        set.name = CString(set.properties2.properties.deviceName, arrayn(set.properties2.properties.deviceName));

        { // score limits
            const auto limits = set.properties2.properties.limits;
            for (TUint i = 0; i < 63; ++i) {
                set.score += i[(TUint*)&limits];
            }
        }

        { // score memory
            for (TUint i = 0; i < set.memory.memoryHeapCount; ++i) {
                const auto heap = set.memory.memoryHeaps[i];
                set.score += heap.size;
            }
        }

        { // score features
            for (auto val = (TUint32*)&set.features2.features; 
                val != (TUint32*)&set.meshShaderExt.sType;
                val++) 
            {
                set.score += val[0];
            }

            for (auto val = &set.features13.robustImageAccess;
                val != &set.features13.maintenance4; val++) 
            {
                set.score += val[0];
            }

            for (auto val = &set.features12.samplerMirrorClampToEdge;
                val != &set.features12.subgroupBroadcastDynamicId; val++) 
            {
                set.score += val[0];
            }

            set.score += set.meshShaderExt.meshShader;
        }

        set.queueFamilyInfo = getPhysicalDeviceQueueFamilyInfo(pd, pSurface);

        return set;
    }

    QueueFamilyInfo Neowise::CRHIVulkanAdapter::getPhysicalDeviceQueueFamilyInfo(VkPhysicalDevice pd, const CRHIVulkanSurface* pSurface) const {
        QueueFamilyInfo info = {};

        TUint32 queueFamilyCount = 0;
        getPhysicalDeviceQueueFamilyProperties(pd, &queueFamilyCount, nullptr);
        TStaticVector<VkQueueFamilyProperties, 16> queueFamilies(queueFamilyCount);
        getPhysicalDeviceQueueFamilyProperties(pd, &queueFamilyCount, queueFamilies.data());

        TUint32 queueIdx = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (info.complete())
                break;

            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                info.graphicsIdx = queueIdx;
            }

            if (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT) {
                info.transferIdx = queueIdx;
            }

            if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT) {
                info.computeIdx = queueIdx;
            }

            VkBool32 presentSupported = VK_FALSE;
            if (pSurface) {
                pSurface->getPhysicalDeviceSupport(pd, queueIdx, &presentSupported);
            }
            if (presentSupported) {
                info.presentIdx = queueIdx;
            }

            ++queueIdx;
        }

        return info;
    }
}
