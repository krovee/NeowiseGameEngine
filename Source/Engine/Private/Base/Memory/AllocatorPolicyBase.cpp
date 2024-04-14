#include <Base/Memory/AllocatorPolicyBase.h>

namespace Neowise {
    CAllocatorPolicyBase::CAllocatorPolicyBase(const DAllocationInfo& info) 
        : _info(info)
    {
    }
    
    DAllocationInfo const& CAllocatorPolicyBase::getInfo() const {
        return _info;
    }

    TUint64 CAllocatorPolicyBase::getTotalAllocated() const {
        return _info.totalAllocated;
    }

    TUint64 CAllocatorPolicyBase::getCurrentAllocated() const {
        return _info.currentAllocated;
    }

    void CAllocatorPolicyBase::onAllocate(TUint64 size) {
        _info.currentAllocated += size;
        if (_info.currentAllocated > _info.totalAllocated) {
            _info.totalAllocated = _info.currentAllocated;
        }
    }

    void CAllocatorPolicyBase::onFree(TUint64 size) {
        _info.currentAllocated -= size;
    }

}
