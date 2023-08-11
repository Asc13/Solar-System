#include "../../include/Generator/Teapot.h"
#include "../../include/Shared/Maths.h"

#define TAM 4

// Matriz de Bezier
static float M[TAM*TAM] = {-1.0f, 3.0f,  -3.0f, 1.0f,
                           3.0f,  -6.0f, 3.0f,  0.0f,
                           -3.0f, 3.0f,  0.0f,  0.0f,
                           1.0f,  0.0f,  0.0f,  0.0f};

/**
 *
 * Construtor parametrizado de um teapot
 * @param path
 */
Teapot::Teapot(int tesselation, char* path) {

    _tesselation = tesselation;
    string line;

    ifstream file;
    file.open (path);

    if(file.is_open()) {
        file >> _nrIndexes;
        int xDiv, yDiv;
        Maths::divisions(_nrIndexes, xDiv, yDiv);

        _xDelta = 1.0f / (float) (xDiv * _tesselation);
        _yDelta = 1.0f / (float) (yDiv * _tesselation);

        _indexes.reserve(_nrIndexes);
        getline(file,line);

        for(int i = 0; i < _nrIndexes; ++i) {

            getline(file,line);

            stringstream check1(line);
            string intermediate;
            vector<int> index;

            while(getline(check1, intermediate, ','))
                index.push_back(std::stoi(intermediate));

            _indexes.push_back(index);
        }

        file >> _nrControlPoints;

        _controlPoints.reserve(_nrIndexes);
        getline(file,line);

        for(int i = 0; i < _nrControlPoints; ++i) {

            getline(file, line);

            stringstream check1(line);
            string intermediate;
            vector<float> aux;

            while(getline(check1, intermediate, ','))
                aux.push_back(stof(intermediate));

            _controlPoints.emplace_back(aux[0], aux[1], aux[2]);
        }

        file.close();
    }

    else cout << "Unable to open file";
}


float dpv(float u, float v, float* mpm) {
    float uvec[4] = {powf(u, 3), powf(u, 2), u, 1.0f};
    float vvec[4] = {3 * powf(v, 2), 2 * v, 1.0f, 0.0f};
    float mpmu[4] = {0};
    Maths::multiplyMatrixVector(mpm, TAM, TAM, uvec, 4, mpmu);

    return Maths::multiplyVectorVector(vvec,mpmu,4);
}


float dpu(float u, float v, float* mpm) {
    float uvec[4] = {3 * powf(u, 2), 2 * u, 1.0f, 0.0f};
    float vvec[4] = {powf(v, 3), powf(v, 2), v, 1.0f};
    float mpmu[4] = {0};
    Maths::multiplyMatrixVector(mpm, TAM, TAM, uvec, 4, mpmu);

    return Maths::multiplyVectorVector(vvec,mpmu,4);
}


float p(float u, float v, float* mpm) {
    float uvec[4] = {powf(u, 3), powf(u, 2), u, 1.0f};
    float vvec[4] = {powf(v, 3), powf(v, 2), v, 1.0f};
    float mpmu[4] = {0};
    Maths::multiplyMatrixVector(mpm, TAM, TAM, uvec, 4, mpmu);

    return Maths::multiplyVectorVector(vvec,mpmu,4);
}


void Teapot::pointsFromPatch(vector<Point> & cp, vector<Point> & pontos, vector<Point> & normais, vector<Vec2> & texturas) const {

    float P_x[TAM*TAM], P_y[TAM*TAM], P_z[TAM*TAM];

    float temp[TAM*TAM] = {0};
    float mpm_x[TAM*TAM] = {0};
    float mpm_y[TAM*TAM] = {0};
    float mpm_z[TAM*TAM] = {0};

    // Criação da matriz P
    for(int i = 0; i < TAM; ++i)
        for(int j = 0; j < TAM; ++j) {
            Point p = cp[i * TAM + j];

            P_x[i*TAM+j] = p.getX();
            P_y[i*TAM+j] = p.getY();
            P_z[i*TAM+j] = p.getZ();
        }


    // Multiplicação das matrizes M . P . M^T (igual a M por ser simétrica)
    Maths::multiplyMatrixMatrix(P_x, TAM, TAM, M, TAM, TAM, temp);
    Maths::multiplyMatrixMatrix(M, TAM, TAM, temp, TAM, TAM, mpm_x);

    Maths::multiplyMatrixMatrix(P_y, TAM, TAM, M, TAM, TAM, temp);
    Maths::multiplyMatrixMatrix(M, TAM, TAM, temp, TAM, TAM, mpm_y);

    Maths::multiplyMatrixMatrix(P_z, TAM, TAM, M, TAM, TAM, temp);
    Maths::multiplyMatrixMatrix(M, TAM, TAM, temp, TAM, TAM, mpm_z);


    // Tesselation p(u, v)
    for (int u = 0; u < _tesselation ; u++) {
        float ut = (float) u / (float) _tesselation;
        float next_ut = (float) (u + 1) / (float) _tesselation;

        for (int v = 0; v < _tesselation ; v++) {
            float vt = (float) v / (float) _tesselation;
            float next_vt = (float) (v + 1) / (float) _tesselation;


            pontos.emplace_back(p(ut, vt, mpm_x), p(ut, vt, mpm_y), p(ut, vt, mpm_z));
            normais.emplace_back(Maths::normalize(Maths::cross((vector<float>) {dpu(ut, vt, mpm_x), dpu(ut, vt, mpm_y), dpu(ut, vt, mpm_z)},
                                                                (vector<float>) {dpv(ut, vt, mpm_x), dpv(ut, vt, mpm_y), dpv(ut, vt, mpm_z)})));
            texturas.emplace_back(_xDelta * (float) u, _yDelta * (float) v);

            pontos.emplace_back(p(next_ut, vt, mpm_x), p(next_ut, vt, mpm_y), p(next_ut, vt, mpm_z));
            normais.emplace_back(Maths::normalize(Maths::cross((vector<float>) {dpu(next_ut, vt, mpm_x), dpu(next_ut, vt, mpm_y), dpu(next_ut, vt, mpm_z)},
                                                               (vector<float>) {dpv(next_ut, vt, mpm_x), dpv(next_ut, vt, mpm_y), dpv(next_ut, vt, mpm_z)})));
            texturas.emplace_back(_xDelta * (float) (u + 1), _yDelta * (float) v);

            pontos.emplace_back(p(ut, next_vt, mpm_x), p(ut, next_vt, mpm_y), p(ut, next_vt,mpm_z));
            normais.emplace_back(Maths::normalize(Maths::cross((vector<float>) {dpu(ut, next_vt, mpm_x), dpu(ut, next_vt, mpm_y), dpu(ut, next_vt,mpm_z)},
                                                               (vector<float>) {dpv(ut, next_vt, mpm_x), dpv(ut, next_vt, mpm_y), dpv(ut, next_vt,mpm_z)})));
            texturas.emplace_back(_xDelta * (float) u, _yDelta * (float) (v + 1));

            pontos.emplace_back(p(ut, next_vt, mpm_x), p(ut, next_vt, mpm_y), p(ut, next_vt, mpm_z));
            normais.emplace_back(Maths::normalize(Maths::cross((vector<float>) {dpu(ut, next_vt, mpm_x), dpu(ut, next_vt, mpm_y), dpu(ut, next_vt,mpm_z)},
                                                               (vector<float>) {dpv(ut, next_vt, mpm_x), dpv(ut, next_vt, mpm_y), dpv(ut, next_vt,mpm_z)})));
            texturas.emplace_back(_xDelta * (float) u, _yDelta * (float) (v + 1));

            pontos.emplace_back(p(next_ut, vt, mpm_x), p(next_ut, vt, mpm_y), p(next_ut, vt, mpm_z));
            normais.emplace_back(Maths::normalize(Maths::cross((vector<float>) {dpu(next_ut, vt, mpm_x), dpu(next_ut, vt, mpm_y), dpu(next_ut, vt, mpm_z)},
                                                               (vector<float>) {dpv(next_ut, vt, mpm_x), dpv(next_ut, vt, mpm_y), dpv(next_ut, vt, mpm_z)})));
            texturas.emplace_back(_xDelta * (float) (u + 1), _yDelta * (float) v);

            pontos.emplace_back(p(next_ut, next_vt, mpm_x), p(next_ut, next_vt, mpm_y), p(next_ut, next_vt, mpm_z));
            normais.emplace_back(Maths::normalize(Maths::cross((vector<float>) {dpu(next_ut, next_vt, mpm_x), dpu(next_ut, next_vt, mpm_y), dpu(next_ut, next_vt, mpm_z)},
                                                               (vector<float>) {dpv(next_ut, next_vt, mpm_x), dpv(next_ut, next_vt, mpm_y), dpv(next_ut, next_vt, mpm_z)})));
            texturas.emplace_back(_xDelta * (float) (u + 1), _yDelta * (float) (v + 1));
        }
    }
}


void Teapot::generatePoints(vector<Point> & pontos, vector<Point> & normais, vector<Vec2> & texturas) {

    for(auto & index : _indexes) {
        vector<Point> v;
        v.reserve(pow(TAM, 2));
        for(auto i : index)
            v.push_back(_controlPoints[i]);

        pointsFromPatch(v, pontos, normais, texturas);
    }

}