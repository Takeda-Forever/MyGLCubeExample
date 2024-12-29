#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <string>
using std::pair;
using std::vector;

using pair_d = pair<double, double>;

void CheckGLError()
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
        case GL_INVALID_ENUM:
            error = "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            error = "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            error = "GL_INVALID_OPERATION";
            break;
        case GL_STACK_OVERFLOW:
            error = "GL_STACK_OVERFLOW";
            break;
        case GL_STACK_UNDERFLOW:
            error = "GL_STACK_UNDERFLOW";
            break;
        case GL_OUT_OF_MEMORY:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "Unknown OpenGL error.";
            break;
        }

        throw "OpenGL Error [" + std::to_string(errorCode) + "]: " + error + '\n';
    }
}


int main(void)
{
    GLFWwindow* window;
    if (!glfwInit())
        CheckGLError();


    // L - Left             p1 *----* p4
    // R - Right               |    |
    // T - Top              p2 *----* p3
    // B - Bottom
    vector<pair_d> Pointers
    {
        pair_d(NULL, NULL),
        pair_d(-0.5, 0.5  ), // Point 1 - LT
        pair_d(-0.5, -0.5 ), // Point 2 - LB
        pair_d(0.5 , -0.5 ), // Point 3 - RB
        pair_d(0.5 , 0.5  ), // Point 4 - RT
    };

    
    auto pt_x = [&Pointers](int ord)
                { return Pointers[ord].first; };

    auto pt_y = [&Pointers](int ord)
        { return Pointers[ord].second; };

    auto add_p = [&Pointers = Pointers](double x, double y)
        {
            return Pointers.push_back(pair_d(x, y));
        };

    add_p(pt_x(1) + 0.2, pt_y(1) + 0.1); // Pointer 5
    add_p(pt_x(4) + 0.2, pt_y(4) + 0.1); // Pointer 6
    add_p(pt_x(3) + 0.2, pt_y(3) + 0.1); // Pointer 7

    auto crTriangle = [&](int p1, int p2, int p3, int color = 4)
        {
            int red   = (color == 1 || color == 4) ? 1 : 0;
            int green = (color == 2 || color == 4) ? 1 : 0;
            int blue  = (color == 3 || color == 4) ? 1 : 0;
            glColor3f(red, green, blue);
            glBegin(GL_TRIANGLES);
            glVertex2d(pt_x(p1), pt_y(p1));
            glVertex2d(pt_x(p2), pt_y(p2));
            glVertex2d(pt_x(p3), pt_y(p3));
            glEnd();
        };


    window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        CheckGLError();
    }


    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        // Cube's front side
        crTriangle(1, 2, 3, 1); 
        crTriangle(1, 3, 4, 1);

        // Cube's top side
        crTriangle(1, 5, 4, 2);
        crTriangle(4, 5, 6, 2);

       // Cube's right side
        crTriangle(4, 6, 3, 3);
        crTriangle(6, 7, 3, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return EXIT_SUCCESS;
}
