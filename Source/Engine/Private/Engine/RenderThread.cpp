#include <Engine/EngineGlobals.h>
#include <Engine/RenderThread.h>
#include <Engine/BaseWindow.h>
#include <Base/Thread.h>

namespace Neowise {
    CRenderThread* GRenderThread = nullptr;

    bool RT_Initialize() {
        NW_PROFILE_FUNCTION();
        NW_OPT_ASSERT(!GRenderThread, "Failed to initialize already created GRenderThread object!");

        auto rtp = GAlloc->allocate(sizeof(CRenderThread));
        GRenderThread = reinterpret_cast<CRenderThread*>(rtp);
        
        construct_at<CRenderThread>(GRenderThread);

        return true;
    }
    
    bool RT_Shutdown() {
        return true;
    }
    
    
    CRenderThread::CRenderThread() {
        
    }

    void CRenderThread::spawn() {
        (void)CThread::create(&CRenderThread::loop, GRenderThread, true, true);
    }

    void CRenderThread::initializeBasic(const CBaseWindow& window) {
        NW_PROFILE_FUNCTION();

        this->window = &const_cast<CBaseWindow&>(window);

        // Call setup on every renderer module
    }

    void CRenderThread::waitResourcesIdle() {

    }

    bool CRenderThread::startFrameRecord() {

        return true;
    }

    void CRenderThread::endFrameRecord() {

    }

    bool CRenderThread::beginFrame() {

        return true;
    }

    bool CRenderThread::endFrame() {

        return true;
    }

    void CRenderThread::loop(void* params) {
        auto RT = reinterpret_cast<CRenderThread*>(params);


        while (!isExitRequested()) {
            if (!RT->beginFrame()) continue;

                // TODO(krovee): Execute 'commands'?

            RT->endFrame();
        }
    }
}
