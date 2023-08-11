#include "../../include/Engine/ModelInfo.h"

ModelInfo::ModelInfo(int vertexIndex, int normalIndex, int textureIndex, int textureId, vector<float>& diffuse, vector<float>& ambient, vector<float>& specular, vector<float>& emissive, float shininess, ModelType modelType, bool flagLight) {
    _vertexIndex = vertexIndex;
    _normalIndex = normalIndex;
    _textureIndex = textureIndex;
    _textureId = textureId;
    _modelType = modelType;
    _diffuse = diffuse;
    _ambient = ambient;
    _specular = specular;
    _emissive = emissive;
    _shininess = shininess;
    _flagLight = flagLight;
}

int ModelInfo::getVertexIndex() const {
    return _vertexIndex;
}

int ModelInfo::getNormalIndex() const {
    return _normalIndex;
}

int ModelInfo::getTextureIndex() const {
    return _textureIndex;
}

int ModelInfo::getTextureId() const {
    return _textureId;
}

ModelType ModelInfo::getModelType() {
    return _modelType;
}

vector<float> ModelInfo::getDiffuse(){
    return _diffuse;
}

vector<float> ModelInfo::getAmbient(){
    return _ambient;
}

vector<float> ModelInfo::getSpecular(){
    return _specular;
}

vector<float> ModelInfo::getEmissive() {
    return _emissive;
}

float ModelInfo::getShininess() const {
    return _shininess;
}

bool ModelInfo::afectedByLight() const {
    return _flagLight;
}