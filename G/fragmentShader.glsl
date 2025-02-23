#version 330 core
out vec4 FragColor;  
in vec3 ourColor;

uniform float offset1;
uniform float offset2;
uniform float offset3;

void main()
{
    vec3 temp = vec3(ourColor.x+offset2, ourColor.y+offset3, ourColor.z+offset1);
    FragColor = vec4(temp, 1.0f);
}