#version 460 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

out vec2 texCoord;
out vec3 vColor;

in vec3 color[1];
in vec3 pos[1];
in float vSize[1];

uniform mat4 projection;
float siu = 0.1;

void main()
{
    vColor = color[0];
    float size = vSize[0];
    mat4 m = projection;

    // Bottom left
    gl_Position = m * (vec4(-size,-size,size,0.0) + gl_in[0].gl_Position);
    texCoord = vec2(0.0,0.0);
    EmitVertex();

    // Bottom right
    gl_Position = m * (vec4(size,-size,size,0.0) + gl_in[0].gl_Position);
    texCoord = vec2(1.0,0.0);
    EmitVertex();

    // Top left
    gl_Position = m * (vec4(-size,size,size,0.0) + gl_in[0].gl_Position);
    texCoord = vec2(0.0,1.0);
    EmitVertex();

    // Top right
    gl_Position = m * (vec4(size,size,size,0.0) + gl_in[0].gl_Position);
    texCoord = vec2(1.0,1.0);
    EmitVertex();

    EndPrimitive();
}