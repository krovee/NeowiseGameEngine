#pragma once

#include <Base/Templated.h>
#include <Base/Allocators.h>
#include <Base/ArrayView.h>

namespace Neowise {
	extern CFixedHeapAllocatorPolicy* GAlloc;

    /** 
	* 
	*/
	template<class T>
	class NW_API CVector {
	public:
		constexpr CVector() = default;

		constexpr CVector(T* first, T* last) {
			construct(first, last - first);
		}

		constexpr CVector(const TInitializerList<T>& list) {
			construct(list.begin(), list.size());
		}

		constexpr CVector(T* data, uint len) {
			construct(data, len);
		}

		template<uint N>
		constexpr CVector(T(&arr)[N]) {
			construct(arr, N);
		}

		template<class...Args>
		constexpr CVector(uint sz, Args&&...args) {
			constructArgs(sz, forward<Args>(args)...);
		}

		constexpr CVector(const CVector& o) {
			construct(o.data(), o.size());
		}
		
		constexpr CVector(CVector&& o) {
			construct(o.data(), o.size());
		}
		
		constexpr CVector& operator=(const CVector& o) {
			construct(o.data(), o.size());
			return *this;
		}

		constexpr CVector& operator=(CVector&& o) {
			construct(o.data(), o.size());
			return *this;
		}
		
		~CVector() {
			destroy_range(_ptr, _size);
		}

		constexpr uint size() const {
			return _size;
		}

		constexpr uint capacity() const {
			return _capacity;
		}

		constexpr const T* data() const {
			return _ptr;
		}

		constexpr T* data() {
			return _ptr;
		}

		constexpr const T* begin() const {
			return _ptr;
		}

		constexpr T* begin() {
			return _ptr;
		}

		constexpr const T* end() const {
			return _ptr + _size;
		}
		
		constexpr T* end() {
			return _ptr + _size;
		}

		template<class...Args>
		constexpr T* emplace(Args&&...args) {
			if (_capacity == kInitialCap && !_size) {
				growStorage();
			}
			else if (_size >= _capacity) {
				growCapacity();
				growStorage();
			}

			constructAt(_size++, forward<Args>(args)...);
			return _ptr + _size - 1;
		}

		constexpr void pushBack(const T& obj) {
			emplace(obj);
		}

		constexpr void pushBack(T&& obj) {
			emplace(move(obj));
		}

		constexpr void popBack() {
			NW_ASSERT(_size > 0, "Failed to pop back empty vector.");

			--_size;
		}

		constexpr void clear() {
			Memory::clear(_ptr, sizeof(T) * _size);
			_size = 0;
		}

		constexpr void shrinkToFit() {
			T* p = reinterpret_cast<T*>(GAlloc->allocate(sizeof(T) * _size));
			NW_ASSERT(p, "");
			move_range(p, _ptr, _size);
			GAlloc->free(_ptr, _size);
			_capacity = _size;
			_ptr = p;
		}

		constexpr operator CArrayView<T>() const {
			return CArrayView<T>(_ptr, _size);
		}

	private:
		constexpr static inline real	kAdvanceCapFactor = real(1.4);
		constexpr static inline uint	kInitialCap = 8;

		template<class...Args>
		constexpr void constructAt(uint i, Args&&...args) {
			NW_ASSERT(i <= _capacity, "Failed construction in CVector: out of bounds!");

			construct_at<T>((_ptr + i), forward<Args>(args)...);
		}

		constexpr void construct(const T* data, uint len) {
			_capacity = alignedSize(len, 4);
			_size = len;
			growStorage();
			T* p = reinterpret_cast<T*>(GAlloc->allocate(sizeof(T) * _capacity));
			NW_ASSERT(p, "");
			move_range(p, data, _size);
			_ptr = p;
		}

		template<class...Args>
		constexpr void constructArgs(uint len, Args&&...args) {
			_capacity = alignedSize(len, 4);
			_size = len;
			growStorage();
			T* p = reinterpret_cast<T*>(GAlloc->allocate(sizeof(T) * _capacity));
			NW_ASSERT(p, "");
			for (uint i = 0; i < _size; ++i) {
				constructAt(i, forward<Args>(args)...);
			}
			_ptr = p;
		}

		constexpr void growStorage() {
			T* p = reinterpret_cast<T*>(GAlloc->allocate(sizeof(T) * _capacity));
			NW_ASSERT(p, "");
			if (_ptr) {
				move_range(p, _ptr, _size);
				GAlloc->free(_ptr, _size);
			}
			_ptr = p;
		}

		constexpr void growCapacity() {
			_capacity = alignedSize((uint)((real)(_capacity)*kAdvanceCapFactor), 4);
		}
	private:
		T*		_ptr = nullptr;
		uint	_capacity = kInitialCap;
		uint	_size = 0;
	};

	template<class T>
	class NW_API CObjectHash<CVector<T>> {
	public:
		static uint get(const CVector<T>& vec) {
			auto hs = vec.size() * 0xab0ba + 1;
			for (const auto& v : vec) {
				hs *= hs + CObjectHash<T>::get(v);
			}
			return hs;
		}
	};
}
