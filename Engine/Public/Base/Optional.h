#pragma once

#include <Base/NumericTypes.h>
#include <Base/Utilities.h>

namespace Neowise {
	struct TNullopt {};
	static constexpr TNullopt nullopt;

	/** 
	* Simple container that manages optional contained value.
	*/
	template<class T>
	class NW_API COptional {
	public:
		constexpr COptional() = default;

		constexpr ~COptional() {
			destruct();
			check = false;
		}

		constexpr COptional(TNullopt) {}
		
		constexpr COptional(const COptional& o) {
			if (o.hasValue()) {
				construct(o.value());
			}
		}
		
		constexpr COptional(COptional&& o) {
			if (o.hasValue()) {
				construct(move(o.value()));
			}
		}
		
		template<class U>
		constexpr COptional(const COptional<U>& o) {
			if (o.hasValue()) {
				construct(o.value());
			}
		}
		
		template<class U>
		constexpr COptional(COptional<U>&& o) {
			if (o.hasValue()) {
				construct(move(o.value()));
			}
		}

		template<class...Args>
		constexpr COptional(Args&&...args) {
			construct(forward<Args>(args)...);
		}

		constexpr COptional& operator=(TNullopt) {
			reset();
			return *this;
		}

		constexpr COptional& operator=(const COptional& r) {
			if (r.hasValue()) {
				if (hasValue()) {
					value() = r.value();
				}
				else {
					construct(r.value());
				}
			}
			else {
				reset();
			}

			return *this;
		}

		template<class U>
		constexpr COptional& operator=(const COptional<U>& r) {
			if (r.hasValue()) {
				if (hasValue()) {
					value() = r.value();
				}
				else {
					construct(r.value());
				}
			}
			else {
				reset();
			}

			return *this;
		}

		constexpr COptional& operator=(COptional&& r) {
			if (r.hasValue()) {
				if (hasValue()) {
					value() = move(r.value());
				}
				else {
					construct(move(r.value()));
				}
			}
			else {
				reset();
			}

			return *this;
		}

		template<class U>
		constexpr COptional& operator=(COptional<U>&& r) {
			if (r.hasValue()) {
				if (hasValue()) {
					value() = move(r.value());
				}
				else {
					construct(move(r.value()));
				}
			}
			else {
				reset();
			}

			return *this;
		}

		template<class...Args>
		constexpr T& emplace(Args&&...args) {
			reset();
			construct(forward<Args>(args)...);
			return value();
		}

		constexpr bool hasValue() const {
			return check;
		}

		constexpr operator bool() const {
			return check;
		}

		constexpr T& value() {
			return static_cast<T&>(*reinterpret_cast<T*>(getStorage()));
		}

		constexpr const T& value() const {
			return static_cast<const T&>(*reinterpret_cast<const T*>(getStorage()));
		}

		constexpr T&& value() {
			return static_cast<T&&>(*reinterpret_cast<T*>(getStorage()));
		}

		constexpr const T&& value() const {
			return static_cast<const T&&>(*reinterpret_cast<const T*>(getStorage()));
		}

		constexpr T* operator->() {
			return &value();
		}
		
		constexpr const T* operator->() const {
			return &value();
		}
		
		constexpr T& operator*() {
			return value();
		}
		
		constexpr const T& operator*() const {
			return value();
		}

		constexpr T&& operator*() {
			return value();
		}
		
		constexpr const T&& operator*() const {
			return value();
		}

		constexpr void reset() {
			if (hasValue()) {
				destruct();
				check = false;
			}
		}

		constexpr void swap(COptional& r) {
			if (r.hasValue()) {
				if (hasValue()) {
					Neowise::swap(value(), r.value());
				}
				else {
					construct(move(r.value()));
					r.reset();
				}
			}
			else {
				if (hasValue()) {
					r.construct(move(value()));
					reset();
				}
			}
		}

		template<class U>
		constexpr bool operator==(const COptional<U>& r) const {
			if (hasValue() != hasValue()) return false;
			if (!hasValue()) return true;
			return value() == r.value();
		}

		template<class U>
		constexpr bool operator!=(const COptional<U>& r) const {
			return !(*this == r);
		}
	private:
		STATIC_ASSERT(!isOptional<T>);
		STATIC_ASSERT(!isConst<T>);
		STATIC_ASSERT(!isLValReference<T>);
		STATIC_ASSERT(!isRValReference<T>);
	private:
		constexpr void* getStorage() {
			return reinterpret_cast<void*>(storage);
		}

		constexpr const void* getStorage() const {
			return reinterpret_cast<void*>(storage);
		}

		template<class...Args>
		constexpr void construct(Args&&...args) {
			NW_ASSERT(!hasValue(), "Failed to construct optional that already have a value!");
			construct_at<T>(getStorage(), forward<Args>(args)...);
			check = true;
		}

		constexpr void destruct() {
			if (hasValue()) {
				destroy_at(value());
			}
		}

	private:
		uint8	storage[alignedSize(sizeof(T), alignmentOf<T>)] = {};
		bool	check = false;
	};
}
