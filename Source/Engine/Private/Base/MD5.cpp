#include <Base/MD5.h>
#include <Base/Utilities.h>

namespace Neowise {
    static const TUint32 sInitialData[64] = {
        7, 12, 17, 22, 7, 12, 17, 22, 
        7, 12, 17, 22, 7, 12, 17, 22,
        5, 9,  14, 20, 5, 9,  14, 20, 
        5, 9,  14, 20, 5, 9,  14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 
        4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 
        6, 10, 15, 21, 6, 10, 15, 21
    };

    static const TUint32 sPRNround[64] = {
        3614090360, 3905402710, 606105819,  3250441966, 
        4118548399, 1200080426, 2821735955, 4249261313, 
        1770035416, 2336552879, 4294925233, 2304563134,
        1804603682, 4254626195, 2792965006, 1236535329, 
        4129170786, 3225465664, 643717713,  3921069994, 
        3593408605, 38016083,   3634488961, 3889429448,
        568446438,  3275163606, 4107603335, 1163531501, 
        2850285829, 4243563512, 1735328473, 2368359562, 
        4294588738, 2272392833, 1839030562, 4259657740,
        2763975236, 1272893353, 4139469664, 3200236656, 
        681279174,  3936430074, 3572445317, 76029189,   
        3654602809, 3873151461, 530742520,  3299628645,
        4096336452, 1126891415, 2878612391, 4237533241, 
        1700485571, 2399980690, 4293915773, 2240044497, 
        1873313359, 4264355552, 2734768916, 1309151649,
        4149444226, 3174756917, 718787259,  3951481745
    };

    void MD5(const void* data, const TUint size, const TUint8 out[16]) {
        NW_UNUSED(sInitialData);
        NW_UNUSED(sPRNround);
        NW_UNUSED(data);
        NW_UNUSED(size);
        NW_UNUSED(out);

        // uint32 a0 = 0x67452301, A = 0;
        // uint32 b0 = 0xefcdab89, B = 0;
        // uint32 c0 = 0x98badcfe, C = 0;
        // uint32 d0 = 0x10325476, D = 0;

        // 1: Processing the bytestring
        // TODO(krovee): Make a md5 function.
    }
}
