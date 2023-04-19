/*
 * Some utility functions for the course TNM046
 *
 * Authors: Stefan Gustavson (stegu@itn.liu.se) 2013-2014
 *          Martin Falk (martin.falk@liu.se) 2021
 *
 * This code is in the public domain.
 */
#pragma once

#include <array>

struct GLFWwindow;

namespace util {

	/*
	 * displayFPS() - Calculate, display and return frame rate statistics.
	 * Called every frame, but statistics are updated only once per second.
	 * The time per frame is a better measure of performance than the
	 * number of frames per second, so both are displayed.
	 *
	 * NOTE: This function doesn't work properly if you call it for multiple
	 * windows. Call it only for one window, and only once every frame.
	 */
	double displayFPS(GLFWwindow* window);

	void mat4print(const std::array<float, 16>& m);

	std::array<float, 16> mat4mult(const std::array<float, 16>& m1,
		const std::array<float, 16>& m2);

	std::array<float, 16> mat4indentity();			// Returns the 4D identity matrix
	std::array<float, 16> mat4rotx(float angle);	// Rotation matrix around x-axis. Radians. 
	std::array<float, 16> mat4roty(float angle);	// Rotation matrix around y-axis. Radians. 
	std::array<float, 16> mat4rotz(float angle);	// Rotation matrix around z-axis. Radians. 
	std::array<float, 16> mat4scale(float scale);	// Uniform scaling matrix
    std::array<float, 16> mat4translate(float x, float y, float z); // Translation matrix

}  // namespace util
