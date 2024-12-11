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
#pragma comment(lib,"d3dcompiler.lib")// ���̺귯�� ����ϰڴٴ� ������ ȯ�濡 ���� �ص� �ȴ�.

#ifdef _DEBUG
#pragma comment(lib,"DirectXTex\\DirectXTex_Debug.lib")
#else
#pragma comment(lib,"DirectXTex\\DirectXTex.lib")
#endif
// ���� 2���� 

// #Define CHECK(P) assert(SUCCEEDED(hr));  // ��ũ�η� ������ ũ�������� üũ 

#define CHECK(p) assert(SUCCEEDED(p))

//engine
#include "Graphics.h"

