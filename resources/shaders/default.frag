#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Imports the current position from the Vertex Shader
in vec3 crntPos;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;

// Gets the Texture Units from the main function
uniform sampler2D diffuse0;
uniform sampler2D specular0;
// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;

uniform uint type;


vec4 pointLight(){

    vec3 lightVec = lightPos - crntPos;
    float dist = length(lightVec);
    float a = 3.0f;
    float b = 0.7f;
    float intensity = 1.0f / (a * dist * dist + b * dist + 1.0f);

    float ambient = 0.2f;

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightVec);

    float diffuse = max(dot(normal, lightDirection), 0.0f);
    float specLight = 0.50f;
    vec3 viewDir = normalize(camPos - crntPos);

    vec3 reflecDir = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDir, reflecDir), 0.0f), 16);
    float specular = specAmount * specLight;

    return texture(diffuse0, texCoord)  * (diffuse * intensity + ambient)  + (texture(specular0, texCoord).r * specular * intensity) * lightColor;

}

vec4 directionalLight(){
    // ambient lighting
    float ambient = 0.20f;

    // diffuse lighting
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    // specular lighting
    float specularLight = 0.50f;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
    float specular = specAmount * specularLight;

    return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 spotLight()
{
    // controls how big the area that is lit up is
    float outerCone = 0.90f;
    float innerCone = 0.95f;

    // ambient lighting
    float ambient = 0.20f;

    // diffuse lighting
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - crntPos);
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    // specular lighting
    float specularLight = 0.50f;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
    float specular = specAmount * specularLight;

    // calculates the intensity of the crntPos based on its angle to the center of the light cone
    float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
    float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

    return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}


void main()
{
    if (type == 0u) FragColor = pointLight();
    else if (type == 1u) FragColor = spotLight();
    else FragColor = directionalLight();
}