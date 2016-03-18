#pragma once

/********************************

Class:	CShader

Purpose:	Wraps OpenGL shader loading
			and compiling.

********************************/

class CShader
{
public:
	bool loadShader(string sFile, int a_iType);
	void deleteShader();

	bool isLoaded();
	UINT getShaderID();

	CShader();

private:
	UINT uiShader; // ID of shader
	int iType; // GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...
	bool bLoaded; // Whether shader was loaded and compiled
};

/********************************

Class:	CShaderProgram

Purpose:	Wraps OpenGL shader program
			and make its usage easy.

********************************/

class CShaderProgram
{
public:
	void createProgram();
	void deleteProgram();

	bool addShaderToProgram(CShader* shShader);
	bool linkProgram();

	void useProgram();

	UINT getProgramID();


	// Setting vectors
	void setUniform(string sName, glm::vec2* vVectors, int iCount = 1);
	void setUniform(string sName, const glm::vec2 vVector);
	void setUniform(string sName, glm::vec3* vVectors, int iCount = 1);
	void setUniform(string sName, const glm::vec3 vVector);
	void setUniform(string sName, glm::vec4* vVectors, int iCount = 1);
	void setUniform(string sName, const glm::vec4 vVector);

	// Setting floats
	void setUniform(string sName, float* fValues, int iCount = 1);
	void setUniform(string sName, const float fValue);

	// Setting 4x4 matrices
	void setUniform(string sName, glm::mat4* mMatrices, int iCount = 1);
	void setUniform(string sName, const glm::mat4 mMatrix);

	// Setting integers
	void setUniform(string sName, int* iValues, int iCount = 1);
	void setUniform(string sName, const int iValue);

	CShaderProgram();

private:
	UINT uiProgram; // ID of program
	bool bLinked; // Whether program was linked and is ready to use
};