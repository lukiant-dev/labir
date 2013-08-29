#ifndef LATARNIA_H
#define LATARNIA_H
#include "library.h"
#include "tga.h"
extern int daszekVertexCount;

extern float daszekVertices[];

extern float daszekColors[];

// tablica ze wspolrzednymi tesktury - troche juz wiem jak to dziala
extern float daszekTexCoords2[];

// tablica z wpolrzednymi do wektorow normalnych
extern float daszekNormals[];

extern int latarniaVertexCount;

extern float latarniaVertices[];

extern float latarniaColors[];

// tablica ze wspolrzednymi tesktury - troche juz wiem jak to dziala
extern float latarniaTexCoords2[];

// tablica z wpolrzednymi do wektorow normalnych
extern float latarniaNormals[];

extern int lightVertexCount;//16;

extern float lightVertices[];

extern float lightColors[];

// tablica ze wspolrzednymi tesktury - troche juz wiem jak to dziala
extern float lightTexCoords2[];

// tablica z wpolrzednymi do wektorow normalnych
extern float lightNormals[];

extern GLuint tex5, tex3; //Globalnie
extern TGAImg img5, img3; //Obojętnie czy globalnie, czy lokalnie


void draw_latarnia(glm::mat4 , float , float , float );



#endif
