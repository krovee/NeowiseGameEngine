#pragma once

#include <Base/Common.h>

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

		bool startFrameRecord();
		void endFrameRecord();

	private:
		bool beginFrame();
		bool endFrame();

	private:
		static void loop(void* params);

		CBaseWindow*			window = nullptr;
	};

	NW_API bool RT_Initialize();
	NW_API bool RT_Shutdown();
}
