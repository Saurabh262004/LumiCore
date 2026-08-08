#pragma once

#include <cmath>

struct Vec3 {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	Vec3 operator+(const Vec3& other) const {
		return {
			x + other.x,
			y + other.y,
			z + other.z
		};
	}

	Vec3& operator+=(const Vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	Vec3 operator-(const Vec3& other) const {
		return {
			x - other.x,
			y - other.y,
			z - other.z
		};
	}

	Vec3& operator-=(const Vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	Vec3 operator-() const {
		return {-x, -y, -z};
	}

	Vec3 operator*(const Vec3& other) const {
		return {
			x * other.x,
			y * other.y,
			z * other.z
		};
	}

	Vec3& operator*=(const Vec3& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	Vec3 operator*(const float other) const {
		return {
			x * other,
			y * other,
			z * other
		};
	}

	Vec3& operator*=(const float other) {
		x *= other;
		y *= other;
		z *= other;

		return *this;
	}

	Vec3 operator/(const Vec3& other) const {
		return {
			x / other.x,
			y / other.y,
			z / other.z
		};
	}

	Vec3& operator/=(const Vec3& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	Vec3 operator/(const float other) const {
		return {
			x / other,
			y / other,
			z / other
		};
	}

	Vec3& operator/=(const float other) {
		x /= other;
		y /= other;
		z /= other;

		return *this;
	}

	float length() const {
		return std::sqrt(x*x + y*y + z*z);
	}
};
