#version 410 core
layout (location = 0) in vec3 aPos; // Vertex position
layout (location = 1) in vec2 aTexCoord; // Texture coordinate per vertex

out vec2 TexCoord; // Texture coordinate for fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time; // Uniform for time to animate the vertex positions
out vec3 ourPosition;
void main()
{
    // Create a simple wave effect by manipulating the vertex positions
    float wave = sin(5.0 * aPos.x + time); // This creates a wave effect based on the x position and time
    vec3 newPosition = vec3(aPos.x, aPos.y + wave * 0.1, aPos.z); // We are adding the wave effect to the y position

    gl_Position = projection * view * model * vec4(newPosition, 1.0); // Transform the vertex position
    TexCoord = aTexCoord;
    ourPosition = vec3(model * vec4(aPos, 1.0));
     // Pass the texture coordinate to the fragment shader
}
