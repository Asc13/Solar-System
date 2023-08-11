#include "../../include/Engine/Light.h"

Light::Light(vector<float> & amb, vector<float> & diff, vector<float> & spe, vector<float> & pos, float atenuation, LightType lightType) {
    _pos = pos;
    _atenuation = atenuation;
    _lightType = lightType;
    _amb = amb;
    _diff = diff;
    _spe = spe;
}

Light::Light(vector<float> & amb, vector<float> & diff, vector<float> & spe, vector<float> & pos, vector<float> & spotDir, float cutOff, float exponent, float atenuation, LightType lightType) {
    _pos = pos;
    _spotDir = spotDir;
    _cutOff = cutOff;
    _exponent = exponent;
    _atenuation = atenuation;
    _lightType = lightType;
    _amb = amb;
    _diff = diff;
    _spe = spe;
}

vector<float>  Light::getAmb() const {
    return _amb;
}

vector<float>  Light::getDiff() const {
    return _diff;
}

vector<float>  Light::getSpe() const {
    return _spe;
}

vector<float>  Light::getPos() const {
    return _pos;
}

vector<float>  Light::getSpotDir() const {
    return _spotDir;
}

float Light::getCutOff() const {
    return _cutOff;
}

float Light::getExponent() const {
    return _exponent;
}

float Light::getAtenuation() const {
    return _atenuation;
}

LightType Light::getLightType() {
    return _lightType;
}