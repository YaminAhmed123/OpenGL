#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

uniform vec3 lol;

void main()
{
    vec4 temp = texture(ourTexture, TexCoord);
    temp = vec4(temp.x+lol.x, temp.y+lol.y, temp.z+lol.z, temp.w);
    FragColor = temp;
}