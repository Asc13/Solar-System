#include <iostream>
#include "../../include/Shared/Maths.h"
#include <math.h>

void Maths::multiplyMatrixMatrix(const float* m1, int r1, int c1, const float* m2, int r2, int c2, float* res){
    float temp;
    for(int i = 0; i < r1; i++)
        for(int j = 0; j < c2; j++) {
            temp = 0.0f;
            for (int k = 0; k < c1; k++)
                temp += m1[i * c1 + k] * m2[k * c2 + j];
            res[i * c2 + j] = temp;
        }
}


std::vector<float> Maths::normalize(std::vector<float> vec){
    std::vector<float> res;
    float l = sqrt(vec[0]*vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
    res.push_back(vec[0]/l);
    res.push_back(vec[1]/l);
    res.push_back(vec[2]/l);
    return res;
}


void Maths::normalize(float* vec) {
    float l = sqrt(vec[0]*vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
    vec[0] = vec[0]/l;
    vec[1] = vec[1]/l;
    vec[2] = vec[2]/l;
}


std::vector<float> Maths::cross(std::vector<float> a, std::vector<float> b){
    std::vector<float> res;
    res.push_back(a[1]*b[2] - a[2]*b[1]);
    res.push_back(a[2]*b[0] - a[0]*b[2]);
    res.push_back(a[0]*b[1] - a[1]*b[0]);
    return res;
}


std::vector<float> Maths::add(std::vector<float> a, std::vector<float> b) {
    return {a[0] + b[0], a[1] + b[1], a[2] + b[2]};
}

std::vector<float> Maths::sub(std::vector<float> a, std::vector<float> b) {
    return {a[0] - b[0], a[1] - b[1], a[2] - b[2]};
}

std::vector<float> Maths::multiply(std::vector<float> a, float multiplier) {
    return {a[0] * multiplier, a[1] * multiplier, a[2] * multiplier};
}


std::vector<float> Maths::inverse(std::vector<float> a) {
    return {-a[0], -a[1], -a[2]};
}


void Maths::multiplyVectorMatrix(const float* v, int lenV, const float* m, int c, float* res){
    float t;
    for(int i = 0; i < c; i++) {
        t = 0.0;
        for (int j = 0; j < lenV; j++)
            t += v[j] * m[j*c+i];
        res[i] = t;
    }
}


void Maths::multiplyMatrixVector(float* m, int r, int c, float* v, int len, float* res){
    float t;
    for(int i = 0; i < r; i++) {
        t = 0.0;
        for (int j = 0; j < len; j++)
            t += m[i*c+j]*v[j];
        res[i] = t;
    }
}


float Maths::multiplyVectorVector(const float* v1, const float* v2, int len){
    float res = 0.0;
    for(int i = 0; i < len;i++)
        res += v1[i]*v2[i];
    return res;
}


void getVector(const float *p1, const float *p2, float *v){
    for (int i = 0; i < 3; i++)
        v[i] = p2[i]-p1[i];
}


void Maths::divisions(int total, int & x, int & y) {

    long long sr = sqrt(total);

    if (sr * sr != total) {
        std::vector<int> multiples;

        for (int i = 1; i <= total; ++i)
            if (total % i == 0)
                multiples.push_back(i);

        int halfSize = (int) (multiples.size()) / 2;

        x = multiples[halfSize - 1];
        y = multiples[halfSize];
    } else {
        x = (int) sqrt(total);
        y = x;
    }

}