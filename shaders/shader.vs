#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vertexColor;
out vec3 vPos;
uniform float offset;

void main()
  {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = aColor;
    vPos = vec3(gl_Position.x, gl_Position.y, gl_Position.z);
  }

