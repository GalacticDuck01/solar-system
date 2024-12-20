#pragma once

#include <vector>
#include <json.hpp>
#include <rendering/window/mesh/mesh.hpp>
#include <utilities/utilities.hpp> 

using json = nlohmann::json;

class Model {
    public:
        Model(const char* modelFilePath);

        std::vector<unsigned char> ReadData();
        std::vector<float> GetFloats(json accessor);
        std::vector<GLuint> GetIndices(json accessor);
        void Draw(Shader& shader, Camera& camera);

        std::vector<glm::vec2> ToVec2(std::vector<float> floats);
        std::vector<glm::vec3> ToVec3(std::vector<float> floats);
        std::vector<glm::vec4> ToVec4(std::vector<float> floats);

    private:
        const char* modelFilePath;
        std::vector<unsigned char> data;
        json parsedContent;
};