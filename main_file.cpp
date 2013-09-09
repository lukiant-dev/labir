#include "library.h"
#include "tga.h"
#include "cube.h"
#include "latarnia.h"
#include "elementy.h"
#include "glm.h"
#define PI 3.14159265
int temp=0;
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
float v_oddalania=0.1; // predkosc oddalania sie przy uzyciu strzalek UP, DOWN
float v_obracania=5; // kat obracania sie bohatera przy uzyciu strzalek LEFT, RIGHT  

float sw1, sw2;
float angle_x;
float angle_y;
float speed_x=0; //60 stopni/s
float speed_y=0; //60 stopni/s
GLuint tex,tex2; //Globalnie
TGAImg img; //Obojętnie czy globalnie, czy lokalnie
 GLMmodel * buka;    // obiekt modelu z glm.h 
 
GLuint triangleVBO;

int mapa_x=20;
int mapa_y=20; 
int tab[20][20];
int sekcja[1][2];
int directions[4];
void rotateModel(GLMmodel* model, GLuint texture,glm::mat4 V, float x, float y, float z, float kat)
{
    glm::mat4 M=glm::mat4(1.0f);

    glMatrixMode(GL_MODELVIEW);
 // glLoadMatrixf(glm::value_ptr(M));
//glLoadIdentity();
M=glm::translate(M,glm::vec3(x,y,z));
M=glm::rotate(M,kat,glm::vec3(0.0f,1.0f,0.0f));    
M=glm::translate(M,glm::vec3(-x,-y,-z));

	
glLoadMatrixf(glm::value_ptr(V*M));
}

void drawModel(GLMmodel* model, GLuint texture,glm::mat4 V, float x, float y, float z, float kat)
{
    glm::mat4 M=glm::mat4(1.0f);

    glMatrixMode(GL_MODELVIEW);
GLfloat pocz_x,pocz_y,pocz_z;
//M=glm::translate(M,glm::vec3(x,y,z));
//glLoadIdentity();

//glLoadMatrixf(glm::value_ptr(V*M));
//

    

//pocz_x=1.1f;
//pocz_y=1.1f;
pocz_x=-1.1f;
pocz_y=-1.4f;
pocz_z=0.0f;
glm::vec3 poz_pocz=glm::vec3(pocz_x,pocz_y,pocz_z);
//glm::mat4 V2=glm::lookAt(glm::vec3(0,0,0), glm::vec3(x,y,z), glm::vec3(0.0f,1.0f,0.0f));



//M=glm::translate(M,glm::vec3(x,y,z));
M=glm::translate(M,poz_pocz); 	
M=glm::translate(M,glm::vec3(x-pocz_x,y-pocz_y,z-pocz_z));
M=glm::rotate(M,kat,glm::vec3(0.0f,1.0f,0.0f));
M=glm::translate(M,glm::vec3(-x+pocz_x,-y+pocz_y,-z+pocz_z));
glLoadMatrixf(glm::value_ptr(V*M));

//glGenBuffers(1, &triangleVBO);
//glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
//printf("%d", sizeof(model->vertices2));
//printf(" %d\n", sizeof(GLuint)*model->numtriangles);
//sleep(100);
//glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint)*model->numvertices2, model->vertices2, GL_STATIC_DRAW);
    glBindTexture(GL_TEXTURE_2D,texture);// do tekstury
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

// glEnableClientState(GL_COLOR_ARRAY);

//glColorPointer(3,GL_FLOAT,0,cubeColors2);// do kolorow
    glTexCoordPointer( 2, GL_FLOAT, 0, model->texcoords2);// do tekstury
    glNormalPointer( GL_FLOAT, 0, model->normals2);
    glVertexPointer(3, GL_FLOAT, 0, model->vertices2);
    float amb[]={0,0,0,1};
    float dif[]={0.7,0.5,0.5,1};
    float spec[]={0,0,0,0};
  
    printf("ok");
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, amb); 
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50);
//glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
//glBindBuffer(GL_ARRAY_BUFFER,0);
glDrawArrays(GL_TRIANGLES,0,model->numtriangles*3);
  

    glDisableClientState( GL_NORMAL_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState(GL_TEXTURE_COORD_ARRAY); 
//	glDisableClientState(GL_COLOR_ARRAY);


}
void animate(GLMmodel* model, GLfloat x, GLfloat y, GLfloat z){

for (int i=0; i<model->numtriangles*3; i++){

	model->vertices2[3*i]+=x;
	model->vertices2[3*i+1]+=y;
	model->vertices2[3*i+2]+=z;
	
	}
	model->posx+=x;
		model->posy+=y;
		model->posz+=z;

}
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
    
  
   glm::mat4 M=glm::rotate(glm::mat4(1.0f),angle,glm::vec3(0.0f,0.0f,-10.0f)); // odpowiada za obrot
    M=glm::translate(M,glm::vec3(0.0f,0.0f,0.0f));
    
    M2=glm::translate(M2,glm::vec3(2.8f,0.0f,0.0f));
    M2=glm::rotate(M2,angle,glm::vec3(0.0f,0.0f,10.0f)); // odpowiada za obrot
    */
    
    // zaladowanie tego do przestrzeni P, a potem V i M
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(P));
    glMatrixMode(GL_MODELVIEW);
    
   // glLoadIdentity();
/*    
    float lightPos[]={0,,1,1};//{0,sw1,0,1};
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

	
    float lightPos2[]={0,1,0,0}; // wskazuje na przestrzen ktora oswietla
    
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,lightPos2);
    
    glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,2);// kat rozwarcia stozka /2
    glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,128); // 128 najbardziej skupione
  */  
    


    glm::mat4 M=glm::mat4(1.0f);
    M=glm::rotate(M,angle_y,glm::vec3(0.0f,1.0f,0.0f));
    M=glm::rotate(M,angle_x,glm::vec3(1.0f,0.0f,0.0f));
  
   
    glLoadMatrixf(glm::value_ptr(V)); // albo polaczone
/*
    float lightPos[]={1,-0.5,-40};//{0,sw1,0,1};
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
*/
      
    // stozkowe nieruchome np. daszek
    float lightPos[]={1.5,172,-41,1};//{0,sw1,0,1};
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

	
    float lightPos2[]={0,-1,0,0}; // wskazuje na przestrzen ktora oswietla
    
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,lightPos2);
    
    glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,1);// kat rozwarcia stozka /2
    glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,128); // 128 najbardziej skupione
    

    glLoadMatrixf(glm::value_ptr(V*M));
    
    
    
    // ustawienie latarki :)
    
    // obracanie
    
    // gl Draw arrays - metoda rysowania powierchni,ponizej zestaw funkcji, ktore wszystko ustawiaja
    glBindTexture(GL_TEXTURE_2D,tex);// do tekstury

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState( GL_NORMAL_ARRAY );
    glEnableClientState(GL_COLOR_ARRAY);
    
    
    //glVertexPointer(liczba wspolrzednych wierzcholka,typ tablicy z wierzcholkami,0,cubeVertices);
    glVertexPointer(3,GL_FLOAT,0,cubeVertices);
    glNormalPointer( GL_FLOAT, 0, cubeNormals);
    glTexCoordPointer( 2, GL_FLOAT, 0, geomTexCoords2);// do tekstury
    glColorPointer(3,GL_FLOAT,0,cubeColors);// do kolorow
    
    
    float amb[]={0,0,0,1};
    float dif[]={0.7,0.5,0.5,1};
    float spec[]={0,0,0,0};
  
    printf("ok");
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, amb); 
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50);

    //gLightfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    
    glDrawArrays(GL_QUADS,0,cubeVertexCount);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState( GL_NORMAL_ARRAY );

//buka!



/*    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
// glEnableClientState(GL_COLOR_ARRAY);

//glColorPointer(3,GL_FLOAT,0,cubeColors2);// do kolorow tekstury
    glNormalPointer( GL_FLOAT, 0, (buka->normals2));
    glVertexPointer(3,GL_FLOAT,0,(buka->vertices2));

//glDrawArrays(GL_TRIANGLES,0,buka->numtriangles);
  

    glDisableClientState( GL_NORMAL_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState(GL_TEXTURE_COORD_ARRAY); 
//	glDisableClientState(GL_COLOR_ARRAY);
*/
  //  glBindTexture(GL_TEXTURE_2D,tex2);// do tekstury
//glmDraw(buka,GLM_TEXTURE); // alternatywne rysowanie - funkcja używa glBegin
   
drawModel(buka,tex2, V,buka->posx,buka->posy,buka->posz, buka->rot);
//buka->rot = 180;
printf("buka->rot %f\n", buka->rot);
printf("buka->posx %f\n", buka->posx);
printf("buka->posy %f\n", buka->posy);
printf("buka->posz %f\n", buka->posz);

if (temp==1) {
if (buka->posz<15) animate(buka, 0.0,0.0,0.1);
else temp=2;
}
if (temp==0) {
if (buka->rot<180) buka->rot+=1;
else
temp = 1;
}
if (temp==3) {
if (buka->posz>0) animate(buka, 0.0,0.0,-0.1);
else temp=0;
}

if (temp==2) {
if (buka->rot>0) buka->rot-=1;
else
temp = 3;
}

//rotateModel(buka,tex2,V,buka->posx,buka->posy,buka->posz,90);

    // generowanie labiryntu

    int x,y;
    x=(mapa_x/2)-1;
    y=(mapa_y-1);
    for(int i = 0; i<mapa_y ; i++)for(int j = 0; j<mapa_x;j++)
    {
	  if(tab[j][i]==1)draw_crossing(V,-(j-x)*3,0,41.5-(i-y)*3);
	  if(tab[j][i]==2)draw_corridor(V,-(j-x)*3,0,41.5-(i-y)*3,0.0);
	  if(tab[j][i]==3)draw_corridor(V,-(j-x)*3,0,41.5-(i-y)*3,90.0);
	  if(tab[j][i]==4)draw_ending(V,-(j-x)*3,0,41.5-(i-y)*3,0.0);
	  if(tab[j][i]==5)draw_ending(V,-(j-x)*3,0,41.5-(i-y)*3,90.0);
	  if(tab[j][i]==6)draw_ending(V,-(j-x)*3,0,41.5-(i-y)*3,180.0);
	  if(tab[j][i]==7)draw_ending(V,-(j-x)*3,0,41.5-(i-y)*3,270.0);
	  
    }
    draw_latarnia(V,0,0,-40);
    
    
    // sprawdzanie w ktorej sekcji jest gracz
    for(int i = 0; i<mapa_y ; i++)for(int j = 0; j<mapa_x;j++)
    {
      if((pozycja_obserwatora[0]>(-(j-x)*3-1.5)) && (pozycja_obserwatora[0]<(-(j-x)*3+1.5))
	&& (pozycja_obserwatora[2]>(41.5-(i-y)*3-1.5)) && (pozycja_obserwatora[2]<(41.5-(i-y)*3+1.5)))
      {
	    sekcja[0][0]=j;
	    sekcja[0][1]=i;
	    
      }
    }
    
     
    
    printf(" sekcja: %d , %d \n", sekcja[0][0],sekcja[0][1]);
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

void keyDown2(unsigned char c, int x, int y) 
{
     if (c=='q')
     {
       sw1=sw1-2;
       printf("sw= %f \n",sw1);
     }
      
     if (c=='w')
     {
       sw1=sw1+2;
       printf("sw= %f \n",sw1);
     }
}

int main(int argc, char* argv[]) 
{
    
    //poczatkowe wartosci dla obserwatora
    pozycja_obserwatora[0]=0;//os x
    pozycja_obserwatora[1]=0;// os y
    pozycja_obserwatora[2]=-5;//os z
    cel_obserwatora[0]=0;
    cel_obserwatora[1]=0;
    cel_obserwatora[2]=0;
    sw1=-40;
    directions[0]=0;
    directions[1]=0;
    directions[2]=0;
    directions[3]=0;
    sekcja[0][0]=-1;
    sekcja[0][1]=-1;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(ekran_x,ekran_y);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Program OpenGL");        
    glutDisplayFunc(displayFrame);
    glutIdleFunc(nextFrame);

     glewInit();
    // obsluga przycisnietego i puszczonego klawisza
    glutSpecialFunc(keyDown);
    glutKeyboardFunc(keyDown2);
// funkcji z glm.cpp, zaskakująco wczytuje model 
buka = glmReadOBJ("bunia2.obj");

buka->posx = 0.0;
buka->posy = 0.0;
buka->posz = 0.0;
buka->rot = 0.0;
/*for (int i =0; i<buka->numtriangles*9+3; i++)
{
printf("%f ",buka->vertices2[i]);
}printf("\n");
sleep(100);
*/
    glEnable(GL_LIGHTING); // do cieniowania
    glEnable(GL_LIGHT0);// do ustawienia swiatla - domyslnie 0, bialy i oznacza to ze jest w nieskonczonosci
    
    //glShadeModel(GL_FLAT); // cienowanie plaske
    //glShadeModel(GL_SMOOTH); // cienowanie gladki

    glEnable(GL_DEPTH_TEST); // wlacza Z-bufor w tym buforze znajduja sie odleglosci pikseli od obserwatora
    glEnable(GL_NORMALIZE); // normalizuje wektory 
    //glEnable(GL_COLOR_MATERIAL); // sledzenie przez material kolorow
    // glColor3d(0.1, 0.2, 1); // ustawia kolor rysowanego obiektu
    
    float lightPosAm[]={1,1,1,1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lightPosAm); // dodaje blasku hehe :)
  
// tekstury zrobię potem w tablicy i załatwię pętlą for, żeby nie powielać tyle kodu
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
    glEnable(GL_TEXTURE_2D);

    if (img3.Load("bricks2.tga")==IMG_OK) 
    {

      glGenTextures(1,&tex3); //Zainicjuj uchwyt tex3
      glBindTexture(GL_TEXTURE_2D,tex3); //Przetwarzaj uchwyt tex3
      if (img3.GetBPP()==24) //Obrazek 24bit
	  glTexImage2D(GL_TEXTURE_2D,0,3,img3.GetWidth(),img3.GetHeight(),0,
	  GL_RGB,GL_UNSIGNED_BYTE,img3.GetImg());
      else if (img3.GetBPP()==32)
	  //Obrazek 32bit
	  glTexImage2D(GL_TEXTURE_2D,0,4,img3.GetWidth(),img3.GetHeight(),0,
	  GL_RGBA,GL_UNSIGNED_BYTE,img3.GetImg());
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
    glEnable(GL_TEXTURE_2D);

    if (img4.Load("bricks.tga")==IMG_OK) 
    {

      glGenTextures(1,&tex4); //Zainicjuj uchwyt tex4
      glBindTexture(GL_TEXTURE_2D,tex4); //Przetwarzaj uchwyt tex4
      if (img4.GetBPP()==24) //Obrazek 24bit
	  glTexImage2D(GL_TEXTURE_2D,0,3,img4.GetWidth(),img4.GetHeight(),0,
	  GL_RGB,GL_UNSIGNED_BYTE,img4.GetImg());
      else if (img4.GetBPP()==32)
	  //Obrazek 32bit
	  glTexImage2D(GL_TEXTURE_2D,0,4,img4.GetWidth(),img4.GetHeight(),0,
	  GL_RGBA,GL_UNSIGNED_BYTE,img4.GetImg());
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
    glEnable(GL_TEXTURE_2D);
  
    if (img5.Load("bricks1.tga")==IMG_OK) 
    {

      glGenTextures(1,&tex5); //Zainicjuj uchwyt tex5
      glBindTexture(GL_TEXTURE_2D,tex5); //Przetwarzaj uchwyt tex5
      if (img5.GetBPP()==24) //Obrazek 24bit
	  glTexImage2D(GL_TEXTURE_2D,0,3,img5.GetWidth(),img5.GetHeight(),0,
	  GL_RGB,GL_UNSIGNED_BYTE,img5.GetImg());
      else if (img5.GetBPP()==32)
	  //Obrazek 32bit
	  glTexImage2D(GL_TEXTURE_2D,0,4,img5.GetWidth(),img5.GetHeight(),0,
	  GL_RGBA,GL_UNSIGNED_BYTE,img5.GetImg());
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
    glEnable(GL_TEXTURE_2D);
    
    FILE *fp;

    if ((fp=fopen("mapa.txt", "r"))==NULL)
	{
	printf("Nie moge otworzyc pliku mapa.txt do odczytu");
	exit(1);
	}
   
    
      for(int i=0;i<mapa_y;i++)for(int j=0;j<mapa_x;j++)
    {
      //fseek(fp,1,SEEK_CUR);
      fscanf (fp, "%d", &tab[j][i]);
      //cout<<"liczba1: "<<liczba<<endl;
    }

    if (img.Load("bunia.tga")==IMG_OK) 
    {

      glGenTextures(1,&tex2); //Zainicjuj uchwyt tex
      glBindTexture(GL_TEXTURE_2D,tex2); //Przetwarzaj uchwyt tex
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
    glEnable(GL_TEXTURE_2D);

    glutMainLoop();
    glDeleteTextures(1,&tex);// usuniecie przycisku do tekstury
    glDeleteTextures(1,&tex2);// usuniecie przycisku do tekstury
    glDeleteTextures(1,&tex3);// usuniecie przycisku do tekstury
    glDeleteTextures(1,&tex4);// usuniecie przycisku do tekstury
    glDeleteTextures(1,&tex5);// usuniecie przycisku do tekstury
    
    return 0;
}
