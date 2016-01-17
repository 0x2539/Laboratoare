#include "common_header.h"

#include "vertexBufferObject.h"

CVertexBufferObject::CVertexBufferObject()
{
	bDataUploaded = false;
}

/*-----------------------------------------------

Name:		createVBO

Params:	a_iSize - initial size of buffer

Result:	Creates vertex buffer object.

/*---------------------------------------------*/

void CVertexBufferObject::createVBO(int a_iSize)
{
	glGenBuffers(1, &uiBuffer);
	data.reserve(a_iSize);
	iSize = a_iSize;
}

/*-----------------------------------------------

Name:		releaseVBO

Params:	none

Result:	Releases VBO and frees all memory.

/*---------------------------------------------*/

void CVertexBufferObject::releaseVBO()
{
	glDeleteBuffers(1, &uiBuffer);
	bDataUploaded = false;
	data.clear();
}

/*-----------------------------------------------

Name:		mapBufferToMemory

Params:	iUsageHint - GL_READ_ONLY, GL_WRITE_ONLY...

Result:	Maps whole buffer data to memory and
			returns pointer to data.

/*---------------------------------------------*/

void* CVertexBufferObject::mapBufferToMemory(int iUsageHint)
{
	if(!bDataUploaded)return NULL;
	void* ptrRes = glMapBuffer(iBufferType, iUsageHint);
	return ptrRes;
}

/*-----------------------------------------------

Name:		mapSubBufferToMemory

Params:	iUsageHint - GL_READ_ONLY, GL_WRITE_ONLY...
			uiOffset - data offset (from where should
							data be mapped).
			uiLength - length of data

Result:	Maps specified part of buffer to memory.

/*---------------------------------------------*/

void* CVertexBufferObject::mapSubBufferToMemory(int iUsageHint, UINT uiOffset, UINT uiLength)
{
	if(!bDataUploaded)return NULL;
	void* ptrRes = glMapBufferRange(iBufferType, uiOffset, uiLength, iUsageHint);
	return ptrRes;
}

/*-----------------------------------------------

Name:		unmapBuffer

Params:	none

Result:	Unmaps previously mapped buffer.

/*---------------------------------------------*/

void CVertexBufferObject::unmapBuffer()
{
	glUnmapBuffer(iBufferType);
}

/*-----------------------------------------------

Name:		bindVBO

Params:	a_iBufferType - buffer type (GL_ARRAY_BUFFER, ...)

Result:	Binds this VBO.

/*---------------------------------------------*/

void CVertexBufferObject::bindVBO(int a_iBufferType)
{
	iBufferType = a_iBufferType;
	glBindBuffer(iBufferType, uiBuffer);
}

/*-----------------------------------------------

Name:		uploadDataToGPU

Params:	iUsageHint - GL_STATIC_DRAW, GL_DYNAMIC_DRAW...

Result:	Sends data to GPU.

/*---------------------------------------------*/

void CVertexBufferObject::uploadDataToGPU(int iDrawingHint)
{
	glBufferData(iBufferType, data.size(), &data[0], iDrawingHint);
	bDataUploaded = true;
	data.clear();
}

/*-----------------------------------------------

Name:		addData

Params:	ptrData - pointer to arbitrary data
			uiDataSize - data size in bytes

Result:	Adds arbitrary data to VBO.

/*---------------------------------------------*/

void CVertexBufferObject::addData(void* ptrData, UINT uiDataSize)
{
	data.insert(data.end(), (BYTE*)ptrData, (BYTE*)ptrData+uiDataSize);
}

/*-----------------------------------------------

Name:		getDataPointer

Params:	none

Result:	Returns data pointer (only before uplading).

/*---------------------------------------------*/

void* CVertexBufferObject::getDataPointer()
{
	if(bDataUploaded)return NULL;
	return (void*)data[0];
}

/*-----------------------------------------------

Name:		getBuffer

Params:	none

Result:	Returns VBO ID.

/*---------------------------------------------*/

UINT CVertexBufferObject::getBuffer()
{
	return uiBuffer;
}


