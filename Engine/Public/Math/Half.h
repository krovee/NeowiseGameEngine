#pragma once

#include "Scalar.h"

namespace Neowise {
	/** 
	* 16-bit floating point representation.
	*/
	class NW_API half {
	public:
		~half() = default;
		constexpr half() = default;
		half(real r);

		operator real() const;
		operator int16() const;
	private:
		int16 _rep = {};
	};
}
