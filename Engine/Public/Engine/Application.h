#pragma once

#include <Base/Common.h>
#include <Engine/EngineGlobals.h>

namespace Neowise {
	/** 
	* Type of instatiated application, used to correct
	* pointer-cast of an CApplication object.
	*/
	enum EApplicationType : uint8 {
		E_APPLICATION_TYPE_INVALID		= 0x00,
		E_APPLICATION_TYPE_GAME_RUNTIME	= 0x01,
		E_APPLICATION_TYPE_EDITOR		= 0x02,
		E_APPLICATION_TYPE_LINE_COUNTER	= 0x04,
		E_APPLICATION_TYPE_SHADER_COOKER= 0x08,
	};

	/** 
	* Base class for every instance of engine's application.
	*/
	class NW_API CApplication {
	public:
		virtual ~CApplication() = default;
		constexpr CApplication() = default;

		virtual bool initialize() = 0;
		virtual void onUpdate() = 0;
		virtual void shutdown() = 0;

		virtual void postInitialize() {}
		virtual void onRenderFrame() {}
		virtual void preShutdown() {}

		EApplicationType getType() const {
			return type;
		}
	protected:
		inline CApplication(EApplicationType appType, const CStringView& name) : type(appType)
		{
			*const_cast<CString*>(&GApplicationName) = name;
		}

	private:
		const EApplicationType type = E_APPLICATION_TYPE_INVALID;
	};
}
