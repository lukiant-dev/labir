#ifndef CUBE_H
#define CUBE_H

//cubeVertices - tablica ze wspolrzednymi wierzcholkow.
//cubeColors - tablica z kolorami wierzcholkow
//cubeVertexCount - liczba wierzcholkow

//*
//kwadrat 
int cubeVertexCount=16;

float cubeVertices[]={

	-1,-1,-1,
	-1,-1, 40,
	 1,-1, 40,
	 1,-1,-1,

	-1, 1,-1,
	-1, 1, 40,
	 1, 1, 40,
	 1, 1,-1,

	-1,-1,-1,
	-1,-1, 40,
	-1, 1, 40,
	-1, 1,-1,

	 1,-1,-1,
	 1,-1, 40,
	 1, 1, 40,
	 1, 1,-1
};

float cubeColors[]={
	0,0,1, 0,0,1, 0,0,1, 0,0,1,
	1,1,0, 1,1,0, 1,1,0, 1,1,0,
	0,1,1, 0,1,1, 0,1,1, 0,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1
};
//*/
/*

//ostroslup
float geomVertices1[]={
  0,4.08,0,	0,0,2.88,
  0,4.08,0,	2.5,0,-1.44,
  0,4.08,0,	-2.5,0,-1.44,
  0,0,2.88,	-2.5,0,-1.44,
  0,0,2.88,	2.5,0,-1.44,
  -2.5,0,-1.44, 2.5,0,-1.44
};
int geomVertexCount1=12;

*/

//pierwsza sciana
/*
int cubeVertexCount=4;

float cubeVertices[]={
	1,1,5,
	-1,1,5,
	-1,-1,5,
	1,-1,5
};

float cubeColors[]={
	1,0,0, 1,0,0, 1,0,0, 1,0,0
	
};
*/

#endif
