
#include "SGL/Wrapper/PropertyShader.h"

using namespace sgl;

PropertyShader::PropertyShader()
{
}

void PropertyShader::setBaseLight(const std::string &name, const BaseLight & light)
{
	uniform(name + ".color").set(light.color);
	uniform(name + ".ambientIntensity").set(light.ambientIntensity);
}

void PropertyShader::setDirectionLight(const std::string &name, const DirectionalLight &light)
{
	setBaseLight(name, light);
	uniform(name + ".direction").set(light.direction);
}

void PropertyShader::setPointLight(const std::string &name, const PointLight &light)
{
	setBaseLight(name, light);
	uniform(name + ".position").set(light.position);
	uniform(name + ".atten.c").set(light.atten.c);
	uniform(name + ".atten.l").set(light.atten.l);
	uniform(name + ".atten.e").set(light.atten.e);
}

void PropertyShader::setMaterial(const std::string &name, const Material &mat)
{
	uniform(name + ".ambientColor").set(mat.ambientColor);

	uniform(name + ".diffuseColor").set(mat.diffuseColor);
	uniform(name + ".diffuseIntensity").set(mat.diffuseIntensity);

	uniform(name + ".specularColor").set(mat.specularColor);
	uniform(name + ".specularIntensity").set(mat.specularIntensity);
	uniform(name + ".specularPower").set(mat.specularPower);
}


PropertyShader::~PropertyShader()
{
}
