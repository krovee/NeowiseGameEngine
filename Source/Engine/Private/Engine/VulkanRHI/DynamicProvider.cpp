#include "Engine/RHI/RHIAdapter.h"
#include <Engine/VulkanRHI/DynamicProvider.h>
#include <Engine/VulkanRHI/VulkanAdapter.h>
#include <Engine/VulkanRHI/VulkanSurface.h>

#include <Engine/EngineGlobals.h>
#include <Base/DynamicLibrary.h>
#include <Base/BuildVersion.h>

namespace Neowise {

    static VkBool32 sDebugMessageCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void*) 
    {
        CString message;
        CStringBuilder ss(message);

        switch (messageType) {
            case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT: {
                ss << "[VKGNRL]";
            } break;
            case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT: {
                ss << "[VKPERF]";
            } break;
            default: {
                ss << "[VKUNKW]";
            } break;
        }

        switch (messageSeverity) {
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: {
                ss << "[ERRR]";
            } break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: {
                ss << "[WARN]";
            } break;
            default: {
                ss << "[UNKW]";
            } break;
        }

        ss << ": " << pCallbackData->pMessage << "\n";
        GDiag << message;

        return VK_FALSE; // Applications must return kFalse here
    }

    IRHIDynamicProvider RHIMakeVulkanProvider() {
        return RHIMakeProvider<CRHIVulkanDynamicProvider>();
    }

    VkInstance CRHIVulkanDynamicProvider::getInstance() const {
        return instance;
    }

    IRHIAdapter CRHIVulkanDynamicProvider::createAdapter(const SRHIAdapterSpecification& specs) {
        return IRHIAdapter::make<CRHIVulkanAdapter>(specs, instance);
    }

    IRHIAdapter CRHIVulkanDynamicProvider::createAdapter(const SRHIAdapterSpecification& specs, const IRHISurface& requredSurface) {
        return IRHIAdapter::make<CRHIVulkanAdapter>(specs, instance, requredSurface.getImpl<CRHIVulkanSurface>());
    }

    IRHISurface CRHIVulkanDynamicProvider::createSurface(const CBaseWindow* window) {
        if (!_cachedSurface) {
            RHIVKUtil::createSurfaceFromWindow(window, this, _cachedSurface);
        }

        return _cachedSurface;
    }

    CRHIVulkanDynamicProvider::~CRHIVulkanDynamicProvider()
    {
        if (_debugMessenger && instance) {
            destroyDebugUtilsMessengerEXT(instance, _debugMessenger, nullptr);
        }

        if (instance) {
            destroyInstance(instance, nullptr);
        }
    }

    CRHIVulkanDynamicProvider::CRHIVulkanDynamicProvider() : CRHIDynamicProviderInterface(E_RHI_BACKEND_VULKAN) 
    {
        auto vkLib = CDynamicLibrary::load(NW_VK_LIBRARY_NAME);
        NW_ASSERT(vkLib, "Failed to load Vulkan dynamic provider (missing " NW_VK_LIBRARY_NAME ")");

        // acquire global level function
        getInstanceProcAddr = vkLib->getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
        
        // acquire instace level functions
        enumerateInstanceExtensionProperties = 
            reinterpret_cast<PFN_vkEnumerateInstanceExtensionProperties>(
                getInstanceProcAddr(instance, "vkEnumerateInstanceExtensionProperties")
            );
        enumerateInstanceLayerProperties = 
            reinterpret_cast<PFN_vkEnumerateInstanceLayerProperties>(
                getInstanceProcAddr(instance, "vkEnumerateInstanceLayerProperties")
            );
        enumerateInstanceVersion = 
            reinterpret_cast<PFN_vkEnumerateInstanceVersion>(
                getInstanceProcAddr(instance, "vkEnumerateInstanceVersion")
            );
        

        // get system present instance extensions
        TUint32 extensionsCount = 0;
        enumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);

        NW_ASSERT(extensionsCount, "Failed to create Vulkan RHI Provider since your PC doesn't support required set of extensions.");

        TVector<VkExtensionProperties> extensions(extensionsCount);
        enumerateInstanceExtensionProperties(nullptr, &extensionsCount, extensions.data());

        const auto& requiredExtensions = RHIVKUtil::getRequiredInstanceExtensions();
        TVector<const char*> presentInstanceExtensions = {};

        for (auto& ext : extensions) {
            const auto name = CStringView(ext.extensionName);
            for (auto& rext : requiredExtensions) {
                if (name == rext) {
                    presentInstanceExtensions.emplace(name.cstr());
                }
            }
        }

        GDiag << "Found instance extensions(" << presentInstanceExtensions.size() << "): ";
        for (auto& ext : presentInstanceExtensions) {
            GDiag << ext << " ";
        }
        GDiag << "\n";

        // acquire instance level functions
        createInstance = 
            reinterpret_cast<PFN_vkCreateInstance>(
                getInstanceProcAddr(nullptr, "vkCreateInstance")
            );

        const auto& requiredInstanceLayers = RHIVKUtil::getRequiredInstanceLayers();

        TUint32 layersCount = {};
        enumerateInstanceLayerProperties(&layersCount, nullptr);

        TVector<VkLayerProperties> availableLayers(layersCount);
        enumerateInstanceLayerProperties(&layersCount, availableLayers.data());

        for (auto& layer : availableLayers) {
            GDiag << "\n(" << layer.layerName << ") " << layer.description;
        }
        GDiag << "\n";

        TVector<const char*> presentInstanceLayers = {};

        for (auto& layer : availableLayers) {
            const auto name = CStringView(layer.layerName);
            for (auto& rlayer : requiredInstanceLayers) {
                if (name == rlayer) {
                    presentInstanceLayers.emplace(name.cstr());
                }
            }
        }

        VkApplicationInfo applicationInfo = {};
        applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        applicationInfo.apiVersion = VK_MAKE_VERSION(1, 3, 0);
        applicationInfo.pEngineName = "NeowiseEngine";
        applicationInfo.engineVersion = TUint32(buildVersion);
        applicationInfo.pApplicationName = GApplicationName.cstr();
        applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);

        VkInstanceCreateInfo instanceCI = {};
        instanceCI.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCI.pApplicationInfo = &applicationInfo;
        instanceCI.enabledExtensionCount = (TUint32) presentInstanceExtensions.size();
        instanceCI.ppEnabledExtensionNames = presentInstanceExtensions.data();
        instanceCI.ppEnabledLayerNames = presentInstanceLayers.data();
        instanceCI.enabledLayerCount = (TUint32) presentInstanceLayers.size();

        VkValidationFeaturesEXT validationFeatsEXT = { VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT };

        const VkValidationFeatureEnableEXT enabledValFeats[] = {
            VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT
        };
        
        validationFeatsEXT.pEnabledValidationFeatures = enabledValFeats;
        validationFeatsEXT.enabledValidationFeatureCount = arrayn(enabledValFeats);
        
        instanceCI.pNext = addressof(validationFeatsEXT);
        
        createInstance(&instanceCI, nullptr, &instance);

        destroyInstance = 
            reinterpret_cast<PFN_vkDestroyInstance>(
                getInstanceProcAddr(instance, "vkDestroyInstance")
            );
        createDebugUtilsMessengerEXT = 
            reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
                getInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT")
            );

        if (createDebugUtilsMessengerEXT) {

            destroyDebugUtilsMessengerEXT = 
                reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
                    getInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT")
                );
            
            
    #if NW_BUILD_TYPE_DEBUG
            VkDebugUtilsMessengerCreateInfoEXT dumCI = {};
            dumCI.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            dumCI.pfnUserCallback = sDebugMessageCallback;
            dumCI.messageSeverity = 
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
            dumCI.messageType = 
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            createDebugUtilsMessengerEXT(instance, &dumCI, nullptr, &_debugMessenger);
    #endif

        }
    }
 
}
