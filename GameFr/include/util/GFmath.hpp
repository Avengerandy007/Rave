#pragma once
#include "vectors.hpp"
#include <math.h>

#define RAD_TO_DEGREES * 57

namespace GameFr::Util::Math{
	float Pythagorean(const float a, const float b);
	float AngleBetweenVectors(const GameFr::Vector2& a, const GameFr::Vector2& b);
}
