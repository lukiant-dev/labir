  
#ifndef CUBE_H
#define CUBE_H

//cubeVertices - tablica ze wspolrzednymi wierzcholkow.
//cubeColors - tablica z kolorami wierzcholkow
//cubeVertexCount - liczba wierzcholkow


//korytarz z chodznikiem 
int cubeVertexCount=20;//16;

float cubeVertices[]={
// uwagi : kolejnosc wazna
 /*
	 10,-1.5,10,
	 10,-1.5,0,
	 0,-1.5,0,
	 0,-1.5,10,
	 
	 
	 10,-1.5,-10,
	 10,-1.5,0,
	 0,-1.5,0,
	 0,-1.5,-10,
	 
	 -10,-1.5,-10,
	 0,-1.5,-10,
	 0,-1.5,0,
	 -10,-1.5,0,
	 
	 -10,-1.5,10,
	 0,-1.5,10,
	 0,-1.5,0,
	 -10,-1.5,0
//*/	 
	 
  
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
	 -1,-1,-41,
	 1,-1,-41
	 
	 
};

float cubeColors[]={
/*
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1
//*/
	
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1
	
};

// tablica ze wspolrzednymi tesktury - troche juz wiem jak to dziala
float geomTexCoords2[]={
/*
	0,0, 2.5,0, 2.5,2.5, 0,2.5,
	0,0, 2.5,0, 2.5,2.5, 0,2.5,
	0,0, 2.5,0, 2.5,2.5, 0,2.5,
	0,0, 2.5,0, 2.5,2.5, 0,2.5
*/
	//*
	0,0, 1,0, 1,1, 0,1,
	0,0, 1,0, 1,1, 0,1,
	0,0, 1,0, 1,1, 0,1,
	0,0, 1,0, 1,1, 0,1,
	0,0, 1,0, 1,1, 0,1 //w tym momencie cala sciana nr 5 bedzie pokryta cala tekstura, gdyby zamiast wszystkich "1" w tym wierszu wpisac 0.5 to polowa tekstury   
//*/
	
};

// tablica z wpolrzednymi do wektorow normalnych
float cubeNormals[]={
/*	
  	0,1,0,
	0,1,0,
	0,1,0,
	0,1,0,
	
	0,1,0,
	0,1,0,
	0,1,0,
	0,1,0,
	
	0,1,0,
	0,1,0,
	0,1,0,
	0,1,0,
	
	0,1,0,
	0,1,0,
	0,1,0,
	0,1,0
 //*/

  
//*
         1,1,1,
	 -1,-1,1,
	 1,-1,1,
	 -1,1,1,

	1, -1,1,
	1, -1, 1,
	 -1,-1, 1,
	 -1, -1,1,

	1,1,1,
	1,1, 1,
	1, -1, 1,
	1, -1,1,

	 -1,1,1,
	 -1,1, 1,
	 -1, -1, 1,
	 -1, -1,1,
	 
	 -1,1,1,
	 1,1,1,
	 0,1,0,
	 0,1,0
	  
//*/
  
};


#endif
