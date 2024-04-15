#pragma once

#include <Base/NumericTypes.h>

namespace Neowise {
    /** 
    * Aessage-digest algorithm that is a widely used hash function producing a 128-bit hash value.
    * Can be used as a checksum to verify data integrity against unintentional corruption.
    */
    NW_API void MD5(const void* data, const TUint size, const TUint8 out[16]);
}
