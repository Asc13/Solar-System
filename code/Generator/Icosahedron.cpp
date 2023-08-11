#include "../../include/Generator/Icosahedron.h"
#include "../../include/Shared/Point.h"
#include "../../include/Shared/Maths.h"

using namespace std;

/**
 *
 * Construtor parametrizado de um icosahedro
 * @param length
 * @param width
 * @param dpe
 */
Icosahedron::Icosahedron(float length, float width, int dpe) {
    _length = length;
    _width = width;
    _dpe = dpe;
}

/**
 *
 * Função que gera pontos e guarda-os num ficheiro
 * @param ofs (path do ficheiro)
 */
void Icosahedron::generatePoints(vector<Point> & pontos, vector<Point> & normais, vector<Vec2> & texturas) const {

    float halfL = _length / 2;
    float halfW = _width / 2;

    // 1º Ponto Top Right
    Point p1 = Point(halfW, halfL, 0.0f);

    // 2º Ponto Top Left
    Point p2 = Point(-halfW, halfL, 0.0f);

    //3º Ponto Bottom Right
    Point p3 = Point(halfW, -halfL, 0.0f);

    // 4º Ponto Bottom Left
    Point p4 = Point(-halfW, -halfL, 0.0f);

    // 1º Ponto Back Right
    Point p5 = Point(halfL, 0.0f, -halfW);

    // 2º Ponto Back Left
    Point p6 = Point(-halfL, 0.0f, -halfW);

    // 3º Ponto Front Right
    Point p7 = Point(halfL, 0.0f, halfW);

    // 4º Ponto Front Left
    Point p8 = Point(-halfL, 0.0f, halfW);

    // 1º Ponto Top Back
    Point p9 = Point(0.0f, halfW, -halfL);

    // 2º Ponto Bottom Back
    Point p10 = Point(0.0f, -halfW, -halfL);

    // 3º Ponto Top Front
    Point p11 = Point(0.0f, halfW, halfL);

    // 4º Ponto Bottom Front
    Point p12 = Point(0.0f, -halfW, halfL);

    float deltaW = 1.0f / 5.0f;
    float deltaH = 1.0f / 4.0f;

    geodesicTriangles(p1, p2, p11, pontos, normais, texturas, 0.0f, 0.0f);
    geodesicTriangles(p9, p2, p1, pontos, normais, texturas, deltaW * 1.0f, 0.0f);
    geodesicTriangles(p11, p7, p1, pontos, normais, texturas, deltaW * 2.0f, 0.0f);
    geodesicTriangles(p1, p5, p9, pontos, normais, texturas, deltaW * 3.0f, 0.0f);
    geodesicTriangles(p2, p8, p11, pontos, normais, texturas, deltaW * 4.0f, 0.0f);
    geodesicTriangles(p9, p6, p2, pontos, normais, texturas, 0.0f, deltaH * 1.0f);
    geodesicTriangles(p5, p1, p7, pontos, normais, texturas, deltaW * 1.0f, deltaH * 1.0f);
    geodesicTriangles(p8, p2, p6, pontos, normais, texturas, deltaW * 2.0f, deltaH * 1.0f);
    geodesicTriangles(p11, p8, p12, pontos, normais, texturas, deltaW * 3.0f, deltaH * 1.0f);
    geodesicTriangles(p12, p7, p11, pontos, normais, texturas, deltaW * 4.0f, deltaH * 1.0f);
    geodesicTriangles(p10, p6, p9, pontos, normais, texturas, 0.0f, deltaH * 2.0f);
    geodesicTriangles(p9, p5, p10, pontos, normais, texturas, deltaW * 1.0f, deltaH * 2.0f);
    geodesicTriangles(p12, p8, p4, pontos, normais, texturas, deltaW * 2.0f, deltaH * 2.0f);
    geodesicTriangles(p4, p6, p10, pontos, normais, texturas, deltaW * 3.0f, deltaH * 2.0f);
    geodesicTriangles(p12, p4, p3, pontos, normais, texturas, deltaW * 4.0f, deltaH * 2.0f);
    geodesicTriangles(p3, p4, p10, pontos, normais, texturas, 0.0f, deltaH * 3.0f);
    geodesicTriangles(p7, p3, p5, pontos, normais, texturas, deltaW * 1.0f, deltaH * 3.0f);
    geodesicTriangles(p6, p4, p8, pontos, normais, texturas, deltaW * 2.0f, deltaH * 3.0f);
    geodesicTriangles(p3, p7, p12, pontos, normais, texturas, deltaW * 3.0f, deltaH * 3.0f);
    geodesicTriangles(p10, p5, p3, pontos, normais, texturas, deltaW * 4.0f, deltaH * 3.0f);

}

void Icosahedron::geodesicTriangles(Point p1, Point p2, Point p3, vector<Point> & pontos, vector<Point> & normais, vector<Vec2> & texturas, float deltaW, float deltaH) const {

    // normal da face
    Point normal;
    normal.cross(p3.sub(p1), p2.sub(p1));
    normal.normalize();

    // triangles per edge
    int tpe = _dpe + 1;

    float delta_iW = 1.0f / (5.0f * (float) tpe);
    float delta_iH = 1.0f / (4.0f * (float) tpe);

    // progressão aritmetica para gerar os triangulos
    int progression = 1;

    float x1 = p1.getX(), y1 = p1.getY(), z1 = p1.getZ();
    float x2 = p2.getX(), y2 = p2.getY(), z2 = p2.getZ();
    float x3 = p3.getX(), y3 = p3.getY(), z3 = p3.getZ();

    // size per division edge aresta da esquerda
    float xesped = (x3 - x1) / (float) tpe, yesped = (y3 - y1) / (float) tpe, zesped = (z3 - z1) / (float) tpe;

    // size per division edge - aresta de baixo
    float xbsped = (x2 - x3) / (float) tpe, ybsped = (y2 - y3) / (float) tpe, zbsped = (z2 - z3) / (float) tpe;

    // vetor i da aresta da esquerda x,y e z
    float xiesped, yiesped, ziesped;

    // vetor j da aresta de baixo x,y e z
    float xjbsped, yjbsped, zjbsped;

    for(auto i = 0; i < tpe && progression <= tpe; ++i) {

        xiesped = xesped * (float) i;
        yiesped = yesped * (float) i;
        ziesped = zesped * (float) i;

        for(auto j = 0; j < progression; ++j) {

            xjbsped = xbsped * (float) j;
            yjbsped = ybsped * (float) j;
            zjbsped = zbsped * (float) j;

            // triangulos normais
            pontos.emplace_back(x1 + xiesped + xjbsped, y1 + yiesped + yjbsped, z1 + ziesped + zjbsped);
            normais.push_back(normal);

            pontos.emplace_back(x1 + xiesped + xesped + xjbsped + xbsped, y1 + yiesped + yesped + yjbsped + ybsped, z1 + ziesped + zesped + zjbsped + zbsped);
            normais.push_back(normal);

            pontos.emplace_back(x1 + xiesped + xesped + xjbsped, y1 + yiesped + yesped + yjbsped, z1 + ziesped + zesped + zjbsped);
            normais.push_back(normal);

            texturas.emplace_back(deltaW + (delta_iW * (i + 1.0f)), deltaH + (delta_iH * j));
            texturas.emplace_back(deltaW + (delta_iW * i), deltaH + (delta_iH * j));
            texturas.emplace_back(deltaW + (delta_iW * i), deltaH + (delta_iH * (j + 1.0f)));

            // triangulos invertidos
            if(i < tpe - 1) {
                pontos.emplace_back(x1 + xiesped + (2 * xesped) + xjbsped + xbsped, y1 + yiesped + (2 * yesped) + yjbsped + ybsped, z1 + ziesped + (2 * zesped) + zjbsped + zbsped);
                normais.push_back(normal);

                pontos.emplace_back(x1 + xiesped + xesped + xjbsped, y1 + yiesped + yesped + yjbsped, z1 + ziesped + zesped + zjbsped);
                normais.push_back(normal);

                pontos.emplace_back(x1 + xiesped + xesped + xjbsped + xbsped, y1 + yiesped + yesped + yjbsped + ybsped, z1 + ziesped + zesped + zjbsped + zbsped);
                normais.push_back(normal);

                texturas.emplace_back(deltaW + (delta_iW * i), deltaH + (delta_iH * (j + 1.0f)));
                texturas.emplace_back(deltaW + (delta_iW * (i + 1.0f)), deltaH + (delta_iH * (j + 1.0f)));
                texturas.emplace_back(deltaW + (delta_iW * (i + 1.0f)), deltaH + (delta_iH * j));
            }
        }

        // p(n + 1) = p(n) + 1
        progression++;
    }

}