#include "ObjectController.h"
#include "InputCommands.h"


void ObjectController::Init(std::vector<DisplayObject>* startingObjs, const std::shared_ptr<DX::DeviceResources>& deviceResources)
{
	allDisplayObjs = startingObjs;
	deviceResource = deviceResources;

	//Assign each object an ID
	for (int i = 0; i < allDisplayObjs->size(); ++i) 
	{
		(*allDisplayObjs)[i].m_ID = i;
	}
}

void ObjectController::Update(InputCommands& inputComs)
{
	//Check for selected Objects

	if (!selectedObjs.empty()) 
	{
		//Loop through all objects, if selected move according to user input
		for (int i = 0; i < allDisplayObjs->size(); ++i) 
		{
			if(std::find(selectedObjs.begin(), selectedObjs.end(), i) != selectedObjs.end())
			{
				if(inputComs.)
			}
		}
	}

}

void ObjectController::MultiTextureChange()
{
}

void ObjectController::RemoveTexture(const int id)
{
	for (int i = 0; i < allDisplayObjs->size(); ++i) 
	{
		if (id == i) 
		{
			DirectX::CreateDDSTextureFromFile(deviceResource->GetD3DDevice(), L"database/data/placeholder.dds", nullptr, &(*allDisplayObjs)[i].m_texture_diffuse);
			(*allDisplayObjs)[i].m_model->UpdateEffects([&](DirectX::IEffect* effect)
				{
					const auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
					if (basicEffect)
					{
						basicEffect->SetTexture((*allDisplayObjs)[i].m_texture_diffuse);
					}
				});
		}
	}
}

void ObjectController::RemoveAllTextures()
{
}

DisplayObject ObjectController::GetLastDisplayObject()
{

	for (int i = 0; i < allDisplayObjs->size(); ++i) 
	{
		if (selectedObjs.empty()) return{};

		if (i == selectedObjs.back()) {
			return (*allDisplayObjs)[i];
		}
	}


	return {};
}

DisplayObject ObjectController::GetObject(int id)
{

	for (int i = 0; i < allDisplayObjs->size(); ++i) 
	{
		if (i == id) {
			return (*allDisplayObjs)[i];
		}

	}

	return {};
}

void ObjectController::SetDisplayObject(const DisplayObject& newObjectParam)
{
	for (int i = 0; i < allDisplayObjs->size(); ++i) 
	{
		if (i == newObjectParam.m_ID) 
		{
			(*allDisplayObjs)[i].m_position = newObjectParam.m_position;
			(*allDisplayObjs)[i].m_scale = newObjectParam.m_scale;
			(*allDisplayObjs)[i].m_orientation = newObjectParam.m_orientation;

			return;
		}
	}
}

void ObjectController::Undo()
{
}

bool ObjectController::isInstanceMade = false;

bool RemoveIntFromVector(std::vector<int>& vec, int target)
{

	auto it = std::find(vec.begin(), vec.end(), target);

	if (it != vec.end()) {
		vec.erase(it);
		return true;
	}

	return false;
}
