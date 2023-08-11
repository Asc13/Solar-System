#include "../../include/Engine/Grupo.h"

Grupo::Grupo(){
}

void Grupo::setGroupChildren(std::vector<Grupo>& g) {
    _groupChildren = g;
}

std::vector <Grupo> Grupo::getGroups() {
    return _groupChildren;
}

void renderCatmullRomCurve(CatmullRom catmullRom) {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 100; i++){
        std::vector<float> ponto, deriv;
        catmullRom.getGlobalCatmullRomPoint((float) i / 100.0f, ponto, deriv);
        glVertex3fv(ponto.data());
    }
    glEnd();
}

void Grupo::applyTranformations(bool & showTrajetoria) {

    std::vector<Transformation *> transformacoes = _transformacoes;

    for(Transformation *t : transformacoes){
        if(t->getTransformationType() == TRANSLATE){
            auto *translate = (Translate*) t;
            glTranslatef(translate->getX(), translate->getY(), translate->getZ());
        }
        else if(t->getTransformationType() == ROTATE) {
            auto *rotate = (Rotate*) t;
            glRotatef(rotate->getAngle(), rotate->getX(), rotate->getY(), rotate->getZ());
        }
        else if(t->getTransformationType() == SCALE){
            auto *scale = (Scale*) t;
            glScalef(scale->getX(), scale->getY(), scale->getZ());
        }
        else if(t->getTransformationType() == TRANSLATETIME) {
            auto *translateTime = (TranslateTime *) t;
            std::vector<Point> pontos = translateTime->getPoints();
            float global_t = (float) (fmod(glutGet(GLUT_ELAPSED_TIME), translateTime->getTime() * 1000)) / 1000 / translateTime->getTime();

            CatmullRom *catmullRom = translateTime->getCatullRom();
            std::vector<float> ponto;
            std::vector<float> derivada;

            catmullRom->getGlobalCatmullRomPoint(global_t, ponto, derivada);
            if(showTrajetoria) renderCatmullRomCurve(*catmullRom);

            glTranslatef(ponto[0], ponto[1], ponto[2]);

            std::vector<float> x = {derivada[0],derivada[1],derivada[2]};
            x = Maths::normalize(x);

            std::vector<float> temp = translateTime->getYVec();
            std::vector<float> z = Maths::cross(x, temp);
            z = Maths::normalize(z);

            std::vector<float> y = Maths::cross(z,x);
            y = Maths::normalize(y);

            translateTime->setYVec(y);

            float rotMatrix[16]={0};
            CatmullRom::buildRotMatrix(x, y, z, rotMatrix);

            glMultMatrixf(rotMatrix);
        }
        else if(t->getTransformationType() == ROTATETIME){
            auto *rotateTime = (RotateTime *) t;
            float alpha = (float) ((fmod(glutGet(GLUT_ELAPSED_TIME), rotateTime->getTime() * 1000)) / 1000) / rotateTime->getTime() * 360;
            glRotatef(alpha, rotateTime->getX(), rotateTime->getY(), rotateTime->getZ());
        }
    }
}



void Grupo::vboDraw(bool & showVfc, vector<bool> & flagIndexes, GLuint *vertices, GLuint *normals, GLuint *textures, vector<int> & vertexNumber) {

    for(ModelInfo m : _indexs) {

        if(flagIndexes[m.getVertexIndex()]) {
            if(m.getTextureId() >= 0)
                glBindTexture(GL_TEXTURE_2D,m.getTextureId());

            // Points
            glEnableClientState(GL_VERTEX_ARRAY);
            glBindBuffer(GL_ARRAY_BUFFER, vertices[m.getVertexIndex()]);
            glVertexPointer(3, GL_FLOAT, 0, nullptr);

            // Normals
            if(!m.afectedByLight() || m.getNormalIndex() == -1){
                glDisable(GL_LIGHTING);
            }
            else{
                glEnableClientState(GL_NORMAL_ARRAY);
                glEnable(GL_LIGHTING);
                glBindBuffer(GL_ARRAY_BUFFER, normals[m.getNormalIndex()]);
                glNormalPointer(GL_FLOAT, 0, nullptr);
                //glMaterialfv(GL_FRONT, GL_AMBIENT, m.getAmbient().data());
                glMaterialfv(GL_FRONT, GL_DIFFUSE, m.getDiffuse().data());
                //glMaterialfv(GL_FRONT, GL_SPECULAR, m.getSpecular().data());
                glMaterialf(GL_FRONT, GL_SHININESS, m.getShininess());
                glBindBuffer(GL_ARRAY_BUFFER, normals[m.getNormalIndex()]);
                glNormalPointer(GL_FLOAT, 0, nullptr);

            }

            // Textures
            if(m.getTextureIndex() == -1){
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            }
            else{
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                glBindBuffer(GL_ARRAY_BUFFER, textures[m.getTextureIndex()]);
                glTexCoordPointer(2, GL_FLOAT, 0, nullptr);
            }

            // draw vertex, normals and textures Arrays
            glDrawArrays(GL_TRIANGLES, 0, vertexNumber[m.getVertexIndex()]);

            if(m.getTextureId() >= 0)
                glBindTexture(GL_TEXTURE_2D,0);
        }
    }
}


void Grupo::drawGroup(bool & showVfc, bool & showTrajetoria, ViewFrustumCulling & vfc, std::vector<vector<Point>> & boundingVolumes, GLuint *vertices, GLuint *normals, GLuint *textures, vector<int> & vertexNumber) {

    glPushMatrix();

    // aplica as transformações do grupo.
    applyTranformations(showTrajetoria);

    // get da Matrix de Transformação
    float transMatrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, transMatrix);

    // update das caixas do VFC com as transformações
    vector<bool> flagIndexes;

    if(showVfc) vfc.boxesUpdate(transMatrix, flagIndexes, boundingVolumes);
    else for(int i : vertexNumber) flagIndexes.push_back(true);

    // desenha os modelos com VBO's
    vboDraw(showVfc, flagIndexes, vertices, normals, textures, vertexNumber);

    // desenha os sub grupos
    for(Grupo g : _groupChildren)
        g.drawGroup(showVfc, showTrajetoria, vfc, boundingVolumes, vertices, normals, textures, vertexNumber);

    glPopMatrix();
}


void Grupo::addModelInfo(ModelInfo modelInfo) {
    _indexs.push_back(modelInfo);
}


std::vector<ModelInfo> Grupo::getModelInfo() {
    return _indexs;
}


void Grupo::addTransformation(Transformation *t) {
    _transformacoes.push_back(t);
}


std::vector<Transformation *> *Grupo::getTransformacoes(){
    return &_transformacoes;
}

