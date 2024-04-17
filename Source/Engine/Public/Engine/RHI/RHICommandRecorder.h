#pragma once

#include <Engine/RHI/Common.h>

namespace Neowise {
    /**
     * 
     */
    enum ERHICmdRecorder {
        E_RHI_CMD_RECORDER_GRAPHICS, // 0<<- by default cmd recorder have a graphics type
        E_RHI_CMD_RECORDER_COMPUTE,
        E_RHI_CMD_RECORDER_TRANSFER,
    };
    /**
     * 
     */
    struct SRHICmdRecorderSpecification {
        ERHICmdRecorder type = E_RHI_CMD_RECORDER_GRAPHICS;
        TUint           processedFramesCount = 2;   // 2<<- double-buffering by default
    };

    /**
     * 
     */
    class NW_API CRHICmdRecorderInterface : public RHIBase {
    public:
        virtual ~CRHICmdRecorderInterface() = default;

        template<class DerivedInterface>
        constexpr DerivedInterface* as() {
            return reinterpret_cast<DerivedInterface*>(this);
        }

        template<class DerivedInterface>
        constexpr const DerivedInterface* as() const {
            return reinterpret_cast<const DerivedInterface*>(this);
        }

        NW_RHI_CLASS_DECLARATION(CRHICmdRecorderInterface)
    };

    class NW_API CRHIGraphicsCmdRecorderInterface : public CRHICmdRecorderInterface {
    public:
        virtual ~CRHIGraphicsCmdRecorderInterface() = default;

        inline CRHIGraphicsCmdRecorderInterface(const ERHIBackend _backend) : CRHICmdRecorderInterface(_backend) 
        {}

        constexpr ERHIBackend getBackend() const { 
            return CRHICmdRecorderInterface::getBackend(); 
        }
    };
    
    class NW_API CRHIComputeCmdRecorderInterface : public CRHICmdRecorderInterface {
    public:
        virtual ~CRHIComputeCmdRecorderInterface() = default;

        inline CRHIComputeCmdRecorderInterface(const ERHIBackend _backend) : CRHICmdRecorderInterface(_backend) 
        {}

        constexpr ERHIBackend getBackend() const { 
            return CRHICmdRecorderInterface::getBackend(); 
        }
    };

    class NW_API CRHITransferCmdRecorderInterface : public CRHICmdRecorderInterface {
    public:
        virtual ~CRHITransferCmdRecorderInterface() = default;

        inline CRHITransferCmdRecorderInterface(const ERHIBackend _backend) : CRHICmdRecorderInterface(_backend) 
        {}

        constexpr ERHIBackend getBackend() const { 
            return CRHICmdRecorderInterface::getBackend(); 
        }
    };
}
