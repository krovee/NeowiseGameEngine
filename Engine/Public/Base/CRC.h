#pragma once

#include <Base/NumericTypes.h>

namespace Neowise {
	/** 
	* [32-bit version]
	* An error-detecting code commonly used in digital networks
	* and storage devices to detect accidental changes to digital data. 
	* Blocks of data entering these systems get a short check value attached, 
	* based on the remainder of a polynomial division of their contents. 
	* On retrieval, the calculation is repeated and, in the event the check 
	* values do not match, corrective action can be taken against data corruption. 
	* CRCs can be used for error correction.
	*/
	NW_API uint32	CRC32(const void* data, const uint size);

	/**
	* [64-bit version]
	* An error-detecting code commonly used in digital networks
	* and storage devices to detect accidental changes to digital data.
	* Blocks of data entering these systems get a short check value attached,
	* based on the remainder of a polynomial division of their contents.
	* On retrieval, the calculation is repeated and, in the event the check
	* values do not match, corrective action can be taken against data corruption.
	* CRCs can be used for error correction.
	*/
	NW_API uint		CRC64(const void* data, const uint size);

}
