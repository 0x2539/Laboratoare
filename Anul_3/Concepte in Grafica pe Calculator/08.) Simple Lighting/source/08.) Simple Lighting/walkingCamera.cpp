#include "common_header.h"

#include "win_OpenGLApp.h"
#include "walkingCamera.h"

#include <glm/gtc/matrix_transform.hpp>

CWalkingCamera::CWalkingCamera() :vEye(0.0f, 0.0f, 0.0f), vView(0.0f, 0.0f, -1.0f), vUp(0.0f, 1.0f, 0.0f), fSpeed(25.0f)
{
}

CWalkingCamera::CWalkingCamera(glm::vec3 a_vEye, glm::vec3 a_vView, glm::vec3 a_vUp, float a_fSpeed)
{
	vEye = a_vEye;
	vView = a_vView;
	vUp = a_vUp;
	fSpeed = a_fSpeed;
}

/*-----------------------------------------------

Name:		look

Params:	none

Result:	"Looks" at the scene.

/*---------------------------------------------*/

glm::mat4 CWalkingCamera::look()
{
	return glm::lookAt(vEye, vView, vUp);
}

/*-----------------------------------------------

Name:		rotateViewY

Params:	fAngle - angle to rotate by

Result:	Rotates view along Y axis by specified
			angle.

/*---------------------------------------------*/

void CWalkingCamera::rotateViewY(float fAngle)
{
	glm::mat4 mRotation = glm::rotate(glm::mat4(1.0f), fAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 vDir = vView-vEye;
	glm::vec4 vNewView = mRotation*glm::vec4(vDir, 1.0f);
	vView = glm::vec3(vNewView.x, vNewView.y, vNewView.z);
	vView += vEye;
}

/*-----------------------------------------------

Name:		move

Params:	fBy - how much to move

Result:	Moves in the view direction.

/*---------------------------------------------*/

void CWalkingCamera::move(float fBy)
{
	glm::vec3 vDir = vView-vEye;
	vDir *= fBy;
	vEye += vDir;
	vView += vDir;
}
/*-----------------------------------------------

Name:		update

Params:	none

Result:	Handles keys and updates camera.

/*---------------------------------------------*/

void CWalkingCamera::update()
{
	if(Keys::key('W'))move(appMain.sof(fSpeed));
	if(Keys::key('S'))move(appMain.sof(-fSpeed));
	if(Keys::key('A'))rotateViewY(appMain.sof(90.0f));
	if(Keys::key('D'))rotateViewY(appMain.sof(-90.0f));
}