#pragma once

#include "Wave/Utils.h"

#include <cstdint>

namespace Wave {

	enum class AttenuationModel : uint8_t
	{
		None = 0, Inverse, Linear, Exponential,
	};

	struct Vec3
	{
		float X, Y, Z;

		Vec3(float x, float y, float z)
			: X(x), Y(y), Z(z) { }
	};

	struct AudioCone
	{
		float InnerAngle = Utils::DegreesToRadians(10.0f);
		float OuterAngle = Utils::DegreesToRadians(45.0f);
		float OuterGain = 0.0f;
	};

	struct DataSource
	{
		uint8_t* Data;
		size_t Length;
	};

}
