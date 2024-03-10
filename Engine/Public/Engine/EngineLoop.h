#pragma once

#include <Base/Export.h>
#include <Base/NumericTypes.h>
#include <Engine/EngineGlobals.h>
#include <Input/InputSystem.h>
#include <Engine/BaseWindow.h>

namespace Neowise {

	/**
	* Result values of CEngineLoop object's critical methods.
	*/
	enum EEngineLoop {
		E_ENGINE_LOOP_SETUP_SUCCESS,
		E_ENGINE_LOOP_APP_INIT_FAIL,
	};

	/**
	* Engine initialization, loading and running, as well
	* as shutting down controlled by this class. Second after
	* CEngineBoot, but not least.
	*/
	class NW_API CEngineLoop {
	public:
		/** 
		* Creates an instance of CEngineLoop class 
		* with NO initialization or something. Zero bytes written.
		*/
		static CEngineLoop* instantiate();

		EEngineLoop setupSystems();
		void load();
		void run();
		void releaseResources();
		void shutdown();

		void requestExit(int32 code = 0);
	private:
	};
}
