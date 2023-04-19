/*
 * Some utility functions for the course TNM046
 *
 * Authors: Stefan Gustavson (stegu@itn.liu.se) 2014
 *          Martin Falk (martin.falk@liu.se) 2021
 *
 * This code is in the public domain.
 */
#include "Utilities.hpp"

#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>


namespace util {

    double displayFPS(GLFWwindow* window) {
        static int frames = 0;
        static double fps = 0.0;

        static double t0 = glfwGetTime();  // Gets number of seconds since glfwInit()

        double t = glfwGetTime();  // Get current time

        // update fps only once every second
        if (t - t0 >= 1.0) {
            fps = static_cast<double>(frames) / (t - t0);
            t0 = t;
            frames = 0;
        }

        // update the window title
        if (frames == 0) {
            char title[201];
            // convert fps to milliseconds
            double frametime = (fps > 0.0) ? 1000.0 / fps : 0.0;
            snprintf(title, 200, "TNM046: %.2f ms/frame (%.1f FPS)", frametime, fps);
            glfwSetWindowTitle(window, title);
        }

        ++frames;
        return fps;
    }

    void mat4print(const std::array<float, 16>& m) {
        printf("Matrix:\n");
        printf("%6.2f %6.2f %6.2f %6.2f\n", m[0], m[4], m[8], m[12]);
        printf("%6.2f %6.2f %6.2f %6.2f\n", m[1], m[5], m[9], m[13]);
        printf("%6.2f %6.2f %6.2f %6.2f\n", m[2], m[6], m[10], m[14]);
        printf("%6.2f %6.2f %6.2f %6.2f\n", m[3], m[7], m[11], m[15]);
        printf("\n");
    }

    std::array<float, 16> mat4mult(const std::array<float, 16>& m1, const std::array<float, 16>& m2) {
        std::array<float, 16> results = {0};

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    results[4 * i + j] += m1[4 * k + j] * m2[4 * i + k];
                }
            }
        }

        return results;
    }

    std::array<float, 16> mat4rotx(float angle) {
        return {
            1.0f, 0.0f,        0.0f,         0.0f,
            0.0f, cosf(angle), sinf(angle),  0.0f,
            0.0f, -sinf(angle), cosf(angle), 0.0f,
            0.0f, 0.0f,        0.0f,         1.0f
        };
    }

    std::array<float, 16> mat4roty(float angle) {
        return {
            cosf(angle), 0.0f, -sinf(angle), 0.0f,
            0.0f,        1.0f, 0.0f,         0.0f,
            sinf(angle), 0.0f, cosf(angle),  0.0f,
            0.0f,        0.0f, 0.0f,         1.0f
        };
    }

    std::array<float, 16> mat4rotz(float angle) {
        return {
            cosf(angle),  sinf(angle), 0.0f, 0.0f,
            -sinf(angle), cosf(angle), 0.0f, 0.0f,
            0.0f,         0.0f,        1.0f, 0.0f, 
            0.0f,         0.0f,        0.0f, 0.0f
        };
    }

}  // namespace util
