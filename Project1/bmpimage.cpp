////////////////////////////////////////
// BMPimage.cpp
////////////////////////////////////////

#include "BMPImage.h"
#include "core.h"




void swapTwoBytes (unsigned short* w) {}
void swapFourBytes (unsigned long* dw) {}


//
// quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.
// Taken from Richard Campbell Linux/GLUT code for NeHe's lesson 6:
//     http://nehe.gamedev.net
//
// Wojciech Jarosz (02/02/06) - Ported to big-endian systems (MacOS).
//
bool BMPImage::load (char *filename)
{
    FILE *fp;
    unsigned long size;           // size of the image in bytes.
    unsigned long i;              // standard counter.
    unsigned short int planes;    // number of planes in image (must be 1)
    unsigned short int bpp;       // number of bits per pixel (must be 24)

    // make sure the file is there.
    if ((fp = fopen (filename, "rb")) == 0)
    {
        printf ("File Not Found : %s\n", filename);
        return false;
    }

    // seek through the bmp header, up to the width/height:
    fseek (fp, 18, SEEK_CUR);

    // read the width
    if (fread (&sizeX, 4, 1, fp) != 1)
    {
        printf ("Error reading width from %s.\n", filename);
        fclose (fp);
        return false;
    }
    swapFourBytes (&sizeX);
    printf ("Width of %s: %lu\n", filename, sizeX);

    // read the height
    if (fread (&sizeY, 4, 1, fp) != 1)
    {
        printf ("Error reading height from %s.\n", filename);
        fclose (fp);
        return false;
    }
    swapFourBytes (&sizeY);
    printf ("Height of %s: %lu\n", filename, sizeY);

    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = sizeX * sizeY * 3;

    // read the planes
    if (fread (&planes, 2, 1, fp) != 1)
    {
        printf ("Error reading planes from %s.\n", filename);
        fclose (fp);
        return false;
    }
    swapTwoBytes (&planes);

    if (planes != 1)
    {
        printf ("Planes from %s is not 1: %u\n", filename, planes);
        fclose (fp);
        return false;
    }

    // read the bpp
    if (fread (&bpp, 2, 1, fp) != 1)
    {
        printf ("Error reading bpp from %s.\n", filename);
        fclose (fp);
        return false;
    }
    swapTwoBytes (&bpp);

    if (bpp != 24)
    {
        printf ("Bpp from %s is not 24: %u\n", filename, bpp);
        fclose (fp);
        return false;
    }

    // seek past the rest of the bitmap header.
    fseek (fp, 24, SEEK_CUR);

    // read the data.
    data = new char [size];
    if (data == 0)
    {
        printf ("Error allocating memory for image data");
        fclose (fp);
        return false;
    }

    if (fread (data, size, 1, fp) != 1)
    {
        printf ("Error reading image data from %s.\n", filename);
        fclose (fp);
        return false;
    }

    fclose (fp);
    return true;
}


// Load Bitmaps And Convert To Textures
void BMPImage::LoadGLTextures (char * filename)
{
    // Load Texture
    BMPImage image1;

    if (!image1.load (filename))
        exit (1);

	glEnable(GL_TEXTURE_2D);

    // Create Texture
    glGenTextures (1, &texture[0]);
    glBindTexture (GL_TEXTURE_2D, texture[0]);

	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, image1.sizeX, image1.sizeY,
					GL_BGR_EXT, GL_UNSIGNED_BYTE, image1.data );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

    // note that BMP images store their data in BRG order, not RGB
    glTexImage2D (GL_TEXTURE_2D, 0, 3, image1.sizeX, image1.sizeY, 0, GL_BGR_EXT,
                  GL_UNSIGNED_BYTE, image1.data);
};
