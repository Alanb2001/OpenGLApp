#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <ostream>

#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow* window);

float mixValue = 0.2f;

// A rectangle
static float vertices[] =
    {
    // Positions
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
       0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

glm::vec3 cubePositions[] =
    {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

int main()
{
    // Tell glfw what version of OpenGL we are using as well as what profile we want to use
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window data with glfw
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGLApp", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << '\n';
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Let glad load the address of OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << '\n';
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);
    
    Shader ourShader("VertShader.txt", "FragShader.txt");
    
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("Textures/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture." << "\n";
    }
    
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("Textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture." << "\n";
    }

    stbi_image_free(data);

    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);
    
    // Render loop of the window context
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.5f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        ourShader.use();
        
        ourShader.setFloat("mixValue", mixValue);

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        
        glBindVertexArray(vao);
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            if (i % 3 == 0)
            {
                angle = glfwGetTime() * 25.0f;
            }
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    
    glfwTerminate();
    return 0;
}

// Checks to see if the window context has been resized
void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
    glViewport(0, 0, width, height);
}

// Checks to see if a key has been pressed by the user
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        mixValue += 0.001f;
        if (mixValue >= 1.0f)
        {
            mixValue = 1.0f;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        mixValue -= 0.001f;
        if (mixValue <= 0.0f)
        {
            mixValue = 0.0f;
        }
    }
}