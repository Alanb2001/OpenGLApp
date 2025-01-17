#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <ostream>

#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Shader.h"
#include "stb_image.h"

//const static char* fragment_shader_source2 =
//    "#version 330 core\n"
//    "out vec4 FragColour;\n"
//    "void main()\n"
//    "{\n"
//    "   FragColour = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
//    "}\n";

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow* window);

// Single triangle
//static float vertices[] =
//    {
//    // Positions             // Colours
//         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 
//        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
//         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
//    };

//static float vertices[] =
//    {
//    // First triangle
//        0.0f,  -0.5f, 0.0f,
//        1.0f,  -0.5f, 0.0f,
//        0.5f,  0.5f, 0.0f,
//
//    //Second triangle
//       -1.0f, -0.5f, 0.0f,
//        0.0f, -0.5f, 0.0f,
//       -0.5f,  0.5f, 0.0f    
//    };

//tatic float vertices[] =
//   {
//   // First triangle
//       // Positions        // Colours
//       0.0f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
//       1.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
//       0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
//   };

//tatic float vertices2[] =
//   {
//   //Second triangle
//      -1.0f, -0.5f, 0.0f,
//       0.0f, -0.5f, 0.0f,
//      -0.5f,  0.5f, 0.0f   
//   };

// A rectangle
static float vertices[] =
    {
    // Positions         // Colours         // Texture coords
     0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f
    };

unsigned int indices[] =
    {
        0, 1, 3,
        1, 2, 3
    };

//loat textCoords[] =
//   {
//       0.0f, 0.0f,
//       1.0f, 0.0f,
//       0.5f, 1.0f
//   };

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

    Shader ourShader("VertShader.txt", "FragShader.txt");

   // const unsigned int fragment_shader2 = glCreateShader(GL_FRAGMENT_SHADER);
   // glShaderSource(fragment_shader2, 1,  &fragment_shader_source2, nullptr);
   // glCompileShader(fragment_shader2);
//
   // glGetShaderiv(fragment_shader2, GL_COMPILE_STATUS, &success);
//
   // if (!success)
   // {
   //     char info_log[512];
   //     glGetShaderInfoLog(fragment_shader2, 512, nullptr, info_log);
   //     std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << '\n';
   // }
//
   // const unsigned int shaderProgramYellow = glCreateProgram();
   // glAttachShader(shaderProgramYellow, vertex_shader);
   // glAttachShader(shaderProgramYellow, fragment_shader2);
   // glLinkProgram(shaderProgramYellow);
//
   // glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &success);
//
   // if (!success)
   // {
   //     char info_log[512];
   //     glGetProgramInfoLog(shaderProgramYellow, 512, nullptr, info_log);
   //     std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << '\n';
   // }
    
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    //unsigned int vaos[2], vbos[2];
    //glGenVertexArrays(2, vaos);
    //glGenBuffers(2, vbos);
    //
    //glBindVertexArray(vaos[0]);
    //glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
//
    //glBindVertexArray(vaos[1]);
    //glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
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
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture." << "\n";
    }

    stbi_image_free(data);

    ourShader.use();
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    ourShader.setInt("texture2", 1);
    
    // Render loop of the window context
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.5f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //loat timeValue = glfwGetTime();
        //loat greenValue = sin(timeValue) / 2.0f + 0.5f;
        //int vertexColourLocation = glGetUniformLocation(shaderProgramOrange, "ourColour");
        //float offset = 0.5f;
        //ourShader.setFloat("xOffset", offset);
        //glUniform4f(vertexColourLocation, 0.0f, greenValue, 0.0f, 1.0f);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        
        //glUseProgram(shaderProgramYellow);
        //glBindVertexArray(vaos[1]);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        ourShader.use();
        glBindVertexArray(vao);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glBindVertexArray(0);

        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    //glDeleteProgram(shaderProgramOrange);
    //glDeleteProgram(shaderProgramYellow);
    
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
}