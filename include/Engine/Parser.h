#ifndef CG_TP_PARSER_H
#define CG_TP_PARSER_H
#include <cstring>
#include <cmath>
#include "Grupo.h"
#include "Model.h"
#include "tinyxml2.h"
#include "Light.h"
#include <fstream>

class Parser {
    private:
        char* _path;
    public:
        Parser(char*);
        ~Parser();
        Grupo loadXML(std::vector<Model> &, std::vector<Model> &, std::vector<Model> &, std::vector<Light> &);


};

#endif //CG_TP_PARSER_H
