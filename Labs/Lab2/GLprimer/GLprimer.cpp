/*
 * A C++ framework for OpenGL programming in TNM046 for MT1
 *
 * This is a small, limited framework, designed to be easy to use for students in an introductory
 * computer graphics course in the first year of a M Sc curriculum. It uses custom code for some
 * things that are better solved by external libraries like GLM, but the emphasis is on simplicity
 * andreadability, not generality.
 *
 * For the window management, GLFW 3.x is used for convenience.
 * The framework should work in Windows, MacOS X and Linux.
 * GLEW is used for handling platform specific OpenGL extensions.
 * This code depends only on GLFW, GLEW, and OpenGL libraries.
 * OpenGL 3.3 or higher is required.
 *
 * Authors: Stefan Gustavson (stegu@itn.liu.se) 2013-2015
 *          Martin Falk (martin.falk@liu.se) 2021
 *
 * This code is in the public domain.
 */
#if defined(WIN32) && !defined(_USE_MATH_DEFINES)
#define _USE_MATH_DEFINES
#endif

// File and console I/O for logging and error reporting
#include <iostream>
// Math header for trigonometric functions
#include <cmath>

// glew provides easy access to advanced OpenGL functions and extensions
#include <GL/glew.h>

// GLFW 3.x, to handle the OpenGL window
#include <GLFW/glfw3.h>

#include "Utilities.hpp"

#include <vector>
#include <array>
#include "Shader.hpp"


GLuint createVertexBuffer(int location, int dimensions, const std::vector<GLfloat>& vertices) {
    GLuint bufferID = 0;
    // Generate buffer, activate it and copt the data
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(),
                 GL_STATIC_DRAW);
    // Tell OpenGL how the data is stored in our buffer
    // Attribute location (must match layout(location=#) statment in shader)
    // Number of dimensions (3 -> vec3 in the shader, 2-> vec2 in the shader),
    // type GL_FOAT, not normalized, stride 0, start at element 0
    glVertexAttribPointer(location, dimensions, GL_FLOAT, GL_FALSE, 0, nullptr);
    // Enable the attribute to the currently bound VAO
    glEnableVertexAttribArray(location);

    return bufferID;
}

GLuint createIndexBuffer(const std::vector<GLuint>& indicies) { 
    GLuint bufferID = 0;
    //Generate buffer, activate it and copy the data
    glGenBuffers(1, &bufferID);
    //Activate (bind) the index buffer and copy data to it.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
    //Present our vertex indicies to OpenGL
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(GLuint), indicies.data(),
                 GL_STATIC_DRAW);

    return bufferID;
}

/*
 * main(int argc, char* argv[]) - the standard C++ entry point for the program
 */
int main(int, char*[]) {
    // Vertex coordinates (x,y,z) for three vertices
    const std::vector<GLfloat> vertexArrayData = {
        -1.0f, -1.0f, 0.0f, // First vertex, xyz
        1.0f, -1.0f, 0.0f,  // Second vertex, xyz
        0.0f, 1.0f, 0.0f    // Third vertex, xyz
    };

    const std::vector<GLuint> indexArrayData = {0, 1, 2};

    const std::vector<GLfloat> colorArrayData = {
        1.0f, 0.5f, 0.0f, // Orange
        0.0f, 1.0f, 0.0f, // Green
        0.5f, 0.0f, 1.0f  // Purple
    };

    const std::vector<GLfloat> cubeVertexArrayData = {
        -1.0f, -1.0f, -1.0f,  // p0
        -1.0f, -1.0f, 1.0f,   // p1
        -1.0f, 1.0f,  1.0f,   // p2
        -1.0f, 1.0f,  -1.0f,  // p3
        1.0f,  -1.0f, -1.0f,  // p4
        1.0f,  -1.0f, 1.0f,   // p5
        1.0f,  1.0f,  1.0f,   // p6
        1.0f,  1.0f,  -1.0f   // p7
    };

    const std::vector<GLuint> cubeIndexArrayData = {
        0, 1, 3,  // t0
        1, 2, 3,  // t1
        4, 0, 7,  // t2
        0, 3, 7,  // t3
        5, 4, 6,  // t4
        4, 7, 6,  // t5
        1, 5, 2,  // t6
        5, 6, 2,  // t7
        3, 2, 7,  // t8
        2, 6, 7,  // t9
        1, 0, 5,  // t10
        0, 4, 5   // t11
    };

    const std::vector<GLfloat> cubeColorArrayData = {
        1.0f, 0.0f, 0.0f,  // Red
        0.0f, 1.0f, 0.0f,  // Green
        0.0f, 0.0f, 1.0f,  // Blue

        1.0f, 0.5f, 0.0f,  // Orange
        0.0f, 1.0f, 0.0f,  // Green
        0.5f, 0.0f, 1.0f,  // Purple

        0.5f, 0.5f, 0.5f,  // Brown?
        1.0f, 1.0f, 1.0f,  // White
        0.0f, 0.0f, 0.0f,  // Black

        1.0f, 1.0f, 0.0f,  // ?
        0.0f, 1.0f, 1.0f,  // ?
        1.0f, 0.0f, 1.0f,  // ?
    };

    std::array<GLfloat, 16> matT = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f
    };

    std::array<GLfloat, 16> matR = {
        -1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    // View transpose (scale & rotation)
    const std::array<GLfloat, 16> matViev = util::mat4mult(util::mat4scale(0.05), util::mat4rotx(M_PI / 4));

    // Translate cube (along x)
    const std::array<GLfloat, 16> matTranslate = util::mat4translate(18, 0, 0);

    Shader myShader;

    // Initialise GLFW
    glfwInit();

    const GLFWvidmode* vidmode;  // GLFW struct to hold information about the display
    // Determine the desktop size
    vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    // Make sure we are getting a GL context of at least version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Enable the OpenGL core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Open a square window (aspect 1:1) to fill half the screen height
    GLFWwindow* window =
        glfwCreateWindow(vidmode->height / 2, vidmode->height / 2, "GLprimer", nullptr, nullptr);
    if (!window) {
        std::cout << "Unable to open window. Terminating.\n";
        glfwTerminate();  // No window was opened, so we can't continue in any useful way
        return -1;
    }

    // Make the newly created window the "current context" for OpenGL
    // (This step is strictly required or things will simply not work)
    glfwMakeContextCurrent(window);

    // Initialize glew
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cerr << "Error: " << glewGetErrorString(err) << "\n";
        glfwTerminate();
        return -1;
    }

    // Generate 1 Vertex array object, put the resulting identifier in vertexArrayID
    GLuint vertexArrayID = 0;
    glGenVertexArrays(1, &vertexArrayID);
    // Activate the vertex buffer object
    glBindVertexArray(vertexArrayID);

    //Create the vertex buffer objects for attribute locations 0 and 1
    //(the list of vertex coordinates and the list of vertex colors)
    GLuint vertexBufferID = createVertexBuffer(0, 3, cubeVertexArrayData);
    GLuint colorBufferID = createVertexBuffer(1, 3, cubeColorArrayData);
    //Create the index buffer object (the list of triangles)
    GLuint indexBufferID = createIndexBuffer(cubeIndexArrayData);

    //Deactivate the vertex array object again to be nice
    glBindVertexArray(0);

    myShader.createShader("vertex.glsl", "fragment.glsl");

    //Time uniform variable
    GLint locationTime = glGetUniformLocation(myShader.id(), "time");
    if (locationTime == -1) {
        std::cout << "Unable to locate variable 'time' in shader!\n";
    }

    // Show some useful information on the GL context
    std::cout << "GL vendor:       " << glGetString(GL_VENDOR)
              << "\nGL renderer:     " << glGetString(GL_RENDERER)
              << "\nGL version:      " << glGetString(GL_VERSION)
              << "\nDesktop size:    " << vidmode->width << " x " << vidmode->height << "\n";

    // Get window size. It may start out different from the requested size and
    // will change if the user resizes the window
    int width, height;

    glfwSwapInterval(0);  // Do not wait for screen refresh between frames

    glEnable(GL_CULL_FACE);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        util::displayFPS(window);

        glfwGetWindowSize(window, &width, &height);
        // Set viewport. This is the pixel rectangle we want to draw into
        glViewport(0, 0, width, height);  // The entire window

        // Set the clear color to a dark gray (RGBA)
        glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
        // Clear the color and depth buffers for drawing
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float time = static_cast<float>(glfwGetTime()); // Number of seconds since the program was started
        glUseProgram(myShader.id());                    // Activate the shader to set its variables
        glUniform1f(locationTime, time);                // Copy the value to the shader
        //std::cout << time << "\n";
        
        /*
        GLint locationRx = glGetUniformLocation(myShader.id(), "Rx");
        glUseProgram(myShader.id());
        glUniformMatrix4fv(locationRx, 1, GL_FALSE, util::mat4rotx(M_PI/4).data());
        */
        GLint locationRy = glGetUniformLocation(myShader.id(), "Ry");
        //glUseProgram(myShader.id());
        glUniformMatrix4fv(locationRy, 1, GL_FALSE, util::mat4roty(time/24).data());  // 2PI revolutions?
        /*
        GLint locationRz = glGetUniformLocation(myShader.id(), "Rz");
        glUseProgram(myShader.id());
        glUniformMatrix4fv(locationRz, 1, GL_FALSE, util::mat4rotz(M_PI/4).data());
        */


        std::array<GLfloat, 16> planeT = {util::mat4mult(
            matViev, util::mat4mult(                            // V * (R_Orbit * (T * R_spin))
                util::mat4roty(-time), util::mat4mult(           // R_Orbit * (T * R_spin)
                    matTranslate, util::mat4roty(time * 6))))   // T * R_spin
        };

        GLint locationT = glGetUniformLocation(myShader.id(), "T");
        glUseProgram(myShader.id());
        glUniformMatrix4fv(locationT, 1, GL_FALSE, planeT.data());

        /* ---- Rendering code should go here ---- */

        glUseProgram(myShader.id());

        // Activate the certex array object we want to draw
        glBindVertexArray(vertexArrayID);
        // Draw our triangle with 3 vertices.
        // When the last argument of glDrawElements is nullptr, it means
        // "use the previously bound index buffer". (This is not obvious.)
        // The index buffer is part of the VAO state and is bound with it.

        // BACK AND FRONT FACE CULLING WORKS, but is this method correct?

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // Render both sides with GL_FILL
        glCullFace(GL_BACK);                        // Cull backside?
        
        
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Render both sides with GL_LINE
        glCullFace(GL_FRONT);                       // Cull frontside line render?
        

        // Swap buffers, display the image and prepare for next frame
        glfwSwapBuffers(window);

        // Poll events (read keyboard and mouse input)
        glfwPollEvents();


        // Exit if the ESC key is pressed (and also if the window is closed)
        if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }

    // release the vertex and index buffers as well as the vertex array
    glDeleteVertexArrays(1, &vertexArrayID);
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteBuffers(1, &indexBufferID);
    //release the color buffers
    glDeleteBuffers(1, &colorBufferID);

    // Close the OpenGL window and terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
}
