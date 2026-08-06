#pragma once

#include <Geometry/Vec3.hpp>
#include <Geometry/Vec4.hpp>
#include <cmath>

struct Mat4 {
	float m[16]{}; // zero-initialized, column-major: m[col*4 + row]

	static Mat4 identity() {
		Mat4 r;

		r.m[0] = r.m[5] = r.m[10] = r.m[15] = 1.0f;

		return r;
	}

	Mat4 operator*(const Mat4& o) const {
		Mat4 r;

		for (int c = 0; c < 4; ++c) {
			for (int row = 0; row < 4; ++row) {
				float sum = 0.0f;

				for (int k = 0; k < 4; ++k) {
					sum += m[k * 4 + row] * o.m[c * 4 + k];
				}

				r.m[c * 4 + row] = sum;
			}
		}

		return r;
	}

	Vec4 operator*(const Vec4& v) const {
		return Vec4{
			m[0]*v.x + m[4]*v.y + m[8]*v.z  + m[12]*v.w,
			m[1]*v.x + m[5]*v.y + m[9]*v.z  + m[13]*v.w,
			m[2]*v.x + m[6]*v.y + m[10]*v.z + m[14]*v.w,
			m[3]*v.x + m[7]*v.y + m[11]*v.z + m[15]*v.w
		};
	}

	static Mat4 translate(const Vec3& t) {
		Mat4 r = identity();

		r.m[12] = t.x; r.m[13] = t.y; r.m[14] = t.z;

		return r;
	}

	static Mat4 scale(const Vec3& s) {
		Mat4 r = identity();

		r.m[0] = s.x; r.m[5] = s.y; r.m[10] = s.z;

		return r;
	}

	static Mat4 rotateZ(float radians) {
		Mat4 r = identity();

		float c = std::cos(radians), s = std::sin(radians);

		r.m[0] = c; r.m[1] = s;
		r.m[4] = -s; r.m[5] = c;

		return r;
	}

	// (Rodrigues' rotation formula)
	static Mat4 rotate(float radians, Vec3 axis) {
		float len = std::sqrt(axis.x*axis.x + axis.y*axis.y + axis.z*axis.z);

		axis.x /= len; axis.y /= len; axis.z /= len;

		float c = std::cos(radians), s = std::sin(radians), omc = 1.0f - c;

		Mat4 r = identity();

		r.m[0] = c + axis.x*axis.x*omc;
		r.m[1] = axis.y*axis.x*omc + axis.z*s;
		r.m[2] = axis.z*axis.x*omc - axis.y*s;

		r.m[4] = axis.x*axis.y*omc - axis.z*s;
		r.m[5] = c + axis.y*axis.y*omc;
		r.m[6] = axis.z*axis.y*omc + axis.x*s;

		r.m[8]  = axis.x*axis.z*omc + axis.y*s;
		r.m[9]  = axis.y*axis.z*omc - axis.x*s;
		r.m[10] = c + axis.z*axis.z*omc;

		return r;
	}
};
