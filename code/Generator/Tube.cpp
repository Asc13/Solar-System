#include "../../include/Generator/Tube.h"

/**
 * Construtor parametrizado de um tubo
 * @param baseRadius
 * @param innerRadius
 * @param height
 * @param slices
 * @param stacks
 */
Tube::Tube(float baseRadius, float innerRadius, float height, int slices, int stacks) : Cylinder(baseRadius, height, slices, stacks) {
    _inner_radius = innerRadius;
}

/**
 *
 * Função que gera pontos e guarda-os num ficheiro
 * @param ofs (path do ficheiro)
 */
void Tube::generatePoints(std::vector<Point>& pontos, std::vector<Point>& normais, std::vector<Vec2> & texturas) {

    float x1, x2, x3, x4, y1, y2, z1, z2, z3, z4, inner_x1, inner_x2, inner_x3, inner_x4, inner_z1,inner_z2, inner_z3, inner_z4;

    for(int i = 0; i < _stacks + 2; i++) {
        for(int j = 0; j < _slices; j++) {

            if(i == _stacks + 1){

                z1 = _base_radius * (float) cos(j * 2 * M_PI / _slices);
                x1 = _base_radius * (float) sin(j * 2 * M_PI / _slices);

                z2 = _base_radius * (float) cos((j + 1) * 2 * M_PI / _slices);
                x2 = _base_radius * (float) sin((j + 1) * 2 * M_PI / _slices);

                z3 = _inner_radius * (float) cos(j * 2 * M_PI / _slices);
                x3 = _inner_radius * (float) sin(j * 2 * M_PI / _slices);

                z4 = _inner_radius * (float) cos((j + 1) * 2 * M_PI / _slices);
                x4 = _inner_radius * (float) sin((j + 1) * 2 * M_PI / _slices);

                pontos.emplace_back(x1, -_height / 2, z1);
                pontos.emplace_back(x3, -_height / 2, z3);
                pontos.emplace_back(x4, -_height / 2, z4);

                normais.emplace_back(0.0f, -1.0f, 0.0f);
                normais.emplace_back(0.0f, -1.0f, 0.0f);
                normais.emplace_back(0.0f, -1.0f, 0.0f);

                texturas.emplace_back(1.0f, 0.0f);
                texturas.emplace_back(0.0f, 0.0f);
                texturas.emplace_back(0.0f, 1.0f);

                pontos.emplace_back(x4, -_height / 2, z4);
                pontos.emplace_back(x2, -_height / 2, z2);
                pontos.emplace_back(x1, -_height / 2, z1);

                normais.emplace_back(0.0f, -1.0f, 0.0f);
                normais.emplace_back(0.0f, -1.0f, 0.0f);
                normais.emplace_back(0.0f, -1.0f, 0.0f);

                texturas.emplace_back(0.0f, 1.0f);
                texturas.emplace_back(1.0f, 1.0f);
                texturas.emplace_back(1.0f, 0.0f);

            } else if(i == 0) {

                z1 = _base_radius * (float) cos(j * 2 * M_PI / _slices);
                x1 = _base_radius * (float) sin(j * 2 * M_PI / _slices);

                z2 = _base_radius * (float) cos((j + 1) * 2 * M_PI / _slices);
                x2 = _base_radius * (float) sin((j + 1) * 2 * M_PI / _slices);

                z3 = _inner_radius * (float) cos(j * 2 * M_PI / _slices);
                x3 = _inner_radius * (float) sin(j * 2 * M_PI / _slices);

                z4 = _inner_radius * (float) cos((j + 1) * 2 * M_PI / _slices);
                x4 = _inner_radius * (float) sin((j + 1) * 2 * M_PI / _slices);

                pontos.emplace_back(x4, _height / 2, z4);
                pontos.emplace_back(x3, _height / 2, z3);
                pontos.emplace_back(x1, _height / 2, z1);

                normais.emplace_back(0.0f, 1.0f, 0.0f);
                normais.emplace_back(0.0f, 1.0f, 0.0f);
                normais.emplace_back(0.0f, 1.0f, 0.0f);

                texturas.emplace_back(0.0f, 1.0f);
                texturas.emplace_back(0.0f, 0.0f);
                texturas.emplace_back(1.0f, 0.0f);

                pontos.emplace_back(x1, _height/  2, z1);
                pontos.emplace_back(x2, _height / 2, z2);
                pontos.emplace_back(x4, _height / 2, z4);

                normais.emplace_back(0.0f, 1.0f, 0.0f);
                normais.emplace_back(0.0f, 1.0f, 0.0f);
                normais.emplace_back(0.0f, 1.0f, 0.0f);

                texturas.emplace_back(1.0f, 0.0f);
                texturas.emplace_back(1.0f, 1.0f);
                texturas.emplace_back(0.0f, 1.0f);

            } else {
                y1 = _height / 2 - (_height / (float) _stacks) * (float) i;
                y2 = _height / 2 - (_height / (float) _stacks) * (float) (i - 1);

                z1 = _base_radius * (float) cos(j * 2 * M_PI / _slices);
                x1 = _base_radius * (float) sin(j * 2 * M_PI / _slices);

                z2 = _base_radius * (float) cos((j + 1) * 2 * M_PI / _slices);
                x2 = _base_radius * (float) sin((j + 1) * 2 * M_PI / _slices);

                z3 = _base_radius * (float) cos(j * 2 * M_PI / _slices);
                x3 = _base_radius * (float) sin(j * 2 * M_PI / _slices);

                z4 = _base_radius * (float) cos((j + 1) * 2 * M_PI / _slices);
                x4 = _base_radius * (float) sin((j + 1) * 2 * M_PI / _slices);

                inner_z1 = _inner_radius * (float) cos(j * 2 * M_PI / _slices);
                inner_x1 = _inner_radius * (float) sin(j * 2 * M_PI / _slices);

                inner_z2 = _inner_radius * (float) cos((j + 1) * 2 * M_PI / _slices);
                inner_x2 = _inner_radius * (float) sin((j + 1) * 2 * M_PI / _slices);

                inner_z3 = _inner_radius * (float) cos(j * 2 * M_PI / _slices);
                inner_x3 = _inner_radius * (float) sin(j * 2 * M_PI / _slices);

                inner_z4 = _inner_radius * (float) cos((j + 1) * 2 * M_PI / _slices);
                inner_x4 = _inner_radius * (float) sin((j + 1) * 2 * M_PI / _slices);

                pontos.emplace_back(x4, y2, z4);
                pontos.emplace_back(x3, y2, z3);
                pontos.emplace_back(x1, y1, z1);

                normais.emplace_back((float) sin((j + 1) * 2 * M_PI / _slices), 0.0f, (float) cos((j + 1) * 2 * M_PI / _slices));
                normais.emplace_back((float) sin(j * 2 * M_PI / _slices), 0.0f,  (float) cos(j * 2 * M_PI / _slices));
                normais.emplace_back((float) sin(j * 2 * M_PI / _slices), 0.0f, (float) cos(j * 2 * M_PI / _slices));

                texturas.emplace_back(0.0f, 0.0f);
                texturas.emplace_back(0.0f, 0.0f);
                texturas.emplace_back(0.0f, 0.0f);

                pontos.emplace_back(x4, y2, z4);
                pontos.emplace_back(x1, y1, z1);
                pontos.emplace_back(x2, y1, z2);

                normais.emplace_back((float) sin((j + 1) * 2 * M_PI / _slices), 0.0f, (float) cos((j + 1) * 2 * M_PI / _slices));
                normais.emplace_back((float) sin(j * 2 * M_PI / _slices), 0.0f, _inner_radius * (float) cos(j * 2 * M_PI / _slices));
                normais.emplace_back((float) sin((j + 1) * 2 * M_PI / _slices), 0.0f, (float) cos((j + 1) * 2 * M_PI / _slices));

                texturas.emplace_back(0.0f, 0.0f);
                texturas.emplace_back(0.0f, 0.0f);
                texturas.emplace_back(0.0f, 0.0f);

                pontos.emplace_back(inner_x1, y1, inner_z1);
                pontos.emplace_back(inner_x3, y2, inner_z3);
                pontos.emplace_back(inner_x4, y2, inner_z4);

                normais.emplace_back((float) -sin(j * 2 * M_PI / _slices), 0.0f, (float) -sin(j * 2 * M_PI / _slices));
                normais.emplace_back((float) -sin(j * 2 * M_PI / _slices), 0.0f, (float) -cos(j * 2 * M_PI / _slices));
                normais.emplace_back((float) -sin((j + 1) * 2 * M_PI / _slices), 0.0f, (float) -cos((j + 1) * 2 * M_PI / _slices));

                texturas.emplace_back(0.0f, 0.0f);
                texturas.emplace_back(0.0f, 0.0f);
                texturas.emplace_back(0.0f, 0.0f);

                pontos.emplace_back(inner_x2, y1, inner_z2);
                pontos.emplace_back(inner_x1, y1, inner_z1);
                pontos.emplace_back(inner_x4, y2, inner_z4);

                normais.emplace_back((float) -sin((j + 1) * 2 * M_PI / _slices), 0.0f, (float) cos((j + 1) * 2 * M_PI / _slices));
                normais.emplace_back((float) -sin(j * 2 * M_PI / _slices), 0.0f, (float) -cos(j * 2 * M_PI / _slices));
                normais.emplace_back((float) -sin((j + 1) * 2 * M_PI / _slices), 0.0f, (float) -cos((j + 1) * 2 * M_PI / _slices));

                texturas.emplace_back(0.0f, 0.0f);
                texturas.emplace_back(0.0f, 0.0f);
                texturas.emplace_back(0.0f, 0.0f);
            }
        }
    }
}
