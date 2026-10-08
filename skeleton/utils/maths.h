#ifndef MATHS_H
#define MATHS_H

namespace maths {
	template<typename T>
	T lerp(T factor, T min, T max) {
		return min + factor * (max - min);
	}

	template<typename T>
	T inverse_lerp(T value, T min, T max) {
		return (value - min) / (max - min);
	}

	template<typename T>
	T remap(T value, T origin_min, T origin_max, T end_min, T end_max) {
		return lerp(inverse_lerp(value, origin_min, origin_max), end_min, end_max);
	}
}

#endif