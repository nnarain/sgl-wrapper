
#include <SGL/GL/Uniform.h>
#include <SGL/Util/Exception.h>

using namespace sgl;

Uniform::Uniform(int location) :
	_location(location)
{
	if (_location < 0) throw Exception("invalid uniform location");
}

/* Interger sets */

void Uniform::set(int v1)
{
	glUniform1i(_location, v1);
}

void Uniform::set(int v1, int v2)
{
	glUniform2i(_location, v1, v2);
}

void Uniform::set(int v1, int v2, int v3)
{
	glUniform3i(_location, v1, v2, v3);
}

void Uniform::set(int v1, int v2, int v3, int v4)
{
	glUniform4i(_location, v1, v2, v3, v4);
}

/* Float sets */

void Uniform::set(float v1)
{
	glUniform1f(_location, v1);
}

void Uniform::set(float v1, float v2)
{
	glUniform2f(_location, v1, v2);
}

void Uniform::set(float v1, float v2, float v3)
{
	glUniform3f(_location, v1, v2, v3);
}

void Uniform::set(float v1, float v2, float v3, float v4)
{
	glUniform4f(_location, v1, v2, v3, v4);
}

/* float value pointer */

void Uniform::set(const glm::vec3 &v)
{
	glUniform3fv(_location, 1, &v[0]);
}

void Uniform::set(const glm::vec4 &v)
{
	glUniform4fv(_location, 1, &v[0]);
}

/* Matrix 3x3 set */
void Uniform::set(const glm::mat3 &v)
{
	set(v, false);
}

void Uniform::set(const glm::mat3 &v, bool transpose)
{
	glUniformMatrix3fv(_location, 1, transpose, &v[0][0]);
}

/* Matrix 4x4 set */
void Uniform::set(const glm::mat4 &v)
{
	set(v, false);
}

void Uniform::set(const glm::mat4 &v, bool transpose)
{
	glUniformMatrix4fv(_location, 1, transpose, &v[0][0]);
}

/* Getters */

int Uniform::getLocation() const
{
	return _location;
}

Uniform::~Uniform()
{
}