
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h

#include "myHeader.h"

#include "glm/glm/glm.hpp"  
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtx/transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include "SOIL.h"

using namespace std;

//////////////////////////////////////
// identificatori 
GLuint
VaoId,
VboId,
ColorBufferId,
ProgramId,
myMatrixLocation,
viewLocation,
projLocation,
matrRotlLocation,
codColLocation,
depthLocation;

GLuint texture;

int codCol;
float PI=3.141592;

// matrice utilizate
glm::mat4 myMatrix, matrRot; 

// elemente pentru matricea de vizualizare
float Obsx=0.0, Obsy=0.0, Obsz=-2400.f;
float Refx=0.0f, Refy=0.0f;
float Vx=0.0;
float Vy=1.0;
float Vz=0.0;
glm::mat4 view;

// elemente pentru matricea de proiectie
float width=800, height=600, xwmin=-800.f, xwmax=800, ywmin=-600, ywmax=600, znear=1, zfar=-1, fov=45;
glm::mat4 projection;

float angle = 0; 
float angleZ = 0; 
float colors[] = {0.5, 0.7, 1.0};
int positions[] = {50, 350, 650};
int centerPositions[] = {0, 2, 0};

class SolidSphere
{
public:
  std::vector<GLfloat> sphere_vertices;
  std::vector<GLfloat> sphere_normals;
  std::vector<GLfloat> sphere_texcoords;
  std::vector<GLushort> sphere_indices;

  GLfloat Vertices[];

  SolidSphere(float radius, unsigned int rings, unsigned int sectors)
  {
    float const R = 1./(float)(rings-1);
    float const S = 1./(float)(sectors-1);
    int r, s;

    sphere_vertices.resize(rings * sectors * 6);
    sphere_normals.resize(rings * sectors * 3);
    sphere_texcoords.resize(rings * sectors * 2);
    std::vector<GLfloat>::iterator v = sphere_vertices.begin();
    std::vector<GLfloat>::iterator n = sphere_normals.begin();
    std::vector<GLfloat>::iterator t = sphere_texcoords.begin();
    for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
      float const y = sin( -M_PI_2 + M_PI * r * R );
      float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
      float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );

      *t++ = s*S;
      *t++ = r*R;

      *v++ = x * radius;
      *v++ = y * radius;
      *v++ = z * radius;

      *v++ = x;
      *v++ = y;
      *v++ = z;
    }

    sphere_indices.resize(rings * sectors * 4);
    std:vector<GLushort>::iterator i = sphere_indices.begin();
    for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
      *i++ = r * sectors + s;
      *i++ = r * sectors + (s+1);
      *i++ = (r+1) * sectors + (s+1);
      *i++ = (r+1) * sectors + s;
    }
    cout<<sphere_vertices.size()<<'\n';
    for(int w = 0; w < sphere_vertices.size(); w++)
    {
      cout<<(&sphere_vertices[0])[w]<<' ';
      if(w % 6 == 0)
      {
        cout<<'\n';
      }
    }
        cout<<'\n';
  }
};

void displayMatrix ( )
{
	// for (int ii = 0; ii < 4; ii++)
	// {
	// 	for (int jj = 0; jj < 4; jj++)
	// 	cout <<  myMatrix[ii][jj] << "  " ;
	// 	cout << endl;
	// };

};

void processNormalKeys(unsigned char key, int x, int y)
{

	switch (key) {
		case 'w' :
   angleZ += 0.1;
   break;
   case 's' :
   angleZ -= 0.1;
   break;
   case 'a' :
   angle += 0.1;
   break;
   case 'd' :
   angle -= 0.1;
   break;
   case '+' :
   Obsz += 10.1;
			//znear += 10;
			//zfar += 10;
			//Obsz+=10;
   break;
   case '-' :
   Obsz -= 10.1;
			//znear -= 10;
			//zfar -= 10;
			//Obsz-=10;
   break;

 }
 if (key == 27)
  exit(0);
}
void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {
		case GLUT_KEY_LEFT :
   Obsx+=20;
   break;
   case GLUT_KEY_RIGHT :
   Obsx-=20;
   break;
   case GLUT_KEY_UP :
   Obsy+=20;
   break;
   case GLUT_KEY_DOWN :
   Obsy-=20;
   break;
 }
}

SolidSphere *solidSphere = new SolidSphere(200, 10, 10);
void CreateVBO(int pos)
{
  // varfurile 
  GLfloat Vertices[] = {

   -pos, -pos, -pos,  0.0f,  0.0f, -1.0f,
   pos, -pos, -pos,  0.0f,  0.0f, -1.0f,
   pos,  pos, -pos,  0.0f,  0.0f, -1.0f,
   pos,  pos, -pos,  0.0f,  0.0f, -1.0f,
   -pos,  pos, -pos,  0.0f,  0.0f, -1.0f,
   -pos, -pos, -pos,  0.0f,  0.0f, -1.0f,

   -pos, -pos,  pos,  0.0f,  0.0f,  1.0f,
   pos, -pos,  pos,  0.0f,  0.0f,  1.0f,
   pos,  pos,  pos,  0.0f,  0.0f,  1.0f,
   pos,  pos,  pos,  0.0f,  0.0f,  1.0f,
   -pos,  pos,  pos,  0.0f,  0.0f,  1.0f,
   -pos, -pos,  pos,  0.0f,  0.0f,  1.0f,

   -pos,  pos,  pos, -1.0f,  0.0f,  0.0f,
   -pos,  pos, -pos, -1.0f,  0.0f,  0.0f,
   -pos, -pos, -pos, -1.0f,  0.0f,  0.0f,
   -pos, -pos, -pos, -1.0f,  0.0f,  0.0f,
   -pos, -pos,  pos, -1.0f,  0.0f,  0.0f,
   -pos,  pos,  pos, -1.0f,  0.0f,  0.0f,

   pos,  pos,  pos,  1.0f,  0.0f,  0.0f,
   pos,  pos, -pos,  1.0f,  0.0f,  0.0f,
   pos, -pos, -pos,  1.0f,  0.0f,  0.0f,
   pos, -pos, -pos,  1.0f,  0.0f,  0.0f,
   pos, -pos,  pos,  1.0f,  0.0f,  0.0f,
   pos,  pos,  pos,  1.0f,  0.0f,  0.0f,

   -pos, -pos, -pos,  0.0f, -1.0f,  0.0f,
   pos, -pos, -pos,  0.0f, -1.0f,  0.0f,
   pos, -pos,  pos,  0.0f, -1.0f,  0.0f,
   pos, -pos,  pos,  0.0f, -1.0f,  0.0f,
   -pos, -pos,  pos,  0.0f, -1.0f,  0.0f,
   -pos, -pos, -pos,  0.0f, -1.0f,  0.0f,

   -pos,  pos, -pos,  0.0f,  1.0f,  0.0f,
   pos,  pos, -pos,  0.0f,  1.0f,  0.0f,
   pos,  pos,  pos,  0.0f,  1.0f,  0.0f,
   pos,  pos,  pos,  0.0f,  1.0f,  0.0f,
   -pos,  pos,  pos,  0.0f,  1.0f,  0.0f,
   -pos,  pos, -pos,  0.0f,  1.0f,  0.0f
 };
 
  // se creeaza un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
 glGenVertexArrays(1, &VaoId);
  // se creeaza un buffer nou (atribute)
 glGenBuffers(1, &VboId);
 

  // legarea VAO 
 glBindVertexArray(VaoId);

  // legarea buffer-ului "Array"
 glBindBuffer(GL_ARRAY_BUFFER, VboId);
  // punctele sunt "copiate" in bufferul curent
 glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
 // glBufferData(GL_ARRAY_BUFFER, sizeof(&solidSphere->sphere_vertices[0]), &solidSphere->sphere_vertices[0], GL_STATIC_DRAW);


  // se activeaza lucrul cu atribute; atributul 0 = pozitie
 glEnableVertexAttribArray(0);
 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),(GLvoid*)0);
 // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, solidSphere->sphere_vertices.size() / 6 * sizeof(GLfloat),(GLvoid*)0);

  // se activeaza lucrul cu atribute; atributul 1 = normale
 glEnableVertexAttribArray(1);
 glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),(GLvoid*)(3 * sizeof(GLfloat)));
 // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, solidSphere->sphere_vertices.size() / 6 * sizeof(GLfloat),(GLvoid*)(3 * sizeof(GLfloat)));
 
}
void DestroyVBO(void)
{
 glDisableVertexAttribArray(1);
 glDisableVertexAttribArray(0);

 glBindBuffer(GL_ARRAY_BUFFER, 0);
 
 glDeleteBuffers(1, &VboId);
 

 glBindVertexArray(0);
 glDeleteVertexArrays(1, &VaoId);

}

void LoadTexture(void)
{
	
	glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  int width, height;
  unsigned char* image = SOIL_load_image("smiley_face.png", &width, &height, 0, SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);

  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D, 0);

} 
void CreateShaders(void)
{
  ProgramId=LoadShaders("src/12_03_Shader.vert", "src/12_03_Shader.frag");
  glUseProgram(ProgramId);
}

void DestroyShaders(void)
{
  glDeleteProgram(ProgramId);
}

void Initialize(void)
{

  myMatrix = glm::mat4(1.0f);

  matrRot=glm::rotate(glm::mat4(1.0f), PI/8, glm::vec3(0.0, 0.0, 1.0));
  
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // culoarea de fond a ecranului

    CreateShaders();

  }
  float length = 0.0f;
  void render(int index, int color1, int color2, int color3)
  {

   // se schimba pozitia observatorului
    glm::vec3 Obs = glm::vec3 (Obsx, Obsy, Obsz); 

  // pozitia punctului de referinta
    Refx=Obsx; Refy=Obsy;
    glm::vec3 PctRef = glm::vec3(Refx, Refy, -Obsz); 

  // verticala din planul de vizualizare 

    glm::vec3 Vert =  glm::vec3(0.0f, 1.0f, 0.0f);


    view = glm::lookAt(Obs, PctRef, Vert);
// angle += 0.1f;

    displayMatrix();

//    projection = glm::ortho(xwmin, xwmax, ywmin, ywmax, znear, zfar);
 //  projection = glm::frustum(xwmin, xwmax, ywmin, ywmax, 80.f, -80.f);
    projection = glm::perspective(fov, GLfloat(width)/GLfloat(height), znear, zfar);
    myMatrix = glm::mat4(1.0f);
    myMatrix=glm::rotate(myMatrix, angle, glm::vec3(0.0, 1.0, 0.0));
    myMatrix=glm::rotate(myMatrix, angleZ, glm::vec3(1.0, 0.0, 0.0));
    myMatrix=glm::translate(myMatrix, glm::vec3(positions[index], 0.0, 0.0));

    myMatrix=glm::rotate(myMatrix, length, glm::vec3(0.0, 1.0, 0.0));

    // myMatrix=glm::translate(myMatrix, glm::vec3(positions[centerPositions[index]], 0.0, 0.0));
    // myMatrix=glm::rotate(myMatrix, length, glm::vec3(0.0, 1.0, 0.0));
    //myMatrix=glm::translate(myMatrix, glm::vec3(centerPos, 0.0, 0.0));

    CreateVBO(50);


  //myMatrix= matrRot;
    LoadTexture();

 // variabile uniforme pentru shaderul de varfuri
    myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
    glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  &myMatrix[0][0]);
    viewLocation = glGetUniformLocation(ProgramId, "view");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE,  &view[0][0]);
    projLocation = glGetUniformLocation(ProgramId, "projection");
    glUniformMatrix4fv(projLocation, 1, GL_FALSE,  &projection[0][0]);

  // Variabile unforme pentru iluminare

    GLint objectColorLoc = glGetUniformLocation(ProgramId, "objectColor");
    GLint lightColorLoc  = glGetUniformLocation(ProgramId, "lightColor");
    GLint lightPosLoc    = glGetUniformLocation(ProgramId, "lightPos");
    GLint viewPosLoc     = glGetUniformLocation(ProgramId, "viewPos");
    glUniform3f(objectColorLoc, color1, color2, color3);
    glUniform3f(lightColorLoc,  1.0f, 1.0f, 1.0f);
    glUniform3f(lightPosLoc,    50.f, 0.f, -0.f);
    glUniform3f(viewPosLoc,   Obsx, Obsy, Obsz);

    int nrpoints = 6;
    glDrawArrays(GL_TRIANGLES, 0, nrpoints * 6);
    // glDrawArrays(GL_TRIANGLES, 0, solidSphere->sphere_vertices.size());

  }
  void RenderFunction(void)
  {

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   length += 0.1f;
   render(0, 1.0f, 0.0f, 0.0f);    
   render(2, 0.0f, 0.0f, 1.0f);
   render(1, 0.0f, 1.0f, 0.0f);

  // Eliberare memorie si realocare resurse
   DestroyVBO ( );
   DestroyShaders ( );
  // 
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
  glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowPosition (100,100); 
  glutInitWindowSize(1200,900); 
  glutCreateWindow("Desenarea unui cub"); 
  glewInit(); 
  Initialize( );
  glutIdleFunc(RenderFunction);
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(processSpecialKeys);
  glutCloseFunc(Cleanup);
  glutMainLoop();

}


