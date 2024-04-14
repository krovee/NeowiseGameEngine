#include <Engine/VulkanRHI/Common.h>

namespace Neowise {

#ifndef RESULT_TO_STR
#	define RESULT_TO_STR(x) NW_STRINGIFY(x),
#endif

    static CStringView sResultStringArray[] = {
        RESULT_TO_STR(Success)
        RESULT_TO_STR(NotReady)
        RESULT_TO_STR(Timeout)
        RESULT_TO_STR(EventSet)
        RESULT_TO_STR(EventReset)
        RESULT_TO_STR(Incomplete)
        RESULT_TO_STR(ErrorOutOfHostMemory)
        RESULT_TO_STR(ErrorOutOfDeviceMemory)
        RESULT_TO_STR(ErrorInitializationFailed)
        RESULT_TO_STR(ErrorDeviceLost)
        RESULT_TO_STR(ErrorMemoryMapFailed)
        RESULT_TO_STR(ErrorLayerNotPresent)
        RESULT_TO_STR(ErrorExtensionNotPresent)
        RESULT_TO_STR(ErrorFeatureNotPresent)
        RESULT_TO_STR(ErrorIncompatibleDriver)
        RESULT_TO_STR(ErrorTooManyObjects)
        RESULT_TO_STR(ErrorFormatNotSupported)
        RESULT_TO_STR(ErrorFragmentedPool)
        RESULT_TO_STR(ErrorUnknown)
        RESULT_TO_STR(ErrorOutOfPoolMemory)
        RESULT_TO_STR(ErrorInvalidExternalHandle)
        RESULT_TO_STR(ErrorFragmentation)
        RESULT_TO_STR(ErrorInvalidOpaqueCaptureAddress)
        RESULT_TO_STR(PipelineCompileRequired)
        RESULT_TO_STR(ErrorSurfaceLostKHR)
        RESULT_TO_STR(ErrorNativeWindowInUseKHR)
        RESULT_TO_STR(SuboptimalKHR)
        RESULT_TO_STR(ErrorOutOfDateKHR)
        RESULT_TO_STR(ErrorIncompatibleDisplayKHR)
        RESULT_TO_STR(ErrorValidationFailedEXT)
        RESULT_TO_STR(ErrorInvalidShaderNV)
        RESULT_TO_STR(ErrorImageUsageNotSupportedKHR)
        RESULT_TO_STR(ErrorVideoPictureLayoutNotSupportedKHR)
        RESULT_TO_STR(ErrorVideoProfileOperationNotSupportedKHR)
        RESULT_TO_STR(ErrorVideoProfileFormatNotSupportedKHR)
        RESULT_TO_STR(ErrorVideoProfileCodecNotSupportedKHR)
        RESULT_TO_STR(ErrorVideoStdVersionNotSupportedKHR)
        RESULT_TO_STR(ErrorOutOfPoolMemoryKHR)
        RESULT_TO_STR(ErrorInvalidExternalHandleKHR)
        RESULT_TO_STR(ErrorInvalidDrmFormatModifierPlaneLayoutEXT)
        RESULT_TO_STR(ErrorFragmentationEXT)
        RESULT_TO_STR(ErrorNotPermittedEXT)
        RESULT_TO_STR(ErrorNotPermittedKHR)
        RESULT_TO_STR(ErrorInvalidDeviceAddressEXT)
        RESULT_TO_STR(ErrorFullScreenExclusiveModeLostEXT)
        RESULT_TO_STR(ErrorInvalidOpaqueCaptureAddressKHR)
        RESULT_TO_STR(ThreadIdleKHR)
        RESULT_TO_STR(ThreadDoneKHR)
        RESULT_TO_STR(OperationDeferredKHR)
        RESULT_TO_STR(OperationNotDeferredKHR)
        RESULT_TO_STR(PipelineCompileRequiredEXT)
        RESULT_TO_STR(ErrorPipelineCompileRequiredEXT)
        RESULT_TO_STR(ErrorInvalidVideoStdParametersKHR)
        RESULT_TO_STR(ErrorCompressionExhaustedEXT)
        RESULT_TO_STR(ErrorIncompatibleShaderBinaryEXT)
    };

    bool Neowise::RHIVKUtil::isSuccess(const VkResult result) {
        return result == VK_SUCCESS;
    }

    bool RHIVKUtil::isValid(const VkResult result) {
        switch (result) {
            case VK_SUCCESS:
            case VK_NOT_READY:
            case VK_TIMEOUT:
            case VK_EVENT_SET:
            case VK_EVENT_RESET:
            case VK_INCOMPLETE:
            case VK_PIPELINE_COMPILE_REQUIRED:
                return true;

            default: 
                return false;
        }
        
    }

    void RHIVKUtil::errorLog(const CString msg, const TUint line, const CStringView file, const CStringView fn) {
        GDiag << "[RHI::VK][ERROR](" << file << ":" << line << ") in function " << fn << " an error: " << msg << "\n";
    }

    CStringView RHIVKUtil::toString(const VkResult result) {
        return (TUint)result <= arrayn(sResultStringArray) ? sResultStringArray[(TUint)result] : "eUnknownResult";
    }

#ifdef RESULT_TO_STR
#	undef RESULT_TO_STR
#endif

}
