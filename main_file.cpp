#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h> //Przydatne do wypisywania komunikatów na konsoli
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "tga.h"
#include "cube.h"
#define PI 3.14159265

float speed=180; //360 stopni/s
int lastTime=0;
float angle, angle2;
float pozycja_obserwatora[3];
float cel_obserwatora[3];
int ekran_x=800;
int ekran_y=800;
int obrot=2;
int licznik=0;
int ostatni_cel_x=0;
float v_oddalania=0.01; // predkosc oddalania sie przy uzyciu strzalek UP, DOWN
float v_obracania=5; // kat obracania sie bohatera przy uzyciu strzalek LEFT, RIGHT  

float angle_x;
float angle_y;
float speed_x=0; //60 stopni/s
float speed_y=0; //60 stopni/s
GLuint tex; //Globalnie
TGAImg img; //Obojętnie czy globalnie, czy lokalnie
   

void displayFrame(void) 
{
    
    glClearColor(0,0,0,1);//(w ulamkach ) ustawia kolor czyszczenie buforow
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);// czysci bufor kolorow
	
    // macierz widoku
    /*
    glm::mat4 glm::lookAt(
    glm::vec3 observer, // polozenie kamery - glowy
    glm::vec3 center, //punkt na ktory sie patrzy
    glm::vec3 noseVector // wektor nos jak wysoko nad kamera
    );*/

    glm::mat4 V=glm::lookAt(
    glm::vec3(pozycja_obserwatora[0],pozycja_obserwatora[1],pozycja_obserwatora[2]),
    glm::vec3(cel_obserwatora[0],cel_obserwatora[1],cel_obserwatora[2]),
    glm::vec3(0.0f,1.0f,0.0f));
    
    /*
    Macierz rzutowania perspektywicznego
    glm::mat4 glm::perspective(
    float fovy, // kat rozwarcia stozka
    float aspect, // stosunek szerokosci do wysokosci okna
    float zNear, // blisk plaszczyzna odcinania
    float zFar); // daleka plaszczyzan odcinania  
    */

    glm::mat4 P=glm::perspective(50.0f, 1.0f, 1.0f, 50.0f);

    /*
    // wektory - powtorka
    glm::vec3 wektor3=glm::vec3(1.0f,2.0f,3.0f);
    glm::vec4 wektor4=glm::vec4(1.0f,2.0f,3.0f,4.0f);
    // macierz 3 na 3
    glm::mat3 macierz3x3=glm::mat3(vec3(1.#define PI 3.141592650f,2.0f,3.0f),
				  vec3(4.0f,5.0f,6.0f),
				  vec3(7.0f,8.0f,9.0f));
    // macierz 4 na 4
    glm::mat4 macierz4x4=glm::mat4(1.0f);
    */
    /*
    //macierz jednostkowa -- nic nie zmifloat angle_x;
    float angle_y;enia, jesli jest jednostkowa
    glm::mat4 M=glm::mat4(1.0f);
    glm::mat4 M2=glm::mat4(1.0f);
    
    M=IR(50,<1,0,1>)=R(50,<1,0,1>)
    M=glm::rotate(M,60.0f,glm::vec3(0.0f,1.0f,0.0f));// 1 - os x, 1 - os y, 1 os z
    M=R(50,<1,0,1>)T(<1,1,0>)
    M=glm::translate(M,glm::vec3(1.0f,1.0f,0.0f));
    M=R(50,<1,0,1>)T(<1,1,0>)S(<2,2,2>)
    M=glm::scale(M,glm::vec3(2.0f,2.0f,2.0f));
    glutWireTorus(double innerRadius, double outerRadius,int nsides, int rings);
    
  
    M=glm::rotate(glm::mat4(1.0f),angle,glm::vec3(0.0f,0.0f,-10.0f)); // odpowiada za obrot
    M=glm::translate(M,glm::vec3(0.0f,0.0f,0.0f));
    
    M2=glm::translate(M2,glm::vec3(2.8f,0.0f,0.0f));
    M2=glm::rotate(M2,angle,glm::vec3(0.0f,0.0f,10.0f)); // odpowiada za obrot
    */
    
    // zaladowanie tego do przestrzeni P, a potem V i M
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(P));
    glMatrixMode(GL_MODELVIEW);
    
    // obracanie
    glm::mat4 M=glm::mat4(1.0f);
    M=glm::rotate(M,angle_y,glm::vec3(0.0f,1.0f,0.0f));
    M=glm::rotate(M,angle_x,glm::vec3(1.0f,0.0f,0.0f));
    glLoadMatrixf(glm::value_ptr(V*M));

    
    // gl Draw arrays - metoda rysowania powierchni,ponizej zestaw funkcji, ktore wszystko ustawiaja
    glBindTexture(GL_TEXTURE_2D,tex);// do tekstury

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    //glVertexPointer(liczba wspolrzednych wierzcholka,typ tablicy z wierzcholkami,0,cubeVertices);
    glVertexPointer(3,GL_FLOAT,0,cubeVertices);
    glColorPointer(3,GL_FLOAT,0,cubeColors);// do kolorow
    glTexCoordPointer( 2, GL_FLOAT, 0, geomTexCoords2);// do tekstury

    glDrawArrays(GL_QUADS,0,cubeVertexCount);
    
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);	
   
    
    glutSwapBuffers();// przerzucenie tylnego bufor na przod ( tak jak kiedys )
}

// animacja - tego jeszcze nie wykorzystujemy, a bedziemy zeby zrobic cos ruchomego
void nextFrame(void) 
{

    int actTime=glutGet(GLUT_ELAPSED_TIME);

    int interval=actTime-lastTime; // liczy przedzial
    lastTime=actTime;
    //angle+=speed*interval/1000.0; // liczy predkosc z jaka musi sie obrocic
    angle_x+=speed_x*interval/1000.0;
    angle_y+=speed_y*interval/1000.0;
	
    if (angle_x>360) angle_x-=360;
    if (angle_x>360) angle_x+=360;
    if (angle_y>360) angle_y-=360;
    if (angle_y>360) angle_y+=360;
    
    glutPostRedisplay();

}


// procedury do obslugi klawiszy

//przycisniecie
void keyDown(int c, int x, int y) 
{
    if (c==GLUT_KEY_LEFT) 
    {
      
	float ax=cel_obserwatora[0]-pozycja_obserwatora[0],
	      az=cel_obserwatora[2]-pozycja_obserwatora[2];
	
	cel_obserwatora[0]=pozycja_obserwatora[0]+(ax*cos(-(v_obracania*PI/180))-az*sin(-(v_obracania*PI/180)));
	cel_obserwatora[2]=pozycja_obserwatora[2]+(ax*sin(-(v_obracania*PI/180))+az*cos(-(v_obracania*PI/180)));
	
    }
    if (c==GLUT_KEY_RIGHT) 
    {
      
	float ax=cel_obserwatora[0]-pozycja_obserwatora[0],
	      az=cel_obserwatora[2]-pozycja_obserwatora[2];
	
	cel_obserwatora[0]=pozycja_obserwatora[0]+(ax*cos(v_obracania*PI/180)-az*sin(v_obracania*PI/180));
	cel_obserwatora[2]=pozycja_obserwatora[2]+(ax*sin(v_obracania*PI/180)+az*cos(v_obracania*PI/180));
      
    }

    if (c==GLUT_KEY_UP) 
    {
	
	float ax=cel_obserwatora[0]-pozycja_obserwatora[0],
	      az=cel_obserwatora[2]-pozycja_obserwatora[2];
	
	pozycja_obserwatora[0]=pozycja_obserwatora[0]+(v_oddalania*ax);
	pozycja_obserwatora[2]=pozycja_obserwatora[2]+(v_oddalania*az);
	  	
	cel_obserwatora[0]=cel_obserwatora[0]+(v_oddalania*ax);
	cel_obserwatora[2]=cel_obserwatora[2]+(v_oddalania*az);
	
    }
    
    if (c==GLUT_KEY_DOWN) 
    {
	
	float ax=cel_obserwatora[0]-pozycja_obserwatora[0],
	      az=cel_obserwatora[2]-pozycja_obserwatora[2];
	      
	pozycja_obserwatora[0]=pozycja_obserwatora[0]-(v_oddalania*ax);
	pozycja_obserwatora[2]=pozycja_obserwatora[2]-(v_oddalania*az);
	
	
	cel_obserwatora[0]=cel_obserwatora[0]-(v_oddalania*ax);
	cel_obserwatora[2]=cel_obserwatora[2]-(v_oddalania*az);
    
    }
    
    glutPostRedisplay();
}

int main(int argc, char* argv[]) 
{
    //poczatkowe wartosci dla obserwatora
    pozycja_obserwatora[0]=0;//os x
    pozycja_obserwatora[1]=0;// os y
    pozycja_obserwatora[2]=-5;//os z
    cel_obserwatora[0]=0;
    cel_obserwatora[1]=0;
    cel_obserwatora[2]=10;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(ekran_x,ekran_y);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Program OpenGL");        
    glutDisplayFunc(displayFrame);
    glutIdleFunc(nextFrame);
	    
    //glEnable(GL_LIGHTING); // do cieniowania
    //glEnable(GL_LIGHT0);// do ustawienia swiatla - domyslnie 0, bialy i oznacza to ze jest w nieskonczonosci
    
    //glShadeModel(GL_FLAT); // cienowanie plaske
    glShadeModel(GL_SMOOTH); // cienowanie gladki

    glEnable(GL_DEPTH_TEST); // wlacza Z-bufor w tym buforze znajduja sie odleglosci pikseli od obserwatora
    glEnable(GL_COLOR_MATERIAL); // sledzenie przez material kolorow
    glColor3d(0.1, 0.2, 1); // ustawia kolor rysowanego obiektu
    glEnable(GL_TEXTURE_2D);  
    glewInit();
    // obsluga przycisnietego i puszczonego klawisza
    glutSpecialFunc(keyDown);
    
    
    // ustawienia tekstury i jej pobranie itp.    
    if (img.Load("bricks.tga")==IMG_OK) 
    {

      glGenTextures(1,&tex); //Zainicjuj uchwyt tex
      glBindTexture(GL_TEXTURE_2D,tex); //Przetwarzaj uchwyt tex
      if (img.GetBPP()==24) //Obrazek 24bit
	  glTexImage2D(GL_TEXTURE_2D,0,3,img.GetWidth(),img.GetHeight(),0,
	  GL_RGB,GL_UNSIGNED_BYTE,img.GetImg());
      else if (img.GetBPP()==32)
	  //Obrazek 32bit
	  glTexImage2D(GL_TEXTURE_2D,0,4,img.GetWidth(),img.GetHeight(),0,
	  GL_RGBA,GL_UNSIGNED_BYTE,img.GetImg());
      else 
      {
	  //Obrazek 16 albo 8 bit, takimi się nie przejmujemy
      }
    } 
    else 
    {
	  
    }
	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    glutMainLoop();
    glDeleteTextures(1,&tex);// usuniecie przycisku do tekstury
    
    return 0;
}