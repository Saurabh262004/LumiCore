#pragma once

#include <cmath>

struct Vec4 {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f;

	Vec4 operator+(const Vec4& other) const {
		return {
			x + other.x,
			y + other.y,
			z + other.z,
			w + other.w
		};
	}

	Vec4& operator+=(const Vec4& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	Vec4 operator-(const Vec4& other) const {
		return {
			x - other.x,
			y - other.y,
			z - other.z,
			w - other.w
		};
	}

	Vec4& operator-=(const Vec4& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	Vec4 operator-() const {
		return {-x, -y, -z, -w};
	}

	Vec4 operator*(const Vec4& other) const {
		return {
			x * other.x,
			y * other.y,
			z * other.z,
			w * other.w
		};
	}

	Vec4& operator*=(const Vec4& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;

		return *this;
	}

	Vec4 operator*(const float other) const {
		return {
			x * other,
			y * other,
			z * other,
			w * other
		};
	}

	Vec4& operator*=(const float other) {
		x *= other;
		y *= other;
		z *= other;
		w *= other;

		return *this;
	}

	Vec4 operator/(const Vec4& other) const {
		return {
			x / other.x,
			y / other.y,
			z / other.z,
			w / other.w
		};
	}

	Vec4& operator/=(const Vec4& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;

		return *this;
	}

	Vec4 operator/(const float other) const {
		return {
			x / other,
			y / other,
			z / other,
			w / other
		};
	}

	Vec4& operator/=(const float other) {
		x /= other;
		y /= other;
		z /= other;
		w /= other;

		return *this;
	}

	float length() const {
		return std::sqrt(x*x + y*y + z*z + w*w);
	}
};
