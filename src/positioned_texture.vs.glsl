#version 330 core

//uniforms
uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

//attributes
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

//output
out VS_OUT
{
    out vec2 TexCoord;
}vs_out;

void main()
{
    gl_Position = proj_matrix * view_matrix * world_matrix * vec4(aPos, 1.0);
    vs_out.TexCoord = aTexCoord;
}
