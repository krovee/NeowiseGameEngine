#include <Engine/EngineGlobals.h>
#include <Engine/RenderThread.h>
#include <Engine/BaseWindow.h>
#include <Base/Thread.h>

namespace Neowise {
    CRenderThread* GRenderThread = nullptr;

    TBool RT_Initialize() {
        NW_PROFILE_FUNCTION();
        NW_OPT_ASSERT(!GRenderThread, "Failed to initialize already created GRenderThread object!");

        auto rtp = GAlloc->allocate(sizeof(CRenderThread));
        GRenderThread = reinterpret_cast<CRenderThread*>(rtp);
        
        construct_at<CRenderThread>(GRenderThread);

        return kTrue;
    }
    
    TBool RT_Shutdown() {

        if (GRenderThread) {
            destroy_at<CRenderThread>(GRenderThread);
        }

        return kTrue;
    }

    
    CRenderThread::CRenderThread() {
        
    }

    void CRenderThread::spawn()
    {
        (void)CThread::create(&CRenderThread::loop, GRenderThread, kTrue, kTrue);
    }

    void CRenderThread::initializeBasic(const CBaseWindow* pWindow) {
        NW_PROFILE_FUNCTION();

		this->window = pWindow;

        rhi = RHIMakeVulkanProvider();
        
        surface = rhi->createSurface(this->window);

        SRHIAdapterSpecification adapterSpecs   = {};
        adapterSpecs.required.meshShading       = kTrue;
        adapterSpecs.required.advancedIndexing  = kTrue;
        adapterSpecs.required.openAddressing    = kTrue;
        adapterSpecs.required.dynamicRendering  = kTrue;
        adapterSpecs.required.advancedSync      = kTrue;
        adapter = rhi->createAdapter(adapterSpecs, surface);

        SRHISwapchainSpecification swapchainSpecs = {
            window->getSize(),
            E_VERTICAL_SYNCHRONIZATION_FULL
        };
        swapchain = adapter->createSwapchain(swapchainSpecs, surface);

    }

    void CRenderThread::waitResourcesIdle() {

    }

    TBool CRenderThread::startFrameRecord() {

        return kTrue;
    }

    void CRenderThread::endFrameRecord() {

    }

    TBool CRenderThread::beginFrame() {

        return kTrue;
    }

    TBool CRenderThread::endFrame() {

        return kTrue;
    }

    /**
     * This loop() function works in a <separate> from main thread.
     */
    void CRenderThread::loop(void* params) {
        auto RT = reinterpret_cast<CRenderThread*>(params);

        while (!isExitRequested()) {
            if (!RT->beginFrame()) continue;

                // TODO(krovee): Execute 'commands'?

            RT->endFrame();
        }
    }
}
