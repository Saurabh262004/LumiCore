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
