#pragma once

#include <Geometry/Vec3.hpp>
#include <Geometry/Mat4.hpp>

struct InstanceData {
	Mat4 model; // position + rotation + scale
	Vec3 color;
};
