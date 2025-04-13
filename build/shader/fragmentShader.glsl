#version 330 core
out vec4 FragColor;


uniform sampler2D ourTexture;

uniform vec3 lol;

void main()
{
    vec4 temp = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    temp = vec4(temp.x+lol.x, temp.y+lol.y, temp.z+lol.z, temp.w);
    FragColor = temp;
}