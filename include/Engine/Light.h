#ifndef CG_TP_LIGHT_H
#define CG_TP_LIGHT_H

#include <vector>
using namespace std;

enum LightType {
    POINT,
    DIRECTIONAL,
    SPOT
};

class Light {
    private:
            vector<float> _amb;         // cor da componente ambiente
            vector<float> _diff;        // cor da componente difusa
            vector<float> _spe;         // cor da componente especular
            vector<float> _pos;         // _pos[4] indica se é um luz direcional ou se é um ponto
            vector<float> _spotDir;     // direção do spotlight
            float _cutOff{};            // [0..90] ou 180
            float _exponent{};          // [0..128]
            float _atenuation;          // [0..1]
            LightType _lightType;       // tipo da luz

        public:
            Light(vector<float> &, vector<float> &, vector<float> &, vector<float> &, float, LightType);
            Light(vector<float> &, vector<float> &, vector<float> &, vector<float> &, vector<float> &, float, float, float, LightType );
            vector<float> getAmb() const;
            vector<float> getDiff() const;
            vector<float> getSpe() const;
            vector<float> getPos() const;
            vector<float> getSpotDir() const;
            float getCutOff() const;
            float getExponent() const;
            float getAtenuation() const;
            LightType getLightType();
};


#endif //CG_TP_LIGHT_H
