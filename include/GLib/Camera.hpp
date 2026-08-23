#pragma once

#include <GLib/Geometry/Vec.hpp>
#include <GLib/Geometry/Mat.hpp>

class Camera {
private:
	Vec3 position;

	float pitch{0.0f}, yaw{0.0f}, roll{0.0f};

	float fov = 45.0f * (M_PI / 180.0f);

	float nearPlane = 0.1f;
	float farPlane = 100.0f;

	float viewportWidth = 800.0f;
	float viewportHeight = 600.0f;

	Mat4 viewProjection;

public:
	// setters
	void setPosition(Vec3 position) {
		this->position = position;
	}

	void setPitch(float pitch) {
		this->pitch = pitch;
	}

	void setYaw(float yaw) {
		this->yaw = yaw;
	}

	void setRoll(float roll) {
		this->roll = roll;
	}

	void setFOV(float degrees) {
		fov = degrees * (M_PI / 180.0f);
	}

	void setNearPlane(float nearPlane) {
		this->nearPlane = nearPlane;
	}

	void setFarPlane(float farPlane) {
		this->farPlane = farPlane;
	}

	void setViewportResolution(float width, float height) {
		viewportWidth = width;
		viewportHeight = height;
	}

	// getters
	Vec3 getPosition() const {
		return position;
	}

	float getPitch() const {
		return pitch;
	}

	float getYaw() const {
		return yaw;
	}

	float getRoll() const {
		return roll;
	}

	float getFOV() const {
		return fov * (180 / M_PI);
	}

	float getNearPlane() const {
		return nearPlane;
	}

	float getFarPlane() const {
		return farPlane;
	}

	Mat4 getViewProjection() const {
		return viewProjection;
	}

	void updateViewProjection() {
		Mat4 rotation = Mat4::rotateZ(-roll) * Mat4::rotateY(-yaw) * Mat4::rotateX(-pitch);
		Mat4 translation  = Mat4::translate(-position);
		Mat4 view = rotation * translation;

		float aspect = viewportWidth / viewportHeight;
		Mat4 projection = Mat4::perspective(fov, aspect, nearPlane, farPlane);

		viewProjection = projection * view;
	}
};
