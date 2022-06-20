//-------------------------------------------
//
//		描画用の仮想クラス 
//		auhor: hujioka tomoya
//		
//-------------------------------------------


//インクルード
#include "Mesh.h"
#include "Mesh_ShaderDat.h"
#include "Camera.h"

namespace F_lib_Render
{
	//コンストラクタ
	//値の初期化
	Mesh::Mesh(ID3D11Device * _Device, ID3D11DeviceContext * _DeviceContext, Camera* _Camera) : Device(_Device), DeviceContext(_DeviceContext), camera(_Camera)
	{
		Position = XMFLOAT3(0.0, 0.0, 0.0);
		Size = XMFLOAT3(1.0, 1.0, 1.0);

	}

}