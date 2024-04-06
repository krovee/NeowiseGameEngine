#pragma once

#include <Base/Common.h>

namespace Neowise {
	class CEventBus;
	class CEngineLoop;
	class CApplication;
	class CRenderThread;

	// Value for a check for engine to request an exit.
	extern bool GIsExitRequested;
	extern int32 GExitRequestCode;
	
	/** 
	* Check if some engine system request to exit on next iteration.
	*/
	inline bool isExitRequested() {
		return GIsExitRequested;
	}

	// Value for a check for engine to start again after shutdown.
	extern bool GIsRestarting;

	/** 
	* Check if engine should start again after shutdown.
	*/
	inline bool isRestarting() {
		return GIsRestarting;
	}

	// Value for a check for window if it was resized.
	extern bool GWasWindowResized;

	/** 
	* Check if engine's main window was resized.
	*/
	inline bool wasWindowResized() {
		return GWasWindowResized;
	}

	/** 
	* Mark that main window resize was catched and reset a flag.
	*/
	inline void markWindowResized() {
		GWasWindowResized = false;
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

	extern bool GIgnoreAssertation;

	inline void ignoreAssert(bool value = true) {
		GIgnoreAssertation = value;
	}

	inline bool isIgnoreAssert() {
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
	extern bool GEditorFrameworkProvided;

	inline bool isEditor() {
		return GEditorFrameworkProvided;
	}

	struct STimeData {
		real time = {};
		real frameTime = {};
		union {
			real updateTime;
			real deltaTime = {};
		};
		uint updateCount = {};
		uint frameCount = {};
		real updateRate = {};
		real frameRate = {};
	};

	extern STimeData					GTime;
	extern CFixedHeapAllocatorPolicy*	GAlloc;
	extern CEventBus*					GEventBus;
	extern CEngineLoop*					GEngineLoop;
	extern CRenderThread*				GRenderThread;
	extern CApplication*				GApp;
	
}
