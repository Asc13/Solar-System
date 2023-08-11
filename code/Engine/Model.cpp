#include "../../include/Engine/Model.h"


Model::Model() = default;

void Model::addContent(float add) {
    _content.push_back(add);
}

void Model::reserveContent(int size) {
    _content.reserve(size);
}

std::vector<float> Model::getContent() {
    return _content;
}

void Model::getMinMax(float & minAuxX, float & maxAuxX, float & minAuxY, float & maxAuxY, float & minAuxZ, float & maxAuxZ) {

    float x, y, z;

    for (int i = 0; i < _content.size(); i+=3) {

        x = _content[i]; y = _content[i + 1]; z = _content[i + 2];

        if(minAuxX > x) minAuxX = x;
        if(maxAuxX < x) maxAuxX = x;

        if(minAuxY > y) minAuxY = y;
        if(maxAuxY < y) maxAuxY = y;

        if(minAuxZ > z) minAuxZ = z;
        if(maxAuxZ < z) maxAuxZ = z;

    }
}

unsigned long Model::getVectorSize() const {
    return _content.size();
}

