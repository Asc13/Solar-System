#include "../../include/Generator/Plane.h"

/**
 *
 * Construtor parametrizado do tipo Plane
 * @param width (largura)
 * @param length (comprimento)
 */
Plane::Plane(float width, float length, int divisions){
    _width = width;
    _length = length;
    _divisions = divisions;
}

/**
 *
 * Função que gera pontos e guarda-os num ficheiro
 * @param ofs (path do ficheiro)
 */
void Plane::generatePoints(std::vector<Point> & pontos, std::vector<Point> & normais, std::vector<Vec2> & texturas) const {

    int spe = _divisions + 1;

    float deltaXvec, deltaZvec;

    float x = -(_width / 2.0f), z = -(_length / 2.0f);

    float deltaX = _width / ((float) spe);
    float deltaZ = _length / ((float) spe);

    float deltaXT = 1.0f / ((float) spe);
    float deltaZT = 1.0f / ((float) spe);

    for(int i = 0; i < spe; i++) {
        deltaXvec = deltaX * (float) i;

        for(int j = 0; j < spe; j++) {
            deltaZvec = deltaZT * (float) j;

            pontos.emplace_back(x + deltaXvec + deltaX, 0.0f, z + deltaZvec);
            pontos.emplace_back(x + deltaXvec, 0.0f, z + deltaZvec);
            pontos.emplace_back(x + deltaXvec, 0.0f, z + deltaZvec + deltaZ);

            normais.emplace_back(0.0f, 1.0f, 0.0f);
            normais.emplace_back(0.0f, 1.0f, 0.0f);
            normais.emplace_back(0.0f, 1.0f, 0.0f);

            texturas.emplace_back(deltaXT * (float) (i + 1), 1.0f - deltaZT * (float) j);
            texturas.emplace_back(deltaXT * (float) i, 1.0f - deltaZT * (float) j);
            texturas.emplace_back(deltaXT * (float) i, 1.0f - deltaZT * (float) (j + 1));

            pontos.emplace_back(x + deltaXvec, 0.0f, z + deltaZvec + deltaZ);
            pontos.emplace_back(x + deltaXvec + deltaX, 0.0f, z + deltaZvec + deltaZ);
            pontos.emplace_back(x + deltaXvec + deltaX, 0.0f, z + deltaZvec);

            normais.emplace_back(0.0f, 1.0f, 0.0f);
            normais.emplace_back(0.0f, 1.0f, 0.0f);
            normais.emplace_back(0.0f, 1.0f, 0.0f);

            texturas.emplace_back(deltaXT * (float) i, 1.0f - deltaZT * (float) (j + 1));
            texturas.emplace_back(deltaXT * (float) (i + 1), 1.0f - deltaZT * (float) (j + 1));
            texturas.emplace_back(deltaXT * (float) (i + 1), 1.0f - deltaZT * (float) j);
        }
    }

}
