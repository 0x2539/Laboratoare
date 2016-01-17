#include "GL/glew.h"
#include "GL/glut.h" //GL Utility Library. Manages opening windows and runs the main loop
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-pedantic"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#pragma GCC diagnostic pop

using glm::mat4;
using glm::vec3;
using glm::rotate;
using glm::translate;
using glm::scale;
using glm::perspective;
using glm::lookAt;
using glm::value_ptr; //conversion of matrices to format that shaders expect

/*CONSTANTS*/

const int KEY_ESCAPE = 27;

/**Squares on chessboard. */
const GLuint FACES = 4096;
/** Number of triangles per square */
const GLuint TRIANGLES_PER_FACE = 2;
/** Number of vertices in a triangle. */
const GLuint VERTICES_PER_TRIANGLE = 3;
/** Number of indices used for drawing a cube. */
const GLuint INDICES= FACES * TRIANGLES_PER_FACE * 
   VERTICES_PER_TRIANGLE; //384
/** The size of the index array. */
const GLuint INDEX_ARRAY_SIZE = INDICES;

/** Number of dimensions used. */
const GLuint DIMENSIONS = 3;
/** The amount of components in our colour vectors.(RGB). */
const GLuint COLOUR_COMPONENT_COUNT = 3;
/** The size of an individual vertex. */
const GLuint VERTEX_SIZE = DIMENSIONS + COLOUR_COMPONENT_COUNT;
/** The amount of vertices in a chessboard. */
const GLuint VERTEX_COUNT = 16384;
/** The size of the vertex array. */
const GLuint VERTEX_ARRAY_SIZE = VERTEX_COUNT * VERTEX_SIZE;

/** The window's initial width. */
const int WINDOW_WIDTH = 600;
/** The window's initial height. */
const int WINDOW_HEIGHT = 600;

/** Amount to rotate by for one rotation step. */
const GLfloat ANGLE_DELTA = 15.0f;
/** Amount to move / scale by for each step. */
const GLfloat SCALE = 0.1f;

/*VARIABLES*/

bool active_keys[256];

int last_frame;

int TARGET_DELTA_T = 1/60 * 1000; //converted to milliseconds

int MILLISECONDS_PER_SECOND = 1000;

int last_print;

bool birdsEye = false;

//SCALE MATRIX VARIABLES

/*
 * Scale the x axis by:
 */
GLfloat xScale = 1.0f;
/*
 * Scale the y axis by:
 */
GLfloat yScale = 1.0f;
/*
 * Scale the x axis by:
 */
GLfloat zScale = 1.0f;

//ROTATION MATRIX VARIABLES

/*
 * Rotation around x axiz:
 */
GLfloat xRot = 0.0f;
/*
 * Rotation around y axiz:
 */
GLfloat yRot = 0.0f;
/*
 * Rotation around z axiz:
 */
GLfloat zRot = 0.0f;

//TRANSLATION MATRIX VARIABLES

/*
 * Move on the x axis by: 
 */
GLfloat xMove = -0.5f;
/*
 * Move on the x axis by: 
 */
GLfloat yMove = -0.5f;
/*
 * Move on the x axis by: 
 */
GLfloat zMove = -0.5f;

//VIEW MATRIX VARIABLES

 /*
 * The position of the camera
 */
 vec3 cameraEye(0,2,0); 
 
 /*
 * The direction (vector) the camera is looking
 */
 vec3 cameraAt(64,1,-64);
 
 /*
 * The up direction (vector) for the camera
 */
 vec3 cameraUp(0,1,0);
 
 //PROJECTION MATRIX VARIABLES
 /* 
  * Vertical field-of-view. 
  */
GLfloat FOVY = 45.0f;

/* 
 * Near clipping plane. 
 */
GLfloat NEAR = 1.0f;

/* 
 * Far clipping plane. 
 */
GLfloat FAR = -100.0f;

/*
 * PREVIOUS VIEW MATRIX VARIABLES
 */
 
 /*
 * The position of the camera
 */
 vec3 old_cameraEye(0,2,0); 
 
 /*
 * The direction (vector) the camera is looking
 */
 vec3 old_cameraAt(64,1,-64);

/* HANDLES*/

/* 
 * Handle to the vertex shader program. 
 */
GLuint vertexShader;

/*
 *Handle to the fragment shader program. 
 */
GLuint fragmentShader;

/* 
 *Handle to the shader program. 
 */
GLuint program;

/*
 *Handle for the board (8x8)
 */
GLuint board;

/*
 *Handle for the cube
 */
GLuint cube;

/*
 *Handle for the red triangle. 
 */
GLuint redTriangle;

/*
 *Handle for the blue triangle. 
 */
GLuint blueTriangle;

/*
 *Handle for the position attribute. 
 */
GLint positionLoc;

/*
 *Handle for the colour attribute. 
 */
GLint colourLoc;

/*
 *Handle for the world matrix uniform. 
 */
GLint worldLoc;

/*
 *Handle for the view matrix uniform. 
 */
GLint viewLoc;

/*
 *Handle for the projection matrix uniform. 
 */
GLint projectionLoc;


/*METHODS*/

/**
 * GLUT display callback function.
 */
void display();

void keyboardUp(unsigned char key, int x, int y);

/**
 * GLUT keyboard callback function.
 */
void keyboard(unsigned char, int, int);



/**
 * GLUT mouse callback function.
 */
void mouse(int, int, int, int);


void mouseLook (int x, int y);

/**
 * GLUT reshape callback function.
 *
 * Called whenever the window is resized.
 * Amoung other things, redraws the scene.
 *
 * NB: The window is actually separate from what is displayed inside it. The window is just thw borders and buttons around your scene.
 * That scen is drawn on what we call a Viewport. If the window size changes, it stands to reason that the viewport has to change too.
 * Stretching the viewport would cause pixelation, so we simply redraw the scene at the new resolution.
 *
 * The reshape function will become more important later, once we have to start worrying about Aspect Ratios. 
 */
void reshape(int, int);

/**
 * Updates the current world matrix used by the shaders (Uniform 'world').
 */
void
updateWorld();

/**
 * Updates the current view matrix used by the shaders (Uniform 'view').
 */
void
updateView();

/**
 * Updates the current projection matrix used by the shaders (Uniform 'projection').
 *
 * @param width Window width.
 * @param height Window height.
 */
void
updateProjection(int width, int height);


/**
 * Returns integer value of time in milliseconds that have passed since the program started.
 */
int getTime();

/**
 * Prints the FPS
 */
void printFPS();

/**
 * GLUT idle callback function. Continuously called when there are no other events.
 */
void idle();

/*
 * Check active_keys and adjust view matrix accordingly
 */
void checkKeys(vec3, vec3);


/**
 * GLUT idle callback function. Continuously called when there are no other events.
 */
void initGLEW();

/**
 * Initialise GLEW (GL Extension Wrangler) to manage/Wrangle shader programs)
 */
void init();

/*
 * Read in file.
 */
char* loadFile(const char*);

/*
 * Load all shader programs using loadShaderProgram for each shader. Link all "object files".
 */
void loadShaderPrograms();

/*
 * Load Shader Program. Compile it!
 */
void loadShaderProgram(unsigned&, const char*, GLenum);

/*
 * Load all of the geometry meshes?
 */
void loadGeometry();

void drawBoard2();
/*
 * Load Chess Board Mesh
 */
void drawBoard();

/*
 * Load Cube Mesh?
 */
void loadCube();

/*
 * Load Red Triangle Mesh?
 */
void loadRedTriangle();

/*
 * Load Blue Triangle Mesh?
 */
void loadBlueTriangle();

/*
 * Gets location of an attribute within the shader program.
 */
GLint findAttribute(const char*);

/*
 * Gets location of a Uniform within the shader program.
 */
GLint findUniform(const char*);

/**
 * Clean up any resources we may have used
 */
void cleanUp();

