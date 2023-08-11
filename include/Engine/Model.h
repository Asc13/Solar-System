#ifndef GENERATOR_MODELS_H
#define GENERATOR_MODELS_H

#include "../Shared/Point.h"
#include "../Shared/Vec2.h"

class Model {
    private:
        std::vector<float> _content;

    public:
        explicit Model();
        void addContent(float add);
        void reserveContent(int size);
        std::vector<float> getContent();
        void getMinMax(float & minAuxX, float & maxAuxX, float & minAuxY, float & maxAuxY, float & minAuxZ, float & maxAuxZ);
        unsigned long getVectorSize() const;
};


#endif
