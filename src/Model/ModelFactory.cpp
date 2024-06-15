#include "Model/ModelFactory.hpp"

namespace DK
{
	void ModelFactory::initializeUsingGLTF(Model& model, const std::string& gltfFolder, const std::string& gltfFile, int scene)
	{
		cache.json.initialize(gltfFile);
		cache.dir = gltfFolder;
		model.m_Initialized = true;
		cache.model = &model;

		if (scene != -1)
		{
			initializeScene(scene);
			return;
		}
		if (cache.json.exists("scene"))
		{
			scene = cache.json["scene"];
			if (cache.json["scenes"].size() >= scene) throw std::exception("Scene doesn't exist!\n");

			initializeScene(scene);
			return;
		}
		initializeScene();
	}

	void ModelFactory::initializeScene(int scene)
	{
		if (scene != -1)
		{
			const JSON::JSONValue& nodes = cache.json["scenes"][scene]["nodes"];
			for (unsigned int i = 0; i < nodes.size(); i++)
			{
				evaluateNode(nodes[i]);
			}
		}
		evaluateNode(0);
	}
	void ModelFactory::evaluateNode(int node)
	{
		if (node != -1)
		{
			evaluateMesh(cache.json["nodes"][node]["mesh"]);
		}
	}
	void ModelFactory::evaluateMesh(unsigned int mesh)
	{
		if (cache.json["meshes"].size() <= mesh) throw std::runtime_error("Mesh is out of bounds!\n");
		const JSON::JSONValue& primitives = cache.json["meshes"][mesh]["primitives"];
		std::vector<VB> attribs;
		auto indices = getBufferViewData(primitives[0]["indices"]);
		const JSON::JSONValue& attributes = primitives[0]["attributes"];
		for (unsigned int i = 0; i < attributes.totalKeys(); i++)
		{
			attribs.push_back(evaluateAttribute(attributes.getKey(i), attributes[attributes.getKey(i).c_str()]));
		}
		Mesh* meshPtr = new Mesh;
		if ((unsigned int)cache.json["accessors"][primitives[0]["indices"]]["componentType"] == GL_UNSIGNED_BYTE)
		{
			meshPtr->initialize(attribs, indices);
		}
		else if ((unsigned int)cache.json["accessors"][primitives[0]["indices"]]["componentType"] == GL_UNSIGNED_SHORT)
		{
			meshPtr->initialize(attribs, std::get<std::vector<unsigned short>>(convertData(indices, GL_UNSIGNED_SHORT)));
		}
		else if ((unsigned int)cache.json["accessors"][primitives[0]["indices"]]["componentType"] == GL_UNSIGNED_INT)
		{
			meshPtr->initialize(attribs, std::get<std::vector<unsigned int>>(convertData(indices, GL_UNSIGNED_INT)));
		}
		else
		{
			throw std::runtime_error("Indices must be unsigned char, unsigned short or unsigned int!\n");
		}
		cache.model->m_Meshes.push_back(meshPtr);
	}

	VB ModelFactory::evaluateAttribute(const std::string& attribName, unsigned int accessorIdx)
	{
		VB b;
		b.name = attribName;
		const JSON::JSONValue& accessor = cache.json["accessors"][accessorIdx];
		b.datatype = accessor["componentType"];
		b.data = convertData(getBufferViewData(accessor["bufferView"]), b.datatype);
		if (std::string(accessor["type"]) == "SCALER") b.count = 1;
		else if (std::string(accessor["type"]) == "VEC2") b.count = 2;
		else if (std::string(accessor["type"]) == "VEC3") b.count = 3;
		else if (std::string(accessor["type"]) == "VEC4") b.count = 4;
		switch (b.datatype)
		{
		case GL_BYTE:
			b.stride = b.count * sizeof(char);
			break;
		case GL_UNSIGNED_BYTE:
			b.stride = b.count * sizeof(unsigned char);
			break;
		case GL_SHORT:
			b.stride = b.count * sizeof(short);
			break;
		case GL_UNSIGNED_SHORT:
			b.stride = b.count * sizeof(unsigned short);
			break;
		case GL_INT:
			b.stride = b.count * sizeof(int);
			break;
		case GL_UNSIGNED_INT:
			b.stride = b.count * sizeof(unsigned int);
			break;
		case GL_FLOAT:
			b.stride = b.count * sizeof(float);
			break;
		}
		return b;
	}
	std::vector<unsigned char> ModelFactory::getBufferViewData(unsigned int bufferViewIdx)
	{
		const JSON::JSONValue& bufferView = cache.json["bufferViews"][bufferViewIdx];
		unsigned int offset = bufferView["byteOffset"];
		unsigned int length = bufferView["byteLength"];
		return getDataFromBuffer(bufferView["buffer"], offset, length);
	}
	std::vector<unsigned char> ModelFactory::getDataFromBuffer(unsigned int bufferIdx, unsigned int offset, unsigned int length)
	{
		if (cache.allBufferInitialized)
		{
			std::vector<unsigned char> data;
			for (unsigned int i = offset; i < offset + length; i++)
			{
				data.push_back(cache.bufferData[bufferIdx][i]);
			}
			return data;
		}

		for (unsigned int i = 0; i < cache.json["buffers"].size(); i++)
		{
			std::string path = cache.dir + "/";
			path += cache.json["buffers"][i]["uri"].operator std::string();
			std::ifstream reader(path, std::ios::binary);
			std::vector<unsigned char> v(std::istreambuf_iterator<char>(reader), {});
			cache.bufferData.push_back(v);
		}
		cache.allBufferInitialized = true;
		return getDataFromBuffer(bufferIdx, offset, length);
	}
	std::variant<std::vector<char>, std::vector<unsigned char>, std::vector<short>, std::vector<unsigned short>, std::vector<int>, std::vector<unsigned int>, std::vector<float>> ModelFactory::convertData(const std::vector<unsigned char>& v, unsigned int type)
	{
		switch (type)
		{
		case GL_BYTE:
			{
				std::vector<char> v2;
				for (unsigned int i = 0; i < v.size(); i++)
				{
					v2.push_back(static_cast<char>(v[i]));
				}
				return v2;
			}
		case GL_UNSIGNED_BYTE:
			return v;
		case GL_SHORT:
			{
				std::vector<short> v2;
				for (unsigned int i = 0; i < v.size(); i += 2)
				{
					short s;
					unsigned char d[]{ v[i], v[i + 1] };
					memcpy(&s, d, sizeof(short));
					v2.push_back(s);
				}
				return v2;
			}
		case GL_UNSIGNED_SHORT:
			{
				std::vector<unsigned short> v2;
				for (unsigned int i = 0; i < v.size(); i += 2)
				{
					unsigned short s;
					unsigned char d[]{ v[i], v[i + 1] };
					memcpy(&s, d, sizeof(unsigned short));
					v2.push_back(s);
				}
				return v2;
			}
		case GL_INT:
			{
				std::vector<int> v2;
				for (unsigned int i = 0; i < v.size(); i += 4)
				{
					int s;
					unsigned char d[]{ v[i], v[i + 1], v[i + 2], v[i + 3] };
					memcpy(&s, d, sizeof(int));
					v2.push_back(s);
				}
				return v2;
			}
		case GL_UNSIGNED_INT:
			{
				std::vector<unsigned int> v2;
				for (unsigned int i = 0; i < v.size(); i += 4)
				{
					unsigned int s;
					unsigned char d[]{ v[i], v[i + 1], v[i + 2], v[i + 3] };
					memcpy(&s, d, sizeof(unsigned int));
					v2.push_back(s);
				}
				return v2;
			}
		case GL_FLOAT:
			{
				std::vector<float> v2;
				for (unsigned int i = 0; i < v.size(); i += 4)
				{
					float s;
					unsigned char d[]{ v[i], v[i + 1], v[i + 2], v[i + 3] };
					memcpy(&s, d, sizeof(float));
					v2.push_back(s);
				}
				return v2;
			}
		}
	}

	FactoryCache ModelFactory::cache;
}