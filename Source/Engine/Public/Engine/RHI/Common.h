#pragma once

#include <Base/Common.h>
#include <Engine/EngineGlobals.h>
#include <Math/Math.h>

namespace Neowise {

    extern CFixedHeapAllocatorPolicy* GAlloc;

    enum EVerticalSynchronization {
        E_VERTICAL_SYNCHRONIZATION_NONE,    // update screen AFAP. (VSYNC OFF)
        E_VERTICAL_SYNCHRONIZATION_SEMI,    // update screen when frame is complete and don't wait the actual frame to fully present. (VSYNC 'HALF')
        E_VERTICAL_SYNCHRONIZATION_FULL,    // update screen only when display is completed with last update and render frame complete. (VSYNC ON)
    };

    enum EPixelFormat {
        E_PIXEL_FORMAT_UNKNOWN,
        E_PIXEL_FORMAT_R8_UNORM,	// R8_UNORM 
        E_PIXEL_FORMAT_RG8_UNORM,	// R8G8_UNORM
        E_PIXEL_FORMAT_RGB8_UNORM,	// R8G8B8_UNORM
        E_PIXEL_FORMAT_RGBA8_UNORM,	// R8G8B8A8_UNORM
        E_PIXEL_FORMAT_BGRA8_UNORM,	// B8G8R8A8_UNORM
        E_PIXEL_FORMAT_R16_UNORM,	// R16_UNORM 
        E_PIXEL_FORMAT_RG16_UNORM,	// R16G16_UNORM
        E_PIXEL_FORMAT_RGB16_UNORM,	// R16G16B16_UNORM
        E_PIXEL_FORMAT_RGBA16_UNORM,// R16G16B16A16_UNORM
        E_PIXEL_FORMAT_BGRA16_UNORM,// B16G16R16A16_UNORM
        E_PIXEL_FORMAT_R32_UNORM,	// R32_UNORM 
        E_PIXEL_FORMAT_RG32_UNORM,	// R32G32_UNORM
        E_PIXEL_FORMAT_RGB32_UNORM,	// R32G32B32_UNORM
        E_PIXEL_FORMAT_RGBA32_UNORM,// R32G32B32A32_UNORM
        E_PIXEL_FORMAT_BGRA32_UNORM,// B32G32R32A32_UNORM
        E_PIXEL_FORMAT_R64_UNORM,	// R64_UNORM 
        E_PIXEL_FORMAT_RG64_UNORM,	// R64G64_UNORM
        E_PIXEL_FORMAT_RGB64_UNORM,	// R64G64B64_UNORM
        E_PIXEL_FORMAT_RGBA64_UNORM,// R64G64B64A64_UNORM
        E_PIXEL_FORMAT_BGRA64_UNORM,// B64G64R64A64_UNORM

        E_PIXEL_FORMAT_ABGR8_UNORM_PACKED32,	// A8B8G8R8_UNORM_PACK_32
        E_PIXEL_FORMAT_A2BGR10_UNORM_PACKED32,	// A2B10G10R10_UNORM_PACK_32
        E_PIXEL_FORMAT_A2RGB10_UNORM_PACKED32,	// A2R10G10B10_UNORM_PACK_32

        E_PIXEL_FORMAT_R16_FLOAT,		// R16_SFLOAT
        E_PIXEL_FORMAT_RG16_FLOAT,		// R16G16_SFLOAT
        E_PIXEL_FORMAT_RGB16_FLOAT,		// R16G16B16_SFLOAT
        E_PIXEL_FORMAT_RGBA16_FLOAT,	// R16G16B16A16_SFLOAT
        E_PIXEL_FORMAT_R32_FLOAT,		// R32_SFLOAT
        E_PIXEL_FORMAT_RG32_FLOAT,		// R32G32_SFLOAT
        E_PIXEL_FORMAT_RGB32_FLOAT,		// R32G32B32_SFLOAT
        E_PIXEL_FORMAT_RGBA32_FLOAT,	// R32G32B32A32_SFLOAT
        E_PIXEL_FORMAT_R64_FLOAT,		// R64_SFLOAT
        E_PIXEL_FORMAT_RG64_FLOAT,		// R64G64_SFLOAT
        E_PIXEL_FORMAT_RGB64_FLOAT,		// R64G64B64_SFLOAT
        E_PIXEL_FORMAT_RGBA64_FLOAT,	// R64G64B64A64_SFLOAT

        E_PIXEL_FORMAT_B10GR11U_FLOAT_PACKED32,	// B10G11R11_UFLOAT_PACK32
        E_PIXEL_FORMAT_D16_UNORM,		// D16_UNORM
        E_PIXEL_FORMAT_D32_FLOAT,		// D32_SFLOAT

        E_PIXEL_FORMAT_N_COUNT
    };

    enum ERHIBackend {
        E_RHI_BACKEND_UNDEFINED,
        E_RHI_BACKEND_VULKAN
    };

    template<class Interface>
    class NW_API RHIBase {
    public:

        void incrementRef() {
            if (_refCount)
                (*_refCount)++;
        }

        TBool decrementRef() {
            if (_refCount) {
                (*_refCount)--;

                if ((*_refCount) <= 0) {
                    return kTrue;
                }
            }

            return kFalse;
        }

        RHIBase() {
            _refCount = GAlloc->create<TInt64>();
        }

        RHIBase(const RHIBase& o) : _refCount(o._refCount) {
            incrementRef();
        }
        
        RHIBase(RHIBase&& o) noexcept : _refCount(o._refCount) {
            incrementRef();
        }
        
        RHIBase& operator=(const RHIBase& o) {
            _refCount = o._refCount;
            incrementRef();

            return *this;
        }
        
        RHIBase& operator=(RHIBase&& o) noexcept {
            _refCount = o._refCount;
            incrementRef();

            return *this;
        }
        
        virtual ~RHIBase() {
            decrementRef();
        }

    private:
        TInt64* _refCount = 0;
    };

    template<class Interface>
    class NW_API RHIInterface {
    public:
        virtual ~RHIInterface() {
            if (_iface) {
                if (_iface->decrementRef()) {
                    destroy_at<Interface>(_iface);
                    GAlloc->free(_iface, sizeof *_iface);
                }
            }
        }

        RHIInterface(nullptr_t) : _iface(nullptr) 
        {}

        RHIInterface(Interface* iface) : _iface(iface) {
            iface->incrementRef();
        }

        RHIInterface(const RHIInterface& o) : _iface(o._iface) {
            _iface->incrementRef();
        }
        
        RHIInterface(RHIInterface&& o) noexcept : _iface(o._iface) {
            _iface->incrementRef();
        }
        
        RHIInterface& operator=(const RHIInterface& o) {
            _iface = o._iface;
            _iface->incrementRef();

            return *this;
        }
        
        RHIInterface& operator=(RHIInterface&& o) noexcept {
            _iface = o._iface;
            _iface->incrementRef();

            return *this;
        }

        Interface* operator->() {
            return _iface;
        }
        
        const Interface* operator->() const {
            return _iface;
        }
        
        Interface& operator*() {
            return *_iface;
        }
        
        const Interface& operator*() const {
            return *_iface;
        }

        Interface* get() {
            return _iface;
        }
        
        const Interface* get() const {
            return _iface;
        }
        
        Interface& unwrap() {
            return *_iface;
        }
        
        const Interface& unwrap() const {
            return *_iface;
        }

        operator TBool() const {
            return _iface != nullptr;
        }

        template<class InterfaceImpl>
        InterfaceImpl* getImpl() {
            return reinterpret_cast<InterfaceImpl*>(_iface);
        }
        
        template<class InterfaceImpl>
        const InterfaceImpl* getImpl() const {
            return reinterpret_cast<const InterfaceImpl*>(_iface);
        }
        
        template<class U, class...Args>
        static RHIInterface make(Args&&...args) {
            return RHIInterface(reinterpret_cast<U*>(GAlloc->create<U>(forward<Args>(args)...)));
        }
    private:
        Interface*  _iface = nullptr;
    };

    class CRHIDynamicProviderInterface;
    using IRHIDynamicProvider = RHIInterface<CRHIDynamicProviderInterface>;

    class CRHISurfaceInterface;
    using IRHISurface = RHIInterface<CRHISurfaceInterface>;

    class CRHIAdapterInterface;
    using IRHIAdapter = RHIInterface<CRHIAdapterInterface>;

    class CRHISurfaceInterface;
    using IRHISurface = RHIInterface<CRHISurfaceInterface>;

    class CRHISwapchainInterface;
    using IRHISwapchain = RHIInterface<CRHISwapchainInterface>;

}

#ifndef NW_RHI_CLASS_DECLARATION
#   define NW_RHI_CLASS_DECLARATION(classname)                                      	\
    public:                                                                         	\
        inline classname(const ERHIBackend _backend) : backend(_backend) {}       	\
        constexpr ERHIBackend getBackend() const { return backend; }               		\
    private:                                                                      		\
        const ERHIBackend backend = E_RHI_BACKEND_UNDEFINED;
#endif
