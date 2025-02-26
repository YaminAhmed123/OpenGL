#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;       // that shit gets ignored cause it would overwrite the tex colors 
in vec2 TexCoord;                       // they might left it there so we dont fuck up our code structure for later prjs

uniform sampler2D ourTexture;

//utility unifroms
uniform float x;
uniform float y;
uniform float z;


void main()
{
    vec3 temp = vec3(ourColor.x-offset1, ourColor.y-offset2, ourColor.z-offset3);
    FragColor = vec4(temp, 1.0f);
}