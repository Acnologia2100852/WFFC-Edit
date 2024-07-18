#pragma once

#include "DisplayChunk.h"
#include <vector>
#include <memory>
#include <stack>
#include "DisplayObject.h"

using namespace DirectX::SimpleMath;

struct InputCommands;

class ObjectController
{
public:
	static ObjectController& Instance() 
	{
		static ObjectController instance;
		isInstanceMade = true;
		return instance;
	}

	ObjectController(const ObjectController&) = delete;
	void operator=(const ObjectController&) = delete;

	void Init(std::vector<DisplayObject>* startingObjs, const std::shared_ptr<DX::DeviceResources>& deviceResources);
	void Update(InputCommands& inputComs);
	std::vector<DisplayObject>* GetDisplayObjects() { return allDisplayObjs; }

	static bool IsInstanceMade() { return isInstanceMade; }

	void MultiTextureChange();
	void RemoveTexture(const int id);
	void RemoveAllTextures();

	DisplayObject GetLastDisplayObject();
	DisplayObject GetObject(int id);
	void SetDisplayObject(const DisplayObject& newObjectParam);
	void Undo();


	bool isEditing = false;
	std::vector<int> selectedObjs;
	std::stack<DisplayObject> objHistory;

protected:
	ObjectController();
private:

	std::vector<DisplayObject>* allDisplayObjs;
	std::shared_ptr<DX::DeviceResources> deviceResource;

	static bool isInstanceMade;
};

inline ObjectController::ObjectController(): allDisplayObjs(nullptr)
{
	
}

bool RemoveIntFromVector(std::vector<int>& vec, int target);

