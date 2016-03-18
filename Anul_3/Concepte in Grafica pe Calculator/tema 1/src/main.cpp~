 
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

 

 
void displayMatrix ( )
{
  // for (int ii = 0; ii < 4; ii++)
  // {
    // for (int jj = 0; jj < 4; jj++)
    //cout <<  myMatrix[ii][jj] << "  " ;
    //cout << endl;
  // };
  //cout << "\n";
  
};


class myPoint {
private:
  GLfloat x, y, z1, z2;
public:
  myPoint()
  {
  }
  myPoint(GLfloat x, GLfloat y)
  {
    this->x = x;
    this->y = y;
    this->z1 = 0.0f;
    this->z2 = 1.0f;
  }

  myPoint(GLfloat x, GLfloat y, GLfloat z1, GLfloat z2)
  {
    this->x = x;
    this->y = y;
    this->z1 = z1;
    this->z2 = z2;
  }
};

class myLine {
private:
  myPoint point1, point2;
public:
  myLine()
  {

  }
  myLine(myPoint point1, myPoint point2)
  {
    this->point1 = point1;
    this->point2 = point2;
  }
};

int nrOfPoints = 8;
//varfurile
myPoint myPoints[] = {
  // cele 4 varfuri din colturi 
  myPoint(-390.0f, -290.0f),
   myPoint(390.0f,  -290.0f),
   myPoint(390.0f, 290.0f),
 myPoint(-390.0f, 290.0f),
 // varfuri pentru axe
  myPoint(-400.0f, 0.0f),
    myPoint(400.0f,  0.0f),
    myPoint(0.0f, -300.0f),
  myPoint(0.0f, 300.0f),
  // varfuri pentru dreptunghi
 //   myPoint(-50.0f,  -50.0f, 0.0f, 1.0f),
 //   myPoint(50.0f, -50.0f, 0.0f, 1.0f),
 // myPoint(50.0f,  50.0f, 0.0f, 1.0f),
 // myPoint(-50.0f,  50.0f, 0.0f, 1.0f),
};

//varfurile
myLine myLines[1000];
 
void initLines()
{
  for(int i = 0; i < nrOfPoints; i++)
  {
    myLines[i] = myLine(myPoints[i], myPoints[(i + 1) % nrOfPoints]);
  }
}

void CreateVBO(void)
{
  // se creeaza un buffer nou
  glGenBuffers(1, &VboId);
  // este setat ca buffer curent
  glBindBuffer(GL_ARRAY_BUFFER, VboId);
  // punctele sunt "copiate" in bufferul curent
  glBufferData(GL_ARRAY_BUFFER, sizeof(myPoints), myPoints, GL_STATIC_DRAW);
  
  // se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
  glGenVertexArrays(1, &VaoId);
  glBindVertexArray(VaoId);
  // se activeaza lucrul cu atribute; atributul 0 = pozitie
  glEnableVertexAttribArray(0);
  // 
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);  
  
 }
void CreateVBO2(void)
{
  // se creeaza un buffer nou
  glGenBuffers(1, &VboId);
  // este setat ca buffer curent
  glBindBuffer(GL_ARRAY_BUFFER, VboId);
  // punctele sunt "copiate" in bufferul curent
  glBufferData(GL_ARRAY_BUFFER, sizeof(myLines), myLines, GL_STATIC_DRAW);
  
  // se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
  glGenVertexArrays(1, &VaoId);
  glBindVertexArray(VaoId);
  // se activeaza lucrul cu atribute; atributul 0 = pozitie
  glEnableVertexAttribArray(0);
  // 
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
 
  
 }
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
 
void Initialize(void)
{
  myMatrix = glm::mat4(1.0f);
  
  resizeMatrix= glm::scale(glm::mat4(1.0f), glm::vec3(1.f/width, 1.f/height, 1.0));

  CreateVBO();
  CreateShaders(); 

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // culoarea de fond a ecranului
}
void RenderFunction(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  myMatrix=resizeMatrix;
 
  myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  &myMatrix[0][0]);
  // desenare puncte din colturi si axe
  glPointSize(10.0);
  codCol=0;

  CreateVBO();
  glUniform1i(codColLocation, codCol);
  glDrawArrays(GL_POINTS, 0, nrOfPoints);
  
  CreateVBO2();
  glDrawArrays(GL_LINES, 0, nrOfPoints * 2);

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
initLines();

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
  
  
}

