//-------------------------------------------
//
//		fbxモデルクラス 
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once

//インクルード
#include "Mesh.h"
#include <fbxsdk.h>
#include <vector>
#include"Colision.h"

//定数宣言
#define MAX_REF_POLYGON  60


//3Dデータ用構造体
struct Vertex_3D
{
	XMFLOAT3 Pos;
	XMFLOAT3 Normal;
	XMFLOAT2 Tex;
	int   Boneindex[4];
	float weightBone[4];
	Vertex_3D()
	{
		for (int i = 0; i < 4; i++)
		{
			Boneindex[i] = 0;
			weightBone[i] = 0.0;
		}
	}

};

//３Dモデル用コンスタントバッファ定義
struct CONSTANT_BUFFER_3D
{
	XMMATRIX W;
	XMMATRIX WVP;

};

//マテリアル用コンスタントバッファ定義
struct CONSTANT_BUFFER_3D_MAT
{
	XMFLOAT4 Diffuse;
	XMFLOAT4 Ambient;
	XMFLOAT4 Specular;
	XMFLOAT4 Emmisive;

};

//ボーン用構造体
struct Bone
{
	XMFLOAT4X4 BindPose;
	XMFLOAT4X4 NewPose;
	const char* name;
	FbxCluster* Cluster;
	Bone() {
	   DirectX::XMStoreFloat4x4(&BindPose, XMMatrixIdentity());
		NewPose = BindPose;
	}
};

//マテリアル用構造体
struct MATRIAL
{
	char* matName;
	XMFLOAT4 Difuse, Ambient, Specular, Emmisive;
	ID3D11ShaderResourceView* Texture;
	DWORD NumFace;
	bool  usetex = false;

};

//モデル情報用構造体
struct Mesh_deta
{
	MATRIAL* m;
	ID3D11Buffer*  vertexBuffer;
	ID3D11Buffer** indexBuffer;
	DWORD NumFace, Numvert, NumUV, matnum;

};

//頂点インデックス用構造体
struct polyTable
{
	int PolygonIndex[MAX_REF_POLYGON], index123[MAX_REF_POLYGON];
	int NumRef;

	polyTable()
	{
		ZeroMemory(PolygonIndex, sizeof(PolygonIndex));
		ZeroMemory(index123, sizeof(index123));
		NumRef = 0;
	}
};

//アニメーションデータ用構造体
struct anime_flame
{
	int Flamenum, Flamestert;
	bool useanime;
	anime_flame() { useanime = false; Flamenum = Flamestert = 0; }

};

//アニメーションデータ用構造体
struct anime_dat
{
	int animecount, nowanime, nowflame;
	bool setanime = false;
	anime_dat() { animecount = nowanime = nowflame = 0; }

};

namespace F_lib_Render
{
	//前方宣言
	class Mesh_Fbx;

	//Mesh_Fbx_animeクラス-----------------------------------------

	//Mesh_Fbx_animeクラス　
	//クラスメンバ
	class Mesh_Fbx_anime
	{
		friend Mesh_Fbx;
	public:
		Mesh_Fbx_anime(FbxImporter*);
		Mesh_Fbx_anime(Mesh_Fbx_anime*);

		void setanime(int _animeid = -1, bool arry = false);
		bool getuseanime(int _id);
		int  getmaxanimefleme(int _id);
		int  getanimefureme(int);

	private:
		anime_flame* animeflame;
		anime_dat anime;
		bool useanime;
	};


	//-----------------------------------------

	//Mesh_Fbxクラス-----------------------------------------

	//Mesh_Fbxクラス 継承->Mesh
	//クラスメンバ
	class Mesh_Fbx : public Mesh
	{
		friend Mesh_Fbx_anime;
	public:
		Mesh_Fbx(ID3D11Device* _Device, ID3D11DeviceContext* _DeviceContext,class Camera* _Camera, class Light_Point*);
		~Mesh_Fbx();
		HRESULT InitModel(const char*, F_lib_Mover::Colision_3D* _col = nullptr);

		void Draw() override;
		void RDraw();
		void addposDraw(Mesh_Fbx*, int);

		void setColdate();
		void setanime(int _animeid = -1, bool arry = false);
		void setanime(Mesh_Fbx_anime*);
		void setWorld(XMMATRIX);
		void setRenderingEngine(class RenderingEngine* _engine) { Engine = _engine; }

		XMMATRIX getWorld() { return World; }
		XMMATRIX getBonePos(int);
		XMFLOAT3 getBoneBind(int);
		int getBoneNum() { return BoneNum; }

		F_lib_Mover::Colision_3D* getCol() { return (Col != nullptr) ? Col : nullptr; }
		Mesh_Fbx_anime* getanime();

		bool getuseanime(int _id);
		int  getmaxanimefleme(int _id);
		int  getanimefureme(int);

	private:
		HRESULT InitConstantBuffer();
		void update();
		void render();
		void createvertex(FbxMesh*, bool _useSkin = false);
		void createindexBuffer(DWORD dwSize, int* pIndex, ID3D11Buffer** ppIndexBuffer);
		void pointnode(FbxNode* _node, std::vector<FbxMesh*> &_nodeMeshlist);
		void getSkininfo(FbxMesh*, Vertex_3D*, polyTable*);
		void updateBonemtx();
		void createColision(Vertex_3D*, int _num = 0, int id = 0);

		class RenderingEngine* Engine;
		F_lib_Mover::Colision_3D* Col;
		class Light_Point* light;
		Mesh_Fbx_anime* master, *sreve;

		ID3D11Buffer* ConstantBuffer1;
		ID3D11Buffer* ConstantBufferBone;

		XMMATRIX World, perentWorld;
		Mesh_deta meshdeta;
		Bone* Bonelist;

		XMFLOAT3 pPos, psize;

		int BoneNum, meshNum;
		bool perent = false;

	};

	//-----------------------------------------
}