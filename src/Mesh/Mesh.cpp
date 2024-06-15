
#include "Mesh/Mesh.hpp"

namespace DK
{
	Mesh::~Mesh()
	{
		if (!m_Initialized) return;
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_EBO);
		for (unsigned int& vb : m_VBOs)
		{
			glDeleteBuffers(1, &vb);
		}
	}

	void Mesh::initialize(const VB& vb, const std::vector<unsigned int>& eb)
	{
		glCreateVertexArrays(1, &m_VAO);

		glCreateBuffers(1, &m_EBO);
		glNamedBufferData(m_EBO, sizeof(unsigned int) * eb.size(), eb.data(), GL_STATIC_DRAW);
		glVertexArrayElementBuffer(m_VAO, m_EBO);
		m_ElementCount = eb.size();
		m_ElementDataType = GL_UNSIGNED_INT;

		m_VBOs.reserve(1);
		unsigned int vbo;
		glCreateBuffers(1, &vbo);

		switch (vb.datatype)
		{
		case GL_BYTE:
			glNamedBufferData(vbo, sizeof(char) * std::get<std::vector<char>>(vb.data).size(), std::get<std::vector<char>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		case GL_UNSIGNED_BYTE:
			glNamedBufferData(vbo, sizeof(unsigned char) * std::get<std::vector<unsigned char>>(vb.data).size(), std::get<std::vector<unsigned char>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		case GL_SHORT:
			glNamedBufferData(vbo, sizeof(short) * std::get<std::vector<short>>(vb.data).size(), std::get<std::vector<short>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		case GL_UNSIGNED_SHORT:
			glNamedBufferData(vbo, sizeof(unsigned short) * std::get<std::vector<unsigned short>>(vb.data).size(), std::get<std::vector<unsigned short>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		case GL_INT:
			glNamedBufferData(vbo, sizeof(int) * std::get<std::vector<int>>(vb.data).size(), std::get<std::vector<int>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		case GL_UNSIGNED_INT:
			glNamedBufferData(vbo, sizeof(unsigned int) * std::get<std::vector<unsigned int>>(vb.data).size(), std::get<std::vector<unsigned int>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		case GL_FLOAT:
			glNamedBufferData(vbo, sizeof(float) * std::get<std::vector<float>>(vb.data).size(), std::get<std::vector<float>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		}

		glVertexArrayVertexBuffer(m_VAO, 0, vbo, 0, vb.stride);
		glVertexArrayAttribFormat(m_VAO, 0, vb.count, vb.datatype, GL_FALSE, 0);
		glVertexArrayAttribBinding(m_VAO, 0, 0);
		glEnableVertexArrayAttrib(m_VAO, 0);
		m_VBOs.push_back(vbo);
		m_Initialized = true;
	}
	void Mesh::initialize(const VB& vb, const std::vector<unsigned short>& eb)
	{
		glCreateVertexArrays(1, &m_VAO);

		glCreateBuffers(1, &m_EBO);
		glNamedBufferData(m_EBO, sizeof(unsigned short) * eb.size(), eb.data(), GL_STATIC_DRAW);
		glVertexArrayElementBuffer(m_VAO, m_EBO);
		m_ElementCount = eb.size();
		m_ElementDataType = GL_UNSIGNED_SHORT;

		m_VBOs.reserve(1);
		unsigned int vbo;
		glCreateBuffers(1, &vbo);

		switch (vb.datatype)
		{
		case GL_BYTE:
			glNamedBufferData(vbo, sizeof(char) * std::get<std::vector<char>>(vb.data).size(), std::get<std::vector<char>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		case GL_UNSIGNED_BYTE:
			glNamedBufferData(vbo, sizeof(unsigned char) * std::get<std::vector<unsigned char>>(vb.data).size(), std::get<std::vector<unsigned char>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		case GL_SHORT:
			glNamedBufferData(vbo, sizeof(short) * std::get<std::vector<short>>(vb.data).size(), std::get<std::vector<short>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		case GL_UNSIGNED_SHORT:
			glNamedBufferData(vbo, sizeof(unsigned short) * std::get<std::vector<unsigned short>>(vb.data).size(), std::get<std::vector<unsigned short>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		case GL_INT:
			glNamedBufferData(vbo, sizeof(int) * std::get<std::vector<int>>(vb.data).size(), std::get<std::vector<int>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		case GL_UNSIGNED_INT:
			glNamedBufferData(vbo, sizeof(unsigned int) * std::get<std::vector<unsigned int>>(vb.data).size(), std::get<std::vector<unsigned int>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		case GL_FLOAT:
			glNamedBufferData(vbo, sizeof(float) * std::get<std::vector<float>>(vb.data).size(), std::get<std::vector<float>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		}

		glVertexArrayVertexBuffer(m_VAO, 0, vbo, 0, vb.stride);
		glVertexArrayAttribFormat(m_VAO, 0, vb.count, vb.datatype, GL_FALSE, 0);
		glVertexArrayAttribBinding(m_VAO, 0, 0);
		glEnableVertexArrayAttrib(m_VAO, 0);
		m_VBOs.push_back(vbo);
		m_Initialized = true;
	}
	void Mesh::initialize(const VB& vb, const std::vector<unsigned char>& eb)
	{
		glCreateVertexArrays(1, &m_VAO);

		glCreateBuffers(1, &m_EBO);
		glNamedBufferData(m_EBO, sizeof(unsigned char) * eb.size(), eb.data(), GL_STATIC_DRAW);
		glVertexArrayElementBuffer(m_VAO, m_EBO);
		m_ElementCount = eb.size();
		m_ElementDataType = GL_UNSIGNED_BYTE;

		m_VBOs.reserve(1);
		unsigned int vbo;
		glCreateBuffers(1, &vbo);

		switch (vb.datatype)
		{
		case GL_BYTE:
			glNamedBufferData(vbo, sizeof(char) * std::get<std::vector<char>>(vb.data).size(), std::get<std::vector<char>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		case GL_UNSIGNED_BYTE:
			glNamedBufferData(vbo, sizeof(unsigned char) * std::get<std::vector<unsigned char>>(vb.data).size(), std::get<std::vector<unsigned char>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		case GL_SHORT:
			glNamedBufferData(vbo, sizeof(short) * std::get<std::vector<short>>(vb.data).size(), std::get<std::vector<short>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		case GL_UNSIGNED_SHORT:
			glNamedBufferData(vbo, sizeof(unsigned short) * std::get<std::vector<unsigned short>>(vb.data).size(), std::get<std::vector<unsigned short>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		case GL_INT:
			glNamedBufferData(vbo, sizeof(int) * std::get<std::vector<int>>(vb.data).size(), std::get<std::vector<int>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		case GL_UNSIGNED_INT:
			glNamedBufferData(vbo, sizeof(unsigned int) * std::get<std::vector<unsigned int>>(vb.data).size(), std::get<std::vector<unsigned int>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		case GL_FLOAT:
			glNamedBufferData(vbo, sizeof(float) * std::get<std::vector<float>>(vb.data).size(), std::get<std::vector<float>>(vb.data).data(), GL_STATIC_DRAW);
			break;
		}

		glVertexArrayVertexBuffer(m_VAO, 0, vbo, 0, vb.stride);
		glVertexArrayAttribFormat(m_VAO, 0, vb.count, vb.datatype, GL_FALSE, 0);
		glVertexArrayAttribBinding(m_VAO, 0, 0);
		glEnableVertexArrayAttrib(m_VAO, 0);
		m_VBOs.push_back(vbo);
		m_Initialized = true;
	}

	void Mesh::initialize(const std::vector<VB>& vbs, const std::vector<unsigned int>& eb)
	{
		glCreateVertexArrays(1, &m_VAO);

		glCreateBuffers(1, &m_EBO);
		glNamedBufferData(m_EBO, sizeof(unsigned int) * eb.size(), eb.data(), GL_STATIC_DRAW);
		glVertexArrayElementBuffer(m_VAO, m_EBO);
		m_ElementCount = eb.size();
		m_ElementDataType = GL_UNSIGNED_INT;

		m_VBOs.reserve(vbs.size());
		for (unsigned int i = 0; i < vbs.size(); i++)
		{
			if (vbs[i].name != "POSITION") continue;
			unsigned int vbo;
			glCreateBuffers(1, &vbo);

			switch (vbs[i].datatype)
			{
			case GL_BYTE:
				glNamedBufferData(vbo, sizeof(char) * std::get<std::vector<char>>(vbs[i].data).size(), std::get<std::vector<char>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			case GL_UNSIGNED_BYTE:
				glNamedBufferData(vbo, sizeof(unsigned char) * std::get<std::vector<unsigned char>>(vbs[i].data).size(), std::get<std::vector<unsigned char>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			case GL_SHORT:
				glNamedBufferData(vbo, sizeof(short) * std::get<std::vector<short>>(vbs[i].data).size(), std::get<std::vector<short>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			case GL_UNSIGNED_SHORT:
				glNamedBufferData(vbo, sizeof(unsigned short) * std::get<std::vector<unsigned short>>(vbs[i].data).size(), std::get<std::vector<unsigned short>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			case GL_INT:
				glNamedBufferData(vbo, sizeof(int) * std::get<std::vector<int>>(vbs[i].data).size(), std::get<std::vector<int>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			case GL_UNSIGNED_INT:
				glNamedBufferData(vbo, sizeof(unsigned int) * std::get<std::vector<unsigned int>>(vbs[i].data).size(), std::get<std::vector<unsigned int>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			case GL_FLOAT:
				glNamedBufferData(vbo, sizeof(float) * std::get<std::vector<float>>(vbs[i].data).size(), std::get<std::vector<float>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			}

			glVertexArrayVertexBuffer(m_VAO, 0, vbo, 0, vbs[i].stride);
			glVertexArrayAttribFormat(m_VAO, 0, vbs[i].count, vbs[i].datatype, GL_FALSE, 0);
			glVertexArrayAttribBinding(m_VAO, 0, 0);
			glEnableVertexArrayAttrib(m_VAO, 0);
			m_VBOs.push_back(vbo);
		}
		m_Initialized = true;
	}
	void Mesh::initialize(const std::vector<VB>& vbs, const std::vector<unsigned short>& eb)
	{
		glCreateVertexArrays(1, &m_VAO);

		glCreateBuffers(1, &m_EBO);
		glNamedBufferData(m_EBO, sizeof(unsigned short) * eb.size(), eb.data(), GL_STATIC_DRAW);
		glVertexArrayElementBuffer(m_VAO, m_EBO);
		m_ElementCount = eb.size();
		m_ElementDataType = GL_UNSIGNED_SHORT;

		m_VBOs.reserve(vbs.size());
		for (unsigned int i = 0; i < vbs.size(); i++)
		{
			if (vbs[i].name != "POSITION") continue;
			unsigned int vbo;
			glCreateBuffers(1, &vbo);

			switch (vbs[i].datatype)
			{
			case GL_BYTE:
				glNamedBufferData(vbo, sizeof(char) * std::get<std::vector<char>>(vbs[i].data).size(), std::get<std::vector<char>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			case GL_UNSIGNED_BYTE:
				glNamedBufferData(vbo, sizeof(unsigned char) * std::get<std::vector<unsigned char>>(vbs[i].data).size(), std::get<std::vector<unsigned char>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			case GL_SHORT:
				glNamedBufferData(vbo, sizeof(short) * std::get<std::vector<short>>(vbs[i].data).size(), std::get<std::vector<short>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			case GL_UNSIGNED_SHORT:
				glNamedBufferData(vbo, sizeof(unsigned short) * std::get<std::vector<unsigned short>>(vbs[i].data).size(), std::get<std::vector<unsigned short>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			case GL_INT:
				glNamedBufferData(vbo, sizeof(int) * std::get<std::vector<int>>(vbs[i].data).size(), std::get<std::vector<int>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			case GL_UNSIGNED_INT:
				glNamedBufferData(vbo, sizeof(unsigned int) * std::get<std::vector<unsigned int>>(vbs[i].data).size(), std::get<std::vector<unsigned int>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			case GL_FLOAT:
				glNamedBufferData(vbo, sizeof(float) * std::get<std::vector<float>>(vbs[i].data).size(), std::get<std::vector<float>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			}

			glVertexArrayVertexBuffer(m_VAO, 0, vbo, 0, vbs[i].stride);
			glVertexArrayAttribFormat(m_VAO, 0, vbs[i].count, vbs[i].datatype, GL_FALSE, 0);
			glVertexArrayAttribBinding(m_VAO, 0, 0);
			glEnableVertexArrayAttrib(m_VAO, 0);
			m_VBOs.push_back(vbo);
		}
		m_Initialized = true;
	}
	void Mesh::initialize(const std::vector<VB>& vbs, const std::vector<unsigned char>& eb)
	{
		glCreateVertexArrays(1, &m_VAO);

		glCreateBuffers(1, &m_EBO);
		glNamedBufferData(m_EBO, sizeof(unsigned char) * eb.size(), eb.data(), GL_STATIC_DRAW);
		glVertexArrayElementBuffer(m_VAO, m_EBO);
		m_ElementCount = eb.size();
		m_ElementDataType = GL_UNSIGNED_BYTE;

		m_VBOs.reserve(vbs.size());
		for (unsigned int i = 0; i < vbs.size(); i++)
		{
			if (vbs[i].name != "POSITION") continue;
			unsigned int vbo;
			glCreateBuffers(1, &vbo);

			switch (vbs[i].datatype)
			{
			case GL_BYTE:
				glNamedBufferData(vbo, sizeof(char) * std::get<std::vector<char>>(vbs[i].data).size(), std::get<std::vector<char>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			case GL_UNSIGNED_BYTE:
				glNamedBufferData(vbo, sizeof(unsigned char) * std::get<std::vector<unsigned char>>(vbs[i].data).size(), std::get<std::vector<unsigned char>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			case GL_SHORT:
				glNamedBufferData(vbo, sizeof(short) * std::get<std::vector<short>>(vbs[i].data).size(), std::get<std::vector<short>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			case GL_UNSIGNED_SHORT:
				glNamedBufferData(vbo, sizeof(unsigned short) * std::get<std::vector<unsigned short>>(vbs[i].data).size(), std::get<std::vector<unsigned short>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			case GL_INT:
				glNamedBufferData(vbo, sizeof(int) * std::get<std::vector<int>>(vbs[i].data).size(), std::get<std::vector<int>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			case GL_UNSIGNED_INT:
				glNamedBufferData(vbo, sizeof(unsigned int) * std::get<std::vector<unsigned int>>(vbs[i].data).size(), std::get<std::vector<unsigned int>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			case GL_FLOAT:
				glNamedBufferData(vbo, sizeof(float) * std::get<std::vector<float>>(vbs[i].data).size(), std::get<std::vector<float>>(vbs[i].data).data(), GL_STATIC_DRAW);
				break;
			}

			glVertexArrayVertexBuffer(m_VAO, 0, vbo, 0, vbs[i].stride);
			glVertexArrayAttribFormat(m_VAO, 0, vbs[i].count, vbs[i].datatype, GL_FALSE, 0);
			glVertexArrayAttribBinding(m_VAO, 0, 0);
			glEnableVertexArrayAttrib(m_VAO, 0);
			m_VBOs.push_back(vbo);
		}
		m_Initialized = true;
	}

	void Mesh::draw() const
	{
		if (!m_Initialized) throw std::exception("You have not initialized the Mesh!\n");
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, m_ElementCount, m_ElementDataType, nullptr);
	}
}