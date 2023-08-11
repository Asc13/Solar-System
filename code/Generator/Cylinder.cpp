#include "../../include/Generator/Cylinder.h"
#include "../../include/Shared/Point.h"

/**
 * Construtor parametrizado de um cilindro
 * @param base_radius
 * @param height
 * @param slices
 * @param stacks
 */
Cylinder::Cylinder(float base_radius, float height, int slices, int stacks) {
    _base_radius = base_radius;
    _height = height;
    _slices = slices;
    _stacks = stacks;
}

/**
 *
 * Função que gera pontos e guarda-os num ficheiro
 * @param ofs (path do ficheiro)
 */
void Cylinder::generatePoints(std::vector<Point> & pontos, std::vector<Point> & normais, vector<Vec2> & texturas) const {

    float x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4;

    for(int i = 0; i < _stacks + 2; i++) {
        for(int j = 0; j < _slices; j++) {

            if(i == _stacks + 1) {
                z1 = _base_radius * (float) cos(j * 2 * M_PI / _slices);
                x1 = _base_radius * (float) sin(j * 2 * M_PI / _slices);

                z2 = _base_radius * (float) cos((j + 1) * 2 * M_PI / _slices);
                x2 = _base_radius * (float) sin((j + 1) * 2 * M_PI / _slices);

                pontos.emplace_back(x1, - _height / 2, z1);
                pontos.emplace_back(0, - _height / 2, 0);
                pontos.emplace_back(x2, - _height / 2, z2);

                normais.emplace_back(0.0f, -1.0f, 0.0f);
                normais.emplace_back(0.0f, -1.0f, 0.0f);
                normais.emplace_back(0.0f, -1.0f, 0.0f);

                texturas.emplace_back(0.8125 + sin(j * 2 * M_PI / _slices) * 0.1875, 0.1875 + cos(j * 2 * M_PI / _slices) * 0.1875);
                texturas.emplace_back(0.8125, 0.1875);
                texturas.emplace_back(0.8125 + sin((j+1) * 2 * M_PI / _slices) * 0.1875, 0.1875 + cos((j + 1) * 2 * M_PI / _slices) * 0.1875);


            } else if(i == 0) {

                z1 = _base_radius * (float) cos(j * 2 * M_PI / _slices);
                x1 = _base_radius * (float) sin(j * 2 * M_PI / _slices);

                z2 = _base_radius * (float) cos((j + 1) * 2 * M_PI / _slices);
                x2 = _base_radius * (float) sin((j + 1) * 2 * M_PI / _slices);

                pontos.emplace_back(x2,_height / 2, z2);
                pontos.emplace_back(0.0f, _height / 2, 0.0f);
                pontos.emplace_back(x1, _height / 2, z1);

                normais.emplace_back(0.0f, 1.0f, 0.0f);
                normais.emplace_back(0.0f, 1.0f, 0.0f);
                normais.emplace_back(0.0f, 1.0f, 0.0f);

                texturas.emplace_back(0.4375 + sin((j+1) * 2 * M_PI / _slices) * 0.1875, 0.1875 + cos((j+1) * 2 * M_PI / _slices) * 0.1875);
                texturas.emplace_back(0.4375, 0.1875);
                texturas.emplace_back(0.4375 + sin(j * 2 * M_PI / _slices) * 0.1875, 0.1875 + cos(j * 2 * M_PI / _slices) * 0.1875);

            } else {

                z1 = _base_radius * (float) cos(j * 2 * M_PI / _slices);
                x1 = _base_radius * (float) sin(j * 2 * M_PI / _slices);
                y1 = _height/2 - (_height / (float) _stacks) * (float) i;

                z2 = _base_radius * (float) cos((j + 1) * 2 * M_PI / _slices);
                x2 = _base_radius * (float) sin((j + 1) * 2 * M_PI / _slices);
                y2 = _height/2 - (_height / (float) _stacks) * (float) i;

                z3 = _base_radius * (float) cos(j * 2 * M_PI / _slices);
                x3 = _base_radius * (float) sin(j * 2 * M_PI / _slices);
                y3 = _height/2 - (_height / (float) _stacks) * (float) (i - 1);

                z4 = _base_radius * (float) cos((j + 1) * 2 * M_PI / _slices);
                x4 = _base_radius * (float) sin((j + 1) * 2 * M_PI / _slices);
                y4 = _height/2 - (_height / (float) _stacks) * (float) (i - 1);

                pontos.emplace_back(x4, y4, z4);
                pontos.emplace_back(x1, y1, z1);
                pontos.emplace_back(x2, y2, z2);

                normais.emplace_back(Point(x4 / _base_radius, 0.0f, z4 / _base_radius));
                normais.emplace_back(Point(x1 / _base_radius, 0.0f, z1 / _base_radius));
                normais.emplace_back(Point(x2 / _base_radius, 0.0f, z2 / _base_radius));

                texturas.emplace_back(((float) (j + 1) / _slices), 1.0 - (0.625 / _stacks) * (i - 1));
                texturas.emplace_back(((float) j / _slices), 1.0 - (0.625/ _stacks) * i);
                texturas.emplace_back(((float) (j + 1) / _slices), 1.0 - (0.625/ _stacks) * i);

                pontos.emplace_back(Point(x1, y1, z1));
                pontos.emplace_back(Point(x4, y4, z4));
                pontos.emplace_back(Point(x3, y3, z3));

                normais.emplace_back(Point(x1 / _base_radius, 0.0f, z1 / _base_radius));
                normais.emplace_back(Point(x4 / _base_radius, 0.0f, z4 / _base_radius));
                normais.emplace_back(Point(x3 / _base_radius, 0.0f, z3 / _base_radius));

                texturas.emplace_back(((float) 1 / _slices) * j, 1.0 - (0.625 / _stacks) * i);
                texturas.emplace_back(((float) 1 / _slices) * (j + 1), 1.0 - (0.625 / _stacks) * (i - 1));
                texturas.emplace_back(((float) 1 / _slices) * j, 1.0 - (0.625/ _stacks) * (i - 1));
            }
        }
    }
}