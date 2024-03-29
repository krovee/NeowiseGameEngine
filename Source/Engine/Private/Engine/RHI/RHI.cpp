#include <Engine/RHI/RHI.h>
#include <Engine/EngineGlobals.h>

namespace Neowise {
	RHIInterface* GRHI = nullptr;

	CDiagnostics& operator<<(CDiagnostics& diag, ERHIClass rhi) {
		switch (rhi) {
			case E_RHI_CLASS_DIRECTX:		return diag << "E_RHI_CLASS_DIRECTX(3)";
			case E_RHI_CLASS_VULKAN:		return diag << "E_RHI_CLASS_VULKAN(2)";
			case E_RHI_CLASS_OPENGL:		return diag << "E_RHI_CLASS_OPENGL(1)";
			case E_RHI_CLASS_UNSPECIFIED:	return diag << "E_RHI_CLASS_UNSPECIFIED(0)";
		}
		return diag;
	}

	void RHI_CreateInterface(ERHIClass eRHI) {
		switch (eRHI) {
			default: {
				GDiag << "[ERROR]: Failed to create RHI interface! name=" << eRHI << "\n";
			} break;

			case E_RHI_CLASS_OPENGL: {
				//GRHI = allocateObject<COpenGL_RHIInterface>(GAlloc);
			} break;
		}
	}

	void RHI_DestroyInterface() {
		switch (GRHI->getClass()) {
			case E_RHI_CLASS_OPENGL: {
				//destroy_at<COpenGL_RHIInterface>(GRHI);
			} break;
			default: break;
		}
	}

}
