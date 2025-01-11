#pragma once
#include "ResourceBase.h"

struct keyFrame {

	Vec2 offset = Vec2{0.0f,0.0f};
	Vec2 size = Vec2{0.f,0.f};
	float time = 0.f;

};

class Texture;	

class Animation : public ResourceBase
{

	using Super = ResourceBase;

public:
	Animation();
	virtual ~Animation();
	virtual void Load(const wstring& path) override;
	virtual void Save(const wstring& path) override;

	void SetLoop(bool loop) { _loop = loop; }
	bool isLoop() { return _loop; }
	
	void SetTexture(shared_ptr<Texture> texture) { _texture = texture; }

	shared_ptr<Texture> GetTexture() { return _texture; }
	Vec2 GetTextureSize() { return _texture->GetSize(); }

	const keyFrame& GetKeyFrame(int32 index);
	int32 GetKeyFrameCount();
	void AddKeyFrame(const keyFrame& keyframe);




private:
	shared_ptr<Texture> _texture;
	vector<keyFrame> _keyFrames;
	bool _loop = false;






};

