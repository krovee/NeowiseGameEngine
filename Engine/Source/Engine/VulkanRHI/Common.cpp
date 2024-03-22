#include <Engine/VulkanRHI/Common.h>

namespace Neowise {

#ifndef RESULT_TO_STR
#	define RESULT_TO_STR(x) NW_STRINGIFY(x),
#endif

	static CStringView sResultStringArray[] = {
		RESULT_TO_STR(eSuccess)
		RESULT_TO_STR(eNotReady)
		RESULT_TO_STR(eTimeout)
		RESULT_TO_STR(eEventSet)
		RESULT_TO_STR(eEventReset)
		RESULT_TO_STR(eIncomplete)
		RESULT_TO_STR(eErrorOutOfHostMemory)
		RESULT_TO_STR(eErrorOutOfDeviceMemory)
		RESULT_TO_STR(eErrorInitializationFailed)
		RESULT_TO_STR(eErrorDeviceLost)
		RESULT_TO_STR(eErrorMemoryMapFailed)
		RESULT_TO_STR(eErrorLayerNotPresent)
		RESULT_TO_STR(eErrorExtensionNotPresent)
		RESULT_TO_STR(eErrorFeatureNotPresent)
		RESULT_TO_STR(eErrorIncompatibleDriver)
		RESULT_TO_STR(eErrorTooManyObjects)
		RESULT_TO_STR(eErrorFormatNotSupported)
		RESULT_TO_STR(eErrorFragmentedPool)
		RESULT_TO_STR(eErrorUnknown)
		RESULT_TO_STR(eErrorOutOfPoolMemory)
		RESULT_TO_STR(eErrorInvalidExternalHandle)
		RESULT_TO_STR(eErrorFragmentation)
		RESULT_TO_STR(eErrorInvalidOpaqueCaptureAddress)
		RESULT_TO_STR(ePipelineCompileRequired)
		RESULT_TO_STR(eErrorSurfaceLostKHR)
		RESULT_TO_STR(eErrorNativeWindowInUseKHR)
		RESULT_TO_STR(eSuboptimalKHR)
		RESULT_TO_STR(eErrorOutOfDateKHR)
		RESULT_TO_STR(eErrorIncompatibleDisplayKHR)
		RESULT_TO_STR(eErrorValidationFailedEXT)
		RESULT_TO_STR(eErrorInvalidShaderNV)
		RESULT_TO_STR(eErrorImageUsageNotSupportedKHR)
		RESULT_TO_STR(eErrorVideoPictureLayoutNotSupportedKHR)
		RESULT_TO_STR(eErrorVideoProfileOperationNotSupportedKHR)
		RESULT_TO_STR(eErrorVideoProfileFormatNotSupportedKHR)
		RESULT_TO_STR(eErrorVideoProfileCodecNotSupportedKHR)
		RESULT_TO_STR(eErrorVideoStdVersionNotSupportedKHR)
		RESULT_TO_STR(eErrorOutOfPoolMemoryKHR)
		RESULT_TO_STR(eErrorInvalidExternalHandleKHR)
		RESULT_TO_STR(eErrorInvalidDrmFormatModifierPlaneLayoutEXT)
		RESULT_TO_STR(eErrorFragmentationEXT)
		RESULT_TO_STR(eErrorNotPermittedEXT)
		RESULT_TO_STR(eErrorNotPermittedKHR)
		RESULT_TO_STR(eErrorInvalidDeviceAddressEXT)
		RESULT_TO_STR(eErrorFullScreenExclusiveModeLostEXT)
		RESULT_TO_STR(eErrorInvalidOpaqueCaptureAddressKHR)
		RESULT_TO_STR(eThreadIdleKHR)
		RESULT_TO_STR(eThreadDoneKHR)
		RESULT_TO_STR(eOperationDeferredKHR)
		RESULT_TO_STR(eOperationNotDeferredKHR)
		RESULT_TO_STR(ePipelineCompileRequiredEXT)
		RESULT_TO_STR(eErrorPipelineCompileRequiredEXT)
		RESULT_TO_STR(eErrorInvalidVideoStdParametersKHR)
		RESULT_TO_STR(eErrorCompressionExhaustedEXT)
		RESULT_TO_STR(eErrorIncompatibleShaderBinaryEXT)
	};

	bool Neowise::RHIVKUtil::isSuccess(const vk::Result result) {
		return result == vk::Result::eSuccess;
	}

	bool RHIVKUtil::isValid(const vk::Result result) {
		switch (result) {
			case vk::Result::eSuccess:
			case vk::Result::eNotReady:
			case vk::Result::eTimeout:
			case vk::Result::eEventSet:
			case vk::Result::eEventReset:
			case vk::Result::eIncomplete:
			case vk::Result::ePipelineCompileRequired:
				return true;

			default: 
				return false;
		}
		
	}

	void RHIVKUtil::errorLog(const CString msg, const uint line, const CStringView file, const CStringView fn) {
		GDiag << "[RHI::VK][ERROR](" << file << ":" << line << ") in function " << fn << " an error: " << msg << "\n";
	}

	CStringView RHIVKUtil::toString(const vk::Result result) {
		return (uint)result <= arrayn(sResultStringArray) ? sResultStringArray[(uint)result] : "eUnknownResult";
	}

#ifdef RESULT_TO_STR
#	undef RESULT_TO_STR
#endif

}
