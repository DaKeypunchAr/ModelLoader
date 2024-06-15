#include "Model/Model.hpp"

namespace DK
{
	Model::~Model()
	{
		if (!m_Initialized) return;
		for (Mesh* mesh : m_Meshes)
		{
			delete mesh;
		}
	}

	void Model::draw(const OGL::Program& program) const
	{
		if (!m_Initialized) throw std::exception("Model is not initialized!\n");

		program.use();
		for (const Mesh* const mesh : m_Meshes)
		{
			mesh->draw();
		}
	}
}