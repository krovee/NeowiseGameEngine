#pragma once

#include <Math/Scalar.h>

namespace Neowise {
    /** 
    * Point2 is a simple structure to represent a point.
    */
    struct NW_API Point2i {
        TInt32 x;
        TInt32 y;
    };
    struct NW_API Point2u {
        TUint32 x;
        TUint32 y;
    };
    struct NW_API Point2r {
        TReal x;
        TReal y;
    };

    constexpr Point2i operator+(const Point2i& a, const Point2i& b) {
        return { a.x + b.x, a.y + b.y };
    }
    
    constexpr Point2i operator-(const Point2i& a, const Point2i& b) {
        return { a.x - b.x, a.y - b.y };
    }
    
    constexpr Point2i operator*(const Point2i& a, const Point2i& b) {
        return { a.x * b.x, a.y + b.y };
    }
    
    constexpr Point2i operator/(const Point2i& a, const Point2i& b) {
        return { a.x / b.x, a.y + b.y };
    }
    

    constexpr Point2u operator+(const Point2u& a, const Point2u& b) {
        return { a.x + b.x, a.y + b.y };
    }
    
    constexpr Point2u operator-(const Point2u& a, const Point2u& b) {
        return { a.x - b.x, a.y - b.y };
    }
    
    constexpr Point2u operator*(const Point2u& a, const Point2u& b) {
        return { a.x * b.x, a.y + b.y };
    }
    
    constexpr Point2u operator/(const Point2u& a, const Point2u& b) {
        return { a.x / b.x, a.y + b.y };
    }
    
    constexpr Point2r operator+(const Point2r& a, const Point2r& b) {
        return { a.x + b.x, a.y + b.y };
    }
    
    constexpr Point2r operator-(const Point2r& a, const Point2r& b) {
        return { a.x - b.x, a.y - b.y };
    }
    
    constexpr Point2r operator*(const Point2r& a, const Point2r& b) {
        return { a.x * b.x, a.y + b.y };
    }
    
    constexpr Point2r operator/(const Point2r& a, const Point2r& b) {
        return { a.x / b.x, a.y + b.y };
    }
    
}
