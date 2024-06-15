#ifndef _MODEL_HPP
#define _MODEL_HPP

#include "JSON.hpp"
#include "Mesh/Mesh.hpp"
#include "OGL/ShaderProgram/Program.hpp"

namespace DK
{
	class ModelFactory;

	class Model
	{
	public:
		Model() : m_Meshes() {}
		~Model();

		void draw(const OGL::Program& program) const;

	private:
		mutable bool m_Initialized = false;
		std::vector<Mesh*> m_Meshes;

		friend ModelFactory;
	};
}

#endif