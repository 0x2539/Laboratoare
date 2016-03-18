 
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
    x = -99999;
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
  bool equals(myPoint point)
  {
    if(getX() == point.getX() && getY() == point.getY())
    {
      return true;
    }
    return false;
  }
  int getX()
  {
    return (int) x;
  }
  int getY()
  {
    return (int) y;
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
  myPoint getPoint1()
  {
    return point1;
  }
  myPoint getPoint2()
  {
    return point2;
  }

  bool isPoint() {
    if(point1.getX() == point2.getX() && point1.getY() == point2.getY()) {
      return true;
    }
    return false;
  }

  void printString()
  {
    if(point1.getX() != -99999){
      cout<<point1.getX()<<' '<<point1.getY()<<" | "<<point2.getX()<<' '<<point2.getY()<<'\n';
    }
  }
};

// Returns a position of the point c relative to the line going through a and b
//         Points a, b are expected to be different
int side(myPoint a, myPoint b, myPoint c) {
    int d = (c.getY()-a.getY())*(b.getX()-a.getX()) - (b.getY()-a.getY())*(c.getX()-a.getX());
    if(d > 0) {
      return 1;
    }
    else if(d < 0) {
      return -1;
    }
    else return 0;
}

// Returns True if c is inside closed segment, False otherwise.
//         a, b, c are expected to be collinear
bool is_point_in_closed_segment(myPoint a, myPoint b, myPoint c){
    if (a.getX() < b.getX()) {
        return a.getX() <= c.getX() && c.getX() <= b.getX();
    }
    if (b.getX() < a.getX()) {
        return b.getX() <= c.getX() && c.getX() <= a.getX();
    }

    if (a.getY() < b.getY()) {
        return a.getY() <= c.getY() && c.getY() <= b.getY();
      }
    if (b.getY() < a.getY()) {
        return b.getY() <= c.getY() && c.getY() <= a.getY();
      }

    return a.getX() == c.getX() && a.getY() == c.getY();
}

myPoint checkLineIntersection(myLine myLine1, myLine myLine2) {
  int line1StartX = myLine1.getPoint1().getX(), 
  line1StartY = myLine1.getPoint1().getY(), 
  line1EndX = myLine1.getPoint2().getX(), 
  line1EndY = myLine1.getPoint2().getY(), 
  line2StartX = myLine2.getPoint1().getX(), 
  line2StartY = myLine2.getPoint1().getY(), 
  line2EndX = myLine2.getPoint2().getX(), 
  line2EndY = myLine2.getPoint2().getY();
  // if the lines intersect, the result contains the x and y of the intersection (treating the lines as infinite) and booleans for whether line segment 1 or line segment 2 contain the point
  float denominator, a, b, numerator1, numerator2, x, y;
  myPoint result;

    denominator = ((line2EndY - line2StartY) * (line1EndX - line1StartX)) - ((line2EndX - line2StartX) * (line1EndY - line1StartY));
    if (denominator == 0) {
        return result;
    }
    a = line1StartY - line2StartY;
    b = line1StartX - line2StartX;
    numerator1 = ((line2EndX - line2StartX) * a) - ((line2EndY - line2StartY) * b);
    numerator2 = ((line1EndX - line1StartX) * a) - ((line1EndY - line1StartY) * b);
    a = numerator1 / denominator;
    b = numerator2 / denominator;

    // if we cast these lines infinitely in both directions, they intersect here:
    x = line1StartX + (a * (line1EndX - line1StartX));
    y = line1StartY + (a * (line1EndY - line1StartY));
    result = myPoint(x, y);
/*
        // it is worth noting that this should be the same as:
        x = line2StartX + (b * (line2EndX - line2StartX));
        y = line2StartX + (b * (line2EndY - line2StartY));
        */
    // // if line1 is a segment and line2 is infinite, they intersect if:
    // if (a > 0 && a < 1) {
    //     result.onLine1 = true;
    // }
    // // if line2 is a segment and line1 is infinite, they intersect if:
    // if (b > 0 && b < 1) {
    //     result.onLine2 = true;
    // }
    // if line1 and line2 are segments, they intersect if both of the above are true
    if (a > 0 && a < 1 && b > 0 && b < 1) {
      return result;
    }
    return myPoint();
}

myLine getMutualLine(int s1, int s2, myPoint a, myPoint b, myPoint c, myPoint d)
{
  if (s1 == 0 || s2 == 0) {
    myPoint points[4];
    int index = 0;

    if(is_point_in_closed_segment(a, b, c))
    {
      points[index++] = c;
    }
    if(is_point_in_closed_segment(a, b, d))
    {
      points[index++] = d;
    }
    if(is_point_in_closed_segment(c, d, a))
    {
      points[index++] = a;
    }
    if(is_point_in_closed_segment(c, d, b))
    {
      points[index++] = b;
    }
    // // if c-d is inside a-b
    // if (is_point_in_closed_segment(a, b, c) && 
    //       is_point_in_closed_segment(a, b, d)) {
    //   myLine = myLine(c, d);
    // }
    // else
    //   //if a-b is inside c-d
    //   if (is_point_in_closed_segment(c, d, a) && 
    //         is_point_in_closed_segment(c, d, b)) {
    //     myLine = myLine(a, b);
    //   }
    //   else
    //   {
    //     myPoint insidePoint;
    //     // if only c is inside a-b
    //     if (is_point_in_closed_segment(a, b, c) {
    //       insidePoint = c;
    //     }
    //     else
    //       // if only d is inside a-b
    //       if (is_point_in_closed_segment(a, b, d) {
    //         insidePoint = d;
    //       }
    //     //check if a is between c-d
    //     if (is_point_in_closed_segment(c, d, a) {
    //       myLine = myLine(insidePoint, a);
    //     }
    //     else
    //       //check if b is between c-d
    //       if (is_point_in_closed_segment(c, d, b) {
    //         myLine = myLine(insidePoint, b);
    //       }
    //   }

    //if there is a common segment
    if(index == 2) {
      return myLine(points[0], points[1]);
    }
    else
      //if there is only one point on the other segment
      if(index == 1) {
        return myLine(points[0], points[0]);
      }
  }  
  return myLine();
}

// Verifies if closed segments a, b, c, d do intersect.
myLine closed_segment_intersect(myPoint a, myPoint b, myPoint c, myPoint d) {
    if (a.equals(b)) {
      if(a.equals(c) || a.equals(d)) {
        return myLine(a, a);
      }
      return myLine();
    }
    if (c.equals(d)) {  
      if(c.equals(a) || c.equals(b)) {
        return myLine(c, c);
      }
      return myLine();
    }

    int s1 = side(a,b,c);
    int s2 = side(a,b,d);

    // Some (maybe all) points are collinear
    if (s1 == 0 || s2 == 0) {
      return getMutualLine(s1, s2, a, b, c, d);
    }

    // No touching and on the same side
    if (s1 && s1 == s2) {
        return myLine();
      }

    s1 = side(c,d,a);
    s2 = side(c,d,b);

    // Some (maybe all) points are collinear
    if (s1 == 0 || s2 == 0) {
      return getMutualLine(s1, s2, a, b, c, d);
    }

    // No touching and on the same side
    if (s1 && s1 == s2) {
        return myLine();
      }

    myPoint intersectionPoint = checkLineIntersection(myLine(a, b), myLine(c, d));
    return myLine(intersectionPoint, intersectionPoint);
}

int nrOfPoints = 8;
//varfurile
// myPoint myPoints[] = {
//   // cele 4 varfuri din colturi 
//   myPoint(-390.0f, -290.0f),
//    myPoint(390.0f,  -290.0f),
//    myPoint(390.0f, 290.0f),
//  myPoint(-390.0f, 290.0f),
//  // varfuri pentru axe
//   myPoint(-400.0f, 0.0f),
//     myPoint(400.0f,  0.0f),
//     myPoint(0.0f, -300.0f),
//   myPoint(0.0f, 300.0f),
//   // varfuri pentru dreptunghi
//  //   myPoint(-50.0f,  -50.0f, 0.0f, 1.0f),
//  //   myPoint(50.0f, -50.0f, 0.0f, 1.0f),
//  // myPoint(50.0f,  50.0f, 0.0f, 1.0f),
//  // myPoint(-50.0f,  50.0f, 0.0f, 1.0f),
// };
myPoint myPoints[] = {
  myPoint(0.0f, 0.0f),
  myPoint(300.0f, 0.0f),
  myPoint(300.0f, 300.0f),
  myPoint(150.0f, 300.0f),
  myPoint(150.0f, 0.0f),
  myPoint(450.0f, 0.0f),
  myPoint(0.0f, 150.0f),
  myPoint(150.0f, 300.0f),
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
 
    // matrTransl=glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0));
  resizeMatrix= glm::scale(glm::mat4(1.0f), glm::vec3(1.f/width, 1.f/height, 1.0));
  matrTransl=glm::translate<GLfloat>(glm::vec3(0, 0, 0.0f));
  myMatrix=resizeMatrix*matrTransl;
  
  myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  glm::value_ptr(myMatrix));

  glUniform1i(codColLocation, 0);
  glDrawArrays(GL_POINTS, 0, nrOfPoints); 
}
void CreateVBOLines(void)
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
  
  glUniform1i(codColLocation, 0);
  glDrawArrays(GL_LINE_LOOP, 0, nrOfPoints);
 }

void CreateVBOIntersectionPoints(myPoint myPointss[], int sizee)
{
  // se creeaza un buffer nou
  glGenBuffers(1, &VboId);
  // este setat ca buffer curent
  glBindBuffer(GL_ARRAY_BUFFER, VboId);
  // punctele sunt "copiate" in bufferul curent
  glBufferData(GL_ARRAY_BUFFER, sizeof(myPoint) * sizee, myPointss, GL_STATIC_DRAW);
  
  // se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
  glGenVertexArrays(1, &VaoId);
  glBindVertexArray(VaoId);
  // se activeaza lucrul cu atribute; atributul 0 = pozitie
  glEnableVertexAttribArray(0);
  // 
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);  
 
    // matrTransl=glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0));
  resizeMatrix= glm::scale(glm::mat4(1.0f), glm::vec3(1.f/width, 1.f/height, 1.0));
  matrTransl=glm::translate<GLfloat>(glm::vec3(0, 0, 0.0f));
  myMatrix=resizeMatrix*matrTransl;
  
  myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  glm::value_ptr(myMatrix));

  glUniform1i(codColLocation, 1);
  glDrawArrays(GL_POINTS, 0, sizee); 
}

void CreateVBOIntersectionLines(myLine myLines[], int size)
{
  // se creeaza un buffer nou
  glGenBuffers(1, &VboId);
  // este setat ca buffer curent
  glBindBuffer(GL_ARRAY_BUFFER, VboId);
  // punctele sunt "copiate" in bufferul curent
  glBufferData(GL_ARRAY_BUFFER, sizeof(myLine) * size, myLines, GL_STATIC_DRAW);
  
  // se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
  glGenVertexArrays(1, &VaoId);
  glBindVertexArray(VaoId);
  // se activeaza lucrul cu atribute; atributul 0 = pozitie
  glEnableVertexAttribArray(0);
  // 
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    // matrTransl=glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0));
  resizeMatrix= glm::scale(glm::mat4(1.0f), glm::vec3(1.f/width, 1.f/height, 1.0));
  matrTransl=glm::translate<GLfloat>(glm::vec3(0, 0, 0.0f));
  myMatrix=resizeMatrix*matrTransl;
  
  myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  glm::value_ptr(myMatrix));
  
// cout<<"sizeL "<<size<<'\n';
  glUniform1i(codColLocation, 1);
  glDrawArrays(GL_LINES, 0, size);
}

void CreateVBOIntersection() {
  myPoint myPointss[100];
  int index1=0;
  myLine myLiness[100];
  int index2=0;

  for(int i = 0; i < nrOfPoints; i++) {
    for(int j = i + 2; j < nrOfPoints + 2; j++) {

      myLine myLineTemp = closed_segment_intersect(
              myLines[i].getPoint1(), myLines[i].getPoint2(), 
              myLines[j%nrOfPoints].getPoint1(), myLines[j%nrOfPoints].getPoint2()
            );
      if(myLineTemp.getPoint1().getX() != -99999 &&
          myLineTemp.getPoint2().getX() != -99999) {

        if(myLineTemp.isPoint()) {
          myPointss[index1++] = myLineTemp.getPoint1();
        }
        else{
          myLiness[index2++] = myLineTemp;
          myPointss[index1++] = myLineTemp.getPoint1();
          myPointss[index1++] = myLineTemp.getPoint2();
        }
        // cout<<"yolo "<<index1<<" "<<index2<<'\n';
      }
    }
  }
  cout<<index1<<' '<< index2<<'\n';
  CreateVBOIntersectionPoints(myPointss, index1);
  CreateVBOIntersectionLines(myLiness, index2);
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
 
  // myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
  // matrTransl=glm::translate<GLfloat>(glm::vec3(0.0f, 0.0f, 0.0f));
  // myMatrix=resizeMatrix*matrTransl;
  //   glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  glm::value_ptr(myMatrix));
  // desenare puncte din colturi si axe
  glPointSize(10.0);
  codCol=0;

  CreateVBO();
  CreateVBOLines();
  CreateVBOIntersection();

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
  glutInitWindowPosition (400,100); 
  glutInitWindowSize(width,height); 
  glutCreateWindow("Utilizarea glm pentru transformari"); 
  glewInit(); 
  Initialize( );
  glutDisplayFunc(RenderFunction);
  glutCloseFunc(Cleanup);
  glutMainLoop();
  
  
}

