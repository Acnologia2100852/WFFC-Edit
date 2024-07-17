#pragma once
#include "DisplayChunk.h"
#include "DisplayObject.h"

using namespace DirectX::SimpleMath;

struct InputCommands;


class CameraController
{

public:
	CameraController();
	void Update(const InputCommands& inputCom);
	void FocusCam(const Vector3& targetPos);
	void LookAt(const Vector3& target);

protected:
	void Init();
	void CreateUpdate();
	void HandleMouse(const InputCommands& inputCom);

	//Floats
	float moveSpeed;
	float camRotRate;

	//Vectors
	Vector3 camPos;
	Vector3 camOrientation;

	Vector3 camLookAt;
	Vector3 camLookDirection;
	Vector3 camRight;

	Vector2 oldMousePos;
	Vector2 newMousePos;

	//Matrices
	Matrix view;

public:

	Matrix GetViewMatrix() const { return view; }
	Vector3 GetPos() const { return camPos; }

};

