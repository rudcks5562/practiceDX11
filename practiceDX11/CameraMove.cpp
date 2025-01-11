#include "stdafx.h"
#include "CameraMove.h"
#include "GameObject.h"
void CameraMove::Update()
{

	//GetGameObject()->GetCamera();
	auto pos=GetTransform()->GetPosition();
	pos.x += 0.01f;
	GetTransform()->SetPosition(pos);
}
