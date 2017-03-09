#pragma once

#include <vector>
#include "MeshHolder.h"
#include <GL\glew.h>
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp"

class Planet
{

public:
	Planet(MeshHolder* mesh, float mass, glm::vec3 pos);
	Planet(MeshHolder* mesh, float mass, glm::vec3 pos, glm::vec3 move);
	~Planet();

	float getMass() { return m_mass; }
	glm::vec3 getPos() { return m_pos; }
	void setPos(glm::vec3 pos) { m_pos = pos;  }
	glm::vec3 getMove() { return m_move; }
	float getRadius() { return m_radius; }
	void setMove(glm::vec3 move) { m_move = move; m_cMove = move;  }
	void addMass(float mass) { m_mass += mass;  m_radius += glm::log(mass);  }
	glm::mat4 getModelMatrix() const;


	bool calculate(std::vector<Planet*> planets);
	void update();
	void Draw(GLuint id_drawTail);

	bool collisionFlag = false;

private:

	glm::vec3 m_pos;
	glm::vec3 m_cPos;

	glm::vec3 m_move;
	glm::vec3 m_cMove;

	float m_mass;
	float m_radius;
	std::vector<glm::vec4> tail_vertices;
	MeshHolder* m_mesh;

	GLuint tailBuffer;
};

