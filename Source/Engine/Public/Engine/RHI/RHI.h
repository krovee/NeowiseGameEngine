#pragma once

#include <Engine/RHI/Common.h>

namespace Neowise {
	/** 
	* 
	*/
	enum ERHIClass : uint {
		E_RHI_CLASS_UNSPECIFIED,
		E_RHI_CLASS_OPENGL,
		E_RHI_CLASS_VULKAN,
		E_RHI_CLASS_DIRECTX,
	};

	CDiagnostics& operator<<(CDiagnostics& diag, ERHIClass rhi);

	template<class>
	struct RHIInterfaceTraits {
		static constexpr uint RHI_RAW_SIZE = 0;
	};

	/** 
	* 
	*/
	class NW_API RHIInterface {
	public:
		constexpr RHIInterface(ERHIClass eRHI) : rhiClass(eRHI)
		{}

		virtual ~RHIInterface() = default;

		constexpr ERHIClass getClass() const {
			return rhiClass;
		}

		constexpr bool isOpenGLClass() const {
			return rhiClass == E_RHI_CLASS_OPENGL;
		}

		constexpr bool isVulkanClass() const {
			return rhiClass == E_RHI_CLASS_VULKAN;
		}

		constexpr bool isDirectXClass() const {
			return rhiClass == E_RHI_CLASS_DIRECTX;
		}
	private:
		const ERHIClass	rhiClass = E_RHI_CLASS_UNSPECIFIED;
	};

	NW_API void RHI_CreateInterface(ERHIClass eRHI);
	NW_API void RHI_DestroyInterface();
}
