#include "../../include/Generator/Cone.h"


/**
 *
 * Construtor parametrizado do tipo Cone
 * @param base_radius (raio da base)
 * @param height (altura)
 * @param slices
 * @param stacks
 */
Cone::Cone(float base_radius, float height, int slices, int stacks) {
    _base_radius = base_radius;
    _height = height;
    _slices = slices;
    _stacks = stacks;
}

/**
 *
 * Função que devolve o raio da base
 * @return _base_radius (raio da base)
 */
float Cone::getBaseRadius() const{
    return _base_radius;
}

/**
 *
 * Função que devolve a altura
 * @return _height (altura)
 */
float Cone::getHeight() const{
    return _height;
}

/**
 *
 * Função que devolve o número de slices
 * @return _slices
 */
int Cone::getSlices() const {
    return _slices;
}

/**
 *
 * Função que devolve o número de stacks
 * @return _stacks
 */
int Cone::getStacks() const {
    return _stacks;
}

/**
 *
 * Função que gera pontos e guarda-os num ficheiro
 * @param ofs (path do ficheiro)
 */
void Cone::generatePoints(vector<Point> & res, vector<Point> & normals, vector<Vec2> & textureCoordinates) {

    float y1, y2;
    float z1, z2, z3, z4;
    float x1, x2, x3, x4;
    float r1, r2;

    z2 = _base_radius;
    x2 = 0.0f;

    //base do cone
    for(int i = 0; i < getSlices(); i++){
        z1 = z2;
        z2 = _base_radius * (float) cos((i + 1) * 2 * M_PI / _slices);
        z3 = 0.0f;

        x1 = x2;
        x2 = _base_radius * (float) sin((i + 1) * 2 * M_PI / _slices);
        x3 = 0.0f;

        res.emplace_back(x1, -_height / 2, z1);
        res.emplace_back(x3, -_height / 2, z3);
        res.emplace_back(x2, -_height / 2, z2);

        normals.emplace_back(0.0f, -1.0f, 0.0f);
        normals.emplace_back(0.0f, -1.0f, 0.0f);
        normals.emplace_back(0.0f, -1.0f, 0.0f);

        textureCoordinates.emplace_back(0.5 + 0.25 * x1 / _base_radius, 0.25 + 0.25 * z1 / _base_radius);
        textureCoordinates.emplace_back(0.5, 0.25);
        textureCoordinates.emplace_back(0.5 + 0.25 * x2 / _base_radius, 0.25 + 0.25 * z2 / _base_radius);
    }

    r2 = _base_radius;
    y2 = - _height / 2;

    //resto do cone
    for(int i = 0; i < _stacks; i++) {

        r1 = r2;
        r2 = _base_radius - (float) (i+1) * _base_radius / (float) _stacks;

        z3 = r1;
        z4 = r2;

        x3 = 0;
        x4 = 0;

        y1 = y2;
        y2 = (float) (i+1) * _height / (float) _stacks - _height / 2;

        for(int j = 0; j < _slices; j++) {

            if(i == _stacks - 1) {
                z1 = z3;
                z3 = r1 * (float) cos((j+1) * 2 * M_PI / _slices);

                x1 = x3;
                x3 = r1 * (float) sin((j+1) * 2 * M_PI / _slices);

                res.emplace_back(x3, y1, z3);
                res.emplace_back(0, y2, 0);
                res.emplace_back(x1, y1, z1);

                normals.emplace_back(sin((j + 1) * 2 * M_PI / _slices), _base_radius/_height, cos((j + 1) * 2 * M_PI / _slices));
                normals.emplace_back(0.0f, 1.0f, 0.0f);
                normals.emplace_back(x1 / r1, _base_radius/_height, z1 / r1);

                textureCoordinates.emplace_back((float) (j + 1) / _slices + i * 0.5 / _stacks, i * 0.5 / _stacks + 0.5);
                textureCoordinates.emplace_back(0.5f, 1.0f);
                textureCoordinates.emplace_back((float) j / _slices + i * 0.5f / _stacks, i * 0.5f / _stacks + 0.5);

            } else {

                z1 = z3;

                z2 = z4;
                z3 = r1 * (float) cos((j + 1) * 2 * M_PI / _slices);
                z4 = r2 * (float) cos((j + 1) * 2 * M_PI / _slices);

                x1 = x3;
                x2 = x4;
                x3 = r1 * (float) sin((j + 1) * 2 * M_PI / _slices);
                x4 = r2 * (float) sin((j + 1) * 2 * M_PI / _slices);

                res.emplace_back(x3, y1, z3);
                res.emplace_back(x2, y2, z2);
                res.emplace_back(x1, y1, z1);

                normals.emplace_back(x3 / r1, _base_radius / _height, z3 / r1);
                normals.emplace_back(x2 / r2, _base_radius / _height, z2 / r2);
                normals.emplace_back(x1 / r1, _base_radius / _height, z1 / r1);

                textureCoordinates.emplace_back((float) (j + 1) / _slices + i * 0.5 / _stacks, i * 0.5 / _stacks + 0.5);
                textureCoordinates.emplace_back((float) j / _slices + (i + 1) * 0.5f / _stacks, (i + 1) * 0.5f / _stacks + 0.5);
                textureCoordinates.emplace_back((float) j / _slices + i * 0.5f / _stacks, i * 0.5f / _stacks + 0.5);

                res.emplace_back(x3, y1, z3);
                res.emplace_back(x4, y2, z4);
                res.emplace_back(x2, y2, z2);

                normals.emplace_back(x3 / r1, _base_radius / _height, z3 / r1);
                normals.emplace_back(x4 / r2, _base_radius / _height, z4 / r2);
                normals.emplace_back(x1 / r1, _base_radius / _height, z1 / r1);

                textureCoordinates.emplace_back((float) (j + 1) / _slices + i * 0.5 / _stacks, i * 0.5 / _stacks + 0.5);
                textureCoordinates.emplace_back((float) (j + 1) / _slices + (i + 1) * 0.5 / _stacks, (i + 1) * 0.5 / _stacks + 0.5);
                textureCoordinates.emplace_back((float) j / _slices + i * 0.5 / _stacks, (i + 1) * 0.5 / _stacks + 0.5);
            }
        }
    }
}
