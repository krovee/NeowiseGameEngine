#pragma once

#include <Base/Common.h>

namespace Neowise {
	class CBaseWindow;
	class CPlugRenderer;

	/** 
	* 
	*/
	class NW_API CSplashScreen {
	public:

	private:
		Scope<CBaseWindow>		_window = nullptr;
		Scope<CPlugRenderer>	_renderer = nullptr;
	};
}
