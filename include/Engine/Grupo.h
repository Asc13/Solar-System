#ifndef CG_TP_GRUPO_H
#define CG_TP_GRUPO_H
#include "./Model.h"
#include "Transformation/Transformation.h"
#include "../../include/Engine/Transformation/Translate.h"
#include "../../include/Engine/Transformation/Rotate.h"
#include "../../include/Engine/Transformation/Scale.h"
#include "../../include/Engine/Transformation/TranslateTime.h"
#include "../../include/Engine/Transformation/RotateTime.h"
#include "../../include/Engine/ViewFrustumCulling.h"
#include "Model.h"
#include "ModelInfo.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>

class Grupo {
    private:
        std::vector<Transformation*> _transformacoes;
        std::vector<Grupo> _groupChildren;
        std::vector<ModelInfo> _indexs;

    public:
        Grupo();
        void setGroupChildren(std::vector<Grupo>&);
        std::vector<Grupo> getGroups();
        void vboDraw(bool &, vector<bool> &, GLuint *, GLuint *, GLuint *, vector<int> &);
        void drawGroup(bool &, bool &, ViewFrustumCulling &, std::vector<vector<Point>> &, GLuint *, GLuint *, GLuint *, vector<int> &);
        void applyTranformations(bool &);
        void addModelInfo(ModelInfo);
        std::vector<ModelInfo> getModelInfo();
        void addTransformation(Transformation *);
        std::vector<Transformation *> *getTransformacoes();

};

#endif //CG_TP_GRUPO_H
