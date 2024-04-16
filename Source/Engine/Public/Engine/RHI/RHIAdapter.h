#pragma once

#include <Engine/RHI/Common.h>
#include <Engine/RHI/RHISwapchain.h>

namespace Neowise {

    struct SRHIAdapterSpecification {
        struct {
            /**
             * Mesh and Task shaders follow the compute programming model and use threads 
             * cooperatively to generate meshes within a workgroup. The vertex and index data 
             * for these meshes are written similarly to shared memory in compute shaders. 
             * Mesh shader output is directly consumed by the rasterizer, as opposed to the 
             * previous approach of using a compute dispatch followed by an indirect draw. 
             * Therefore mesh shading applications can avoid preallocation of output buffers.
             */
            TBool meshShading = kTrue;
            
            /**
             * Internal flag that is REQUIRED to be set TRUE.
             */
            TBool dynamicRendering = kTrue;
            
            /**
             * Internal flag that increases performance and memory efficiency for syncronization.
             */
            TBool advancedSync = kTrue;
            
            /**
             * Bindless textures feature enabler.
             */
            TBool advancedIndexing = kTrue;
            
            /**
             * Bindless access to GPU memory without need to bind our host pointers to local memory.
             */
            TBool openAddressing = kTrue;
        } required = {};
    };

    class NW_API CRHIAdapterInterface : public RHIBase<CRHIAdapterInterface> {
    public:
        virtual ~CRHIAdapterInterface() = default;

        virtual CStringView getName() const = 0;
        virtual IRHISwapchain createSwapchain(const SRHISwapchainSpecification& specs, const IRHISurface& surface, const IRHISwapchain& oldSwapchain = nullptr) = 0;

        NW_RHI_CLASS_DECLARATION(CRHIAdapterInterface)
    };

}
