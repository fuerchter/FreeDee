#version 150

uniform vec3 lightPosition;
uniform vec3 lightColor;

uniform mat4 model;

uniform vec3 diffuse;
uniform sampler2D diffuseTex;

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 finalColor; //this is the output color of the pixel

void main() {
	mat3 normalMatrix = transpose(inverse(mat3(model)));
	vec3 normal = normalize(normalMatrix * fragNormal);
	
	vec3 fragPosition = vec3(model * vec4(fragPosition, 1));
	vec3 surfaceToLight = normalize(lightPosition - fragPosition);
	
	float brightness = max(dot(normal, surfaceToLight), 0);
	finalColor=brightness* vec4(lightColor, 1)* vec4(diffuse, 1.0);
	finalColor=brightness* vec4(lightColor, 1)* texture(diffuseTex, fragTexCoord);
}