#include <Engine/EngineGlobals.h>
#include <Engine/VulkanRHI/DynamicProvider.h>
#include <Base/DynamicLibrary.h>

namespace Neowise {

	IRHIDynamicProvider RHIMakeVulkanProvider() {
        return RHIMakeProvider<CRHIVulkanDynamicProvider>();
    }


    CRHIVulkanDynamicProvider::~CRHIVulkanDynamicProvider() {
        
    }

    CRHIVulkanDynamicProvider::CRHIVulkanDynamicProvider() 
        : CRHIDynamicProviderInterface(E_RHI_PROVIDER_CLASS_VULKAN) 
    {

        //volkInitialize();

        auto vkLib = CDynamicLibrary::load(NW_VK_LIBRARY_NAME);
        NW_ASSERT(vkLib, "Failed to load Vulkan dynamic provider (missing " NW_VK_LIBRARY_NAME ")");

        getInstanceProcAddr = vkLib->getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
        createInstance = (PFN_vkCreateInstance)getInstanceProcAddr(nullptr, "vkCreateInstance");
        enumerateInstanceExtensionProperties = 
            vkLib->getProcAddress<PFN_vkEnumerateInstanceExtensionProperties>("vkEnumerateInstanceExtensionProperties");

        VkApplicationInfo applicationInfo = {};
        applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        applicationInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);
        applicationInfo.pEngineName = "NeowiseEngine";
        // applicationInfo.engineVersion = uint32(buildVersion);
        applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        applicationInfo.pApplicationName = GApplicationName.cstr();
        applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);

        VkInstanceCreateInfo instanceCI = {};
        instanceCI.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCI.pApplicationInfo = &applicationInfo;
        instanceCI.enabledExtensionCount = 0;
        instanceCI.enabledLayerCount = 0;

        uint32 count = 0;
        enumerateInstanceExtensionProperties(nullptr, &count, nullptr);
        
        createInstance(&instanceCI, nullptr, &_instance);

    }
 
}
