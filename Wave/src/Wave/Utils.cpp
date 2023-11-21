#include "Utils.h"

#define _USE_MATH_DEFINES
#include <cmath>

namespace Wave {

	namespace Utils {

		float DegreesToRadians(float degrees)
		{
			return degrees * (M_PI / 180.0f);
		}

		float RadiansToDegrees(float radians)
		{
			return radians * (180 / M_PI);
		}

	}

}
