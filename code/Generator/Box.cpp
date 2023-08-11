#include "../../include/Generator/Box.h"

using namespace std;

/**
 *
 * Construtor parametrizado de uma caixa
 * @param length (comprimento)
 * @param width (largura)
 * @param height (altura)
 * @param dpe (divisões por aresta)
 */
Box::Box(float length, float width, float height, int dpe){
    _length = length;
    _width = width;
    _height = height;
    _dpe = dpe;
}

/**
 *
 * Função que gera pontos e guarda-os num ficheiro
 * @param ofs (path do ficheiro)
 */
void Box::generatePoints(vector<Point> & pontos, vector<Point> & normais, vector<Vec2> & textures) const {

    // square per edge
    int sqpe = _dpe + 1;

    // size per edge division
    float xsped = _length / (float) sqpe;
    float ysped = _height / (float) sqpe;
    float zsped = _width / (float) sqpe;

    // i, j, k vectors
    float xisped, yjsped, zisped, zjsped;

    // half coordinates
    float xhalf = _length / 2;
    float yhalf = _height / 2;
    float zhalf = _width / 2;

    // First Point - upper left corner (z > 0)
    float x1 = -xhalf, y1 = yhalf, z1 = zhalf;

    // Second Point - bottom right corner (z < 0)
    float x2 = xhalf, y2 = -yhalf, z2 = -zhalf;

    // textSize
    float deltaW = 1.0f / 3.0f;
    float deltaH = 1.0f / 2.0f;
    float textSizeW = 1.0f / (3.0f * (float) sqpe);
    float textSizeH = 1.0f / (2.0f * (float) sqpe);

    for(auto i = 0; i < sqpe; ++i) {
        xisped = xsped * (float) i;

        for(auto j = 0; j < sqpe; ++j) {

            yjsped = ysped * (float) j;
            zisped = zsped * (float) i;
            zjsped = zsped * (float) j;

            // Front Face
            pontos.emplace_back(x1 + xisped + xsped, y1 - yjsped, z1); normais.emplace_back(0.0f, 0.0f, 1.0f);
            pontos.emplace_back(x1 + xisped, y1 - yjsped, z1); normais.emplace_back(0.0f, 0.0f, 1.0f);
            pontos.emplace_back(x1 + xisped, y1 - yjsped - ysped, z1); normais.emplace_back(0.0f, 0.0f, 1.0f);

            textures.emplace_back(textSizeW * (i + 1.0f) , textSizeH * j);
            textures.emplace_back(textSizeW * i, textSizeH * j);
            textures.emplace_back(textSizeW * i , textSizeH * (j + 1.0f));

            pontos.emplace_back(x1 + xisped, y1 - yjsped - ysped, z1); normais.emplace_back(0.0f, 0.0f, 1.0f);
            pontos.emplace_back(x1 + xisped + xsped, y1 - yjsped - ysped, z1); normais.emplace_back(0.0f, 0.0f, 1.0f);
            pontos.emplace_back(x1 + xisped + xsped, y1 - yjsped, z1); normais.emplace_back(0.0f, 0.0f, 1.0f);

            textures.emplace_back(textSizeW * i , textSizeH * (j + 1.0f));
            textures.emplace_back(textSizeW * (i + 1.0f) , textSizeH * (j + 1.0f));
            textures.emplace_back(textSizeW * (i + 1.0f), textSizeH * j);

            // Back Face
            pontos.emplace_back(x2 - xisped, y2 + yjsped + ysped, z2); normais.emplace_back(0.0f, 0.0f, -1.0f);
            pontos.emplace_back(x2 - xisped, y2 + yjsped, z2); normais.emplace_back(0.0f, 0.0f, -1.0f);
            pontos.emplace_back(x2 - xisped - xsped, y2 + yjsped, z2); normais.emplace_back(0.0f, 0.0f, -1.0f);

            textures.emplace_back(deltaW + textSizeW * i , textSizeH * (j + 1.0f));
            textures.emplace_back(deltaW + textSizeW * i, textSizeH * j);
            textures.emplace_back(deltaW + textSizeW * (i + 1.0f) , textSizeH * j);

            pontos.emplace_back(x2 - xisped - xsped, y2 + yjsped, z2); normais.emplace_back(0.0f, 0.0f, -1.0f);
            pontos.emplace_back(x2 - xisped - xsped, y2 + yjsped + ysped, z2); normais.emplace_back(0.0f, 0.0f, -1.0f);
            pontos.emplace_back(x2 - xisped, y2 + yjsped + ysped, z2); normais.emplace_back(0.0f, 0.0f, -1.0f);

            textures.emplace_back(deltaW + textSizeW * (i + 1.0f), textSizeH * j);
            textures.emplace_back(deltaW + textSizeW * (i + 1.0f) , textSizeH * (j + 1.0f));
            textures.emplace_back(deltaW + textSizeW * i , textSizeH * (j + 1.0f));

            // Top Face
            pontos.emplace_back(x1 + xisped, y1, z1 - zjsped - zsped); normais.emplace_back(0.0f, 1.0f, 0.0f);
            pontos.emplace_back(x1 + xisped, y1, z1 - zjsped); normais.emplace_back(0.0f, 1.0f, 0.0f);
            pontos.emplace_back(x1 + xisped + xsped, y1, z1 - zjsped); normais.emplace_back(0.0f, 1.0f, 0.0f);

            textures.emplace_back(2 * deltaW + textSizeW * i , textSizeH * (j + 1.0f));
            textures.emplace_back(2 * deltaW + textSizeW * i, textSizeH * j);
            textures.emplace_back(2 * deltaW + textSizeW * (i + 1.0f), textSizeH * j);

            pontos.emplace_back(x1 + xisped + xsped, y1, z1 - zjsped); normais.emplace_back(0.0f, 1.0f, 0.0f);
            pontos.emplace_back(x1 + xisped + xsped, y1, z1 - zjsped - zsped); normais.emplace_back(0.0f, 1.0f, 0.0f);
            pontos.emplace_back(x1 + xisped, y1, z1 - zjsped - zsped); normais.emplace_back(0.0f, 1.0f, 0.0f);

            textures.emplace_back(2.0f * deltaW + textSizeW * (i + 1.0f), textSizeH * j);
            textures.emplace_back(2.0f * deltaW + textSizeW * (i + 1.0f), textSizeH * (j + 1.0f));
            textures.emplace_back(2.0f * deltaW + textSizeW * i, textSizeH * (j + 1.0f));

            // Bottom Face
            pontos.emplace_back(x2 - xisped - xsped, y2, z2 + zjsped); normais.emplace_back(0.0f, -1.0f, 0.0f);
            pontos.emplace_back(x2 - xisped, y2, z2 + zjsped); normais.emplace_back(0.0f, -1.0f, 0.0f);
            pontos.emplace_back(x2 - xisped, y2, z2 + zjsped + zsped); normais.emplace_back(0.0f, -1.0f, 0.0f);

            textures.emplace_back(textSizeW * (i + 1.0f), deltaH + textSizeH * j);
            textures.emplace_back(textSizeW * i, deltaH + textSizeH * j);
            textures.emplace_back(textSizeW * i, deltaH + textSizeH * (j + 1.0f));

            pontos.emplace_back(x2 - xisped, y2, z2 + zjsped + zsped); normais.emplace_back(0.0f, -1.0f, 0.0f);
            pontos.emplace_back(x2 - xisped - xsped, y2, z2 + zjsped + zsped); normais.emplace_back(0.0f, -1.0f, 0.0f);
            pontos.emplace_back(x2 - xisped - xsped, y2, z2 + zjsped); normais.emplace_back(0.0f, -1.0f, 0.0f);

            textures.emplace_back(textSizeW * i, deltaH + textSizeH * (j + 1.0f));
            textures.emplace_back(textSizeW * (i + 1.0f), deltaH + textSizeH * (j + 1.0f));
            textures.emplace_back(textSizeW * (i + 1.0f), deltaH + textSizeH * j);

            // Left Face
            pontos.emplace_back(x1, y1 - yjsped - ysped, z1 - zisped); normais.emplace_back(-1.0f, 0.0f, 0.0f);
            pontos.emplace_back(x1, y1 - yjsped, z1 - zisped); normais.emplace_back(-1.0f, 0.0f, 0.0f);
            pontos.emplace_back(x1, y1 - yjsped, z1 - zisped - zsped); normais.emplace_back(-1.0f, 0.0f, 0.0f);

            textures.emplace_back(deltaW + textSizeW * (j + 1.0f), deltaH + textSizeH * i);
            textures.emplace_back(deltaW + textSizeW * j, deltaH + textSizeH * i);
            textures.emplace_back(deltaW + textSizeW * j, deltaH + textSizeH * (i + 1.0f));

            pontos.emplace_back(x1, y1 - yjsped, z1 - zisped - zsped); normais.emplace_back(-1.0f, 0.0f, 0.0f);
            pontos.emplace_back(x1, y1 - yjsped - ysped, z1 - zisped - zsped); normais.emplace_back(-1.0f, 0.0f, 0.0f);
            pontos.emplace_back(x1, y1 - yjsped - ysped, z1 - zisped); normais.emplace_back(-1.0f, 0.0f, 0.0f);

            textures.emplace_back(deltaW + textSizeW * j, deltaH + textSizeH * (i + 1.0f));
            textures.emplace_back(deltaW + textSizeW * (j + 1.0f), deltaH + textSizeH * (i + 1.0f));
            textures.emplace_back(deltaW + textSizeW * (j + 1.0f), deltaH + textSizeH * i);

            // Right Face
            pontos.emplace_back(x2, y2 + yjsped, z2 + zisped + zsped); normais.emplace_back(1.0f, 0.0f, 0.0f);
            pontos.emplace_back(x2, y2 + yjsped, z2 + zisped); normais.emplace_back(1.0f, 0.0f, 0.0f);
            pontos.emplace_back(x2, y2 + yjsped + ysped, z2 + zisped); normais.emplace_back(1.0f, 0.0f, 0.0f);

            textures.emplace_back(2.0f * deltaW + textSizeW * (i + 1.0f), deltaH + textSizeH * j);
            textures.emplace_back(2.0f * deltaW + textSizeW * i, deltaH + textSizeH * j);
            textures.emplace_back(2.0f * deltaW + textSizeW * i, deltaH + textSizeH * (j + 1.0f));

            pontos.emplace_back(x2, y2 + yjsped + ysped, z2 + zisped); normais.emplace_back(1.0f, 0.0f, 0.0f);
            pontos.emplace_back(x2, y2 + yjsped + ysped, z2 + zisped + zsped); normais.emplace_back(1.0f, 0.0f, 0.0f);
            pontos.emplace_back(x2, y2 + yjsped, z2 + zisped + zsped); normais.emplace_back(1.0f, 0.0f, 0.0f);

            textures.emplace_back(2.0f * deltaW + textSizeW * i, deltaH + textSizeH * (j + 1.0f));
            textures.emplace_back(2.0f * deltaW + textSizeW * (i + 1.0f), deltaH + textSizeH * (j + 1.0f));
            textures.emplace_back(2.0f * deltaW + textSizeW * (i + 1.0f), deltaH + textSizeH * j);
        }
    }
}
