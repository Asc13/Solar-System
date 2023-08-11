#ifndef CG_TP_MODELINFO_H
#define CG_TP_MODELINFO_H

#include <vector>

using namespace std;

enum ModelType {
    OBJECT,
};

class ModelInfo{
    private:
        int _vertexIndex;
        int _normalIndex;
        int _textureIndex;
        int _textureId;
        vector<float> _diffuse;
        vector<float> _specular;
        vector<float> _ambient;
        vector<float> _emissive;
        float _shininess{};
        ModelType _modelType;
        bool _flagLight;

    public:
        ModelInfo(int, int, int, int, vector<float> &, vector<float> &, vector<float> &, vector<float> &, float, ModelType, bool);
        int getVertexIndex() const;
        int getNormalIndex() const;
        int getTextureIndex() const;
        int getTextureId() const;
        vector<float> getDiffuse();
        vector<float> getAmbient();
        vector<float> getSpecular();
        vector<float> getEmissive();
        float getShininess() const;
        ModelType getModelType();
        bool afectedByLight() const;
};

#endif //CG_TP_MODELINFO_H