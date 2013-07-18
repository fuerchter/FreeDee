#version 150

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

in vec3 position;
in vec3 normal;
in vec2 texCoord;

out vec3 fragPosition;
out vec3 fragNormal;
out vec2 fragTexCoord;

void main() {
	fragPosition=position;
	fragNormal=normal;
	fragTexCoord=texCoord;
	
	gl_Position = projection*view*model* vec4(position, 1);
}