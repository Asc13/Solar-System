#include "../../include/Generator/ConicalFrustum.h"
#include "../../include/Shared/Maths.h"

/**
 *
 * Construtor parametrizado de uma frustum cónico
 * @param base_radius
 * @param height
 * @param height of cut
 * @param slices
 * @param stacks
 */
ConicalFrustum::ConicalFrustum(float base_radius, float height_cone, float height_cut, int slices, int stacks): Cone(base_radius, height_cone, slices, stacks) {
    _height_cut = height_cut;
}

/**
 *
 * Função que gera pontos e guarda-os num ficheiro
 * @param ofs (path do ficheiro)
 */
void ConicalFrustum::generatePoints(std::vector<Point> & res, std::vector<Point> & normals, std::vector<Vec2> & textureCoordinates)  {

    float y1, y2;
    float z1, z2, z3, z4;
    float x1, x2, x3, x4;
    float r1, r2;

    z2 = _base_radius;
    x2 = 0;
    float maxHeight = _height_cut < _height ? _height_cut : _height;

    //base do cone
    for(int i = 0; i < getSlices(); i++){
        z1 = z2;
        z2 = _base_radius * (float) cos((i + 1) * 2 * M_PI / _slices);
        z3 = 0.0f;

        x1 = x2;
        x2 = _base_radius * (float) sin((i + 1) * 2 * M_PI / _slices);
        x3 = 0.0f;

        res.emplace_back(x1, -_height_cut / 2, z1);
        res.emplace_back(x3, -_height_cut / 2, z3);
        res.emplace_back(x2, -_height_cut / 2, z2);

        normals.emplace_back(0.0f, -1.0f, 0.0f);
        normals.emplace_back(0.0f, -1.0f, 0.0f);
        normals.emplace_back(0.0f, -1.0f, 0.0f);

        textureCoordinates.emplace_back(0.5 + 0.25 * x1 / _base_radius, 0.25 + 0.25 * z1 / _base_radius);
        textureCoordinates.emplace_back(0.5, 0.25);
        textureCoordinates.emplace_back(0.5 + 0.25 * x2 / _base_radius, 0.25 + 0.25 * z2 / _base_radius);
    }

    r2 = _base_radius;
    y2 = -maxHeight / 2;

    //resto do cone
    for(int i = 0; i < _stacks; i++) {

        r1 = r2;
        r2 = _base_radius - (float) (i+1) * _base_radius / ((float) _stacks * _height / maxHeight);

        z3 = r1;
        z4 = r2;

        x3 = 0;
        x4 = 0;

        y1 = y2;
        y2 = (float) (i+1) * maxHeight / (float) _stacks - maxHeight / 2;

        for(int j = 0; j < _slices; j++) {
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

            normals.emplace_back(Maths::normalize({x3 / r1, _base_radius / _height_cut, z3 / r1}));
            normals.emplace_back(Maths::normalize({x2 / r2, _base_radius / _height_cut, z2 / r2}));
            normals.emplace_back(Maths::normalize({x1 / r1, _base_radius / _height_cut, z1 / r1}));

            textureCoordinates.emplace_back((float) (j + 1) / _slices + i * 0.5 / _stacks, i * 0.5 / _stacks + 0.5);
            textureCoordinates.emplace_back((float) j / _slices + (i + 1) * 0.5f / _stacks, (i + 1) * 0.5f / _stacks + 0.5);
            textureCoordinates.emplace_back((float) j / _slices + i * 0.5f / _stacks, i * 0.5f / _stacks + 0.5);

            res.emplace_back(x3, y1, z3);
            res.emplace_back(x4, y2, z4);
            res.emplace_back(x2, y2, z2);

            normals.emplace_back(Maths::normalize({x3 / r1, _base_radius / _height_cut, z3 / r1}));
            normals.emplace_back(Maths::normalize({x4 / r2, _base_radius / _height_cut, z4 / r2}));
            normals.emplace_back(Maths::normalize({x2 / r2, _base_radius / _height_cut, z2 / r2}));

            textureCoordinates.emplace_back((float) (j + 1) / _slices + i * 0.5 / _stacks, i * 0.5 / _stacks + 0.5);
            textureCoordinates.emplace_back((float) (j + 1) / _slices + (i + 1) * 0.5 / _stacks, (i + 1) * 0.5 / _stacks + 0.5);
            textureCoordinates.emplace_back((float) j / _slices + i * 0.5 / _stacks, (i + 1) * 0.5 / _stacks + 0.5);

            if(i == _stacks - 1){

                res.emplace_back(x4, y2, z4);
                res.emplace_back(0.0f, y2, 0.0f);
                res.emplace_back(x2, y2, z2);

                normals.emplace_back(x4 / r2, 1.0f, z4 / r2);
                normals.emplace_back(0.0f, 1.0f, 0.0f);
                normals.emplace_back(x2 / r2, 1.0f, z2 / r2);

                textureCoordinates.emplace_back((float) (j + 1) / _slices + i * 0.5 / _stacks, i * 0.5 / _stacks + 0.5);
                textureCoordinates.emplace_back(0.5f, 1.0f);
                textureCoordinates.emplace_back((float) j / _slices + i * 0.5f / _stacks, i * 0.5f / _stacks + 0.5);
            }
        }
    }
}