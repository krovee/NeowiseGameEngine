#pragma once

#include <Math/Vector4.h>

namespace Neowise {
    /** 
    * CPackUnorm2x16 is used to pack FVector2 values in
    * a range [0...1]
    */
    class NW_API CPackUnorm2x16 {
    public:
        TUint32 operator()(const FVector2& v) const;
        const FVector2 operator()(TUint32 p) const;
    };

    /** 
    * CPackSnorm2x16 is used to pack FVector2 values in
    * a range [-1...1]
    */
    class NW_API CPackSnorm2x16 {
    public:
        TUint32 operator()(const FVector2& v) const;
        const FVector2 operator()(TUint32 p) const;
    };

    /** 
    * CPackUnorm4x8 is used to pack FVector4 values in
    * a range [0...1]
    */
    class NW_API CPackUnorm4x8 {
    public:
        TUint32 operator()(const FVector4& v) const;
        const FVector4 operator()(TUint32 p) const;
    };

    /** 
    * CPackSnorm4x8 is used to pack FVector4 values in
    * a range [-1...1]
    */
    class NW_API CPackSnorm4x8 {
    public:
        TUint32 operator()(const FVector4& v) const;
        const FVector4 operator()(TUint32 p) const;
    };

    /** 
    * 
    */
    class NW_API CPackHalf2x16 {
    public:
        TUint32 operator()(const FVector2& v) const; 
        const FVector2 operator()(TUint32 p) const; 
    };
}
