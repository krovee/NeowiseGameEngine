#pragma once

#include <Base/Utilities.h>
#include "AllocatorPolicyBase.h"

namespace Neowise {
	/** 
	* Fixed-size static stack-based allocator policy.
	*/
	template<uint64 N> 
	class NW_API CFixedStackAllocatorPolicy : public CAllocatorPolicyBase {
	public:

		constexpr CFixedStackAllocatorPolicy() {
			construct_range(_buffer, N, 0xdeadbeef);
		}

		virtual  ~CFixedStackAllocatorPolicy() = default;

		CFixedStackAllocatorPolicy(const CFixedStackAllocatorPolicy&) = default;
		constexpr CFixedStackAllocatorPolicy(CFixedStackAllocatorPolicy&& o) {
			swap(_buffer, o._buffer);
			swap(_allocated, o._allocated); 
			swap(_info, o._info);
		}
		CFixedStackAllocatorPolicy& operator=(const CFixedStackAllocatorPolicy&) = default;
		constexpr CFixedStackAllocatorPolicy& operator=(CFixedStackAllocatorPolicy&& r) {
			swap(_buffer, r._buffer);
			swap(_allocated, r._allocated);
			swap(_info, r._info);
			return *this;
		}

		constexpr void destroy() override {}

		inline void* allocate(uint64 size) override {
			if (_allocated < N && size) {
				const uint64 i = _allocated;
				_allocated += size;
				onAllocate(size);
				return reinterpret_cast<void*>(&_buffer[i]);
			}
			return nullptr;
		}

		inline void* getBuffer() {
			return _buffer;
		}

		inline void free(void* p, uint64 size) override {
			if (size <= _allocated) {
				_allocated -= size;
				onFree(size);
				if (int64(_allocated) < 0) {
					_allocated = 0;
				}
				if (p) {
					Memory::clear(p, size);
				}
			}
		}

	private:
		alignas(8)
		uint8	_buffer[N] = {};
		uint64	_allocated = {};

		template<uint64 M>
		friend constexpr void swap(CFixedStackAllocatorPolicy<M>& a, CFixedStackAllocatorPolicy<M>& b);
	};

	template<uint64 N>
	constexpr void swap(CFixedStackAllocatorPolicy<N>& a, CFixedStackAllocatorPolicy<N>& b) {
		swap(a._buffer, b._buffer);
		swap(a._allocated, b._allocated);
		swap(a._info, b._info);
	}

}
