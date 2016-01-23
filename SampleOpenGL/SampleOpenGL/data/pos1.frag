#version 330 core

in vec2 TexCoord;

out vec4 outputColor;

uniform sampler2D myTexture1;
uniform sampler2D myTexture2;

void main()
{
 outputColor = mix(texture(myTexture1, TexCoord), texture(myTexture2,TexCoord), 0.2);  
}