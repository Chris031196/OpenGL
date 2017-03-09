#version 330 core

in vec2 UV;
in vec3 normal_Cameraspace;
in vec3 lightDirection_Cameraspace;
in float distanceToLight;
in float drawTail;
out vec4 color;

uniform sampler2D texSampler;

void main(){
	if(drawTail == 0){
		vec3 normalFragment = normalize(normal_Cameraspace);
		vec3 lightDirection = normalize(lightDirection_Cameraspace);
		float cosTheta = clamp(dot(normalFragment, lightDirection), 0, 1) *2;
		color.rgb = texture(texSampler, UV).rgb * cosTheta;
	}
	else {
		color.r = 0.0f;
		color.g = 0.0f;
		color.b = 1.0f;
		color.a = 1.0f;
	}
}