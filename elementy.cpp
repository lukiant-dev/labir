#include "elementy.h"
int crossingVertexCount=8;//16;

float crossingVertices[]={
        
	-1.5,-1,-1.5,
	-1.5,-1, 1.5,
	 1.5,-1, 1.5,
	 1.5,-1,-1.5,

	-1.5, 1,-1.5,
	-1.5, 1, 1.5,
	 1.5, 1, 1.5,
	 1.5, 1,-1.5

	
     
 
};

float crossingColors[]={
  
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1
	
};

// tablica ze wspolrzednymi tesktury - troche juz wiem jak to dziala
float crossingTexCoords[]={
	0,0, 1,0, 1,1, 0,1,
	0,0, 1,0, 1,1, 0,1
	
};

// tablica z wpolrzednymi do wektorow normalnych
float crossingNormals[]={
	-1,-1,-1,
	-1,-1, 1,
	 1,-1, 1,
	 1,-1,-1,

	-1, 1,-1,
	-1, 1, 1,
	 1, 1, 1,
	 1, 1,-1,

	
};

int corridorVertexCount=16;

float corridorVertices[]={
      
	-1.5,-1,-1.5,
	-1.5,-1, 1.5,
	 1.5,-1, 1.5,
	 1.5,-1,-1.5,

	-1.5, 1,-1.5,
	-1.5, 1, 1.5,
	 1.5, 1, 1.5,
	 1.5, 1,-1.5,

	-1.5,-1,-1.5,
	-1.5,-1, 1.5,
	-1.5, 1, 1.5,
	-1.5, 1,-1.5,

	 1.5,-1,-1.5,
	 1.5,-1, 1.5,
	 1.5, 1, 1.5,
	 1.5, 1,-1.5
      
 
};

float corridorColors[]={
  
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1
};

// tablica ze wspolrzednymi tesktury - troche juz wiem jak to dziala
float corridorTexCoords[]={
	
	0,0, 1,0, 1,1, 0,1,
	0,0, 1,0, 1,1, 0,1,
	0,0, 1,0, 1,1, 0,1,
	0,0, 1,0, 1,1, 0,1
	
};

// tablica z wpolrzednymi do wektorow normalnych
float corridorNormals[]={
  
	-1,-1,-1,
	-1,-1, 1,
	 1,-1, 1,
	 1,-1,-1,

	-1, 1,-1,
	-1, 1, 1,
	 1, 1, 1,
	 1, 1,-1,

	-1,-1,-1,
	-1,-1, 1,
	-1, 1, 1,
	-1, 1,-1,

	 1,-1,-1,
	 1,-1, 1,
	 1, 1, 1,
	 1, 1,-1
};

int endingVertexCount=4;//16;

float endingVertices[]={
      
      
	-1.5,-1,-1.5,
	-1.5, 1,-1.5,
	 1.5, 1,-1.5,
	 1.5,-1,-1.5
      
};

float endingColors[]={
  
	1,1,1, 1,1,1, 1,1,1, 1,1,1
	
};

// tablica ze wspolrzednymi tesktury - troche juz wiem jak to dziala
float endingTexCoords[]={
	0,0, 1,0, 1,1, 0,1
	
};

// tablica z wpolrzednymi do wektorow normalnych
float endingNormals[]={
  
	 1,-1,-1,
	 1,-1, 1,
	 1, 1, 1,
	 1, 1,-1
};
GLuint tex4; //Globalnie
TGAImg img4; //Obojętnie czy globalnie, czy lokalnie

void draw_crossing(glm::mat4 V, float x, float y, float z)
{
    glm::mat4 M=glm::mat4(1.0f);
    M=glm::translate(M,glm::vec3(x,y,z));

    glLoadMatrixf(glm::value_ptr(V*M));
    
    
 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,tex4);// do tekstury
  
  
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    //glEnableClientState( GL_NORMAL_ARRAY );
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      
    glTexCoordPointer( 2, GL_FLOAT, 0, crossingTexCoords);
   // glNormalPointer( GL_FLOAT, 0, crossingNormals);
    glVertexPointer(3,GL_FLOAT,0,crossingVertices);
    glColorPointer(3,GL_FLOAT,0,crossingColors);// do kolorow
    
    glDrawArrays(GL_QUADS,0,crossingVertexCount);
   
    //glDisableClientState( GL_NORMAL_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    
 
}

void draw_corridor(glm::mat4 V, float x, float y, float z, float kat)
{
//*
    glm::mat4 M=glm::mat4(1.0f);
    M=glm::translate(M,glm::vec3(x,y,z));

    M=glm::rotate(M,kat,glm::vec3(0.0f,1.0f,0.0f));// 1 - os x, 1 - os y, 1 os z
   
  
    glLoadMatrixf(glm::value_ptr(V*M));
    
    
 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,tex4);// do tekstury
  
  
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    //glEnableClientState( GL_NORMAL_ARRAY );
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      
    glTexCoordPointer( 2, GL_FLOAT, 0, corridorTexCoords);
    //glNormalPointer( GL_FLOAT, 0, corridorNormals);
    glVertexPointer(3,GL_FLOAT,0,corridorVertices);
    glColorPointer(3,GL_FLOAT,0,corridorColors);// do kolorow
    
    glDrawArrays(GL_QUADS,0,corridorVertexCount);
   
    //glDisableClientState( GL_NORMAL_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    
 
    
    
    
    
    
}
void draw_ending(glm::mat4 V, float x, float y, float z, float kat)
{
    glm::mat4 M=glm::mat4(1.0f);
    M=glm::translate(M,glm::vec3(x,y,z));
    M=glm::rotate(M,kat,glm::vec3(0.0f,1.0f,0.0f));// 1 - os x, 1 - os y, 1 os z
   
    
    glLoadMatrixf(glm::value_ptr(V*M));
    
    
 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,tex4);// do tekstury
  
  
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    //glEnableClientState( GL_NORMAL_ARRAY );
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      
    glTexCoordPointer( 2, GL_FLOAT, 0, endingTexCoords);
    //glNormalPointer( GL_FLOAT, 0, endingNormals);
    glVertexPointer(3,GL_FLOAT,0,endingVertices);
    glColorPointer(3,GL_FLOAT,0,endingColors);// do kolorow
    
    glDrawArrays(GL_QUADS,0,endingVertexCount);
   
    //glDisableClientState( GL_NORMAL_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
 
}
