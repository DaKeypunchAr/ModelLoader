#ifndef _MODEL_FACTORY_HPP
#define _MODEL_FACTORY_HPP

#include "Model.hpp"

namespace DK
{
	struct FactoryCache
	{
		JSON::JSON json;
		std::string dir;
		bool allBufferInitialized = false;
		std::vector<std::vector<unsigned char>> bufferData;
		Model* model;
	};

	class ModelFactory
	{
	public:
		ModelFactory() = delete;
		ModelFactory(const ModelFactory& other) = delete;
		ModelFactory(const ModelFactory&& other) = delete;
		~ModelFactory() = delete;
		void operator=(const ModelFactory& other) = delete;
		void operator=(const ModelFactory&& other) = delete;

		static void initializeUsingGLTF(Model& model, const std::string& gltfFolder, const std::string& gltfFile, int scene = -1);

	private:
		static void initializeScene(int scene = -1);
		static void evaluateNode(int node = -1);
		static void evaluateMesh(unsigned int mesh);
		static VB evaluateAttribute(const std::string& attribName, unsigned int accessorIdx);
		static std::vector<unsigned char> getBufferViewData(unsigned int bufferViewIdx);
		static std::vector<unsigned char> getDataFromBuffer(unsigned int bufferIdx, unsigned int offset, unsigned int length);
		static std::variant<std::vector<char>, std::vector<unsigned char>, std::vector<short>, std::vector<unsigned short>, std::vector<int>, std::vector<unsigned int>, std::vector<float>> convertData(const std::vector<unsigned char>& v, unsigned int type);

	private:
		static FactoryCache cache;
	};
}

#endif