#ifndef _MESH_HPP
#define _MESH_HPP

#include "GL/glew.h"
#include <vector>
#include <variant>
#include <exception>
#include <string>

namespace DK
{
	struct VB
	{
		std::string name;
		unsigned int datatype;
		unsigned int count;
		unsigned int stride;
		std::variant<std::vector<char>, std::vector<unsigned char>, std::vector<short>, std::vector<unsigned short>, std::vector<int>, std::vector<unsigned int>, std::vector<float>> data;
	};

	class Mesh
	{
	public:
		Mesh() : m_VAO(), m_EBO(), m_ElementCount(), m_VBOs() {}
		Mesh(const Mesh& other) = delete;
		Mesh(const Mesh&& other) = delete;
		~Mesh();

		void operator=(const Mesh& other) = delete;
		void initialize(const std::vector<VB>& vbs, const std::vector<unsigned int>& eb);
		void initialize(const std::vector<VB>& vbs, const std::vector<unsigned short>& eb);
		void initialize(const std::vector<VB>& vbs, const std::vector<unsigned char>& eb);
		void initialize(const VB& vb, const std::vector<unsigned int>& eb);
		void initialize(const VB& vb, const std::vector<unsigned short>& eb);
		void initialize(const VB& vb, const std::vector<unsigned char>& eb);

		void draw() const;

		bool isInitialized() const { return m_Initialized; }

	private:
		mutable bool m_Initialized = false;
		unsigned int m_VAO, m_EBO, m_ElementCount;
		unsigned int m_ElementDataType;
		std::vector<unsigned int> m_VBOs;
	};
}

#endif