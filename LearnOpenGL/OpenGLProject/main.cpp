#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource =
    "#version 330 core\n"
    "layout(location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\n\0";

const char* firstTriangleFragmentShaderSource =
    "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "   color = vec4(0.2f, 0.9f, 0.2f, 1.0f);"
    "}\n\0";

const char* secondTriangleFragmentShaderSource =
    "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "   color = vec4(0.9f, 0.2f, 0.2f, 1.0f);"
    "}\n\0";

int main() 
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // WINDOW CREATION
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // LOAD ALL OPENGL FUNCTION POINTERS
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int firstFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(firstFragmentShader, 1, &firstTriangleFragmentShaderSource, NULL);
    glCompileShader(firstFragmentShader);

    unsigned int secondFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(secondFragmentShader, 1, &secondTriangleFragmentShaderSource, NULL);
    glCompileShader(secondFragmentShader);

    unsigned int firstShaderProgram = glCreateProgram();
    glAttachShader(firstShaderProgram, vertexShader);
    glAttachShader(firstShaderProgram, firstFragmentShader);
    glLinkProgram(firstShaderProgram);

    unsigned int secondShaderProgram = glCreateProgram();
    glAttachShader(secondShaderProgram, vertexShader);
    glAttachShader(secondShaderProgram, secondFragmentShader);
    glLinkProgram(secondShaderProgram);

    float firstTriangleVertices[] =
    {
        -0.9f, -0.5f, 0.0f,
        -0.0f, -0.5f, 0.0f,
        -0.45f, 0.5f, 0.0f
    };

    float secondTriangleVertices[] =
    {
         0.0f, -0.5f, 0.0f,
         0.9f, -0.5f, 0.0f,
         0.45f, 0.5f, 0.0f
    };
   
    unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    //=====First Triangle=====
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangleVertices), firstTriangleVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //=====Second Triangle=====
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangleVertices), secondTriangleVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    // RENDER LOOP
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);        

        glClearColor(1.7f, 1.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(firstShaderProgram);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(secondShaderProgram);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(firstShaderProgram);
    glDeleteProgram(secondShaderProgram);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}