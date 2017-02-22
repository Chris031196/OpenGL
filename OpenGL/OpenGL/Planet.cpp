#include "Planet.h"


Planet::Planet(MeshHolder* mesh, float mass, glm::vec3 pos)
{
	m_mesh = mesh;
	m_mass = mass;
	m_pos = pos;
	glGenBuffers(1, &tailBuffer);
}

Planet::Planet(MeshHolder* mesh, float mass, glm::vec3 pos, glm::vec3 move)
{
	m_mesh = mesh;
	m_mass = mass;
	m_pos = pos;
	m_move = move;
	m_cMove = move;

	glGenBuffers(1, &tailBuffer);
}

Planet::~Planet()
{
	printf("jep");
	glDeleteBuffers(1, &tailBuffer);
}

glm::mat4 Planet::getModelMatrix() const
{
	glm::mat4 model = glm::translate(m_pos);
	//model *= glm::scale(glm::vec3(glm::log(m_mass), glm::log(m_mass), glm::log(m_mass)));
	model *= glm::scale(glm::vec3(m_mass, m_mass, m_mass));
	return model;
}


void Planet::calculate(std::vector<Planet*> planets)
{
	glm::vec3 force;
	for (int i = 0; i < planets.size(); i++) {
		Planet* c_planet = planets[i];
		if (c_planet != this) {
			float c_mass = c_planet->getMass();
			glm::vec3 c_pos = c_planet->getPos();

			glm::vec3 c_direction = c_pos - m_pos;
			float c_distance = glm::sqrt((c_direction.x * c_direction.x) + (c_direction.y * c_direction.y) + (c_direction.z * c_direction.z));

			glm::vec3 c_normalizedDirection = glm::normalize(c_direction);
			float c_force = mult * ((m_mass * c_mass) / (c_distance * c_distance));

			if ((c_distance < m_mass + c_mass) || collisionFlag) {
				m_pos -= c_normalizedDirection * (((m_mass + c_mass) - c_distance));

				float cforce = glm::length(c_planet->getMove()) * c_mass;
				float mforce = glm::length(m_move) * m_mass;
				float totalForce = cforce + mforce;
				if (mforce >= cforce) {
					m_cMove -= c_normalizedDirection * (totalForce * (cforce / mforce));
					//c_planet->setMove(c_planet->getMove() + c_normalizedDirection * (totalForce * ( 1.0f - (c_mass / m_mass))));
				}
				else {
					m_cMove -= c_normalizedDirection * (totalForce * ( 1.0f - (mforce / cforce)));
					//c_planet->setMove(c_planet->getMove() + c_normalizedDirection * (totalForce * m_mass / c_mass));
				}
				if (collisionFlag) {
					collisionFlag = false;
				}
				else {
					c_planet->collisionFlag = true;
				}
			}
			else {
				force += c_normalizedDirection * c_force * (c_distance - (c_mass + m_mass));
			}
		}
	}
	m_cMove += force / m_mass;
}

void Planet::update()
{
	m_move = m_cMove;
	m_pos += m_move;

	tail_vertices.push_back(glm::vec4(m_pos, 1.0f));
	if (tail_vertices.size() >= 1000) {
		tail_vertices.erase(tail_vertices.begin());
	}
}



void Planet::Draw(GLuint id_drawTail)
{
	m_mesh->Draw();

	if (tail_vertices.size() >= 2) {

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, tailBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * tail_vertices.size(), &tail_vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_LINE_STRIP, 0, tail_vertices.size());
	}
}