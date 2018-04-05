#pragma once

#include <iostream>
#include <math.h>
#include "src/maths/maths.h"

using namespace sparky;
using namespace maths;

float a = 202.5;
float b = 30;

std::cout << "Duzina: " << a << std::endl;
std::cout << "Visina: " << b << std::endl;

for (float angle = 0; angle <= 180; angle += 5)
{
	float x = a * cos(toRadians(angle));
	float y = b * sin(toRadians(angle));

	std::cout << "Ugao: " << angle << ", X: " << roundf(x * 100) / 100 << ", Y: " << roundf(y * 100) / 100 << std::endl;
}
