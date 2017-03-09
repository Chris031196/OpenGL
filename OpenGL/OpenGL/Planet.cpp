#include "Planet.h"


Planet::Planet(MeshHolder* mesh, float mass, glm::vec3 pos)
{
	m_mesh = mesh;
	m_mass = mass;
	m_pos = pos;
	m_radius = glm::log(m_mass);

	glGenBuffers(1, &tailBuffer);
}

Planet::Planet(MeshHolder* mesh, float mass, glm::vec3 pos, glm::vec3 move)
{
	m_mesh = mesh;
	m_mass = mass;
	m_pos = pos;
	m_move = move;
	m_cMove = move; 
	m_radius = glm::log(m_mass);

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
	model *= glm::scale(glm::vec3(m_radius, m_radius, m_radius));
	//model *= glm::scale(glm::vec3(m_mass, m_mass, m_mass));
	//model *= glm::scale(glm::vec3(5, 5, 5));
	return model;
}


bool Planet::calculate(std::vector<Planet*> planets)
{
	glm::vec3 force = glm::vec3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < planets.size(); i++) {
		Planet* c_planet = planets[i];
		if (c_planet != this) {

			float c_mass = c_planet->getMass();
			float c_radius = c_planet->getRadius();
			glm::vec3 c_pos = c_planet->getPos();
			glm::vec3 c_direction = c_pos - m_pos;
			float c_distance = glm::sqrt((c_direction.x * c_direction.x) + (c_direction.y * c_direction.y) + (c_direction.z * c_direction.z));

			glm::vec3 c_normalizedDirection = glm::normalize(c_direction);

			float c_force = 0.2f * ((m_mass * c_mass) / (c_distance * c_distance));

			if ((c_distance < m_radius + c_radius) || collisionFlag) {

				if (m_mass > c_mass) {
					c_planet->setMove(m_move);
				}
				c_planet->addMass(m_mass);
				return false;

				// ---COLLISION NOT WORKING---

				//if (collisionFlag) {
				//	collisionFlag = false;
				//}
				//else {
				//	c_planet->collisionFlag = true;
				//	m_pos -= c_normalizedDirection * (((m_radius + c_radius) - c_distance));
				//}
				//glm::vec3 cforce_vector = c_planet->getMove() * c_normalizedDirection;
				//glm::vec3 mforce_vector = m_move * c_normalizedDirection;

				//float cforce = glm::length(cforce_vector) * c_mass;
				//float mforce = glm::length(mforce_vector) * m_mass;
				//float cwouldBe = glm::length(c_planet->getMove()) * c_mass;
				//float mwouldBe = glm::length(m_move) * m_mass;

				//printf("cForce: %f, cWould: %f, mForce: %f, mWould: %f\n", cforce, cwouldBe, mforce, mwouldBe);
				//float totalForce = cforce + mforce;
				//float newForce = (totalForce / m_mass);
				//newForce *= 0.1f;
				//glm::vec3 dirComponent = m_move * glm::vec3(c_normalizedDirection.x, c_normalizedDirection.y, c_normalizedDirection.z);
				//m_cMove -= c_normalizedDirection * newForce;
				//if (dirComponent.x > 0 && dirComponent.y > 0 && dirComponent.z > 0) {
				//	m_cMove -= dirComponent;
				//}
			}
			else {
				force += c_normalizedDirection * c_force;// *(c_distance - (c_mass + m_mass));
			}
		}
	}
	m_cMove += force / m_mass;
	return true;
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