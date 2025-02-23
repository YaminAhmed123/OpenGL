#version 330 core
out vec4 FragColor;  
in vec3 ourColor;

uniform float offset1;
uniform float offset2;
uniform float offset3;

void main()
{
    vec3 temp = vec3(ourColor.x+offset1, ourColor.y+offset2, ourColor.z+offset3);
    FragColor = vec4(temp, 1.0f);
}