 
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h

#include "myHeader.h"

#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;
  
//////////////////////////////////////

GLuint
  VaoId,
  VboId,
  ColorBufferId,
  ProgramId,
  myMatrixLocation,
  matrScaleLocation,
  matrTranslLocation,
  matrRotlLocation,
  codColLocation;
 
glm::mat4 myMatrix, resizeMatrix, matrTransl, matrScale, matrRot; 


int codCol;
 float PI=3.141592;

 int width=1280, height=720;

void DestroyVBO(void)
{
 

  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &ColorBufferId);
  glDeleteBuffers(1, &VboId);

  glBindVertexArray(0);
  glDeleteVertexArrays(1, &VaoId);

   
}

void CreateShaders(void)
{
  ProgramId=LoadShaders("src/08_01_Shader.vert", "src/08_01_Shader.frag");
  glUseProgram(ProgramId);
}

 
void DestroyShaders(void)
{
  glDeleteProgram(ProgramId);
}
 
void init (void)  // initializare fereastra de vizualizare
{
	glClearColor (1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

    glMatrixMode (GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D (0.0, 1200.0, 0.0, 700.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}
void Initialize(void)
{
  myMatrix = glm::mat4(1.0f);
  
  resizeMatrix= glm::scale(glm::mat4(1.0f), glm::vec3(1.f/width, 1.f/height, 1.0));

  // CreateVBOPoints();
  // CreateVBOLines1();
  // CreateVBOLines2();
  CreateShaders(); 

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // culoarea de fond a ecranului
}

void CreateVBOPoints(void)
{
  // varfurile 
  GLfloat Vertices[] = {
    20.0f, 20.0f, 0.0f, 1.0f,
    21.0f, 21.0f, 0.0f, 1.0f,
    22.0f, 22.0f, 0.0f, 1.0f,
    23.0f, 23.0f, 0.0f, 1.0f,
    24.0f, 24.0f, 0.0f, 1.0f,
    27.0f, 27.0f, 0.0f, 1.0f,
    100.0f, 100.0f, 0.0f, 1.0f,
    100.0f, 400.0f, 0.0f, 1.0f,
    300.0f, 500.0f, 0.0f, 1.0f,
  };
   
 

  // culorile varfurilor din colturi
  GLfloat Colors[] = {
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 0.5f, 1.0f,
  };
  // se creeaza un buffer nou
  glGenBuffers(1, &VboId);
  // este setat ca buffer curent
  glBindBuffer(GL_ARRAY_BUFFER, VboId);
  // punctele sunt "copiate" in bufferul curent
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  
  // se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
  glGenVertexArrays(1, &VaoId);
  glBindVertexArray(VaoId);
  // se activeaza lucrul cu atribute; atributul 0 = pozitie
  glEnableVertexAttribArray(0);
  // 
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);  

  // un nou buffer, pentru culoare
  glGenBuffers(1, &ColorBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
  // atributul 1 =  culoare
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    
  glDrawArrays(GL_POINTS, 0, 8);    
 }

void CreateVBOLines1(void)
{
  // varfurile 
  GLfloat Vertices[] = {
    0.0f, 100.0f, 0.0f, 1.0f,
    400.0f, 500.0f, 0.0f, 1.0f,
  };
   
  // se creeaza un buffer nou
  glGenBuffers(1, &VboId);
  // este setat ca buffer curent
  glBindBuffer(GL_ARRAY_BUFFER, VboId);
  // punctele sunt "copiate" in bufferul curent
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  
  // se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
  glGenVertexArrays(1, &VaoId);
  glBindVertexArray(VaoId);
  // se activeaza lucrul cu atribute; atributul 0 = pozitie
  glEnableVertexAttribArray(0);
  // 
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);  

  codCol = 2;
  glUniform1i(codColLocation, codCol);
  glDrawArrays(GL_LINE_STRIP, 0, 2);    
 }

void CreateVBOLines2(void)
{
  // varfurile 
  GLfloat Vertices[] = {
    400.0f, 400.0f, 0.0f, 1.0f,
    600.0f, 500.0f, 0.0f, 1.0f,
    700.0f, 520.0f, 0.0f, 1.0f,
    655.0f, 690.0f, 0.0f, 1.0f,
  };

  // se creeaza un buffer nou
  glGenBuffers(1, &VboId);
  // este setat ca buffer curent
  glBindBuffer(GL_ARRAY_BUFFER, VboId);
  // punctele sunt "copiate" in bufferul curent
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  
  // se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
  glGenVertexArrays(1, &VaoId);
  glBindVertexArray(VaoId);
  // se activeaza lucrul cu atribute; atributul 0 = pozitie
  glEnableVertexAttribArray(0);
  // 
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);  

  codCol = 3;
  glUniform1i(codColLocation, codCol);
  glDrawArrays(GL_LINES, 0, 4);  
 }

void desen (void) // procedura desenare  
{
	
	glColor3f (0.0, 0.0, 1.0); // culoarea punctelor: albastru
	{
		 glPointSize (1.0);
		glBegin (GL_POINTS); // reprezinta puncte
		glVertex2i (20, 20);
		glVertex2i (21, 21);
		glVertex2i (22, 22);
		glVertex2i (23, 23);
		glVertex2i (24, 24);
		glVertex2i (27, 27);
		glVertex2i (100, 100);
		glEnd ( );
		
	}
 
    
	glColor3d (0.0, 0.05, 0.05);
	// glPointSize (6.0);
	glBegin (GL_POINTS);
	   glVertex2i (100, 400);
	   glColor3f (1.0, 0.0, 0.5);
	   glVertex2i (300, 500);
    glEnd ( );
	

   glColor3f (1.0, 0.0, 0.0); // culoarea liniei: rosu
       // reprezinta o linie franta
     //  glLineWidth (2.0);
	  //  glEnable (GL_LINE_STIPPLE);
	 //  glLineStipple (1, 0x1EED);
	   glBegin (GL_LINE_STRIP); 
       glVertex2i (0,100);
	   glVertex2i (400, 500);
   glEnd ( );
  // glDisable (GL_LINE_STIPPLE);

    glColor3f (0.5, 0.0, 1.0);  
	//	   glLineWidth (6.0);
       glBegin (GL_LINES); // reprezinta o reuniune de segmente
       glVertex2i (400,400);
	   glVertex2i (600, 500);
	   glVertex2i (700, 520);
	   glVertex2i (655, 690);
   glEnd ( );

 
   glFlush ( ); // proceseaza procedurile OpenGL cat mai rapid
}

void RenderFunction(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  myMatrix=resizeMatrix;
 
  myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  &myMatrix[0][0]);
  // desenare puncte din colturi si axe
  glPointSize(1.0);
  codCol=0;

  CreateVBOPoints();
  CreateVBOLines1();
  CreateVBOLines2();

  // codCol=2;
  // glUniform1i(codColLocation, codCol);
  // glDrawArrays(GL_LINES, 1, nrOfPoints * 2);

  glutPostRedisplay();
  glutSwapBuffers();
  glFlush ( );
}
void Cleanup(void)
{
  DestroyShaders();
  DestroyVBO();
}

int main(int argc, char* argv[])
{
//initLines();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
  glutInitWindowPosition (100,100); 
  glutInitWindowSize(width,height); 
  glutCreateWindow("Utilizarea glm pentru transformari"); 
  glewInit(); 
  Initialize( );
  glutDisplayFunc(RenderFunction);
  glutCloseFunc(Cleanup);
  glutMainLoop();
  
  return 0;
}

/*
int main (int argc, char** argv)
{
	glutInit (&argc, argv); // initializare GLUT
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition (100, 100); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize (1200, 700); // dimensiunile ferestrei 
	glutCreateWindow ("Puncte & Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara

	init (); // executa procedura de initializare
	glClear (GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
	glutDisplayFunc (desen); // procedura desen este invocata ori de cate ori este nevoie
	glutMainLoop ( ); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
	return 0;
}*/
