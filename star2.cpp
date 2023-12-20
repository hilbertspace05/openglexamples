#include <GLFW/glfw3.h>
#include <cmath>

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Star properties
float starPosX = 0.0f, starPosY = 0.0f;
float starVelX = 0.007f, starVelY = 0.005f;
const float starSize = 0.1f;

void drawStar(float centerX, float centerY, float size) {
    const int numPoints = 5;
    glBegin(GL_TRIANGLE_FAN);
    
    // Center of the star
    glVertex2f(centerX, centerY);

    for (int i = 0; i <= 2 * numPoints; i++) {
        // Calculate angle and radius
        float angle = i * M_PI / numPoints;
        float radius = (i % 2 == 0) ? size : size / 2;

        float x = centerX + radius * sin(angle);
        float y = centerY + radius * cos(angle);

        glVertex2f(x, y);
    }

    glEnd();
}

void updateStarPosition() {
    // Update position based on velocity
    starPosX += starVelX;
    starPosY += starVelY;

    // Collision detection with walls
    if (starPosX + starSize > 1.0f || starPosX - starSize < -1.0f) {
        starVelX = -starVelX; // Reverse the horizontal velocity
        starPosX += starVelX; // Move star back in bounds to prevent sticking to the wall
    }
    if (starPosY + starSize > 1.0f || starPosY - starSize < -1.0f) {
        starVelY = -starVelY; // Reverse the vertical velocity
        starPosY += starVelY; // Move star back in bounds to prevent sticking to the wall
    }
}

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Bouncing Star", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        updateStarPosition();
        drawStar(starPosX, starPosY, starSize);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
