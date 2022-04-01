#pragma once

#ifndef QUATERNION_H
#define QUATERNION_H
#include <tgmath.h>
#include <math.h>
#include "Vector4.h"
#define PI 3.14
#define RAD2DEG 57.2958

const float DEG2RAD = 0.0174533;

struct Quaternion{
    public:
        Quaternion();

        Quaternion(float x, float y, float z, float w):
            mQuat_(x,y,z,w)
        {
        };
        ~Quaternion() {};

        Vector3 quaternionToEuler() {
            Vector3 euler;

            // if the input quaternion is normalized, this is exactly one. Otherwise, this acts as a correction factor for the quaternion's not-normalizedness
            float unit = (mQuat_.GetX() * mQuat_.GetX()) + (mQuat_.GetY() * mQuat_.GetY()) + (mQuat_.GetZ() * mQuat_.GetZ()) + (mQuat_.GetW() * mQuat_.GetW());

            // this will have a magnitude of 0.5 or greater if and only if this is a singularity case
            float test = mQuat_.GetX() * mQuat_.GetW() - mQuat_.GetY() * mQuat_.GetZ();

            if (test > 0.4995f * unit) // singularity at north pole
            {
                euler.SetX(PI / 2);
                euler.SetY (2.0f * atan2(mQuat_.GetY(), mQuat_.GetX()));
                euler.SetZ (0);
            }
            else if (test < -0.4995f * unit) // singularity at south pole
            {
                euler.SetX(-PI / 2);
                euler.SetY(-2.0f * atan2(mQuat_.GetY(), mQuat_.GetX()));
                euler.SetZ(0);
            }
            else // no singularity - this is the majority of cases
            {
                euler.SetX( asin(2.0f * (mQuat_.GetW() * mQuat_.GetX() - mQuat_.GetY() * mQuat_.GetZ())));
                euler.SetY (atan2(2.0f * mQuat_.GetW() * mQuat_.GetY() + 2.0f * mQuat_.GetZ() * mQuat_.GetX(), 1 - 2.0f * (mQuat_.GetX() * mQuat_.GetX() + mQuat_.GetY() * mQuat_.GetY())));
                euler.SetZ(atan2(2.0f * mQuat_.GetW() * mQuat_.GetZ() + 2.0f * mQuat_.GetX() * mQuat_.GetY(), 1 - 2.0f * (mQuat_.GetZ() * mQuat_.GetZ() + mQuat_.GetX() * mQuat_.GetX())));


            }
            // all the math so far has been done in radians. Before returning, we convert to degrees...
            euler *= Mathf.Rad2Deg;

           
            return euler;
        }
        Quaternion eulerToQuaternion(const Vector3& euler) {
            float xOver2 = euler.GetX() * DEG2RAD * 0.5f;
            float yOver2 = euler.GetY() * DEG2RAD * 0.5f;
            float zOver2 = euler.GetZ() * DEG2RAD * 0.5f;

            float sinXOver2 = sin(xOver2);
            float cosXOver2 = cos(xOver2);
            float sinYOver2 = sin(yOver2);
            float cosYOver2 = cos(yOver2);
            float sinZOver2 = sin(zOver2);
            float cosZOver2 = cos(zOver2);

            Quaternion result;
            result.setX (cosYOver2 * sinXOver2 * cosZOver2 + sinYOver2 * cosXOver2 * sinZOver2);
            result.setY (sinYOver2 * cosXOver2 * cosZOver2 - cosYOver2 * sinXOver2 * sinZOver2);
            result.setZ (cosYOver2 * cosXOver2 * sinZOver2 - sinYOver2 * sinXOver2 * cosZOver2);
            result.setW ( cosYOver2 * cosXOver2 * cosZOver2 + sinYOver2 * sinXOver2 * sinZOver2);

            return result;
        }
        bool isIdentity() const {
            return mQuat_.GetX() == 0.0f && mQuat_.GetY() == 0.0f && mQuat_.GetZ() == 0.0f && mQuat_.GetW() == 1.0f;
        }
        float getAngle() const {
            return acos(mQuat_.GetW()) * 2.0f;
        }

        float magnitudeSquared() {
            return getX() * getX() + getY() * getY() + getZ() * getZ() + getW() * getW();
        }

        float dot(const Quaternion& v) const {
            return mQuat_.GetX() * v.getX() + getY() * v.getY() + getZ() * v.getZ() + getW() * v.getW();
        }

        const Vector3 rotate(const Vector3& v) const
        {
            const float vx = 2.0f * v.GetX();
            const float vy = 2.0f * v.GetY();
            const float vz = 2.0f * v.GetZ();
            const float w2 = getW() * getW() - 0.5f;
            const float dot2 = (getX() * vx + getY() * vy + getZ() * vz);
            return Vector3((vx * w2 + (getY() * vz - getZ() * vy) * getW() + getX() * dot2), 
                (vy * w2 + (getZ() * vx - getX() * vz) * getW()+ getY() * dot2),
                (vz * w2 + ( vy - getY() * vx) * getW() + getZ() * dot2));
        }


        inline float getX()const {return mQuat_.GetX();}
        inline float getY()const {return mQuat_.GetY();}
        inline float getZ()const {return mQuat_.GetZ();}
        inline float getW()const {return mQuat_.GetW();}

        inline void setX(float x) {return mQuat_.SetX(x);}
        inline void setY(float y) {return mQuat_.SetY(y);}
        inline void setZ(float z) {return mQuat_.SetZ(z);}
        inline void setW(float w) {return mQuat_.SetW(w);}


        Quaternion operator+(Quaternion const& b) { return Quaternion(getX() + b.getX(), getY() + b.getY(), getZ() + b.getZ(), getW() + b.getW()); }
        Quaternion operator-(Quaternion const& b) { return Quaternion(getX() - b.getX(), getY() - b.getY(), getZ() - b.getZ(), getW() - b.getW()); }
        Quaternion operator*(Quaternion const& b) { return Quaternion(getX() * b.getX(), getY() * b.getY(), getZ() * b.getZ(), getW() * b.getW()); }
        Quaternion operator*(float const& f) { return Quaternion(getX() * f, getY() * f, getZ() * f, getW() * f); }
       
        bool operator==(Quaternion const& b) { return ((getX() == b.getX()) && (getY() == b.getY()) && (getZ() == b.getZ()) && (getW() == b.getW())); }
        bool operator!=(Quaternion const& b) { return !(getX() == b.getX()) && (getY() == b.getY()) && (getZ() == b.getZ()) && (getW() == b.getW()); }


        //define
        static void ConvertToLua(lua_State* state) {
            getGlobalNamespace(state).
                beginNamespace("ECS").beginClass<Quaternion>("Quaternion").
                addConstructor<void(*)(float, float, float, float)>().
                addProperty("x", &Quaternion::getX, &Quaternion::setX).
                addProperty("y", &Quaternion::getY, &Quaternion::setY).
                addProperty("z", &Quaternion::getZ, &Quaternion::setZ).
                addProperty("w", &Quaternion::getW, &Quaternion::setW).
                addFunction("toEuler", &Quaternion::quaternionToEuler).
                addFunction("eulerToQuaternion", &Quaternion::eulerToQuaternion).
                addFunction("getAngle", &Quaternion::getAngle).
                addFunction("rotate", &Quaternion::rotate).

                endClass().
                endNamespace();
        }

    protected:
        Vector4 mQuat_;
        


};

#endif