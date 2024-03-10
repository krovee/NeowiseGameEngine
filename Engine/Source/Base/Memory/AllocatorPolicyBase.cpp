#include <Base/Memory/AllocatorPolicyBase.h>

namespace Neowise {
	CAllocatorPolicyBase::CAllocatorPolicyBase(const DAllocationInfo& info) 
		: _info(info)
	{
	}
	
	DAllocationInfo const& CAllocatorPolicyBase::getInfo() const {
		return _info;
	}

	uint64 CAllocatorPolicyBase::getTotalAllocated() const {
		return _info.totalAllocated;
	}

	uint64 CAllocatorPolicyBase::getCurrentAllocated() const {
		return _info.currentAllocated;
	}

	void CAllocatorPolicyBase::onAllocate(uint64 size) {
		_info.currentAllocated += size;
		if (_info.currentAllocated > _info.totalAllocated) {
			_info.totalAllocated = _info.currentAllocated;
		}
	}

	void CAllocatorPolicyBase::onFree(uint64 size) {
		_info.currentAllocated -= size;
	}

}
