#version 330 core

in vec2 UV;
in vec3 normal_Cameraspace;
in vec3 lightDirection_Cameraspace;
out vec3 color;

uniform sampler2D texSampler;

void main(){
	vec3 normalFragment = normalize(normal_Cameraspace);
	vec3 lightDirection = normalize(lightDirection_Cameraspace);
	float cosTheta = clamp(dot(normalFragment, lightDirection), 0, 1) *2;
	color = texture(texSampler, UV).rgb * cosTheta;
}