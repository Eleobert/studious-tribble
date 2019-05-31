#pragma once

#include <string>

class Texture
{
    unsigned int tid; //texture id
    int w, h;
    int channels;
public:
    Texture(const char* filename);
    unsigned int id(){return tid;}
    int width(){return w;}
    int height(){return h;}

};