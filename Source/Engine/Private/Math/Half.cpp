#include <Math/Half.h>
#include <Base/Templated.h>

namespace Neowise {
    union uif32
    {
        inline uif32() :
            i(0)
        {}

        inline uif32(TReal f_) :
            f(f_)
        {}

        inline uif32(TFloatAsIntRep i_) :
            i(i_)
        {}

        TReal f;
        TFloatAsIntRep i;
    };

    half::half(TReal f) {
        uif32 Entry;
        Entry.f = f;
        auto i = Entry.i;

        //
        // Our floating point number, f, is represented by the bit
        // pattern in integer i.  Disassemble that bit pattern into
        // the sign, s, the exponent, e, and the significand, m.
        // Shift s into the position where it will go in the
        // resulting half number.
        // Adjust e, accounting for the different exponent bias
        // of float and half (127 versus 15).
        //

        TFloatAsIntRep s = (i >> 16) & 0x00008000;
        TFloatAsIntRep e = ((i >> 23) & 0x000000ff) - (127 - 15);
        TFloatAsIntRep m = i & 0x007fffff;

        //
        // Now reassemble s, e and m into a half:
        //

        if (e <= 0)
        {
            if (e < TFloatAsIntRep(-10))
            {
                //
                // E is less than -10.  The absolute value of f is
                // less than half_MIN (f may be a small normalized
                // float, a denormalized float or a zero).
                //
                // We convert f to a half zero.
                //

                _rep = s;
                return;
            }

            //
            // E is between -10 and 0.  F is a normalized float,
            // whose magnitude is less than __half_NRM_MIN.
            //
            // We convert f to a denormalized half.
            //

            m = (m | 0x00800000) >> (1 - e);

            //
            // Round to nearest, round "0.5" up.
            //
            // Rounding may cause the significand to overflow and make
            // our number normalized.  Because of the way a half's bits
            // are laid out, we don't have to treat this case separately;
            // the code below will handle it correctly.
            //

            if (m & 0x00001000)
                m += 0x00002000;

            //
            // Assemble the half from s, e (zero) and m.
            //

            _rep = (s | (m >> 13));
            return;
        }
        else if (e == TFloatAsIntRep(0xff - (127 - 15)))
        {
            if (m == 0)
            {
                //
                // F is an infinity; convert f to a half
                // infinity with the same sign as f.
                //

                _rep = (s | 0x7c00);
                return;
            }
            else
            {
                //
                // F is a NAN; we produce a half NAN that preserves
                // the sign bit and the 10 leftmost bits of the
                // significand of f, with one exception: If the 10
                // leftmost bits are all zero, the NAN would turn
                // into an infinity, so we have to set at least one
                // bit in the significand.
                //

                m >>= 13;

                _rep = (s | 0x7c00 | m | (m == 0));
                return;
            }
        }
        else
        {
            //
            // E is greater than zero.  F is a normalized float.
            // We try to convert f to a normalized half.
            //

            //
            // Round to nearest, round "0.5" up
            //

            if (m & 0x00001000)
            {
                m += 0x00002000;

                if (m & 0x00800000)
                {
                    m = 0;     // overflow in significand,
                    e += 1;     // adjust exponent
                }
            }

            //
            // Handle exponent overflow
            //

            if (e > 30)
            {
                _rep = (s | 0x7c00);
                return;
                // if this returns, the half becomes an
            }   // infinity with the same sign as f.

            //
            // Assemble the half from s, e and m.
            //

            _rep = (s | (e << 10) | (m >> 13));
            return;
        }
    }

    half::operator TReal() const {
        TFloatAsIntRep s = (_rep >> 15) & 0x00000001;
        TFloatAsIntRep e = (_rep >> 10) & 0x0000001f;
        TFloatAsIntRep m = _rep & 0x000003ff;

        if (e == 0)
        {
            if (m == 0)
            {
                //
                // Plus or minus zero
                //

                uif32 result;
                result.i = static_cast<TFloatAsIntRep>(s << 31);
                return result.f;
            }
            else
            {
                //
                // Denormalized number -- renormalize it
                //

                while (!(m & 0x00000400))
                {
                    m <<= 1;
                    e -= 1;
                }

                e += 1;
                m &= ~0x00000400;
            }
        }
        else if (e == 31)
        {
            if (m == 0)
            {
                //
                // Positive or negative infinity
                //

                uif32 result;
                result.i = static_cast<TFloatAsIntRep>((s << 31) | 0x7f800000);
                return result.f;
            }
            else
            {
                //
                // Nan -- preserve sign and significand bits
                //

                uif32 result;
                result.i = static_cast<TFloatAsIntRep>((s << 31) | 0x7f800000 | (m << 13));
                return result.f;
            }
        }

        //
        // Normalized number
        //

        e = e + (127 - 15);
        m = m << 13;

        //
        // Assemble s, e and m.
        //

        uif32 Result;
        Result.i = static_cast<TFloatAsIntRep>((s << 31) | (e << 23) | m);
        return Result.f;
    }

    half::operator TInt16() const {
        return _rep;
    }
    
}
