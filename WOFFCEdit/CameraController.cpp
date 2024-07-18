#include "CameraController.h"
#include "InputCommands.h"

CameraController::CameraController()
{
	Init();
}

void CameraController::Update(const InputCommands& inputCom)
{
	HandleMouse(inputCom);

	if (inputCom.rotRight) 
	{
		camOrientation.y -= camRotRate;
	}
	if (inputCom.rotLeft) 
	{
		camOrientation.y += camRotRate;
	}

	

	camLookDirection.x = sin((camOrientation.y) * 3.1415 / 180);
	camLookDirection.z = cos((camOrientation.y) * 3.1415 / 180);

	camLookDirection.Normalize();

	camLookDirection.Cross(Vector3::UnitY, camRight);

	if (inputCom.forward) 
	{
		camPos += camLookDirection * moveSpeed;
	}

	if (inputCom.back)
	{
		camPos -= camLookDirection * moveSpeed;
	}

	if (inputCom.right)
	{
		camPos += camRight * moveSpeed;
	}

	if (inputCom.left)
	{
		camPos -= camRight * moveSpeed;
	}

	camLookAt = camPos + camLookDirection;

	view = Matrix::CreateLookAt(camPos, camLookAt, Vector3::UnitY);
	

}

void CameraController::FocusCam(const Vector3& targetPos)
{
	camPos.x = targetPos.x;
	camPos.y = targetPos.y + 1;
	camPos.z = targetPos.z - 3;

	LookAt(targetPos);
}

void CameraController::LookAt(const Vector3& target)
{
	float dx = target.x - camPos.x;
	float dy = target.y - camPos.y;
	float dz = target.z - camPos.z;

	camOrientation.y = atan2(dx, dz) * (180 / 3.1415);

	float dist = sqrt(dx * dx + dz * dz);
	camOrientation.x = -atan2(dy, dist) * (180 / 3.1415);
}

void CameraController::Init()
{
	moveSpeed = 0.30;
	camRotRate = 3.0;

	camPos.x = 0.0f;
	camPos.y = 3.7f;
	camPos.z = -3.5f;

	camOrientation.x = 0;
	camOrientation.y = 0;
	camOrientation.z = 0;

	camLookAt.x = 0;
	camLookAt.y = 0;
	camLookAt.z = 0;

	camLookDirection.x = 0;
	camLookDirection.y = 0;
	camLookDirection.z = 0;

	camRight.x = 0;
	camRight.y = 0;
	camRight.z = 0;


}

void CameraController::CreateUpdate()
{
}

void CameraController::HandleMouse(const InputCommands& inputCom)
{
	newMousePos = Vector2(inputCom.mouseX, inputCom.mouseY);

	if (inputCom.RMB) 
	{
		Vector2 diff;

		diff.x = newMousePos.x - oldMousePos.x;
		diff.y = newMousePos.y - oldMousePos.y;

		diff.Normalize();

		if(diff.x != 0 || diff.y != 0)
		{
			camOrientation.y -= camRotRate * diff.x;

			camOrientation.x -= camRotRate * diff.y;
		}

		float cosR, cosP, cosY;
		float sinR, sinP, sinY;

		cosP = cosf(camOrientation.x * (3.1415 / 180));
		cosY = cosf(camOrientation.y * (3.1415 / 180));
		cosR = cosf(camOrientation.z * (3.1415 / 180));

		sinP = sinf(camOrientation.x * (3.1415 / 180));
		sinY = sinf(camOrientation.y * (3.1415 / 180));
		sinR = sinf(camOrientation.z * (3.1415 / 180));

		camLookDirection.x = sinY * cosP;
		camLookDirection.y = sinP;
		camLookDirection.z = cosP * -cosY;

		view = Matrix::CreateLookAt(camPos, camLookAt, Vector3::UnitY);

	}
	oldMousePos = newMousePos;
}
