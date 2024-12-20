#include <rendering/window/model/model.hpp>

Model::Model(const char* modelFilePath) {
    std::string contents = ReadFile(modelFilePath);
    this->modelFilePath = modelFilePath;
    this->parsedContent = json::parse(contents);
    this->data = ReadData();
}

std::vector<unsigned char> Model::ReadData() {
    std::string bytesText;
    std::string uri = parsedContent["buffers"][0]["uri"];

    std::string file = std::string(modelFilePath);
    std::string fileDirectory = file.substr(0, file.find_last_of("/") + 1);
    bytesText = ReadFile(fileDirectory + uri);

    std::vector<unsigned char> data(bytesText.begin(), bytesText.end());
    return data;
}

std::vector<float> Model::GetFloats(json accessor) {
    std::vector<float> floats;
    unsigned int bufferView = accessor.value("bufferView", 1);
    unsigned int count = accessor["count"];
    unsigned int accessorByteOffset = accessor.value("byteOffset", 0);
    std::string type = accessor["type"];

    json bufferView = parsedContent["bufferViews"][bufferView];
    unsigned int byteOffset = bufferView["byteOffset"];

    unsigned int numPerVect;
    if (type == "SCALAR") {
        numPerVect = 1;
    } else if (type == "VEC2") {
        numPerVect = 2;
    } else if (type == "VEC3") {
        numPerVect = 3;
    } else if (type == "VEC4") {
        numPerVect = 4;
    } else {
        throw std::invalid_argument("unsupported accessor type");
    }

    unsigned int beginningOfData = byteOffset + accessorByteOffset;
    unsigned int lengthOfData = count * numPerVect * sizeof(float);
    for (unsigned int i = 0; i < lengthOfData; i += sizeof(float)) {
        unsigned int index = beginningOfData + i;
        float value = *(float*)&data[index];
        floats.push_back(value);
    }
    
    return floats;
}

std::vector<GLuint> Model::GetIndices(json accessor) {
    std::vector<GLuint> indices;
    unsigned int bufferView = accessor.value("bufferView", 1);
    unsigned int count = accessor["count"];
    unsigned int accessorByteOffset = accessor.value("byteOffset", 0);
    std::string type = accessor["type"];

    json bufferView = parsedContent["bufferViews"][bufferView];
    unsigned int byteOffset = bufferView["byteOffset"];

    unsigned int beginningOfData = byteOffset + accessorByteOffset;
    unsigned int lengthOfData = count * sizeof(GLuint);
    for (unsigned int i = 0; i < lengthOfData; i += sizeof(GLuint)) {
        unsigned int index = beginningOfData + i;
        GLuint value = *(GLuint*)&data[index];
        indices.push_back(value);
    }
    
    return indices;
}