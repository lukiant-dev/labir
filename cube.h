#ifndef CUBE_H
#define CUBE_H

//cubeVertices - tablica ze wspolrzednymi wierzcholkow.
//cubeColors - tablica z kolorami wierzcholkow
//cubeVertexCount - liczba wierzcholkow


//korytarz z chodznikiem 
int cubeVertexCount=20;

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
	 1, 1,-1,
	 
	 1,-1,-1,
	 -1,-1,-1,
	 -1,-1,-40,
	 1,-1,-40
	 
	 
};

float cubeColors[]={
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1
};

// tablica ze wspolrzednymi tesktury - nie wiem jak do konca dziala
float geomTexCoords2[]={
0,0, 1,0, 1,1, 0,1,
0,0, 1,0, 1,1, 0,1,
0,0, 1,0, 1,1, 0,1,
0,0, 1,0, 1,1, 0,1,
0,0, 1,0, 1,1, 0,1

	
};

#endif
