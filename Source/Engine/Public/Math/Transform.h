#pragma once

#include <Base/Wrap.h>
#include <Base/Vector.h>
#include <Math/Math.h>

namespace Neowise {

    class CTransform {
    public:
        CTransform(const FVector3& translation = FVector3::zero, const FVector3& rotation = FVector3::zero, const FVector3& scale = FVector3::one);
        CTransform(const FVector3& translation, const FQuaternion& rotation, const FVector3& scale = FVector3::one);
        explicit CTransform(const FQuaternion& rotation);
        
        CTransform createChild(const FVector3& translation = FVector3::zero, const FVector3& rotation = FVector3::zero, const FVector3& scale = FVector3::one);
        CTransform createChild(const FVector3& translation, const FQuaternion& rotation, const FVector3& scale = FVector3::one);

        TWrap<const CTransform> getParent() const {
            return _parent;
        }

        void resetParent(TWrap<const CTransform> parent = nullptr);

        FMatrix4 getMatrix() const;
        const FVector3& getLocalPosition() const;
        FVector3 getLocalRotationEuler() const;
        const FQuaternion& getLocalRotation() const;
        const FVector3& getLocalScale() const;

        FVector3& localPosition();
        FQuaternion& localRotation();
        FVector3& localScale();

        void recalculate();
    private:
        TBool isDirty(const TUint8 flag) const;
        void setDirty(const TUint8 flag);

    private:
        FMatrix4                _localMatrix = FMatrix4(1);

        FVector3                _localPosition = {};
        FQuaternion             _localRotation = {};
        FVector3                _localScale = FVector3::one;
    
        TWrap<const CTransform> _parent = nullptr;

        TUint8                   _dirtyFlags = 14;
    };

}
