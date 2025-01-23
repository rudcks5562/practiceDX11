#include "stdafx.h"
#include "Animation.h"
#include "Texture.h"

Animation::Animation():Super(ResourceType::Animation)
{

}

Animation::~Animation()
{

}

void Animation::Load(const wstring& path)
{
	tinyxml2::XMLDocument doc;

	string pathStr(path.begin(), path.end());

	XMLError error= doc.LoadFile(pathStr.c_str());

	assert(error == XMLError::XML_SUCCESS);
	
	XmlElement* root = doc.FirstChildElement();
	string nameStr = root->Attribute("Name");
	_name = wstring(nameStr.begin(), nameStr.end());

	_loop = root->BoolAttribute("Loop");
	_path = path;


// load texture

	XmlElement* node = root->FirstChildElement();


	for (; node != nullptr;node=node->NextSiblingElement()) {
		

		keyFrame keyframe;
		
		keyframe.offset.x = node->FloatAttribute("OffsetX");
		keyframe.offset.y = node->FloatAttribute("OffsetY");
		keyframe.size.x = node->FloatAttribute("SizeX");
		keyframe.size.y = node->FloatAttribute("SizeY");
		keyframe.time = node->FloatAttribute("Time");


		AddKeyFrame(keyframe);

	}


}



void Animation::Save(const wstring& path)
{
	tinyxml2::XMLDocument doc;

	XMLElement* root = doc.NewElement("Animation");
	doc.LinkEndChild(root);

	string nameStr(GetName().begin(), GetName().end());

	root->SetAttribute("Name", nameStr.c_str());
	root->SetAttribute("Loop", _loop);// 오버로딩 많음
	root->SetAttribute("TexturePath", "TODO");


	for (const auto& keyframe : _keyFrames) {

		XMLElement* node = doc.NewElement("KeyFrame");
		root->LinkEndChild(node);

		// 멜공격 6인?
		node->SetAttribute("OffsetX", keyframe.offset.x);
		node->SetAttribute("OffsetY", keyframe.offset.y);
		node->SetAttribute("SizeX", keyframe.offset.x);
		node->SetAttribute("SizeY", keyframe.offset.x);
		node->SetAttribute("Time", keyframe.time);
		 

	}
	string pathStr(path.begin(), path.end());
	auto result = doc.SaveFile(pathStr.c_str());

	assert(result == XMLError::XML_SUCCESS);

}


const keyFrame& Animation::GetKeyFrame(int32 index)
{
	return _keyFrames[index];
}

int32 Animation::GetKeyFrameCount()
{
	return  static_cast<int32>(_keyFrames.size());

}

void Animation::AddKeyFrame(const keyFrame& keyframe)
{
	_keyFrames.push_back(keyframe);

}
