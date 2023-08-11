#include <GL/glew.h>
#include <GL/glut.h>

#include "../../include/Engine/Model.h"
#include "../../include/Engine/Grupo.h"
#include "../../include/Engine/Parser.h"
#include "../../include/Engine/CameraExplorer.h"
#include "../../include/Engine/CameraFPS.h"
#include <cstdio>

GLenum mode;
Grupo grupos;
std::vector<vector<Point>> boundingVolumes;

bool showTrajetoria;
bool showVfc;

// Camera Setup
CameraFPS cFPS = CameraFPS(Point(100.0f, 100.0f, 100.0f));
CameraExplorer cEXP = CameraExplorer(500.0f,500.0f,500.0f);

// View Frustum Culling
int w = 1920, h = 1080;
ViewFrustumCulling vfc = ViewFrustumCulling(45.0f, (float) w * 1.0f / (float) h,1.0f, 10000.0f);

// VBO's
GLuint *vertices, *normals, *textures;
vector<Model> vertexTemp;
vector<int> vertexNumber;
vector<Light> lights;

// Informações para os fps
int timebase;
float frames = 0;
float fps;
float timeF;
char showFrames[256];
bool cameraType = true;


/**
 *
 * Função que realiza eventos
 * @param key (tecla com ação definida)
 * @param x
 * @param y
 */

void normalKeyboardEvents(unsigned char key, int x, int y){
    switch (key) {
        case 'w':case 'h':
            if(cameraType)
                cFPS.keyboardEvent("FRONT");
            else
                cEXP.keyboardEvent("FRONT");
            break;
        case 's':case 'j':
            if(cameraType)
                cFPS.keyboardEvent("BACK");
            else
                cEXP.keyboardEvent("BACK");
            break;

        case 'a':case 'k':
            if(cameraType)
                cFPS.keyboardEvent("LEFT");
            else
                cEXP.keyboardEvent("LEFT");
            break;

        case 'd':case 'l':
            if(cameraType)
                cFPS.keyboardEvent("RIGHT");
            else
                cEXP.keyboardEvent("RIGHT");
            break;

        case 'm':
            mode = mode == GL_LINE ? GL_FILL : GL_LINE;
            break;
        case ',':
            if(cameraType)
                cEXP.setNewPos(cFPS.getPx(), cFPS.getPy(), cFPS.getPz(), cFPS.getFrontX(), cFPS.getFrontY(), cFPS.getFrontZ());
            else
                cFPS.setNewPosition(cEXP.getPx(), cEXP.getPy(), cEXP.getPz(), cEXP.getDx()-cEXP.getPx(), cEXP.getDy()-cEXP.getPy(), cEXP.getDz()-cEXP.getPz());
            cameraType = !cameraType;
            break;
        case 'r':
            if(!cameraType)
                cEXP.resetRadius();
            break;
        case 'o':
            if(!cameraType)
                cEXP.setRadiusToOrigin();
            break;
        case '+':
            if(!cameraType)
                cEXP.increaseRadius();
            break;
        case '-':
            if(!cameraType)
                cEXP.decreaseRadius();
            break;
        case 'c':
            if(cameraType)
                cFPS.speedChanger(1);
            else
                cEXP.speedChanger(1);
            break;
        case 'v':
            if(cameraType)
                cFPS.speedChanger(0);
            else
                cEXP.speedChanger(0);
            break;
        case 't':
            if(showTrajetoria)
                showTrajetoria = false;
            else
                showTrajetoria = true;
            break;
        case 'i':
            if(showVfc)
                showVfc = false;
            else
                showVfc = true;
            break;
        default: break;
    }
    glutPostRedisplay();
}


void mouseMovementEvents(int x, int y) {
    if(cameraType) cFPS.mouseEvent((float) x, (float) y);
    glutPostRedisplay();
}


void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you can�t make a window with zero width).
    if(h == 0) h = 1;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);

    // Load the identity matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the perspective
    gluPerspective(vfc.getFOV(), vfc.getRatio(), vfc.getNear(), vfc.getFar());

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}


void lightSettings() {

    int i = 0;

    for(Light l : lights) {

        if(l.getLightType() == POINT || l.getLightType() == DIRECTIONAL) {
            glLightfv(GL_LIGHT0 + i, GL_POSITION, l.getPos().data());
            //glLightfv(GL_LIGHT0 + i, GL_AMBIENT, l.getAmb().data());
            glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, l.getDiff().data());
            //glLightfv(GL_LIGHT0 + i, GL_SPECULAR, l.getSpe().data());
        }
        else if(l.getLightType() == SPOT) {

            glLightfv(GL_LIGHT0 + i, GL_POSITION, l.getPos().data());
            glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION, l.getSpotDir().data());
            glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, l.getCutOff());
            glLightf(GL_LIGHT0 + i,GL_SPOT_EXPONENT, l.getExponent());
            glLightf(GL_LIGHT0 + i, GL_QUADRATIC_ATTENUATION, l.getAtenuation());
            glLightfv(GL_LIGHT0 + i, GL_AMBIENT, l.getAmb().data());
            glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, l.getDiff().data());
            glLightfv(GL_LIGHT0 + i, GL_SPECULAR, l.getSpe().data());

        }
        i++;
    }
}


void fpsCounter() {
    frames++;
    timeF = (float) glutGet(GLUT_ELAPSED_TIME);
    if (timeF - (float) timebase > 1000) {
        fps = (float) frames * 1000.0f / (timeF - (float) timebase);
        timebase = (int) timeF;
        frames = 0;
    }
    sprintf(showFrames,"Frames: %f", fps);
    glutSetWindowTitle(showFrames);
}


void renderScene() {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT, mode);

    // set camera
    glLoadIdentity();

    if (cameraType) {
        gluLookAt(cFPS.getPx(), cFPS.getPy(), cFPS.getPz(),
                  cFPS.getDx(), cFPS.getDy(), cFPS.getDz(),
                  cFPS.getUx(), cFPS.getUy(), cFPS.getUz());

        vfc.setupPlanes(cFPS.getP(), cFPS.getU(), cFPS.getD(), cFPS.getR());
    } else {
        gluLookAt(cEXP.getPx(), cEXP.getPy(), cEXP.getPz(),
                  cEXP.getDx(), cEXP.getDy(), cEXP.getDz(),
                  CameraExplorer::getUx(), CameraExplorer::getUy(), CameraExplorer::getUz());

        vfc.setupPlanes(cEXP.getP(), CameraExplorer::getU(), cEXP.getD(), cEXP.getR());
    }
    // light Settings
    lightSettings();

    // desenhar os grupos e subgrupos
    grupos.drawGroup(showVfc, showTrajetoria, vfc, boundingVolumes, vertices, normals, textures, vertexNumber);

    fpsCounter();

    // End of frame
    glutSwapBuffers();
}


void vboSetup(vector<Model>& normalsTemp, vector<Model>& texturesTemp) {

    int sizeVertex = (int) vertexTemp.size();
    int sizeNormals = (int) normalsTemp.size();
    int sizeTextures = (int) texturesTemp.size();
    int maior;
    if(sizeVertex > sizeNormals && sizeVertex > sizeTextures) maior = sizeVertex;
    else if(sizeNormals > sizeVertex && sizeNormals > sizeTextures) maior = sizeNormals;
    else maior = sizeTextures;

    for(int i = 0; i < maior; i++) {

        vertexNumber.push_back(vertexTemp[i].getVectorSize());

        if(i < sizeVertex){
            // Points
            glBindBuffer(GL_ARRAY_BUFFER, vertices[i]);
            glBufferData(GL_ARRAY_BUFFER,
                         sizeof(float) * (float) vertexTemp[i].getVectorSize(),
                         vertexTemp[i].getContent().data(),
                         GL_STATIC_DRAW);
        }

        if(i < sizeNormals){
            // Normals
            glBindBuffer(GL_ARRAY_BUFFER, normals[i]);
            glBufferData(GL_ARRAY_BUFFER,
                         sizeof(float) * (float) normalsTemp[i].getVectorSize(),
                         normalsTemp[i].getContent().data(),
                         GL_STATIC_DRAW);
        }

        if(i < sizeTextures){
            // Textures
            glBindBuffer(GL_ARRAY_BUFFER, textures[i]);
            glBufferData(GL_ARRAY_BUFFER,
                         (long) (sizeof(float) * (float) texturesTemp[i].getVectorSize()),
                         texturesTemp[i].getContent().data(),
                         GL_STATIC_DRAW);
        }
    }

}


void genBuffers(vector<Model>& normalsTemp, vector<Model>& texturesTemp) {

    // Points
    vertices = static_cast<GLuint *> (malloc(sizeof(GLuint) * vertexTemp.size()));
    glGenBuffers((int) vertexTemp.size(), vertices);

    // Normals
    normals = static_cast<GLuint *> (malloc(sizeof(GLuint) * normalsTemp.size()));
    glGenBuffers((int) normalsTemp.size(), normals);

    // Textures
    textures = static_cast<GLuint *> (malloc(sizeof(GLuint) * texturesTemp.size()));
    glGenBuffers((int) texturesTemp.size(), textures);

    vboSetup(normalsTemp, texturesTemp);

    //free(&vertexTemp);
    //free(&normalsTemp);
    //free(&texturesTemp);
}

void textureSetup() {
    glEnable(GL_TEXTURE_2D);
}



void lightSetup() {
    glEnable(GL_LIGHTING);
    for(int i = 0; i < lights.size(); i++) {

        glEnable(GL_LIGHT0 + i);

    }
}


void printInfo() {
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version: %s\n", glGetString(GL_VERSION));
}


int main(int argc, char** argv) {
    if(argc == 2) {

        mode = GL_LINE;

        // put GLUT's init here
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowPosition(100, 100);
        glutInitWindowSize(w, h);
        glutCreateWindow("CG@DI");

        // put callback registry here
        glutDisplayFunc(renderScene);

        glutReshapeFunc(changeSize);
        glutKeyboardFunc(normalKeyboardEvents);
        glutPassiveMotionFunc(mouseMovementEvents);
        glutIdleFunc(renderScene);

        timebase = glutGet(GLUT_ELAPSED_TIME);

        // put GLEW's init here
        glewInit();

        Parser parser = Parser(argv[1]);
        vector<Model> normalsTemp, texturesTemp;
        grupos = parser.loadXML(vertexTemp, normalsTemp, texturesTemp, lights);
        vfc.boxesSetup(vertexTemp, boundingVolumes);

        // light Setup
        lightSetup();

        // texture Setup
        textureSetup();


        // gen VBO's buffers
        genBuffers(normalsTemp, texturesTemp);

        // some OpenGL settings
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glEnable(GL_RESCALE_NORMAL);
        glEnable(GL_NORMALIZE);

        glutSetCursor(GLUT_CURSOR_NONE); // para esconder o cursor

        printInfo();

        // enter GLUT's main cycle
        glutMainLoop();

        free(vertices);
        free(normals);
        free(textures);
    } else
        std::cout << "Não foi introduzido nenhum ficheiro ou esse ficheiro é inválido" << std::endl;
    return 1;
}
