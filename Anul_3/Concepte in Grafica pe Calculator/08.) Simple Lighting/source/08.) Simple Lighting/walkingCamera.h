#pragma once

/********************************

Class:	CWalkingCamera

Purpose:	Camera that can walk
			around the scene.

********************************/

class CWalkingCamera
{
public:
	glm::mat4 look();
	void update();

	void rotateViewY(float fAngle);
	void move(float fBy);

	CWalkingCamera();
	CWalkingCamera(glm::vec3 a_vEye, glm::vec3 a_vView, glm::vec3 a_vUp, float a_fSpeed);

private:
	glm::vec3 vEye, vView, vUp;
	float fSpeed;
};