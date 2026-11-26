#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>
#include <debug.hpp>

namespace {
void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id,
                            GLenum severity, GLsizei length,
                            const GLchar *message, const void *userParam) {
  // Skip noisy driver notifications (e.g. buffer memory info)
  if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
    return;

  const char *srcStr = "Unknown";
  switch (source) {
  case GL_DEBUG_SOURCE_API:
    srcStr = "API";
    break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
    srcStr = "Window System";
    break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER:
    srcStr = "Shader Compiler";
    break;
  case GL_DEBUG_SOURCE_THIRD_PARTY:
    srcStr = "Third Party";
    break;
  case GL_DEBUG_SOURCE_APPLICATION:
    srcStr = "Application";
    break;
  case GL_DEBUG_SOURCE_OTHER:
    srcStr = "Other";
    break;
  }

  const char *typeStr = "Unknown";
  switch (type) {
  case GL_DEBUG_TYPE_ERROR:
    typeStr = "Error";
    break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    typeStr = "Deprecated";
    break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    typeStr = "Undefined Behavior";
    break;
  case GL_DEBUG_TYPE_PORTABILITY:
    typeStr = "Portability";
    break;
  case GL_DEBUG_TYPE_PERFORMANCE:
    typeStr = "Performance";
    break;
  case GL_DEBUG_TYPE_MARKER:
    typeStr = "Marker";
    break;
  case GL_DEBUG_TYPE_OTHER:
    typeStr = "Other";
    break;
  }

  const char *sevStr = "Unknown";
  switch (severity) {
  case GL_DEBUG_SEVERITY_HIGH:
    sevStr = "HIGH";
    break;
  case GL_DEBUG_SEVERITY_MEDIUM:
    sevStr = "MEDIUM";
    break;
  case GL_DEBUG_SEVERITY_LOW:
    sevStr = "LOW";
    break;
  }

  std::cerr << "[GL " << sevStr << "] " << typeStr << " (" << srcStr << ", id "
            << id << "): " << message << std::endl;
}
}
void setupDebugOutput() {
  GLint flags = 0;
  glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
  if (!(flags & GL_CONTEXT_FLAG_DEBUG_BIT)) {
    std::cout << "Debug context not available; GL debug output disabled"
              << std::endl;
    return;
  }

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(
      GL_DEBUG_OUTPUT_SYNCHRONOUS); // callback fires inside the offending call
  glDebugMessageCallback(debugCallback, nullptr);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr,
                        GL_TRUE);
}
