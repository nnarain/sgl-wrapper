
#ifndef PROPERTY_SHADER_H
#define PROPERTY_SHADER_H

#include <SGL/Util/SGLExport.h>

#include <SGL/GL/ShaderProgram.h>
#include <SGL/Type/Light.h>
#include <SGL/Type/Material.h>

namespace sgl
{
	SGLCLASS PropertyShader : public ShaderProgram
	{
	public:
		PropertyShader();
		~PropertyShader();

		void setBaseLight(const std::string &name, const BaseLight & light);
		void setDirectionLight(const std::string &name, const DirectionalLight &light);
		void setPointLight(const std::string &name, const PointLight &light);
		void setSpotLight(const std::string &name, const SpotLight &light);

		void setMaterial(const std::string &name, const Material &mat);

	private:
	};
}

#endif

