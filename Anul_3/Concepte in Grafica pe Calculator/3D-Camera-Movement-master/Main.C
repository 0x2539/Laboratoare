#include "Main.h"

using namespace std;


//Display Callback
//Called whenever the contents of the window need to be redrawn on the window. 
//e.g. when window was minimized and gets restored, or if window was behind other windows
void display ()
{
	//Clear the screen
	//Clears both the screen's colour and the depth of anything it is displaying
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/* Draw whatever is specified by the currently bound mesh (VAO)
	 * 1. Type of primitive we want to draw
	 * 2. Amount of indices in our array
	 * 3. Type of variable stored in the array
	 * 4. Pointer to the actual index array (leave as null to get the bound GL_ELEMENT_ARRAY_BUFFER instead)
	 */
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			xMove = 8.0f * (float)i;
			zMove = -8.0f * (float)j;
			updateWorld();
			glDrawElements(GL_TRIANGLES, INDEX_ARRAY_SIZE, GL_UNSIGNED_INT, 0);
		}
		
		xMove = 0.0f;
		updateWorld();
	}
	
	//Instruct OpenGL to send all our commands to the graphics card (if it hasn't done so already)
	glFlush();
	
	//Swap the buffers. i.e. we write to one while other displays to prevent "screen tearing" where half of the old pixels still remain.
	glutSwapBuffers();
	
	xMove = 0.0f;
	updateWorld();
	
	printFPS();
	
	last_frame = getTime();
}

#pragma GCC diagnostic ignored "-Wunused-parameter"
void keyboardUp(unsigned char key, int x, int y)
{
	active_keys[key] = false;
}
#pragma GCC diagnostic error "-Wunused-parameter"

#pragma GCC diagnostic ignored "-Wunused-parameter"
void keyboard(unsigned char key, int x, int y)
{
	active_keys[key] = true;
	
	switch (key)
	{
	       case 'h':
		        cout << "CONTROLS: " << endl;
			cout << endl;
			cout << "w: Forward" << endl;
			cout << "s: Backward" << endl;
			cout << "a: Left" << endl;
			cout << "d: Right" << endl;
			cout << "z: Position camera at default position" << endl;
			cout << "x: Bird's Eye View" << endl;
			cout << "c: First Person View" << endl;
			cout << "h: help" << endl;
			cout << endl;
	       break;
	       
	       case 'z':
		xScale = yScale = zScale = 1.0f;
		xRot = yRot = zRot = 0.0f;
		xMove = yMove = zMove = -0.5f;
		FOVY = 45.0f; 
	        cameraAt = vec3(64,1,-64);
	        cameraEye = vec3(0,2,0); 
	        old_cameraEye = cameraEye;
		old_cameraAt = cameraAt;
		break;
	       
	       case 'x':
		
		       if (!birdsEye)
		       {
				xScale = yScale = zScale = 1.0f;
				xRot = yRot = zRot = -0.5f;
				xMove = yMove = zMove = 0.0f;
				FOVY = 45.0f; 
				old_cameraEye = vec3(cameraEye.x, cameraEye.y, cameraEye.z);
				old_cameraAt = vec3(cameraAt.x, cameraAt.y, cameraAt.z);
				cameraAt = vec3(32,1,-32);
				cameraEye = vec3(0,60,0);

				birdsEye = true;
		       }
		
		break;
	       
	        case 'c':
			xScale = yScale = zScale = 1.0f;
			xRot = yRot = zRot = 0.0f;
			xMove = yMove = zMove = -0.5f;
			FOVY = 45.0f; 
			
			if (birdsEye)
			{
				
				cameraAt = old_cameraAt;
				cameraEye = old_cameraEye; 
				
				birdsEye = false;

			}
		       
		case '=':
		 FOVY += 1;
		 break;
		
		case '-':
		 FOVY -= 1;
		 break;
		
		case KEY_ESCAPE:
		 printf("Bye!\n");
		 exit(0);
		 break;
		
	      default:
		// printf("Key '%c' pressed, mouse at (%d, %d).\n", key, x, y);
		 break;
	}
	
	updateWorld();
	updateView();
	updateProjection(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutPostRedisplay();
}
#pragma GCC diagnostic error "-Wunused-parameter"


void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
		{
			cout << "Left ";
			break;
		}
		case GLUT_MIDDLE_BUTTON:
		{
			cout << "Middle ";
			break;
		}
		case GLUT_RIGHT_BUTTON:
		{
			cout << "Right ";
			break;
		}
		
		default:
			cout << "unknown ";
			break;
	}
	
	cout << "mouse button ";
	
	switch (state)
	{
		case GLUT_UP:
			cout << "released ";
			break;
		
		case GLUT_DOWN:
			cout << "pressed ";
			break;
		
		default:
			cout << "did something we don't know...";
			break;

	}
	
	cout << "at [" << x << ", " << y << "] " << endl;
}

void mouseLook (int x, int y)
{
	int horizontal_centre = WINDOW_WIDTH / 2;
	int vertical_centre = WINDOW_HEIGHT / 2;
	
	const int xDistance = -(x - horizontal_centre); //negated because positive rotation is ant-clockwise
	const int yDistance = -(y - vertical_centre);
	
	//We need to find our angle of rotation (max 180 degrees) by scaling max rotation (180) with the ratio of screen moved from centre
	GLfloat horizontalScale = (GLfloat) xDistance / (GLfloat) horizontal_centre;
	GLfloat verticalScale = (GLfloat) yDistance / (GLfloat) vertical_centre;
	
	GLfloat vRotation = verticalScale * 3.14f; //NB: 3.14f is 180 degrees in radions
	GLfloat hRotation = horizontalScale * 3.14f;
	
	//calc current direction vector
	vec3 direction = (cameraAt - cameraEye);
	
	//calculate current right vector
	vec3 right = glm::cross(direction, cameraUp);//will always stay horizontal
	
	//We can thus rotate around the "y-axis" (CameraUp) for left/right looking
	//We can thus rotate around the "x-axis" (right) for up/down looking
	
	mat4 rotation; //create empty 4x4 rotation matrix
	rotation = glm::rotate (rotation, hRotation, cameraUp);
	rotation = glm::rotate (rotation, vRotation, right);
	
	glm::vec4 d (direction.x, direction.y, direction.z, 0.0f);//create a vec4 direction vector so that we can rotate it
	
	d = rotation * d;
	
	cameraAt = cameraEye + vec3(d.x, d.y, d.z);
	
	//Trap mouse in the window
	if ((xDistance!= 0) || (yDistance != 0))
	{
		//each call to this function generates another motion event.
		//Therefore if we do not check if the mouse has moved from centre, this will be continuously called, allowing for no possible mouse movement
		glutWarpPointer(horizontal_centre, vertical_centre);
	}
	
}

void reshape(int newWidth, int newHeight)
{
	//Fix our viewport
	glViewport (0, 0, newWidth, newHeight);
	
	//Ask GLUT for a redraw. Tells GLUT to call display function
	glutPostRedisplay();
}

void updateWorld()
{
	mat4 world;
	
	vec3 xAxis (1, 0, 0);
	world = rotate(world, xRot, xAxis);
	
	vec3 yAxis (0, 1, 0);
	world = rotate(world, yRot, yAxis);
	
	vec3 zAxis (0, 0, 1);
	world = rotate(world, zRot, zAxis);
	
	vec3 translation(xMove, yMove, zMove);
	world = translate (world, translation);
	
	vec3 scales(xScale, yScale, zScale);
	world = scale(world, scales);
	
	glUniformMatrix4fv(worldLoc, 1, GL_FALSE, value_ptr(world));
}

void updateView()
{
	mat4 worldView = lookAt(cameraEye, cameraAt, cameraUp);
	
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(worldView));
}

void updateProjection(int width, int height)
{
	GLfloat aspect = (GLfloat)width / (GLfloat)height; //Aspect ratio, where width and height are the dimensions of the window
	
	mat4 projection = perspective(FOVY, aspect, NEAR, FAR);
	
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));
}

int getTime()
{
	//Return time in milliseconds since the program started (Elapsed Time)
	return glutGet(GLUT_ELAPSED_TIME);
}

void printFPS()
{
	
	int now = getTime();
		
	if (now - last_print > MILLISECONDS_PER_SECOND)
	{
		//Measure the actual time between to frames
		int deltaT = now - last_frame;
	
		//Convert deltaT to seconds 
		double seconds = (double)deltaT/MILLISECONDS_PER_SECOND; 
		double fps = 1.0 / seconds; //1.0 instead of 1 so that we get floating point division.
		
		cout << "FPS: "<<fps<<endl;
		last_print = now;
	}
}

void idle()
{
	const int now = getTime();
	const int deltaT = now - last_frame;
	const GLfloat seconds = (GLfloat)deltaT / (GLfloat)MILLISECONDS_PER_SECOND; //Get deltaT in seconds
	const GLfloat step = seconds * 10.0f;
	
	
	if (deltaT >= TARGET_DELTA_T)
	{
		vec3 d = step  + 0.1f * glm::normalize(cameraAt - cameraEye);
		vec3 r = 0.1f * glm::normalize(glm::cross(d, cameraUp));
		
		checkKeys(d, r);
		
		//Queue up a new frame. Ask GLUT for a redraw.
		glutPostRedisplay();
	}

}

void checkKeys(vec3 d, vec3 r)
{
	if (active_keys['w'])
	{
		//cout << d << endl;
		cameraEye += d;
		cameraAt += d;
	}
	else if (active_keys['s'])
	{
		//cout << d << endl;
		cameraEye -= d;
		cameraAt -= d;
	}
	
	if (active_keys['d'])
	{
		cameraEye += r;
		cameraAt += r;
	}
	else if (active_keys['a'])
	{
		cameraEye -= r;
		cameraAt -= r;
	}
	
	
	updateView();
	glutPostRedisplay();
}

void initGLEW()
{
	//initialise GLEW (GL Extension Wrangler - Managers/Wrangles shader programs)
	glewInit();
	
	if (!GLEW_VERSION_3_2)
	{
		fprintf(stderr, "This progarm requires OpenGL 3.2");
		exit(-1);
	}
}

void init ()
{
	last_print = getTime();
	last_frame = getTime();
	
	glEnable(GL_VERTEX_ARRAY);//?
	//switch on Depth Testing to ensure that if something is behind something, it does not show
	glEnable(GL_DEPTH_TEST);
	//switch on Face Culling (Gets rid of faces looking away from us)
	glEnable(GL_CULL_FACE);
	
	//set the "clear colour" (background colour in any other API) to blue. (red, green, blue, alpha)
	glClearColor(0.0, 0.0, 1.0, 1.0);
	
	//compile and link shader programs
	loadShaderPrograms();
	
	//activate the shader program to tell openGL that we are talking about this program when we use a function that has reference to the shaders.
	glUseProgram(program);
	
	//get a handle on the position and colour inputs in the shader
	positionLoc = findAttribute("position");
	colourLoc =  findAttribute("colour");
	
	worldLoc = findUniform("world");
	viewLoc = findUniform("view");
	projectionLoc = findUniform("projection");
	
	updateProjection(WINDOW_WIDTH, WINDOW_HEIGHT);
	updateView();
	updateWorld();
	
	loadGeometry();
	
	glBindVertexArray(cube);
	
	
}

char* loadFile(const char* fileName)
{
	FILE* file = fopen(fileName, "r");//open file for reading
	
	if (file == NULL)
	{
		fprintf(stderr, "could not open file '%s'.\n", fileName);
	}
	
	//since we don;t know file size, we start with really small array and grow it.
	unsigned int bufferSize = 1;
	char* buffer = (char*) malloc (bufferSize);//malloc() used instead of 'new' because it is guaranteed to work with realloc()
	
	//BASIC IDEA: We read a char, then check if we have space for it. If we don't, we will DOUBLE THE SIZE of the buffer.
	//We therefore need to keep track of where we are in the buffer o perform this check.
	unsigned int index = 0;
	
	//A loop that checks if we are at the end of the file.
	while (true)
	{
		//get next char
		char c = (char) fgetc(file);
		
		//check for errors
		if (ferror(file) != 0)
		{
			fprintf(stderr, "could not open file '%s'.\n", fileName);
		}
		
		if (index == bufferSize - 1)
		{
			bufferSize *= 2;
			
			//realloc() takes in a void* (so we need to cast our buffer pointer) and the new size for the buffer.
			buffer = (char*) realloc((void*) buffer, bufferSize);//buffer is resized and realloc() is used to avoid copying the old contents over character by character.
		}
		
		//Check if end of file
		if (feof (file))
		{
			break;
		}
		
		//Otherwise, add char to buffer
		buffer[index] = c;
		index ++;
	}
	
	buffer[index] = '\0';
	fclose(file);
	return buffer;
}

void loadShaderPrograms()
{
	loadShaderProgram(vertexShader, "vertex.glsl", GL_VERTEX_SHADER);
	loadShaderProgram(fragmentShader, "fragment.glsl", GL_FRAGMENT_SHADER);
	
	/*Time to "link" things together*/
	
	//Get a handle to a program object (a bigger program made of smaller shader programs)
	program = glCreateProgram();
	
	/*Attach each shader program to the program object*/
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	
	//Run the linker
	glLinkProgram(program);
	
	int status;
	
	//Get the compile status for the specified handle and store it in the status integer
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	
	//if errors found, we need to print out the error messages
	if (status == GL_FALSE)
	{
		int len;
		
		//We need length of the info log in order to create a character array of that size.
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
		
		char* log = new char[len];
		
		/* Get the actual log file
		 * 1. handle of shader
		 * 2. pass in the length of the buffer so that openGL does not write past the end of the buffer.
		 * 3. pass in a reference to a variable where openGL will record the "actual" amount of characters that was written in the buffer.
		 * 4. pass the "buffer" you wish openGL to write to.
		 */
		glGetProgramInfoLog(program, len, &len, log);
		
		/*Now we print the error, free its memory and quit the application*/
		
		//Throw an exception.
		fprintf(stderr, "Link error: %s.\n", log);

		//Finally, free the memory allocated.
		delete log;

		//Exit the program.
		exit(-1);
	}
}

void loadShaderProgram(unsigned& handle, const char* file, GLenum shaderType)
{
	/*
	 * shaderType Enum: GL_VERTEX_SHADER, GL_FRAGMENT_SHADER
	 */
	
	//Create an object. Get an integer handle on the object (instead of a pointer)
	handle = glCreateShader(shaderType);
	
	//load the file
	char* source = loadFile(file);
	
	/*
	 * Attach shader file to actual shader object.
	 * 1. We send in the handle of the shader program object whose source we want to set.
	 * 2. We state how many indexes the array (which represents the lines in your program) we're passing in has. i.e. an array of arrays of char or char**. 
	 *     We read in the program as one long line and therefore pass in a 1 as the argument.
	 * 3. We send the actual pointer, which must be a const char** (requiring a cast). 
	 * 4. We send in the length of the string. Since ours is NULL_terminated, we can just pass through NULL here.
	 *
	 * NB: 3. gets rid of some "qualifiers" (it makes the char* a constant. We therefore need to drop -Wcast-qual from the makefile.
	 */
	glShaderSource(handle, 1, (const GLchar**)&source, NULL);
	
	//Compile the source code associated with the given handle
	glCompileShader(handle);
	
	//After the shader source has been set inside OpenGL, we can free the memory we allocated. 
	free(source);
	
	/* Now we need to check if the program compiled properly. In order to check for errors
	    we will need to query some information about our object. */
	    
	int status;
	
	//Get the compile status for the specified handle and store it in the status integer
	glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
	
	//if errors found, we need to print out the error messages
	if (status == GL_FALSE)
	{
		int len;
		
		//We need length of the info log in order to create a character array of that size.
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &len);
		
		char* log = new char[len];
		
		/* Get the actual log file
		 * 1. handle of shader
		 * 2. pass in the length of the buffer so that openGL does not write past the end of the buffer.
		 * 3. pass in a reference to a variable where openGL will record the "actual" amount of characters that was written in the buffer.
		 * 4. pass the "buffer" you wish openGL to write to.
		 */
		glGetShaderInfoLog(handle, len, &len, log);
		
		/*Now we print the error, free its memory and quit the application*/
		
		//Throw an exception.
		fprintf(stderr, "Compilation Error in %s: %s.\n", file,log);

		//Finally, free the memory allocated.
		delete log;

		//Exit the program.
		exit(-1);
	}
	
}

void loadGeometry()
{
	drawBoard();
}

void drawBoard()
{
	
    GLfloat* vertices = new GLfloat[VERTEX_ARRAY_SIZE];
   int i = 0;
   float pX = 0.0f;
   float pZ = 0.0f;
   
   float k = 0.0f;
	
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wfloat-equal"
	for (int l = 0; l < 8; l++)
	{
		for (int j = 0; j < 8; j++)
		{

			vertices[i++] = pX;
			vertices[i++] = 0.0f; // 0,0,0; 1,0,0; 2,0,0; 3,0,0 etc
			vertices[i++] = pZ;
			vertices[i++] = k;
			vertices[i++] = k;
			vertices[i++] = k;
		
			vertices[i++] = (pX + 1.0f);
			vertices[i++] = 0.0f; // 1,0,0; 2,0,0; 3,0,0; 4,0,0 etc
			vertices[i++] = pZ;
			vertices[i++] = k;
			vertices[i++] = k;
			vertices[i++] = k;
		
			vertices[i++] = pX;
			vertices[i++] = 0.0f;//0,0,-1; 1,0,-1; 2,0,-1; 3,0,-1 etc
			vertices[i++] = pZ -1.0f;
			vertices[i++] = k;
			vertices[i++] = k;
			vertices[i++] = k;
		   
			vertices[i++] = (pX + 1.0f);
			vertices[i++] = 0.0f;//1,0,-1; 2,0,-1; 3,0,-1; 4,0,-1 etc
			vertices[i++] = pZ -1.0f;
			vertices[i++] = k;
			vertices[i++] = k;
			vertices[i++] = k;
			
			if (k == 0.0f)
			{
				k = 1.0f;
			}
			else
			{
				k = 0.0f;
			}
			
			pX = pX + 1.0f;
		}
		
		if (k == 0.0f)
			{
				k = 1.0f;
			}
			else
			{
				k = 0.0f;
			}
		
		pZ = pZ - 1.0f;
		pX = 0.0f;
	}
   
    cout << endl;
	#pragma GCC diagnostic pop

   GLuint* indices = new GLuint[INDEX_ARRAY_SIZE];
   i = 0;
	
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
   for (int l = 0; l < 8; l++)
   {
	   for (int j = 0; j < 64; j++)
	   {
		indices[i++] = 0 + (4*j) + 32*l*8;
		indices[i++] = 3 + (4*j) + 32*l*8;
		indices[i++] = 2 + (4*j) + 32*l*8;
		indices[i++] = 0 + (4*j) + 32*l*8;
		indices[i++] = 1 + (4*j) + 32*l*8;
		indices[i++] = 3 + (4*j) + 32*l*8;
	   }
   }
    #pragma GCC diagnostic pop

   /* Declare our handles. */
   GLuint vertexBuffer, indexBuffer;

   glGenVertexArrays(1, &cube);
   glBindVertexArray(cube);

   glGenBuffers(1, &vertexBuffer);
   glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

   glBufferData(GL_ARRAY_BUFFER, VERTEX_ARRAY_SIZE * (int)sizeof(GLfloat),
         vertices, GL_STATIC_DRAW);

   glGenBuffers(1, &indexBuffer);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

   glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDEX_ARRAY_SIZE * (int)sizeof(GLuint),
         indices, GL_STATIC_DRAW);

   glEnableVertexAttribArray((GLuint)positionLoc);
   glVertexAttribPointer((GLuint)positionLoc, DIMENSIONS, GL_FLOAT, GL_FALSE, 
         VERTEX_SIZE * (int)sizeof(GLfloat), 0);
	 
	 glEnableVertexAttribArray((GLuint)colourLoc);
	glVertexAttribPointer((GLuint)colourLoc, COLOUR_COMPONENT_COUNT, GL_FLOAT, 
         GL_FALSE,
         VERTEX_SIZE * (int)sizeof(GLfloat),
         (void*)(DIMENSIONS* (int)sizeof(GLfloat)));
	 
	 delete [] vertices;
	 delete [] indices;
}

GLint findAttribute(const char* name)
{
	GLint location = glGetAttribLocation(program, name);
	
	if (location == 0)
	{
		fprintf(stderr, "Could not find attribute named '%s'.\n", name);
	}
	
	return location;
}

GLint findUniform(const char* name)
{
	GLint location = glGetUniformLocation(program, name);
	
	if (location == -1)
	{
		fprintf(stderr, "Could not find uniform named '%s'.\n", name);
	}
	
	return location;
}

void cleanUp()
{
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);
	
	glDeleteProgram(program);
}

int main (int argc, char** argv)
{
	glutInit(&argc, argv); //Glut needs access to argc and argv since it implements some command line switches
	
	//Use two buffers to prevent screen tearing, 
	//use a depth buffer to work in 3D, 
	//and use a colour screen
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); //Size of the window we would like
	glutCreateWindow("COS344_Assignment_1");//Set title of the window
	
	glutDisplayFunc(display); //Register Display Event/ Callback
	glutSetCursor(GLUT_CURSOR_NONE);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(mouseLook);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	
	cout << "CONTROLS: " << endl;
	cout << endl;
	cout << "w: Forward" << endl;
	cout << "s: Backward" << endl;
	cout << "a: Left" << endl;
	cout << "d: Right" << endl;
	cout << "z: Position camera at default position" << endl;
	cout << "x: Bird's Eye View" << endl;
	cout << "c: First Person View" << endl;
	cout << "h: help" << endl;
	cout << endl;
	

	initGLEW();
	init();
	
	//Hand over to GLUT
	//Will cause GLUT to start calling our callback functions (like Display) and handle anything else it needs to.
	glutMainLoop();
	
	cleanUp();
	
	return 0;	
}
