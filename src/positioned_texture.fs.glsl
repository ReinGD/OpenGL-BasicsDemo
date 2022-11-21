#version 330 core

//uniform
uniform sampler2D ourTexture;

//output
out vec4 FragColor;
  
//input
in VS_OUT
{
    vec2 TexCoord;
} fs_in;


void main()
{
    FragColor = texture(ourTexture, fs_in.TexCoord);
}
