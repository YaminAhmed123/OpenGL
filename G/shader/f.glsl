#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

uniform vec3 lol;

void main()
{
    vec4 temp = texture(ourTexture, TexCoord);
    vec3 ranged = vec3(lol.x*lol.x, lol.y*lol.y, lol.z*lol.z);
    temp = vec4(temp.x-ranged.x, temp.y-ranged.y, temp.z-ranged.z, temp.w);
    FragColor = temp;
}