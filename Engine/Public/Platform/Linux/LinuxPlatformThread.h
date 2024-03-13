#pragma once

#include <Base/Thread.h>

namespace Neowise::Platform::Linux {
	/**
	*
	*/
	class NW_API CThread : public Neowise::CThread {
	public:
		CThread(PFN_StartFunc func, void* params, bool immediateStart, bool immediateDetach);
		~CThread();

		// Probably useless method on linux...
		void start() override;
		bool isActive() const override; 
		void detach() override; 
		void terminate() override; 
		void destroy() override; 

	private:
		uint id = {};
		uint* sharedID = nullptr;
	};
}
