#include "../../include/Generator/Sphere.h"
#include "../../include/Shared/Point.h"
#include "../../include/Shared/Maths.h"

/**
 *
 * Construtor parametrizado de uma esfera
 * @param radius
 * @param slices
 * @param stacks
 */
Sphere::Sphere(float radius, int slices, int stacks){
	_radius = radius;
	_slices = slices;
	_stacks = stacks;
}

/**
 *
 * Função que gera pontos e guarda-os num ficheiro
 * @param ofs (path do ficheiro)
 */

void Sphere::generatePoints(vector<Point> & pontos, vector<Point> & normais, vector<Vec2> & texturas) const {

    float x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;

    for(int i = 0; i < _stacks; i++) {
        for(int j = 0; j < _slices + 1; j++) {

                z1 = _radius * (float) cos((j * 2) * M_PI / _slices) * (float) cos(i * M_PI / _stacks - M_PI/2);
                x1 = _radius * (float) sin((j * 2) * M_PI / _slices) * (float) cos(i * M_PI / _stacks - M_PI/2);
                y1 = _radius * (float) sin(i * M_PI / _stacks- M_PI/2);

                z2 = _radius * (float) cos((j + 1) * 2 * M_PI / _slices) * (float) cos(i * M_PI / _stacks - M_PI/2);
                x2 = _radius * (float) sin((j + 1) * 2 * M_PI / _slices) * (float) cos(i * M_PI / _stacks - M_PI/2);
                y2 = _radius * (float) sin(i * M_PI / _stacks- M_PI/2);

                z3 = _radius * (float) cos((j * 2) * M_PI / _slices) * (float) cos((i + 1) * M_PI / _stacks - M_PI/2);
                x3 = _radius * (float) sin((j * 2) * M_PI / _slices) * (float) cos((i + 1) * M_PI / _stacks - M_PI/2);
                y3 = _radius * (float) sin((i + 1) * M_PI / _stacks- M_PI/2);

                z4 = _radius * (float) cos((j + 1) * 2 * M_PI / _slices) * (float) cos((i + 1) * M_PI / _stacks - M_PI/2);
                x4 = _radius * (float) sin((j + 1) * 2 * M_PI / _slices) * (float) cos((i + 1) * M_PI / _stacks - M_PI/2);
                y4 = _radius * (float) sin((i + 1) * M_PI / _stacks- M_PI/2);

                pontos.emplace_back(x3, y3, z3);
                pontos.emplace_back(x1, y1, z1);
                pontos.emplace_back(x2, y2, z2);

                normais.emplace_back(x3 / _radius, y3 / _radius, z3 / _radius);
                normais.emplace_back(x1 / _radius, y1 / _radius, z1 / _radius);
                normais.emplace_back(x2 / _radius, y2 / _radius, z2 / _radius);

                texturas.emplace_back((float) j / _slices, ((float) (i + 1)) / (float) _stacks);
                texturas.emplace_back((float) j / _slices, ((float) i) / (float) _stacks);
                texturas.emplace_back((float) (j + 1) / _slices, ((float) i) / (float) _stacks);

                pontos.emplace_back(x2, y2, z2);
                pontos.emplace_back(x4, y4, z4);
                pontos.emplace_back(x3, y3, z3);

                normais.emplace_back(x2 / _radius, y2 / _radius, z2 / _radius);
                normais.emplace_back(x4 / _radius, y4 / _radius, z4 / _radius);
                normais.emplace_back(x3 / _radius, y3 / _radius, z3 / _radius);

                texturas.emplace_back((float) (j + 1) / _slices, ((float) i) / (float) _stacks);
                texturas.emplace_back((float) (j + 1) / _slices, ((float) (i + 1)) / (float) _stacks);
                texturas.emplace_back((float) j / _slices, ((float) (i + 1)) / (float) _stacks);

        }
    }
}
