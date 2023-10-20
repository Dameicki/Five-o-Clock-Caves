#version 440

layout (points) in;
layout (line_strip, max_vertices = 100) out;

uniform vec3 size;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    
    gl_Position = projection * view * model * (gl_in[0].gl_Position + vec4(-size.x, -size.y, -size.z, 0.0));
    EmitVertex();

    gl_Position = projection * view * model * (gl_in[0].gl_Position + vec4(size.x, -size.y, -size.z, 0.0));
    EmitVertex();

    gl_Position = projection * view * model * (gl_in[0].gl_Position + vec4(size.x, -size.y, size.z, 0.0));
    EmitVertex();

    gl_Position = projection * view * model * (gl_in[0].gl_Position + vec4(-size.x, -size.y, size.z, 0.0));
    EmitVertex();

    gl_Position = projection * view * model * (gl_in[0].gl_Position + vec4(-size.x, -size.y, -size.z, 0.0));
    EmitVertex();

    gl_Position = projection * view * model * (gl_in[0].gl_Position + vec4(-size.x, size.y, -size.z, 0.0));
    EmitVertex();

    gl_Position = projection * view * model * (gl_in[0].gl_Position + vec4(size.x, size.y, -size.z, 0.0));
    EmitVertex();

    gl_Position = projection * view * model * (gl_in[0].gl_Position + vec4(size.x, size.y, size.z, 0.0));
    EmitVertex();

    gl_Position = projection * view * model * (gl_in[0].gl_Position + vec4(-size.x, size.y, size.z, 0.0));
    EmitVertex();

    gl_Position = projection * view * model * (gl_in[0].gl_Position + vec4(-size.x, size.y, -size.z, 0.0));
    EmitVertex();

    EndPrimitive();

    gl_Position = projection * view * model * (gl_in[0].gl_Position + vec4(size.x, size.y, -size.z, 0.0));
    EmitVertex();

    gl_Position = projection * view * model * (gl_in[0].gl_Position + vec4(size.x, -size.y, -size.z, 0.0));
    EmitVertex();

    EndPrimitive();

    gl_Position = projection * view * model * (gl_in[0].gl_Position + vec4(size.x, size.y, size.z, 0.0));
    EmitVertex();

    gl_Position = projection * view * model * (gl_in[0].gl_Position + vec4(size.x, -size.y, size.z, 0.0));
    EmitVertex();

    EndPrimitive();

    gl_Position = projection * view * model * (gl_in[0].gl_Position + vec4(-size.x, size.y, size.z, 0.0));
    EmitVertex();

    gl_Position = projection * view * model * (gl_in[0].gl_Position + vec4(-size.x, -size.y, size.z, 0.0));
    EmitVertex();

    EndPrimitive();
}