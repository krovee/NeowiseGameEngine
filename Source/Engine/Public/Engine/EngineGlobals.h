#pragma once

#include <Base/Common.h>

namespace Neowise {
    class CEventBus;
    class CEngineLoop;
    class CApplication;
    class CRenderThread;

    // Value for a check for engine to request an exit.
    extern TBool GIsExitRequested;
    extern TInt32 GExitRequestCode;
    
    /** 
    * Check if some engine system request to exit on next iteration.
    */
    inline TBool isExitRequested() {
        return GIsExitRequested;
    }

    // Value for a check for engine to start again after shutdown.
    extern TBool GIsRestarting;

    /** 
    * Check if engine should start again after shutdown.
    */
    inline TBool isRestarting() {
        return GIsRestarting;
    }

    // Value for a check for window if it was resized.
    extern TBool GWasWindowResized;

    /** 
    * Check if engine's main window was resized.
    */
    inline TBool wasWindowResized() {
        return GWasWindowResized;
    }

    /** 
    * Mark that main window resize was catched and reset a flag.
    */
    inline void markWindowResized() {
        GWasWindowResized = kFalse;
    }

    // Value for a check for available base scene path.
    extern CStringView GBaseScenePath;

    /** 
    * Getter for a base scene filepath. Can be provided 
    * at startup through command line prompt.
    */
    inline const CStringView& getBaseScenePath() {
        return GBaseScenePath;
    }

    extern TBool GIgnoreAssertation;

    inline void ignoreAssert(TBool value = kTrue) {
        GIgnoreAssertation = value;
    }

    inline TBool isIgnoreAssert() {
        return GIgnoreAssertation;
    }

    extern CStringView GApplicationName;

    inline auto getApplicationName() {
        return GApplicationName;
    }

    /**
    * Set TRUE only if NeowiseEditorFramework.dll was found in a
    * same directory with this application launched.
    */
    extern TBool GEditorFrameworkProvided;

    inline TBool isEditor() {
        return GEditorFrameworkProvided;
    }

    struct STimeData {
        TReal time = {};
        TReal frameTime = {};
        union {
            TReal updateTime;
            TReal deltaTime = {};
        };
        TUint updateCount = {};
        TUint frameCount = {};
        TReal updateRate = {};
        TReal frameRate = {};
    };

    extern STimeData					GTime;
    extern CFixedHeapAllocatorPolicy*	GAlloc;
    extern CEventBus*					GEventBus;
    extern CEngineLoop*					GEngineLoop;
    extern CRenderThread*				GRenderThread;
    extern CApplication*				GApp;
    
}
