#ifndef ELEMENTY_H
#define ELEMENTY_H
#include "library.h"
#include "tga.h"
extern int crossingVertexCount;

extern float crossingVertices[];

extern float crossingColors[];

// tablica ze wspolrzednymi tesktury - troche juz wiem jak to dziala
extern float crossingTexCoords[];

// tablica z wpolrzednymi do wektorow normalnych
extern float crossingNormals[];

extern int corridorVertexCount;

extern float corridorVertices[];

extern float corridorColors[];

// tablica ze wspolrzednymi tesktury - troche juz wiem jak to dziala
extern float corridorTexCoords[];

// tablica z wpolrzednymi do wektorow normalnych
extern float corridorNormals[];

extern int endingVertexCount;//16;

extern float endingVertices[];

extern float endingColors[];

// tablica ze wspolrzednymi tesktury - troche juz wiem jak to dziala
extern float endingTexCoords[];

// tablica z wpolrzednymi do wektorow normalnych
extern float endingNormals[];

extern GLuint tex4; //Globalnie
extern TGAImg img4; //Obojętnie czy globalnie, czy lokalnie

void draw_crossing(glm::mat4 , float , float , float );
void draw_corridor(glm::mat4 , float , float , float, float );
void draw_ending(glm::mat4 , float , float , float, float );
void draw_win_ending(glm::mat4 V, float x, float y, float z, float kat, GLuint tex);


#endif
