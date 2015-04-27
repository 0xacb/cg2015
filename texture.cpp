#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

static void reverse(void* x,const int n) {
    int k;
    char* ch = (char*)x;
    for (k=0;k<n/2;k++) {
        char tmp = ch[k];
        ch[k] = ch[n-1-k];
        ch[n-1-k] = tmp;
    }
}

int loadTexture(const char * path){
    unsigned int texture;
    FILE* f;
    unsigned short magic;
    unsigned int dx,dy,size;
    unsigned short nbp,bpp;
    unsigned char* image;
    unsigned int k;

    f = fopen(path, "rb");
    if (!f) return 0;

    if (fread(&magic,2,1,f)!=1) return 0;
    if (magic!=0x4D42 && magic!=0x424D) return 0;

    if (fseek(f,16,SEEK_CUR) || fread(&dx ,4,1,f)!=1 || fread(&dy ,4,1,f)!=1 || fread(&nbp,2,1,f)!=1 || fread(&bpp,2,1,f)!=1 || fread(&k,4,1,f)!=1)
        return 0;

    if (magic==0x424D) {
        reverse(&dx,4);
        reverse(&dy,4);
        reverse(&nbp,2);
        reverse(&bpp,2);
        reverse(&k,4);
    }

    if (dx<1 || dx>65536) return 0;
    if (dy<1 || dy>65536) return 0;
    if (nbp!=1)  return 0;
    if (bpp!=24) return 0;
    if (k!=0)    return 0;
    #ifndef GL_VERSION_2_0
        for (k=1;k<dx;k*=2);
        if (k!=dx) return 0;
        for (k=1;k<dy;k*=2);
        if (k!=dy) return 0;
    #endif

    size = 3*dx*dy;
    image = (unsigned char*) malloc(size);
    if (!image) return 0;

    if (fseek(f,20,SEEK_CUR) || fread(image,size,1,f)!=1)
        return 0;
    fclose(f);

    for (k=0;k<size;k+=3) {
        unsigned char temp = image[k];
        image[k]   = image[k+2];
        image[k+2] = temp;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);

    glTexImage2D(GL_TEXTURE_2D,0,3,dx,dy,0,GL_RGB,GL_UNSIGNED_BYTE,image);
    if (glGetError()) return 0;
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    free(image);
    return texture;
}
