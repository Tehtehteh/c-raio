#version 330 core
in vec3 VertexColor;
in vec4 Position;
in vec2 TexPos;

out vec4 FragColor;

uniform sampler2D Texture;
uniform sampler2D Texture2;
uniform float u_mix;


void main() {
    FragColor = mix(texture(Texture, TexPos), texture(Texture2, vec2(1.0 - TexPos.x, 1.0 - TexPos.y)), u_mix);
}
