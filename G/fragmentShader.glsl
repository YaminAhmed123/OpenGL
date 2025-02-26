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
    vec4 temp = texture(ourTexture, -TexCoord);
    vec4 res = vec4(temp.x+x,temp.y+y,temp.z+z,temp.w);
    FragColor = res;
}