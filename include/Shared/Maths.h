#ifndef CG_TP_MATHS_H
#define CG_TP_MATHS_H

#include <vector>

class Maths {
    public:
        static void multiplyMatrixMatrix(const float*, int, int, const float*, int, int, float*);
        static std::vector<float> normalize(std::vector<float>);
        static std::vector<float> cross(std::vector<float>, std::vector<float>);
        static std::vector<float> add(std::vector<float> a, std::vector<float> b);
        static std::vector<float> sub(std::vector<float> a, std::vector<float> b);
        static std::vector<float> multiply(std::vector<float> a, float multiplier);
        static std::vector<float> inverse(std::vector<float> a);
        static void normalize(float*);
        static void multiplyVectorMatrix(const float*, int, const float*, int, float*);
        static void multiplyMatrixVector(float*, int, int, float*, int, float*);
        static float multiplyVectorVector(const float*, const float*, int);
        static void divisions(int, int &, int &);

};

#endif //CG_TP_MATHS_H
