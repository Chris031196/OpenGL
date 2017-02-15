#version 330 core
layout(location = 0) in vec3 vertexPosition_Modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normal_Modelspace;

out vec2 UV;
out vec3 normal_Cameraspace;
out vec3 lightDirection_Cameraspace;

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform vec3 lightPosition_Worldspace;

void main(){
	gl_Position = MVP * vec4(vertexPosition_Modelspace, 1);

	vec3 vertexPosition_Cameraspace = (V * M * vec4(vertexPosition_Modelspace, 1)).xyz;
	vec3 EyeDirection_Cameraspace = vec3(0, 0, 0) - vertexPosition_Cameraspace;

	vec3 lightPosition_Cameraspace = (V * vec4(lightPosition_Worldspace, 1)).xyz; 
	lightDirection_Cameraspace = lightPosition_Cameraspace + EyeDirection_Cameraspace;

	normal_Cameraspace = (V * M * vec4(normal_Modelspace, 0)).xyz;

	UV = vertexUV;
}
