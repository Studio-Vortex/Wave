#pragma once

#include "Wave/Utils.h"

#include <cstdint>

namespace Wave {

	enum class AttenuationModel : uint8_t
	{
		None = 0,
		Inverse,
		Linear,
		Exponential,
	};

	/* Stereo panner. */
	enum class PanMode
	{
		Balance = 0, /* Does not blend one side with the other. Technically just a balance. Compatible with other popular audio engines and therefore the default. */
		Pan,         /* A true pan. The sound from one side will "move" to the other side and blend with it. */
	};

	enum class Positioning
	{
		Absolute = 0,
		Relative,
	};

	struct Vec3
	{
		float X, Y, Z;

		Vec3(float x, float y, float z)
			: X(x), Y(y), Z(z) { }

		Vec3(float value)
			: X(value), Y(value), Z(value) { }
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
