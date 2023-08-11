#include "../../include/Generator/Plane.h"
#include "../../include/Generator/Box.h"
#include "../../include/Generator/Sphere.h"
#include "../../include/Generator/Cone.h"
#include "../../include/Generator/Cylinder.h"
#include "../../include/Generator/ConicalFrustum.h"
#include "../../include/Generator/Torus.h"
#include "../../include/Generator/Icosahedron.h"
#include "../../include/Generator/Tube.h"
#include "../../include/Generator/Teapot.h"
#include <exception>
#include <iostream>


void fileSave(char* path, vector<Point> & pontos, vector<Point> & normais, vector<Vec2> & texturas) {
    unsigned int tam = pontos.size();

    ofstream ficheiro(path, std::ios::binary);
    ficheiro << tam << endl;
    for(int i = 0; i < pontos.size(); i++)
        ficheiro << pontos[i].getX() << ' ' << pontos[i].getY() << ' ' << pontos[i].getZ()
                 << ' ' << normais[i].getX() << ' ' << normais[i].getY() << ' ' << normais[i].getZ()
                 << ' ' << texturas[i].getX() << ' ' << texturas[i].getY() << endl;

    ficheiro.close();
}

/**
 *
 * Função que gera um plano e armazena as coordenadas dos seus pontos num ficheiro
 * @param input (largura, comprimento e path do ficheiro)
 */

void generatePlane(char** input) {
    float i1, i2;
    int i3;

    try {
        if((i1 = stof(input[0])) > 0.0f && (i2 = stof(input[1])) > 0.0f && (i3 = stoi(input[2])) > 0) {
            Plane p = Plane(i1, i2, i3);
            vector<Point> pontos;
            vector<Point> normais;
            vector<Vec2> texturas;

            p.generatePoints(pontos, normais, texturas);

            fileSave(input[3], pontos, normais, texturas);
        } else throw std::exception();

    } catch (std::exception & e){
        std::cout << "INPUT INVÁLIDO" << std::endl;
    }

}

/**
 *
 * Função que gera uma caixa e armazena as coordenadas dos seus pontos num ficheiro
 * @param input (comprimento, largura, altura, divisões por aresta e path do ficheiro)
 */
void generateBox(char** input) {
    float i1, i2, i3;
    int i4;

    try {
        if((i1 = stof(input[0])) > 0.0f && (i2 = stof(input[1])) > 0.0f && (i3 = stof(input[2])) > 0.0f && (i4 = stoi(input[3])) >= 0 ) {
            Box b = Box(i1, i2, i3, i4);
            vector<Point> pontos;
            vector<Point> normais;
            vector<Vec2> texturas;

            b.generatePoints(pontos, normais, texturas);

            fileSave(input[4], pontos, normais, texturas);
        } else throw std::exception();

    } catch (std::exception & e){
            std::cout << "INPUT INVÁLIDO" << std::endl;
        }
}

/**
 *
 * Função que gera uma esfera e armazena as coordenadas dos seus pontos num ficheiro
 * @param input (raio, slices, stacks e path do ficheiro)
 */
void generateSphere(char** input) {
    float i1;
    int i2, i3;

    try {
        if((i1 = stof(input[0])) > 0.0f && (i2 = stoi(input[1])) >= 0 && (i3 = stoi(input[2])) >= 0) {
            Sphere s = Sphere(i1, i2, i3);
            vector<Point> pontos;
            vector<Point> normais;
            vector<Vec2> texturas;

            s.generatePoints(pontos, normais, texturas);

            fileSave(input[3], pontos, normais, texturas);
        } else throw std::exception();
    } catch (std::exception & e){
        std::cout << "INPUT INVÁLIDO" << std::endl;
    }

}

/**
 *
 * Função que gera um cone e armazena as coordenadas dos seus pontos num ficheiro
 * @param input (raio, altura, slices, stacks e path do ficheiro)
 */
void generateCone(char** input) {
    float i1, i2;
    int i3, i4;

    try {
        if((i1 = stof(input[0])) > 0.0f && (i2 = stof(input[1])) > 0.0f && (i3 = stoi(input[2])) >= 0 && (i4 = stoi(input[3])) >= 0) {
            Cone c = Cone(i1, i2, i3, i4);
            vector<Point> pontos;
            vector<Point> normais;
            vector<Vec2> texturas;

            c.generatePoints(pontos, normais, texturas);

            fileSave(input[4], pontos, normais, texturas);
        } else throw std::exception();
    } catch (std::exception & e){
        std::cout << "INPUT INVÁLIDO" << std::endl;
    }


}

/**
 *
 * Função que gera um frustrum cónico e armazena as coordenadas dos seus pontos num ficheiro
 * @param input (raio, altura, slices, stacks e path do ficheiro)
 */
void generateConicalFrustum(char** input) {
    float i1, i2,i3;
    int i4, i5;

    try {
        if((i1 = stof(input[0])) > 0.0f && (i2 = stof(input[1])) > 0.0f && (i3 = stof(input[2]))>0.0f && (i4 = stoi(input[3])) >= 0 && (i5 = stoi(input[4])) >= 0) {
            ConicalFrustum c = ConicalFrustum(i1, i2, i3, i4, i5);
            vector<Point> pontos;
            vector<Point> normais;
            vector<Vec2> texturas;

            c.generatePoints(pontos, normais, texturas);

            fileSave(input[5], pontos, normais, texturas);
        } else throw std::exception();
    } catch (std::exception & e){
        std::cout << "INPUT INVÁLIDO" << std::endl;
    }

}

/**
 *
 * Função que gera um cilindro e armazena as coordenadas dos seus pontos num ficheiro
 * @param input (raio, altura, slices, stacks e path do ficheiro)
 */
void generateCylinder(char** input) {
    float i1, i2;
    int i3, i4;

    try {
        if((i1 = stof(input[0])) > 0.0f && (i2 = stof(input[1])) > 0.0f && (i3 = stoi(input[2])) >= 0 && (i4 = stoi(input[3])) >= 0) {
            Cylinder c = Cylinder(i1, i2, i3, i4);
            vector<Point> pontos;
            vector<Point> normais;
            vector<Vec2> texturas;

            c.generatePoints(pontos, normais, texturas);

            fileSave(input[4], pontos, normais, texturas);
        } else throw std::exception();
    } catch (std::exception & e){
        std::cout << "INPUT INVÁLIDO" << std::endl;
    }

}

/**
 *
 * Função que gera um tubo e armazena as coordenadas dos seus pontos num ficheiro
 * @param input (raio da base, raio interior, altura, slices, stacks e path do ficheiro)
 */
void generateTube(char** input) {
    float i1, i2, i3;
    int i4, i5;

    try {
        if((i1 = stof(input[0])) > 0.0f && (i2 = stof(input[1])) > 0.0f && (i3 = stof(input[2])) > 0.0f &&
           (i4 = stoi(input[3])) >= 0 && (i5 = stoi(input[4])) >= 0 && i2 < i1) {

            Tube c = Tube(i1, i2, i3, i4, i5);
            vector<Point> pontos;
            vector<Point> normais;
            vector<Vec2> texturas;

            c.generatePoints(pontos, normais, texturas);

            fileSave(input[5], pontos, normais, texturas);
        } else throw std::exception();
    } catch (std::exception & e){
        std::cout << "INPUT INVÁLIDO" << std::endl;
    }

}

/**
 *
 * Função que gera um torus e armazena as coordenadas dos seus pontos num ficheiro
 * @param input (raio, tamanho, slices, stacks e path do ficheiro)
 */
void generateTorus(char** input) {
    float i1, i2;
    int i3, i4;

    try {
        if((i1 = stof(input[0])) > 0.0f && (i2 = stof(input[1])) > 0.0f && (i3 = stoi(input[2])) >= 0 && (i4 = stoi(input[3])) >= 0 && i2 < i1) {
            Torus c = Torus(i1, i2, i3, i4);
            vector<Point> pontos;
            vector<Point> normais;
            vector<Vec2> texturas;

            c.generatePoints(pontos, normais, texturas);

            fileSave(input[4], pontos, normais, texturas);
        } else throw std::exception();
    } catch (std::exception & e){
        std::cout << "INPUT INVÁLIDO" << std::endl;
    }

}

/**
 *
 * Função que gera uma esfera e armazena as coordenadas dos seus pontos num ficheiro
 * @param input (comprimento, largura, divisões por aresta e path do ficheiro)
 */
void generateIcosahedron(char** input) {
    float i1, i2;
    int i3;

    try {
        if((i1 = stof(input[0])) > 0.0f && (i2 = stof(input[1])) > 0.0f && (i3 = stoi(input[2])) >= 0) {
            Icosahedron i = Icosahedron(i1, i2, i3);
            vector<Point> pontos;
            vector<Point> normais;
            vector<Vec2> texturas;

            i.generatePoints(pontos, normais, texturas);

            fileSave(input[3], pontos, normais, texturas);
        } else throw std::exception();
    } catch (std::exception & e){
        std::cout << "INPUT INVÁLIDO" << std::endl;
    }

}



void generateTeapot(char** input) {
    int i1;

    try {
        if((i1 = stoi(input[0])) > 0) {
            Teapot t = Teapot(i1, input[1]);
            vector<Point> pontos;
            vector<Point> normais;
            vector<Vec2> texturas;

            t.generatePoints(pontos, normais, texturas);

            fileSave(input[2], pontos, normais, texturas);
        } else throw std::exception();
    } catch (std::exception & e){
        std::cout << "INPUT INVÁLIDO" << std::endl;
    }

}


/**
 *
 * Menu
 */
static string const helpMenu = "INPUT INVALIDO\n"
        "\tplane:               [X] [Z]\n"
        "\tbox:                 [COMPRIMENTO] [LARGURA] [ALTURA] [DIVISIONS]\n"
        "\tsphere:              [RADIUS] [SLICES] [STACKS]\n"
        "\tcone:                [BASE] [HEIGHT] [SLICES] [STACKS]\n"
        "\tconicalFrustum:      [BASE_RADIUS] [HEIGHT_CONE] [HEIGHT_CUT] [SLICES] [STACKS]\n"
        "\tcylinder:            [RADIUS] [HEIGHT] [SLICES] [STACKS]\n"
        "\ttorus:               [OUTER_RADIUS] [INNER_RADIUS] [SLICES] [STACKS]\n"
        "\ticosahedron:         [LENGHT] [HEIGHT] [DIVISIONS]\n"
        "\ttube:                [BASE_RADIUS] [INNER_RADIUS] [HEIGHT] [SLICES] [STACKS]\n";


/**
 * Função que gera uma figura
 * @param argc (tamanho do input)
 * @param argv (input(nome da figura, parâmetros da figura, path do ficheiro))
 */
void parsePrimitive(int argc, char *argv[]) {
    argc-=2;

    if(argc == 4 && !strcmp(argv[1], "plane")) generatePlane(argv+2);

    else if(argc == 5 && !strcmp(argv[1], "box")) generateBox(argv+2);

    else if(argc == 6 && !strcmp(argv[1], "conicalFrustum")) generateConicalFrustum(argv+2);

    else if(argc == 4 && !strcmp(argv[1], "sphere")) generateSphere(argv+2);

    else if(argc == 5 && !strcmp(argv[1], "cone")) generateCone(argv+2);

    else if(argc == 5 && !strcmp(argv[1], "cylinder")) generateCylinder(argv+2);

    else if(argc == 5 && !strcmp(argv[1], "torus")) generateTorus(argv+2);

    else if(argc == 4 && !strcmp(argv[1], "icosahedron")) generateIcosahedron(argv+2);

    else if(argc == 6 && !strcmp(argv[1], "tube")) generateTube(argv+2);

    else if(argc == 3 && !strcmp(argv[1], "teapot")) generateTeapot(argv+2);

    else cout << helpMenu;
}


int main(int argc, char *argv[]) {
	parsePrimitive(argc, argv);
	return 0;
}