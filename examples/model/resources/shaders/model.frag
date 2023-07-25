#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

//uniform sampler2D ourTexture;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

uniform sampler2D diffuseTexture;
//uniform sampler2D specularTexture;

void main()
{
    //ambient
    const float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    //diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0);

    //specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // result
    vec3 result = (ambient + diffuse) * vec3(texture(diffuseTexture, TexCoord)) + specular;
    //result += spec * vec3(texture(specularTexture, TexCoord));

    FragColor = vec4(result, 1.0);
}