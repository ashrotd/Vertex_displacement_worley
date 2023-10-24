#version 410 core

in vec2 texCoord_TESout; // From tessellation evaluation shader
in vec3 FragPos;         // Fragment position, need to be passed from earlier shader stage
in vec3 Normal;          // Normal, need to be passed from an earlier shader stage

out vec4 color;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    sampler2D diffuse;   // We use the texture as a diffuse component of the material
    vec3 specular;       // Specular color
    float shininess;
};

uniform Light light;       // The properties of the light in the scene
uniform Material material; // The properties of the material of the object
uniform vec3 viewPos;      // The position of the camera/viewer
uniform mat4 mvp_matrix;   // Model-view-projection matrix

void main()
{
    // Ambient light component
    vec3 ambient = light.ambient * texture(material.diffuse, texCoord_TESout).rgb; // Using the texture color

    // Diffuse light component
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texCoord_TESout).rgb; // Using the texture color

    // Specular light component
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * material.specular;

    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0);
}
