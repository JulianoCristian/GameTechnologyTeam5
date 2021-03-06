#include "FloatRange.h"
#include <cstdlib>

/// <summary>
/// Initializes a new instance of the <see cref="FloatRange"/> .
/// </summary>
/// <param name="pMin">The minimum.</param>
/// <param name="pMax">The maximum.</param>
FloatRange::FloatRange(float pMin, float pMax)
{
	this->_min = pMin;
	this->_max = pMax;
}


/// <summary>
/// Finalizes an instance of the <see cref="FloatRange"/> class.
/// </summary>
FloatRange::~FloatRange()
{
}


/// <summary>
/// Returns an random number between the pMin and pMax.
/// </summary>
/// <returns>Random integer in range</returns>
int FloatRange::randomInRange()
{
	return rand() % getMax() + getMin();
}


