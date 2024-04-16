#pragma once

#include <Engine/VulkanRHI/Common.h>
#include <Engine/RHI/RHISwapchain.h>

namespace Neowise {
    class CRHIVulkanAdapter;

    class NW_API CRHIVulkanSwapchain : public CRHISwapchainInterface {
    public:
        ~CRHIVulkanSwapchain() override;

        CRHIVulkanSwapchain(const SRHISwapchainSpecification& specs, 
                            const CRHIVulkanAdapter* adapter,
                            const IRHISurface& surface,
                            const QueueFamilyInfo& queueInfo, 
                            const SwapchainSupportInfo& swapchainSupport, 
                            PFN_vkCreateSwapchainKHR createFn,
                            PFN_vkDestroySwapchainKHR destroyFn,
                            PFN_vkGetSwapchainImagesKHR getImagesFn,
                            PFN_vkCreateImageView createViewFn,
                            PFN_vkDestroyImageView destroyViewFn,
                            const IRHISwapchain& old);
        
        //
    private:
        static VkSurfaceFormatKHR   chooseFormat(const SwapchainSupportInfo& swapchainSupport);
        static VkPresentModeKHR     choosePresentMode(const SRHISwapchainSpecification& specs, const SwapchainSupportInfo& swapchainSupport);
        static VkExtent2D           chooseExtent(const SRHISwapchainSpecification& specs, const SwapchainSupportInfo& swapchainSupport);

        PFN_vkDestroySwapchainKHR   destroySwapchainKHR = nullptr;
        PFN_vkDestroyImageView      destroyImageView = nullptr;
    private:
        VkSwapchainKHR                  swapchain = VK_NULL_HANDLE;
        VkFormat                        imageFormat = VK_FORMAT_UNDEFINED;
        VkDevice                        device = VK_NULL_HANDLE;
        TStaticVector<VkImage, 3>       images = {};
        TStaticVector<VkImageView, 3>   views = {};
        VkExtent2D                      extent = {};
    };

}
