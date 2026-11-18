#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.h>

namespace {
float kVertices1[] = { 
        // positions       // colors
        -0.5, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f
    };

    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    void processInput(GLFWwindow* window) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
    unsigned int createProgram(const char* vsSrc, const char* fsSrc) {
      
    }

    void APIENTRY debugCallback(GLenum source, GLenum type, GLuint id,
        GLenum severity, GLsizei length,
        const GLchar* message, const void* userParam) {
        // Skip noisy driver notifications (e.g. buffer memory info)
        if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;

        const char* srcStr = "Unknown";
        switch (source) {
        case GL_DEBUG_SOURCE_API:             srcStr = "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   srcStr = "Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: srcStr = "Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     srcStr = "Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     srcStr = "Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           srcStr = "Other"; break;
        }

        const char* typeStr = "Unknown";
        switch (type) {
        case GL_DEBUG_TYPE_ERROR:               typeStr = "Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeStr = "Deprecated"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  typeStr = "Undefined Behavior"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         typeStr = "Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         typeStr = "Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              typeStr = "Marker"; break;
        case GL_DEBUG_TYPE_OTHER:               typeStr = "Other"; break;
        }

        const char* sevStr = "Unknown";
        switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:   sevStr = "HIGH"; break;
        case GL_DEBUG_SEVERITY_MEDIUM: sevStr = "MEDIUM"; break;
        case GL_DEBUG_SEVERITY_LOW:    sevStr = "LOW"; break;
        }

        std::cerr << "[GL " << sevStr << "] " << typeStr << " (" << srcStr
            << ", id " << id << "): " << message << std::endl;
    }

    void setupDebugOutput() {
        GLint flags = 0;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (!(flags & GL_CONTEXT_FLAG_DEBUG_BIT)) {
            std::cout << "Debug context not available; GL debug output disabled" << std::endl;
            return;
        }

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);   // callback fires inside the offending call
        glDebugMessageCallback(debugCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
}

namespace GraphicsGL {
	int run() {
        if (!glfwInit()) {
            std::cout << "Failed to initialize GLFW" << std::endl;
            return -1;
        }
        
        // Initialize Window
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS
#endif
        GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
        if (window == NULL) {
            std::cout << "Failed to create window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // initialize GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            glfwDestroyWindow(window);
            glfwTerminate();
            return -1;
        }

	if (glDebugMessageCallback) {
	  setupDebugOutput();
	}

        int fbw, fbh;
        glfwGetFramebufferSize(window, &fbw, &fbh);
        glViewport(0, 0, fbw, fbh);

        Shader shader("shaders/shader.vs", "shaders/shader.fs");

        unsigned int VAO1, VBO1;
        glGenVertexArrays(1, &VAO1);
        glGenBuffers(1, &VBO1);

        glBindVertexArray(VAO1);

        // VBO1
        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(kVertices1), kVertices1, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
        // main loop
        while (!glfwWindowShouldClose(window)) {
            processInput(window);

            // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
	    shader.use();            
	    shader.setFloat("offset", 0.5);

            glBindVertexArray(VAO1);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwPollEvents();
            glfwSwapBuffers(window);
        }
        glDeleteVertexArrays(1, &VAO1);
        glDeleteBuffers(1, &VBO1);
        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
	}
}
