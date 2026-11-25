#ifndef SHADER_H
#define SHADER_H
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include <string>

namespace GraphicsGL {
  class Shader {
  public:
  unsigned int ID;
  Shader(const char *vertexPath, const char *fragmentPath);
  void use();
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setMatrix4(const std::string &name, const glm::mat4& mat, bool transpose) const;
  };
}
#endif
