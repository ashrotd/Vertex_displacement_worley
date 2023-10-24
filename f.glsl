#version 410 core
out vec4 FragColor;

in vec3 ourPosition;
in vec2 TexCoord;

uniform sampler3D worleyTexture; // This will receive our 3D texture
uniform float time; // We'll use time to sample different layers of the texture

void main() {
    float noise = texture(worleyTexture, vec3(TexCoord, time)).r; // Sample the texture with time as the third coordinate
    //FragColor = vec4(vec3(noise), 1.0); 
    FragColor = texture(worleyTexture, ourPosition/2.0 + 0.5); // Apply the noise as a color
}
