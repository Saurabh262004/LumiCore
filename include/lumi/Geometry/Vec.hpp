#pragma once

#include <cmath>

struct Vec2 {
	float x = 0.0f;
	float y = 0.0f;

	Vec2 operator+(const Vec2& other) const {
		return {
			x + other.x,
			y + other.y
		};
	}

	Vec2& operator+=(const Vec2& other) {
		x += other.x;
		y += other.y;

		return *this;
	}

	Vec2 operator-(const Vec2& other) const {
		return {
			x - other.x,
			y - other.y
		};
	}

	Vec2& operator-=(const Vec2& other) {
		x -= other.x;
		y -= other.y;

		return *this;
	}

	Vec2 operator-() const {
		return {-x, -y};
	}

	Vec2 operator*(const Vec2& other) const {
		return {
			x * other.x,
			y * other.y
		};
	}

	Vec2& operator*=(const Vec2& other) {
		x *= other.x;
		y *= other.y;

		return *this;
	}

	Vec2 operator*(const float other) const {
		return {
			x * other,
			y * other
		};
	}

	Vec2& operator*=(const float other) {
		x *= other;
		y *= other;

		return *this;
	}

	Vec2 operator/(const Vec2& other) const {
		return {
			x / other.x,
			y / other.y
		};
	}

	Vec2& operator/=(const Vec2& other) {
		x /= other.x;
		y /= other.y;

		return *this;
	}

	Vec2 operator/(const float other) const {
		return {
			x / other,
			y / other
		};
	}

	Vec2& operator/=(const float other) {
		x /= other;
		y /= other;

		return *this;
	}

	float length() const {
		return std::sqrt(x*x + y*y);
	}
};

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
