#pragma once

#include <Math/Scalar.h>

namespace Neowise {
	/** 
	* Point2 is a simple structure to represent a point.
	*/
	struct NW_API Point2i {
		int32 x;
		int32 y;
	};
	struct NW_API Point2u {
		uint32 x;
		uint32 y;
	};
	struct NW_API Point2r {
		real x;
		real y;
	};
}
