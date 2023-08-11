#include "../../include/Engine/Parser.h"
#include <regex>

#include <GL/glew.h>
#include <GL/glut.h>
#include <IL/il.h>

Parser::Parser(char *fn){
    _path = strdup(fn);
}

float readFloat(const char* text){
    float ret = 0;
    int num;
    float lower;
    float upper;

    std::smatch match;
    std::regex expRand (R"(Rand\((-?\d+\.?\d+?),(-?\d+\.?\d+?)\))");
    std::regex expNum (R"(-?(\d+)\.?(\d+)?(e-?\d+)?)");

    if(text){
        const std::string sctx(text);
        if(std::regex_search(sctx, match, expRand)){
            num = std::rand() % 100;
            lower = std::stof(match.str(1));
            upper = std::stof(match.str(2));
            ret = ((float) num * upper - (float) num * lower) / 100 + lower;
        }
        else if(std::regex_search(sctx, match, expNum)){
            ret = std::stof(match.str(0));
        }
    }

    return ret;
}

void readTimeTranslation(tinyxml2::XMLElement *translacaoTime, Grupo *g) {
    float time;
    float x, y, z;
    Point p;
    std::vector<Point> pontos;

    if(translacaoTime){
        const char* ctime = translacaoTime->Attribute("time");
        time = readFloat(ctime);

        for(tinyxml2::XMLElement* child = translacaoTime->FirstChildElement();child!= nullptr; child = child->NextSiblingElement()){
            const char* cx = child->Attribute("X");
            x = readFloat(cx);

            const char* cy = child->Attribute("Y");
            y = readFloat(cy);

            const char* cz = child->Attribute("Z");
            z = readFloat(cz);

            p = Point(x, y, z);
            pontos.push_back(p);
        }

        auto *tm = new TranslateTime(time, pontos);
        g->addTransformation(tm);
    }
}

void readNormalTranslation(tinyxml2::XMLElement *translacao, Grupo *g){
    float tx, ty, tz;

    if(translacao){
        const char* ctx = translacao->Attribute("X");
        tx = readFloat(ctx);

        const char* cty = translacao->Attribute("Y");
        ty = readFloat(cty);

        const char* ctz = translacao->Attribute("Z");
        tz = readFloat(ctz);

        auto *t = new Translate(tx, ty, tz);
        g->addTransformation(t);
    }
}

void readTranslation(tinyxml2::XMLElement *translacao, Grupo *g) {

    if(translacao){
        if(translacao->Attribute("time")){
            readTimeTranslation(translacao, g);
        }
        else{
            readNormalTranslation(translacao, g);
        }
    }
}

void readTimeRotation(tinyxml2::XMLElement *rotationTime, Grupo *g) {
    float rtime, rtx, rty, rtz;

    if(rotationTime){
        const char* ctime = rotationTime->Attribute("time");
        rtime = readFloat(ctime);

        const char* crtx = rotationTime->Attribute("axisX");
        rtx = readFloat(crtx);

        const char* crty = rotationTime->Attribute("axisY");
        rty = readFloat(crty);

        const char* crtz = rotationTime->Attribute("axisZ");
        rtz = readFloat(crtz);

        auto *rt = new RotateTime(rtime, rtx, rty, rtz);
        g->addTransformation(rt);
    }
}

void readNormalRotation(tinyxml2::XMLElement* rotacao, Grupo* g) {
    float rangle, rx, ry, rz;

    if(rotacao){
        const char* crangle = rotacao->Attribute("angle");
        rangle = readFloat(crangle);

        const char* crx = rotacao->Attribute("axisX");
        rx = readFloat(crx);

        const char* cry = rotacao->Attribute("axisY");
        ry = readFloat(cry);

        const char* crz = rotacao->Attribute("axisZ");
        rz = readFloat(crz);

        auto *r = new Rotate(rangle, rx, ry, rz);
        g->addTransformation(r);
    }
}

void readRotation(tinyxml2::XMLElement* rotacao, Grupo* g) {

    if(rotacao){
        if(rotacao->Attribute("time")){
            readTimeRotation(rotacao, g);
        }
        else{
            readNormalRotation(rotacao, g);
        }
    }
}

void readScale(tinyxml2::XMLElement* escala, Grupo* g) {
    float sx, sy, sz;

    if(escala){
        const char* csx = escala->Attribute("X");
        sx = readFloat(csx);

        const char* csy = escala->Attribute("Y");
        sy = readFloat(csy);

        const char* csz = escala->Attribute("Z");
        sz = readFloat(csz);

        auto *s = new Scale(sx, sy, sz);
        g->addTransformation(s);
    }
}


/**
 *
 * Função que faz a leitura do ficheiro e adiciona os pontos ao model
 * @param path
 */
void loadFilePoint(char *path, std::vector<Model>& vertex, std::vector<Model>& normals, std::vector<Model>& texture) {
    unsigned int size;


    std::ifstream ficheiro(path, std::ios::binary);

    std::string line;
    Model modelVertex;
    Model modelNormal;
    Model modelTexture;
    int i = 0;
    if (ficheiro.is_open()) {
        ficheiro >> size;
        getline(ficheiro, line);

        modelNormal.reserveContent((int) size);
        modelVertex.reserveContent((int) size);
        modelTexture.reserveContent((int) size);

        while(getline(ficheiro, line)) {

            std::stringstream str(line);
            std::string elem;
            std::vector<float> coordinates;

            while (getline(str, elem, ' ')){

                coordinates.push_back(std::stof(elem));
            }

            modelVertex.addContent(coordinates.at(0));
            modelVertex.addContent(coordinates.at(1));
            modelVertex.addContent(coordinates.at(2));

            modelNormal.addContent(coordinates.at(3));
            modelNormal.addContent(coordinates.at(4));
            modelNormal.addContent(coordinates.at(5));

            modelTexture.addContent(coordinates.at(6));
            modelTexture.addContent(coordinates.at(7));

        }

    }

    vertex.push_back(modelVertex);
    normals.push_back(modelNormal);
    texture.push_back(modelTexture);

    ficheiro.close();
}

int loadTexture(const std::string& s) {

    unsigned int t, tw, th;
    unsigned char *texData;
    unsigned int texID;

    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilGenImages(1, &t);
    ilBindImage(t);
    ilLoadImage((ILstring) s.c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1, &texID);

    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (int) tw, (int) th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return (int) texID;

}

void readModels(tinyxml2::XMLElement *modelos, std::vector<Model>& vertex, std::vector<Model>& normals, std::vector<Model>& texture, Grupo *g, std::vector<char *> *files, std::vector<std::string>& textureFile) {
    int flag;
    int i;
    int indexModel, textureId;
    float diffR = 0.8, diffG = 0.8, diffB = 0.8;
    float ambientR = 0.4, ambientG = 0.4, ambientB = 0.4;
    float specularR = 0.8, specularG = 0.8, specularB = 0.8;
    float emissR = 0.4, emissG = 0.4, emissB = 0.4;
    float shi = 5000;
    bool afectedByLight;

    for(const tinyxml2::XMLElement* child = modelos->FirstChildElement("model"); child!= nullptr; child = child->NextSiblingElement()) {
        // firstchildelement dá root e nextsibilingelement dá o próximo
        char *filePoint = (char *) child->Attribute("file");
        char *fileTexture = (char *) child->Attribute("texture");

        char *diffRc = (char *) child->Attribute("diffR");
        if(diffRc) diffR = readFloat(diffRc);
        char *diffGc = (char *) child->Attribute("diffG");
        if(diffGc) diffG = readFloat(diffGc);
        char *diffBc = (char *) child->Attribute("diffB");
        if(diffBc) diffB = readFloat(diffBc);

        char *ambientRc = (char *) child->Attribute("ambR");
        if(ambientRc) ambientR = readFloat(ambientRc);
        char *ambientGc = (char *) child->Attribute("ambG");
        if(ambientGc) ambientG = readFloat(ambientGc);
        char *ambientBc = (char *) child->Attribute("ambB");
        if(ambientBc) ambientB = readFloat(ambientBc);

        char *sepcR = (char *) child->Attribute("specR");
        if(sepcR) specularR = readFloat(sepcR);
        char *sepcG = (char *) child->Attribute("specG");
        if(sepcG) specularG = readFloat(sepcG);
        char *sepcB = (char *) child->Attribute("specB");
        if(sepcB) specularB = readFloat(sepcB);

        char *emisscR = (char *) child->Attribute("emissR");
        if(emisscR) emissR = readFloat(emisscR);
        char *emisscG = (char *) child->Attribute("emissG");
        if(emisscG) emissG = readFloat(emisscG);
        char *emisscB = (char *) child->Attribute("emissB");
        if(emisscB) emissB = readFloat(emisscB);

        char *shiC = (char *) child->Attribute("shi");
        if(shiC) shi = readFloat(shiC);

        char *flagLight = (char *) child->Attribute("flagLight");
        afectedByLight = !(flagLight && !strcmp(flagLight,"false"));

        flag = 1;

        indexModel = 0;
        if(filePoint) {
            for (char *f : *files) {
                if (strcmp(f, filePoint) == 0) {
                    flag = 0;
                    break;
                }
                else indexModel++;
            }

            if(flag) {
                (*files).push_back(strdup(filePoint));
                loadFilePoint(filePoint, vertex, normals, texture);
            }
        }

        flag = 1;
        i = 0;
        if(fileTexture){
            for (const std::string& f : textureFile) {
                if (f == fileTexture) {

                    flag = 0;
                    break;
                }
                else i++;
            }
            if(flag) {
                textureFile.emplace_back(fileTexture);
                textureId = loadTexture(fileTexture);
            }else
                textureId = i+1;
        }else
            textureId = -1;

        vector<float> diff = {diffR, diffG, diffB, 1.0};
        vector<float> amb = {ambientR, ambientG, ambientB, 1.0};
        vector<float> spec = {specularR, specularG, specularB, 1.0};
        vector<float> emiss = {emissR, emissG, emissB, 1.0};

        g->addModelInfo(ModelInfo(indexModel, indexModel, indexModel, textureId, diff, amb, spec, emiss, shi, OBJECT, afectedByLight));
    }
}

void readLight(tinyxml2::XMLElement* elemento, std::vector<Light>& lights) {
    vector<float> amb, diff, spe, pos, spotDir;

    float ambR = 0.2, ambG = 0.2, ambB = 0.2;
    float diffR = 1.0, diffG = 1.0, diffB = 1.0;
    float speR = 1.0f, speG = 1.0f, speB = 1.0f;
    float posX = 0.0f, posY = 0.0f, posZ = 1.0f;
    float spotDirX = 0.0f, spotDirY = 0.0f, spotDirZ = 0.0f;

    float cutOff = 180.0f, attenuation = 1.0f, exponent = 0.0f;

    for(const tinyxml2::XMLElement* child = elemento->FirstChildElement("light"); child!= nullptr; child = child->NextSiblingElement()) {

        const char *ambCX = child->Attribute("ambR");
        if(ambCX) ambR = readFloat(ambCX);
        const char *ambCY = child->Attribute("ambG");
        if(ambCY) ambG = readFloat(ambCY);
        const char *ambCZ = child->Attribute("ambB");
        if(ambCZ) ambB = readFloat(ambCZ);

        const char *diffCX = child->Attribute("diffR");
        if(diffCX) diffR = readFloat(diffCX);
        const char *diffCY = child->Attribute("diffG");
        if(diffCY) diffG = readFloat(diffCY);
        const char *diffCZ = child->Attribute("diffB");
        if(diffCZ) diffB = readFloat(diffCZ);

        const char *speCX = child->Attribute("specR");
        if(speCX) speR = readFloat(speCX);
        const char *speCY = child->Attribute("specG");
        if(speCY) speG = readFloat(speCY);
        const char *speCZ = child->Attribute("specB");
        if(speCZ) speB = readFloat(speCZ);

        amb = {ambR, ambG, ambB, 1.0f};
        diff = {diffR, diffG, diffB, 1.0f};
        spe = {speR, speG, speB, 1.0f};

        const char *posCX = child->Attribute("posX");
        if(posCX) posX = readFloat(posCX);
        const char *posCY = child->Attribute("posY");
        if(posCY) posY = readFloat(posCY);
        const char *posCZ = child->Attribute("posZ");
        if(posCZ) posZ = readFloat(posCZ);

        const char *lt = child->Attribute("type");

        if (!strcmp(lt, "POINT")) {
            pos = {posX, posY, posZ, 1.0f};

            const char *attC = child->Attribute("att");
            if(attC) attenuation = readFloat(attC);

            lights.emplace_back(amb, diff, spe, pos, attenuation, POINT);
        }
        else if (!strcmp(lt, "DIRECTIONAL")) {
            pos = {posX, posY, posZ, 0.0f};

            const char *attC = child->Attribute("att");
            if(attC) attenuation = readFloat(attC);

            lights.emplace_back(amb, diff, spe, pos, attenuation, DIRECTIONAL);
        }
        else if (!strcmp(lt, "SPOT")) {
            pos = {posX, posY, posZ, 1.0f};

            const char *sDirCX = child->Attribute("sDirX");
            if(sDirCX) spotDirX = readFloat(sDirCX);
            const char *sDirCY = child->Attribute("sDirY");
            if(sDirCY) spotDirY = readFloat(sDirCY);
            const char *sDirCZ = child->Attribute("sDirZ");
            if(sDirCZ) spotDirZ = readFloat(sDirCZ);

            spotDir = {spotDirX, spotDirY, spotDirZ};

            const char *cutOffC = child->Attribute("cutO");
            if(cutOffC) cutOff = readFloat(cutOffC);
            const char *expC = child->Attribute("exp");
            if(expC) exponent = readFloat(expC);
            const char *attC = child->Attribute("att");
            if(attC) attenuation = readFloat(attC);

            lights.emplace_back(amb, diff, spe, pos, spotDir, cutOff, attenuation, exponent, SPOT);
        }
    }
}

int isReplicated(tinyxml2::XMLElement* elemento){
    tinyxml2::XMLElement* replicate = elemento->FirstChildElement("replicate");
    return replicate ? (int) atoi(replicate->Attribute("N")) : 1;
}


Grupo readGroup(tinyxml2::XMLElement* elemento, std::vector<Model>& vertex, std::vector<Model>& normal, std::vector<Model>& texture, std::vector<Light>& lights, std::vector<char*>* files, std::vector<std::string>& textures) {
    Grupo grupo, novo_grupo;
    std::vector<Grupo> groupChildren;
    for(tinyxml2::XMLElement* child = elemento->FirstChildElement();child!= nullptr; child = child->NextSiblingElement())
        if (!strcmp(child->Value(),"translate")) {
            readTranslation(child, &grupo);
        } else if (!strcmp(child->Value(),"rotate")) {
            readRotation(child, &grupo);
        } else if (!strcmp(child->Value(),"scale")) {
            readScale(child, &grupo);
        } else if(!strcmp(child->Value(),"group")) {
            for (int i = 0; i < isReplicated(child); i++) {
                groupChildren.push_back(readGroup(child, vertex, normal, texture, lights, files, textures));
            }
        } else if (!strcmp(child->Value(),"models")) {
            readModels(child, vertex, normal, texture, &grupo, files, textures);
        } else if (!strcmp(child->Value(),"lights"))
            readLight(child, lights);
    grupo.setGroupChildren(groupChildren);
    return grupo;
}

/**
 * Função que faz o parse do ficheiro xml
 * @param path (path do ficheiro xml a ler)
 */
Grupo Parser::loadXML(std::vector<Model>& vertex, std::vector<Model>& normal, std::vector<Model>& texture, std::vector<Light>& lights) {
    Grupo grupo;
    std::srand(12345);

    std::vector<char*> filesPoints;
    std::vector<std::string> filesTextures;
    tinyxml2::XMLDocument doc;

    if(!doc.LoadFile(_path)) { // retorna 0 se for sucesso e ErrorID em insucesso
        tinyxml2::XMLElement* root = doc.RootElement();
        grupo = readGroup(root, vertex, normal, texture, lights, &filesPoints, filesTextures);
    }

    for(char* path : filesPoints){
        free(path);
    }

    return grupo;
}

Parser::~Parser() {
    free(_path);
}
