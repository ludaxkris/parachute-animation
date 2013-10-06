////////////////////////////////////////
// bmploader.h
////////////////////////////////////////

#ifndef CSE169_BMPIMAGE_H
#define CSE169_BMPIMAGE_H

#include "core.h"

class BMPImage
{
public:
    ~BMPImage ()
    {
        delete [] data;
    }
    
    bool load (char* filename);
	void LoadGLTextures (char * filename);

	// storage for one texture
	GLuint texture[1];

    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};



#endif