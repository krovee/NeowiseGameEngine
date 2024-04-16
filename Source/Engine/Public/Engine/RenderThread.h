#pragma once

#include <Base/Common.h>
#include <Engine/RHI/RHI.h>
#include <Engine/RHI/RHIAdapter.h>
#include <Engine/RHI/RHISurface.h>
#include <Engine/RHI/RHISwapchain.h>

// Include actual renderer???

namespace Neowise {
    class CBaseWindow;

    /** 
    * Thread-safe (HEAP BASED) interface to render thread, to control it's state.
    */
    class NW_API CRenderThread {
    public:
        CRenderThread();

        static void spawn();

        void initializeBasic(const CBaseWindow& window);
        void waitResourcesIdle();

        TBool startFrameRecord();
        void endFrameRecord();

    private:
        TBool beginFrame();
        TBool endFrame();

    private:
        static void loop(void* params);

        CBaseWindow*            window = nullptr;

        IRHIDynamicProvider     rhi = nullptr;
        IRHISurface             surface = nullptr;
        IRHIAdapter             adapter = nullptr;
        IRHISwapchain           swapchain = nullptr;
	};

    NW_API TBool RT_Initialize();
    NW_API TBool RT_Shutdown();
}
