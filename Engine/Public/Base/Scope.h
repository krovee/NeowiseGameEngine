#pragma once

#include <Base/Allocators.h>

namespace Neowise {
	extern CFixedHeapAllocatorPolicy* GAlloc;

	/** 
	* Smart pointer family container. Holds pointer 
	* in current scope, and destroys it when leave
	* scope. (std::unique_ptr<T>)
	*/
	template<class T>
	class NW_API Scope {
	public:
		Scope() = default;
		explicit Scope(T* ptr) 
			: _ptr(ptr)
		{}
		Scope(nullptr_t) 
			: _ptr()
		{}
		Scope(Scope&& o) 
			: _ptr(o._ptr)
		{
			o._ptr = nullptr;
		}
		~Scope() {
			reset();
		}
		Scope& operator=(Scope&& r) {
			reset(r.release());
			return *this;
		}
		Scope& operator=(nullptr_t) {
			reset();
			return *this;
		}

		template<class U>
		Scope<U> cast() {
			auto p = release();
			return Scope<U>(reinterpret_cast<U*>(p));
		}

		auto& operator[](int32 i) const {
			return get()[i];
		}

		const T* get() const {
			return _ptr;
		}

		T* get() {
			return _ptr;
		}

		operator bool() const {
			return get();
		}

		T& operator*() {
			return *_ptr;
		}

		const T& operator*() const {
			return *_ptr;
		}

		T* operator->() {
			return _ptr;
		}
		
		const T* operator->() const {
			return _ptr;
		}

		T* release() {
			auto p = get();
			_ptr = {};
			return const_cast<T*>(p);
		}

		void reset(T* ptr = {}) {
			swap(_ptr, ptr);
			if (ptr) {
				destroy_at(*ptr);
			}
		}
		void reset(nullptr_t) {
			auto p = get();
			_ptr = {};
		}

	private:
		T*			_ptr = nullptr;
	};

	template<class T, class...Args> 
	Scope<T> makeScope(Args&&...args) {
		auto* p = reinterpret_cast<T*>(GAlloc->allocate(sizeof(T)));
		construct_at<T>(p, forward<Args>(args)...);
		return Scope<T>(p);
	}

}
