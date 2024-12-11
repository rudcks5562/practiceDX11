#pragma once

#include "Types.h"
#include "Struct.h"
#include "Values.h"

// STL

#include<vector>
#include<list>
#include<map>
#include<unordered_map>


// WIN

#include <windows.h>
#include <assert.h>


// DX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include<DirectXMath.h>
#include<DirectXTex/DirectXTex.h>
#include<DirectXTex/DirectXTex.inl>

using namespace DirectX;
using namespace Microsoft::WRL;

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")// 라이브러리 사용하겠다는 선언은 환경에 가서 해도 된다.

#ifdef _DEBUG
#pragma comment(lib,"DirectXTex\\DirectXTex_Debug.lib")
#else
#pragma comment(lib,"DirectXTex\\DirectXTex.lib")
#endif
// 버전 2개라서 

// #Define CHECK(P) assert(SUCCEEDED(hr));  // 매크로로 게임쪽 크래시유도 체크 

#define CHECK(p) assert(SUCCEEDED(p))

//engine
#include "Graphics.h"

