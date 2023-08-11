#include "../../include/Generator/Torus.h"
#include "../../include/Shared/Maths.h"

/**
 * Construtor parametrizado de um torus
 * @param radius
 * @param size
 * @param slices
 * @param stacks
 */
Torus::Torus(float outer_radius, float inner_radius, int slices ,int stacks){
    _outer_radius = outer_radius;
    _inner_radius = inner_radius;
    _slices = slices;
    _stacks = stacks;
}


void computeNormal(float z, float y, float x, Point sliceCenter, std::vector<Point>& normals){
    normals.emplace_back(Maths::normalize({z - sliceCenter.getZ(), y - sliceCenter.getY(), x - sliceCenter.getX()}));
}

/**
 *
 * Função que gera pontos e guarda-os num ficheiro
 * @param ofs (path do ficheiro)
 */
void Torus::generatePoints(std::vector<Point> & pontos, std::vector<Point> & normals, std::vector<Vec2> & texturas) const {

    float alpha1, alpha2;
    float beta;
    float r2;
    float z1, z2, z3, z4;
    float x1, x2, x3, x4;
    float y1, y2;
    Point sliceCenter;
    Point sliceCenter2;
    alpha2 = 0;

    for(int i = 0; i < _slices; i++){

        alpha1 = alpha2;
        alpha2 = (float) ((i + 1) * 2 * M_PI / _slices);

        r2 = _inner_radius;

        z2 = (_outer_radius + r2) * cos(alpha1);
        z4 = (_outer_radius + r2) * cos(alpha2);
        x2 = (_outer_radius + r2) * sin(alpha1);
        x4 = (_outer_radius + r2) * sin(alpha2);
        y2 = 0;

        sliceCenter = Point(_outer_radius * sin(alpha1), 0.0f, _outer_radius * cos(alpha1));
        sliceCenter2 = Point(_outer_radius * sin(alpha2), 0.0f, _outer_radius * cos(alpha2));

        for(int j = 0; j < _stacks; j++) {

            beta = (float) ((j + 1) * 2 * M_PI / _stacks);
            r2 = cos(beta) * _inner_radius;

            z1 = z2;
            x1 = x2;
            y1 = y2;

            z2 = (_outer_radius + r2) * cos(alpha1);
            x2 = (_outer_radius + r2) * sin(alpha1);
            y2 = _inner_radius * sin(beta);

            z3 = z4;
            x3 = x4;

            z4 = (_outer_radius + r2) * cos(alpha2);
            x4 = (_outer_radius + r2) * sin(alpha2);

            pontos.emplace_back(z3, y1, x3);
            pontos.emplace_back(z1, y1, x1);
            pontos.emplace_back(z2, y2, x2);

            computeNormal(z3, y1, x3, sliceCenter2, normals);
            computeNormal(z1, y1, x1, sliceCenter, normals);
            computeNormal(z2, y2, x2, sliceCenter, normals);

            texturas.emplace_back((float) (i + 1) / (float) _slices, (float) j / (float) _stacks);
            texturas.emplace_back((float) i / (float) _slices, (float) j / (float) _stacks);
            texturas.emplace_back((float) i / (float) _slices, (float) (j + 1) / (float) _stacks);

            pontos.emplace_back(z3, y1, x3);
            pontos.emplace_back(z2, y2, x2);
            pontos.emplace_back(z4, y2, x4);

            computeNormal(z3, y1, x3, sliceCenter2, normals);
            computeNormal(z2, y2, x2, sliceCenter, normals);
            computeNormal(z4, y2, x4, sliceCenter2, normals);

            texturas.emplace_back((float) (i + 1) / (float) _slices, (float) j / (float) _stacks);
            texturas.emplace_back((float) i / (float) _slices, (float) (j + 1) / (float) _stacks);
            texturas.emplace_back((float) (i + 1) / (float) _slices, (float) (j + 1) / (float) _stacks);

        }
    }
}
