#version 330 core
out vec4 FragColor;  
in vec3 ourColor;

uniform float offset1; // uniform offset values
uniform float offset2; // the reason why its a uniform is because we want to change it from the CPU
uniform float offset3; // also we do not have a function implememnted called Uniform3f or 4f or fv to change a unifrom like that since thats missing in
// in the header file so it has to be done like this in the first place also i dont have time right now i will do it later for the render engine
// and when i have the PC it will be blazingly fast

void main()
{
    vec3 temp = vec3(ourColor.x+offset1, ourColor.y+offset2, ourColor.z+offset3);
    FragColor = vec4(temp, 1.0f);
}