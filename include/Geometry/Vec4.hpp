#pragma once

#include <cmath>

struct Vec4 {
	float w = 0.0f;
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	Vec4 operator+(const Vec4& other) const {
		return {
			w + other.w,
			x + other.x,
			y + other.y,
			z + other.z
		};
	}

	Vec4& operator+=(const Vec4& other) {
		w += other.w;
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	Vec4 operator-(const Vec4& other) const {
		return {
			w - other.w,
			x - other.x,
			y - other.y,
			z - other.z
		};
	}

	Vec4& operator-=(const Vec4& other) {
		w -= other.w;
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	Vec4 operator*(const Vec4& other) const {
		return {
			w * other.w,
			x * other.x,
			y * other.y,
			z * other.z
		};
	}

	Vec4& operator*=(const Vec4& other) {
		w *= other.w;
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	Vec4 operator*(const float other) const {
		return {
			w * other,
			x * other,
			y * other,
			z * other
		};
	}

	Vec4& operator*=(const float other) {
		w *= other;
		x *= other;
		y *= other;
		z *= other;

		return *this;
	}

	Vec4 operator/(const Vec4& other) const {
		return {
			w / other.w,
			x / other.x,
			y / other.y,
			z / other.z
		};
	}

	Vec4& operator/=(const Vec4& other) {
		w /= other.w;
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	Vec4 operator/(const float other) const {
		return {
			w / other,
			x / other,
			y / other,
			z / other
		};
	}

	Vec4& operator/=(const float other) {
		w /= other;
		x /= other;
		y /= other;
		z /= other;

		return *this;
	}

	float length() const {
		return std::sqrt(w*w + x*x + y*y + z*z);
	}
};
