#include "EzTriangle.h"


EzTriangle::EzTriangle()
{
}


EzTriangle::~EzTriangle()
{
}

void EzTriangle::Init()
{
	//Init coordinates
	GLfloat g_vertex_buffer_data[] = {
		-1.0f,	-1.0f,	0.0f,
		1.0f,	-1.0f,	0.0f,
		0.0f,	1.0f,	0.0f
	};

	//Init vertexBuffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void EzTriangle::Draw()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	//Draw Triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}