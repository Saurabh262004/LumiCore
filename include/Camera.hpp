#pragma once

#include <Geometry/Vec3.hpp>
#include <Geometry/Mat4.hpp>

class Camera {
private:
	Vec3 position;
	float pitch{0.0f}, yaw{0.0f}, roll{0.0f};
	float fov = 45.0f * (M_PI / 180.0f);
	float nearPlane = 0.1f;
	float farPlane = 100.0f;
	float viewportWidth = 800.0f;
    float viewportHeight = 600.0f;

public:
	void setPosition(Vec3 newPosition) {
		position = newPosition;
	}

	void setPitch(float newPitch) {
		pitch = newPitch;
	}

	void setYaw(float newYaw) {
		yaw = newYaw;
	}

	void setRoll(float newRoll) {
		roll = newRoll;
	}

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

	Mat4 getView() const {
		Mat4 rotation = Mat4::rotateZ(-roll) * Mat4::rotateY(-yaw) * Mat4::rotateX(-pitch);
		Mat4 translation  = Mat4::translate(-position);
		return rotation * translation;
	}

	Mat4 getProjection() const {
		float aspect = viewportWidth / viewportHeight;
		return Mat4::perspective(fov, aspect, nearPlane, farPlane);
	}

	Mat4 getViewProjection() const {
		return this->getProjection() * this->getView();
	}
};
