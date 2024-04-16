#include <Engine/VulkanRHI/VulkanSwapchain.h>
#include <Engine/VulkanRHI/VulkanSurface.h>
#include <Engine/VulkanRHI/VulkanAdapter.h>
#include <Base/DynamicLibrary.h>

namespace Neowise {

    CRHIVulkanSwapchain::~CRHIVulkanSwapchain() {
        if (swapchain && destroySwapchainKHR) {
            destroySwapchainKHR(device, swapchain, nullptr);
        }
        for (auto& view : views) {
            destroyImageView(device, view, nullptr);
        }
    }

    CRHIVulkanSwapchain::CRHIVulkanSwapchain(
                                    const SRHISwapchainSpecification &specs, 
                                    const CRHIVulkanAdapter* adapter,
                                    const IRHISurface& surface,
                                    const QueueFamilyInfo& queueInfo, 
                                    const SwapchainSupportInfo &swapchainSupport, 
                                    PFN_vkCreateSwapchainKHR createFn,
                                    PFN_vkDestroySwapchainKHR destroyFn,
                                    PFN_vkGetSwapchainImagesKHR getImagesFn,
                                    PFN_vkCreateImageView createViewFn,
                                    PFN_vkDestroyImageView destroyViewFn,
                                    const IRHISwapchain& old) : CRHISwapchainInterface(E_RHI_BACKEND_VULKAN)
    {
        const auto vkSurface = surface.getImpl<CRHIVulkanSurface>();
        device = adapter->getDevice();

        destroySwapchainKHR = destroyFn;
        destroyImageView = destroyViewFn;

        extent = chooseExtent(specs, swapchainSupport);
        const auto surfaceFormat = chooseFormat(swapchainSupport);
        const auto presentMode = choosePresentMode(specs, swapchainSupport);

        TUint32 imageCount = swapchainSupport.capabilities.minImageCount + 1;
        if (swapchainSupport.capabilities.maxImageCount > 0 && imageCount > swapchainSupport.capabilities.maxImageCount) {
            imageCount = swapchainSupport.capabilities.maxImageCount;
        }

        const TUint32 queueFamilyIndices[] = {
            queueInfo.graphicsIdx.unwrap(),
            queueInfo.transferIdx.unwrap(),
            queueInfo.presentIdx.unwrap(),
            queueInfo.computeIdx.unwrap()
        };

        imageFormat = surfaceFormat.format;

        VkSwapchainCreateInfoKHR swapchainCI = { VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR };
        swapchainCI.surface = vkSurface->getSurface();
        swapchainCI.minImageCount = imageCount;
        swapchainCI.imageFormat = imageFormat;
        swapchainCI.imageColorSpace = surfaceFormat.colorSpace;
        swapchainCI.imageExtent = extent;
        swapchainCI.imageArrayLayers = 1;
        swapchainCI.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
        swapchainCI.pQueueFamilyIndices = queueFamilyIndices;
        swapchainCI.queueFamilyIndexCount = arrayn(queueFamilyIndices);

        if (queueInfo.graphicsIdx != queueInfo.presentIdx) {
            swapchainCI.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        }
        else {
            swapchainCI.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        }

        swapchainCI.preTransform = swapchainSupport.capabilities.currentTransform;
        swapchainCI.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapchainCI.presentMode = presentMode;
        swapchainCI.clipped = VK_TRUE;
        if (old) {
            swapchainCI.oldSwapchain = old.getImpl<CRHIVulkanSwapchain>()->swapchain;
        }

        RHIVKFN(createFn(device, &swapchainCI, nullptr, &swapchain), "Failed to create vulkan swapchain object!");

        images.resize(imageCount);
        views.resize(imageCount);
        RHIVKFN(getImagesFn(device, swapchain, &imageCount, images.data()), "Failed to get vulkan swapchain images!");

        for (TUint i = 0; i < imageCount; ++i) {
            VkImageViewCreateInfo viewCI = { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
            viewCI.image = images[i];
            viewCI.viewType = VK_IMAGE_VIEW_TYPE_2D;
            viewCI.format = imageFormat;
            viewCI.components = {
                VK_COMPONENT_SWIZZLE_IDENTITY,
                VK_COMPONENT_SWIZZLE_IDENTITY,
                VK_COMPONENT_SWIZZLE_IDENTITY,
                VK_COMPONENT_SWIZZLE_IDENTITY
            };
            viewCI.subresourceRange = {
                VK_IMAGE_ASPECT_COLOR_BIT,
                0, 1,
                0, 1
            };

            RHIVKFN(createViewFn(device, &viewCI, nullptr, &views[i]), "Failed to create image view!");
        }

    }

    VkSurfaceFormatKHR CRHIVulkanSwapchain::chooseFormat(const SwapchainSupportInfo &swapchainSupport) {
        for (const auto& availableFormat : swapchainSupport.formats) {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM) {
                return availableFormat;
            }

            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                return availableFormat;
            }
        }

        return swapchainSupport.formats[0];
    }

    VkPresentModeKHR CRHIVulkanSwapchain::choosePresentMode(const SRHISwapchainSpecification& specs, const SwapchainSupportInfo &swapchainSupport) {
        VkPresentModeKHR requestedMode = {};

        switch (specs.vsync) {
            case E_VERTICAL_SYNCHRONIZATION_NONE: { requestedMode = VK_PRESENT_MODE_IMMEDIATE_KHR; } break;
            case E_VERTICAL_SYNCHRONIZATION_SEMI: { requestedMode = VK_PRESENT_MODE_FIFO_RELAXED_KHR; } break;
            case E_VERTICAL_SYNCHRONIZATION_FULL: { requestedMode = VK_PRESENT_MODE_FIFO_KHR; } break;
        }

        // Check if requirested present mode is even available.
        for (const auto& availablePresentMode : swapchainSupport.presentModes) {
            if (availablePresentMode == requestedMode) {
                return requestedMode;
            }
        }

        // If not available, use immediate present mode. =(
        return VK_PRESENT_MODE_IMMEDIATE_KHR;
    }

    VkExtent2D CRHIVulkanSwapchain::chooseExtent(const SRHISwapchainSpecification& specs, const SwapchainSupportInfo &swapchainSupport) {
        if (swapchainSupport.capabilities.currentExtent.width != Const::kMaxU32) {
            return swapchainSupport.capabilities.currentExtent;
        } 
        else {
            // TODO: request current window extent (actual one)

            VkExtent2D actualExtent = {
                static_cast<uint32_t>(specs.extent.x),
                static_cast<uint32_t>(specs.extent.y)
            };

            actualExtent = {
                NW_CLAMP(actualExtent.width, swapchainSupport.capabilities.minImageExtent.width, swapchainSupport.capabilities.maxImageExtent.width),
                NW_CLAMP(actualExtent.height, swapchainSupport.capabilities.minImageExtent.height, swapchainSupport.capabilities.maxImageExtent.height)
            };

            return actualExtent;
        }
    }
}
