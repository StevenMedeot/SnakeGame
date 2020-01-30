#ifndef HELPER_H
#define HELPER_H

template <typename T> T CLAMP(const T& value, const T& low, const T& high)
{
	return value < low ? low : (value > high ? high : value);
}

#endif