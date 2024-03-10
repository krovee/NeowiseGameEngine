#pragma once

#include <Base/Templated.h>

namespace Neowise {
	/** 
	* Common linear search algorithm to iterate over every element in an array
	* of contigous data, and return iterator of found, or last one.
	*/
	template<class T>
	constexpr const T* find(const T* first, const T* last, const T& value) {
		for (; first != last; ++first) {
			if (*first == value) {
				break;
			}
		}
		return first;
	}

	/**
	* Common linear search algorithm to iterate over every element in an array
	* of contigous data, and return iterator of found, or last one.
	*/
	template<class T>
	constexpr T* find(T* first, const T* last, const T& value) {
		for (; first != last; ++first) {
			if (*first == value) {
				break;
			}
		}
		return first;
	}

}
