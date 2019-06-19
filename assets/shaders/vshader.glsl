#version 330 core
layout (location=0) in vec3 in_Pos;
layout (location=1) in vec3 in_Color;
layout (location=2) in vec2 in_TexPos;

out vec3 VertexColor;
out vec4 Position;
out vec2 TexPos;

uniform float H_Offset;

void main() {
    VertexColor = in_Color;
    TexPos = in_TexPos;
    Position = vec4(in_Pos.x, in_Pos.y, in_Pos.z, 1.0f);
    gl_Position = Position;
}