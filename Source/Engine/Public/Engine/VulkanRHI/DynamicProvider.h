#include <Engine/VulkanRHI/Common.h>

namespace Neowise {
    
    class NW_API CRHIVulkanDynamicProvider : public CRHIDynamicProviderInterface {
    public:
        ~CRHIVulkanDynamicProvider() override;
        CRHIVulkanDynamicProvider();

        VkInstance getInstance() const;

        IRHIAdapter createAdapter() override;
    private:
        PFN_vkGetInstanceProcAddr                               getInstanceProcAddr = nullptr;
        PFN_vkCreateInstance                                    createInstance = nullptr;
        PFN_vkDestroyInstance                                   destroyInstance = nullptr;
        PFN_vkEnumerateInstanceExtensionProperties              enumerateInstanceExtensionProperties = nullptr;
        PFN_vkEnumerateInstanceLayerProperties                  enumerateInstanceLayerProperties = nullptr;
        PFN_vkEnumerateInstanceVersion                          enumerateInstanceVersion = nullptr;
        PFN_vkCreateDebugUtilsMessengerEXT                      createDebugUtilsMessengerEXT = nullptr;
        PFN_vkDestroyDebugUtilsMessengerEXT                     destroyDebugUtilsMessengerEXT = nullptr;
    private:
        VkInstance                  instance = VK_NULL_HANDLE;
        VkDebugUtilsMessengerEXT    _debugMessenger = VK_NULL_HANDLE;
    };

}
