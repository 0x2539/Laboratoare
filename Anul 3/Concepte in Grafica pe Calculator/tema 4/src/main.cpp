 
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

float currentTime;

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

class CelestialObject {
private:
  float x, y, radius, speed;
  int index;
  CelestialObject *satellite;
  CelestialObject *gravityPoint;
  int num_segments = 10;
  myPoint myPoints[10];
  myPoint myPointsOrbit[20];
  void initPoints()
  {
    for(int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle

        GLfloat x = radius * cosf(theta);//calculate the x component
        GLfloat y = radius * sinf(theta);//calculate the y component

        myPoints[i] = myPoint(x, y);//output vertex
    }

    if(satellite != NULL) {
      for(int i = 0; i < num_segments * 2; i++)
      {
          float theta = 2.0f * 3.1415926f * float(i) / float(num_segments * 2);//get the current angle

          GLfloat x = (radius * (index)) * cosf(theta);//calculate the x component
          GLfloat y = (radius * (index)) * sinf(theta);//calculate the y component

          myPointsOrbit[i] = myPoint(x, y);//output vertex
      }
    }
  }
public:
  CelestialObject()
  {
    x = 0;
    y = 0;
  }
  CelestialObject(int index, float radius, float speed)
  {
    this->index = index;
    this->radius = radius;
    this->speed = speed;
    this->satellite = new CelestialObject();
    this->satellite->gravityPoint = this;
    initPoints();
  }
  CelestialObject(int index, float radius, float speed, CelestialObject *satellite)
  {
    this->index = index;
    this->radius = radius;
    this->speed = speed;
    this->satellite = satellite;
    this->satellite->gravityPoint = this;
    initPoints();
  }

  float getX()
  {
    return x;
  }

  float getY()
  {
    return y;
  }

  void update()
  {
    int distance = radius * index;
    x = cos(currentTime * speed) * distance + satellite->x;
    y = sin(currentTime * speed) * distance + satellite->y;
  }

  void draw()
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

    // matrTransl=glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0));
    matrTransl=glm::translate<GLfloat>(glm::vec3(x, y, 0.0f));
    matrRot=glm::rotate(glm::mat4(1.0f), currentTime * 4 * (index+1), glm::vec3(0.0, 0.0, 1.0));
    myMatrix=resizeMatrix*matrTransl*matrRot;
    
    myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
    glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  glm::value_ptr(myMatrix));

    glUniform1i(codColLocation, index);
    glDrawArrays(GL_TRIANGLE_FAN, 0, num_segments);    

    drawOrbit();
  }
  void drawOrbit()
  {
    // se creeaza un buffer nou
    glGenBuffers(1, &VboId);
    // este setat ca buffer curent
    glBindBuffer(GL_ARRAY_BUFFER, VboId);
    // punctele sunt "copiate" in bufferul curent
    glBufferData(GL_ARRAY_BUFFER, sizeof(myPointsOrbit), myPointsOrbit, GL_STATIC_DRAW);
    
    // se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);
    // se activeaza lucrul cu atribute; atributul 0 = pozitie
    glEnableVertexAttribArray(0);
    // 
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);  

    // matrTransl=glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0));
    matrTransl=glm::translate<GLfloat>(glm::vec3(satellite->x, satellite->y, 0.0f));
    myMatrix=resizeMatrix*matrTransl;
    
    myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
    glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  glm::value_ptr(myMatrix));

    glUniform1i(codColLocation, index);
    glDrawArrays(GL_LINE_LOOP, 0, num_segments * 2);    
  }
};

class CelestialObjectItem {
private:
  float x, y, speed;
  int index;
  float radius;
  CelestialObject *celestialObject;
  int num_segments = 10;
  myPoint myPoints[10];
  void initPoints()
  {
    for(int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle

        GLfloat x = radius * cosf(theta);//calculate the x component
        GLfloat y = radius * sinf(theta);//calculate the y component

        myPoints[i] = myPoint(x, y);//output vertex
    }
  }
public:
  CelestialObjectItem()
  {
    x = 0;
    y = 0;
  }
  CelestialObjectItem(int index, float radius, float speed)
  {
    this->index = index;
    this->radius = radius;
    this->speed = speed;
    this->celestialObject = new CelestialObject();
    initPoints();
  }
  CelestialObjectItem(int index, float radius, float speed, CelestialObject *celestialObject)
  {
    this->index = index;
    this->radius = radius;
    this->speed = speed;
    this->celestialObject = celestialObject;
    initPoints();
  }

  float lastRadius = 0;
  float lastSinRadius = 0;
  void update()
  {
    int speed = 20;
    float sinRadius = sin(currentTime * speed) > 0 ? sin(currentTime * speed) : sin(currentTime * speed) * -1;
    if(index == 1) {
      radius = sinRadius;
    }
    else{
      radius = 1-sinRadius;// cos(currentTime * speed) > 0 ? cos(currentTime * speed) : cos(currentTime * speed) * -1; 
    }
    if(lastSinRadius > sinRadius && sinRadius > 0.0f)
    {
      if(index == 1) {
        radius = 1;
      }
    }
    else
    if(lastSinRadius < sinRadius && sinRadius < 1.0f)
    {
      if(index == 0) {
        radius = 0;
      }
    }
    lastRadius = radius;
    lastSinRadius = sinRadius;
    x = celestialObject->getX() + 30;
    y = celestialObject->getY() + 30;
    //int distance = radius * index;
    //x = cos(currentTime * speed) * distance + celestialObject->x;
    //y = sin(currentTime * speed) * distance + celestialObject->y;
  }

  void draw()
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

    // matrTransl=glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0));
    matrTransl=glm::translate<GLfloat>(glm::vec3(x, y, 0.0f));
    matrRot=glm::rotate(glm::mat4(1.0f), currentTime * 4 * (index+1), glm::vec3(0.0, 0.0, 1.0));
    resizeMatrix= glm::scale(glm::mat4(1.0), glm::vec3(radius/width, radius/height, 1.0));
    myMatrix=resizeMatrix*matrTransl*matrRot;
    resizeMatrix= glm::scale(glm::mat4(1.0f), glm::vec3(1.f/width, 1.f/height, 1.0));
    
    myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
    glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  glm::value_ptr(myMatrix));

    if(sin(currentTime * speed) > 0) {
      glUniform1i(codColLocation, index);
    }
    else{
      glUniform1i(codColLocation, 1); 
    }
    glDrawArrays(GL_TRIANGLE_FAN, 0, num_segments);
  }
};

CelestialObject *star = new CelestialObject(0, 150, 0.5f);
CelestialObject *planet = new CelestialObject(5, 100, 1, star);
CelestialObject *satellite = new CelestialObject(4, 50, 4, planet);

CelestialObjectItem *starSpot = new CelestialObjectItem(1, 50, 0.5f, star);
CelestialObjectItem *starSpot2 = new CelestialObjectItem(0, 50, 0.5f, star);

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

  CreateShaders(); 

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // culoarea de fond a ecranului
}
void RenderFunction(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  currentTime += 0.0001f;
  satellite->update();
  satellite->draw();
  planet->update();
  planet->draw();
  star->update();
  star->draw();
  starSpot->update();
  starSpot->draw();
  starSpot2->update();
  starSpot2->draw();
  // myMatrix=resizeMatrix;
 
  // myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
  // glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  &myMatrix[0][0]);
  // // desenare puncte din colturi si axe
  // glPointSize(10.0);
  // codCol=0;

  // CreateVBO();
  // glUniform1i(codColLocation, codCol);
  // glDrawArrays(GL_POINTS, 0, nrOfPoints);
  
  // CreateVBO2();
  // glDrawArrays(GL_LINES, 0, nrOfPoints * 2);

  // // codCol=2;
  // // glUniform1i(codColLocation, codCol);
  // // glDrawArrays(GL_LINES, 1, nrOfPoints * 2);

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

