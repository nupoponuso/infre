//-------------------------------------------
//
//		fbxモデルクラス 
//		auhor: hujioka tomoya
//		
//-------------------------------------------


//インクルード
#include "Mesh_Fbxmodel.h"
#include "texture.h"
#include "RenderingEngine.h"
#include "Light.h"
#include "Colision.h"


//定数宣言
#define BONE_MAX (128)

//ボーン行列のコンスタントバッファ定義
struct CONSTANT_BUFFER_BONE
{
	XMMATRIX Bone[BONE_MAX];
	CONSTANT_BUFFER_BONE()
	{
		for (int i = 0; i < BONE_MAX; i++) Bone[i] = XMMatrixIdentity();
	}

};




namespace F_lib_Render
{
	using namespace F_lib_Mover;


	//Mesh_Fbxクラス-----------------------------------------

	//コンストラクタ
	//値の初期化
	Mesh_Fbx::Mesh_Fbx(ID3D11Device* _Device, ID3D11DeviceContext* _DeviceContext,Camera* _Camera, Light_Point*_light) : Mesh(_Device, _DeviceContext, _Camera), Col(nullptr), light(_light), Engine(nullptr)
	{}


	//デストラクタ
	Mesh_Fbx::~Mesh_Fbx()
	{
		SAFE_RELEASE(ConstantBuffer1);
		SAFE_RELEASE(ConstantBufferBone);
		SAFE_RELEASE(meshdeta.vertexBuffer);
		for (unsigned int i = 0; i < meshdeta.matnum; i++)
		{
			SAFE_RELEASE(meshdeta.indexBuffer[i]);
		}

	}


	//initmodel関数
	//引数のfbxファイル名からモデル情報を取り出す　ついでに当たり判定の設定もする
	HRESULT Mesh_Fbx::InitModel(const char* fbxfilename, F_lib_Mover::Colision_3D* _col)
	{
		Col = _col;

		FbxManager* fbxManager = FbxManager::Create();
		FbxScene* fbxScene = FbxScene::Create(fbxManager, "fbxscene");
		FbxString FileName(fbxfilename);
		FbxImporter *fbxImporter = FbxImporter::Create(fbxManager, "imp");

		if (!fbxImporter->Initialize(FileName.Buffer()))
		{
			MessageBoxA(0, "FBXファイルがないよ", fbxfilename, MB_OK);
			return S_OK;
		}

		fbxImporter->Import(fbxScene);

		master = new Mesh_Fbx_anime(fbxImporter);
		//FbxAxisSystem::DirectX.ConvertScene(fbxScene);

		FbxNode* rootnode = fbxScene->GetRootNode();
		std::vector<FbxMesh*> meshlist;

		pointnode(rootnode, meshlist);

		createvertex(meshlist[0]);
		InitConstantBuffer();

		setanime(0);

		return S_OK;
	}


	//InitShader関数
	//シェーダーのロード　シェーダーに送る頂点情報などを設定する
	HRESULT Mesh_Fbx::InitConstantBuffer()
	{

		//コンスタントバッファー作成　ここでは変換行列渡し用
		D3D11_BUFFER_DESC cb;
		cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cb.ByteWidth = sizeof(CONSTANT_BUFFER_3D);
		cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cb.MiscFlags = 0;
		cb.Usage = D3D11_USAGE_DYNAMIC;

		if (FAILED(Device->CreateBuffer(&cb, nullptr, &ConstantBuffer)))
			return E_FAIL;

		//コンスタントバッファー作成　ここではマテリアル渡し用
		cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cb.ByteWidth = sizeof(CONSTANT_BUFFER_3D_MAT);
		cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cb.MiscFlags = 0;
		cb.Usage = D3D11_USAGE_DYNAMIC;

		if (FAILED(Device->CreateBuffer(&cb, nullptr, &ConstantBuffer1)))
			return E_FAIL;


		D3D11_SAMPLER_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		Device->CreateSamplerState(&sd, &SamplerState);

		return S_OK;
	}


	//getBonePos関数
	//ボーンのマトリックスを取り出す
	XMMATRIX Mesh_Fbx::getBonePos(int i)
	{
		XMMATRIX inv;
		XMFLOAT4X4 ret;
		inv = XMMatrixInverse(0, XMLoadFloat4x4(&Bonelist[i].BindPose));
		XMStoreFloat4x4(&ret, inv * XMLoadFloat4x4(&Bonelist[i].NewPose));

		inv = XMLoadFloat4x4(&ret);

		update();
		inv *= World;

		return inv;
	}


	//getBoneBind関数
	//バインドポーズのボーンの位置情報を取り出す	
	XMFLOAT3 Mesh_Fbx::getBoneBind(int i)
	{
		XMFLOAT4X4 rets;
		XMStoreFloat4x4(&rets, XMLoadFloat4x4(&Bonelist[i].BindPose));
		return XMFLOAT3(rets._41, rets._42, rets._43);
	}


	Mesh_Fbx_anime * Mesh_Fbx::getanime()
	{
		if (sreve == nullptr)
			return master;
		else
			return sreve;

	}


	//getuseanime関数
	//マスターデータの指定したアニメーションが再生中か取得する
	bool Mesh_Fbx::getuseanime(int _id)
	{
		return master->getuseanime(_id);

	}


	//getmaxanimefleme関数
	//マスターデータの各アニメーションの最大フレームを取得する
	int Mesh_Fbx::getmaxanimefleme(int _id)
	{
		return  master->getmaxanimefleme(_id);
	}


	//getanimefureme関数
	//マスターデータの初期フレームを取得する
	int Mesh_Fbx::getanimefureme(int _id)
	{
		return master->getanimefureme(_id);
	}


	//Draw関数
	//通常のレンダリング
	void Mesh_Fbx::Draw()
	{
		//使用するシェーダーのセット
		DeviceContext->VSSetShader(Shader->getVertexShader(), nullptr, 0);
		DeviceContext->PSSetShader(Shader->getPixelShader(), nullptr, 0);
		DeviceContext->PSSetSamplers(0, 1, &SamplerState);

		update();
		render();

		if (sreve == nullptr)
			master->useanime = false;
		else
		{
			sreve->useanime = false;
			sreve = nullptr;
		}

	}


	//
	void Mesh_Fbx::RDraw()
	{
		update();
		Engine->addRenderList_3D(this);

		if (sreve == nullptr)
			master->useanime = false;
		else
		{
			sreve->useanime = false;
			sreve = nullptr;
		}

	}


	//setanime関数
	//マスターデータのアニメーションのインデックスを設定する
	void Mesh_Fbx::setanime(int _animeid, bool arry)
	{
		master->useanime = true;
		if (BoneNum > 0)
			master->setanime(_animeid, arry);

	}


	//setanime関数
	//スレイブのアニメーションデータを設定する
	void Mesh_Fbx::setanime(Mesh_Fbx_anime * _anime)
	{
		if (BoneNum > 0)
		{
			sreve = _anime;
			sreve->useanime = true;

		}

	}

	void Mesh_Fbx::setWorld(XMMATRIX _world)
	{
		World = _world;

	}


	//addposDraw関数
	//主に指定したボーンの原点に移動して自身を描画する関数
	void Mesh_Fbx::addposDraw(Mesh_Fbx* _pearent, int _boneid)
	{
		perent = true;

		perentWorld = _pearent->getBonePos(_boneid);
		pPos = _pearent->getBoneBind(_boneid);
		psize = _pearent->getsize();

		Draw();
		perent = false;

	}


	//update関数
	//world行列の更新など
	void Mesh_Fbx::update()
	{
		World = XMMatrixScaling(Size.x, Size.y, Size.z);
		World *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(angle.x), XMConvertToRadians(angle.y), XMConvertToRadians(angle.z));

		if (perent)
		{
			World *= XMMatrixTranslation(pPos.x + Position.x, pPos.y + Position.y, pPos.z + Position.z);
			World *= perentWorld;
		}
		else World *= XMMatrixTranslation(Position.x, Position.y, Position.z);

		setColdate();

	}


	//render関数
	//自身に設定されている情報から自身を描画する
	void Mesh_Fbx::render()
	{
		if (BoneNum > 0) updateBonemtx();

		//プリミティブ・トポロジーをセット
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//頂点インプットレイアウトをセット
		DeviceContext->IASetInputLayout(Shader->getVertexLayout());

		UINT stride = sizeof(Vertex_3D);
		UINT offset = 0;
		DeviceContext->IASetVertexBuffers(0, 1, &meshdeta.vertexBuffer, &stride, &offset);

		XMMATRIX View, Proj, Lght;
		View = camera->GetView();
		Proj = camera->GetProj();
		Lght = light->getLight();

		//シェーダーのコンスタントバッファーに各種データを渡す
		D3D11_MAPPED_SUBRESOURCE pData;
		CONSTANT_BUFFER_3D cb;
		if (SUCCEEDED(DeviceContext->Map(ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			//ワールド、カメラ、射影行列を渡す
			cb.W = XMMatrixTranspose(World);
			cb.WVP = World * View * Proj;
			cb.WVP = XMMatrixTranspose(cb.WVP);

			memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(CONSTANT_BUFFER_3D));
			DeviceContext->Unmap(ConstantBuffer, 0);
		}

		DeviceContext->VSSetConstantBuffers(1, 1, &ConstantBuffer);
		DeviceContext->PSSetConstantBuffers(1, 1, &ConstantBuffer);

		for (DWORD i = 0; i < meshdeta.matnum; i++)
		{
			CONSTANT_BUFFER_3D_MAT cm;
			if (SUCCEEDED(DeviceContext->Map(ConstantBuffer1, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
			{
				//ワールド、カメラ、射影行列を渡す
				cm.Ambient = meshdeta.m[i].Ambient;
				cm.Diffuse = meshdeta.m[i].Difuse;
				cm.Emmisive = meshdeta.m[i].Emmisive;

				memcpy_s(pData.pData, pData.RowPitch, (void*)(&cm), sizeof(CONSTANT_BUFFER_3D_MAT));
				DeviceContext->Unmap(ConstantBuffer1, 0);
			}

			//このコンスタントバッファーをどのシェーダーで使うか
			DeviceContext->VSSetConstantBuffers(2, 1, &ConstantBuffer1);
			DeviceContext->PSSetConstantBuffers(2, 1, &ConstantBuffer1);

			DeviceContext->IASetIndexBuffer(meshdeta.indexBuffer[i], DXGI_FORMAT_R32_UINT, 0);

			if (meshdeta.m[i].usetex) DeviceContext->PSSetShaderResources(0, 1, &meshdeta.m[i].Texture);

			//プリミティブをレンダリング
			DeviceContext->DrawIndexed(meshdeta.m[i].NumFace * 3, 0, 0);
		}

	}


	//createvertex関数
	//FbxMeshクラスの実体から頂点情報、マテリアル情報を取り出す
	void Mesh_Fbx::createvertex(FbxMesh * _mesh, bool _useSkin)// , const char* _name)
	{
		meshdeta.NumFace = _mesh->GetPolygonCount();
		meshdeta.Numvert = _mesh->GetControlPointsCount();
		meshdeta.NumUV = _mesh->GetTextureUVCount();

		if (meshdeta.NumFace == 0 || meshdeta.Numvert == 0) return;

		Vertex_3D* pvVB = new Vertex_3D[(meshdeta.Numvert < meshdeta.NumUV) ? meshdeta.NumUV : meshdeta.Numvert];

		// ポリゴンごとに頂点読み込み、法線読み込み、UV読み込み
		FbxVector4 Normal, Coord;
		int index, UVindex, iStartIndex, iIndex0, iIndex1, iIndex2;
		int* piIndex;

		FbxVector2 v2;
		FbxGeometryElementUV* pUV = nullptr;
		FbxLayerElement::EMappingMode	eMapMode = FbxLayerElement::eNone;
		FbxLayerElement::EReferenceMode eRefMode = FbxLayerElement::eDirect;

		const FbxLayerElementArrayTemplate<int>*		pUVIndex = nullptr;
		const FbxLayerElementArrayTemplate<FbxVector2>* pUVDirect = nullptr;

		if (meshdeta.NumUV) {
			pUV = _mesh->GetElementUV();
			eMapMode = pUV->GetMappingMode();
			eRefMode = pUV->GetReferenceMode();
			pUVIndex = &pUV->GetIndexArray();
			pUVDirect = &pUV->GetDirectArray();
		}

		bool bPolygonVertex = (meshdeta.NumUV && eMapMode == FbxLayerElement::eByPolygonVertex);

		for (DWORD i = 0; i < meshdeta.NumFace; ++i) {
			if (meshdeta.Numvert < meshdeta.NumUV) {	// UV数のほうが多い場合は本来の(頂点ベース)インデックスを利用しない。UVインデックスを基準にする
				iIndex0 = _mesh->GetTextureUVIndex(i, 0);
				iIndex1 = _mesh->GetTextureUVIndex(i, 1);
				iIndex2 = _mesh->GetTextureUVIndex(i, 2);
				if (iIndex0 < 0 || iIndex1 < 0 || iIndex2 < 0) {
					// エラー時は単純にスキップ
					continue;
				}
			}
			else {
				iStartIndex = _mesh->GetPolygonVertexIndex(i);
				piIndex = _mesh->GetPolygonVertices();	//（頂点インデックス）読み込み
				iIndex0 = piIndex[iStartIndex + 0];
				iIndex1 = piIndex[iStartIndex + 1];
				iIndex2 = piIndex[iStartIndex + 2];
			}
			// 頂点
			index = _mesh->GetPolygonVertex(i, 0);
			Coord = _mesh->GetControlPointAt(index);
			pvVB[iIndex0].Pos.x = static_cast<float>(-Coord[0]);
			pvVB[iIndex0].Pos.y = static_cast<float> (Coord[1]);
			pvVB[iIndex0].Pos.z = static_cast<float> (Coord[2]);

			index = _mesh->GetPolygonVertex(i, 1);
			Coord = _mesh->GetControlPointAt(index);
			pvVB[iIndex1].Pos.x = static_cast<float>(-Coord[0]);
			pvVB[iIndex1].Pos.y = static_cast<float> (Coord[1]);
			pvVB[iIndex1].Pos.z = static_cast<float> (Coord[2]);

			index = _mesh->GetPolygonVertex(i, 2);
			Coord = _mesh->GetControlPointAt(index);
			pvVB[iIndex2].Pos.x = static_cast<float>(-Coord[0]);
			pvVB[iIndex2].Pos.y = static_cast<float> (Coord[1]);
			pvVB[iIndex2].Pos.z = static_cast<float> (Coord[2]);
			// 法線
			_mesh->GetPolygonVertexNormal(i, 0, Normal);
			pvVB[iIndex0].Normal.x = static_cast<float>(-Normal[0]);
			pvVB[iIndex0].Normal.y = static_cast<float> (Normal[1]);
			pvVB[iIndex0].Normal.z = static_cast<float> (Normal[2]);

			_mesh->GetPolygonVertexNormal(i, 1, Normal);
			pvVB[iIndex1].Normal.x = static_cast<float>(-Normal[0]);
			pvVB[iIndex1].Normal.y = static_cast<float> (Normal[1]);
			pvVB[iIndex1].Normal.z = static_cast<float> (Normal[2]);

			_mesh->GetPolygonVertexNormal(i, 2, Normal);
			pvVB[iIndex2].Normal.x = static_cast<float>(-Normal[0]);
			pvVB[iIndex2].Normal.y = static_cast<float> (Normal[1]);
			pvVB[iIndex2].Normal.z = static_cast<float> (Normal[2]);

			// テクスチャ座標
			if (bPolygonVertex) {
				// UVマッピングモードがByPolygonVertexの時
				UVindex = _mesh->GetTextureUVIndex(i, 0);
				v2 = pUVDirect->GetAt(UVindex);
				pvVB[iIndex0].Tex.x = static_cast<float>(v2[0]);
				pvVB[iIndex0].Tex.y = static_cast<float>(1.0 - v2[1]);

				UVindex = _mesh->GetTextureUVIndex(i, 1);
				v2 = pUVDirect->GetAt(UVindex);
				pvVB[iIndex1].Tex.x = static_cast<float>(v2[0]);
				pvVB[iIndex1].Tex.y = static_cast<float>(1.0 - v2[1]);

				UVindex = _mesh->GetTextureUVIndex(i, 2);
				v2 = pUVDirect->GetAt(UVindex);
				pvVB[iIndex2].Tex.x = static_cast<float>(v2[0]);
				pvVB[iIndex2].Tex.y = static_cast<float>(1.0 - v2[1]);
			}
		}

		// テクスチャ座標
		if (meshdeta.NumUV && eMapMode == FbxLayerElement::eByControlPoint) {
			// UVマッピングモードがByControlPointの時
			for (DWORD k = 0; k < meshdeta.NumUV; ++k) {
				if (eRefMode == FbxLayerElement::eIndexToDirect) {
					index = pUVIndex->GetAt(k);
				}
				else {
					index = k;
				}
				v2 = pUVDirect->GetAt(index);
				pvVB[k].Tex.x = static_cast<float>(v2[0]);
				pvVB[k].Tex.y = static_cast<float>(1.0 - v2[1]);
			}
		}


		FbxNode* pNode = _mesh->GetNode();
		meshdeta.matnum = pNode->GetMaterialCount();
		meshdeta.m = new MATRIAL[meshdeta.matnum];
		meshdeta.indexBuffer = new ID3D11Buffer*[meshdeta.matnum];

		FbxDouble3 Color, Alpha;
		FbxDouble Factor, AlphaFactor;

		for (DWORD i = 0; i < meshdeta.matnum; i++)
		{
			FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);

			if (pMaterial->GetClassId().Is(FbxSurfacePhong::ClassId)) {
				FbxSurfacePhong* pPhong = (FbxSurfacePhong*)pMaterial;

				//環境光
				Color = pPhong->Ambient.Get();
				Factor = pPhong->AmbientFactor.Get();
				meshdeta.m[i].Ambient.x = static_cast<float>(Color[0] * Factor);
				meshdeta.m[i].Ambient.y = static_cast<float>(Color[1] * Factor);
				meshdeta.m[i].Ambient.z = static_cast<float>(Color[2] * Factor);
				meshdeta.m[i].Ambient.w = 0.0f;

				// 拡散反射光
				Color = pPhong->Diffuse.Get();
				Factor = pPhong->DiffuseFactor.Get();
				Alpha = pPhong->TransparentColor.Get();
				AlphaFactor = pPhong->TransparencyFactor.Get();
				meshdeta.m[i].Difuse.x = static_cast<float>(Color[0] * Factor);
				meshdeta.m[i].Difuse.y = static_cast<float>(Color[1] * Factor);
				meshdeta.m[i].Difuse.z = static_cast<float>(Color[2] * Factor);
				meshdeta.m[i].Difuse.w = static_cast<float>(1.0 - Alpha[0] * AlphaFactor);

				//鏡面反射光
				Color = pPhong->Specular.Get();
				Factor = pPhong->SpecularFactor.Get();
				AlphaFactor = pPhong->Shininess.Get();
				meshdeta.m[i].Specular.x = static_cast<float>(Color[0] * Factor);
				meshdeta.m[i].Specular.y = static_cast<float>(Color[1] * Factor);
				meshdeta.m[i].Specular.z = static_cast<float>(Color[2] * Factor);
				meshdeta.m[i].Specular.w = static_cast<float>(AlphaFactor);

				//発光色
				Color = pPhong->Emissive.Get();
				Factor = pPhong->EmissiveFactor.Get();
				meshdeta.m[i].Emmisive.w = static_cast<float>(Factor);
				meshdeta.m[i].Emmisive.x = static_cast<float>(Color[0] * Factor);
				meshdeta.m[i].Emmisive.y = static_cast<float>(Color[1] * Factor);
				meshdeta.m[i].Emmisive.z = static_cast<float>(Color[2] * Factor);

			}
			else if (pMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId)) {
				FbxSurfaceLambert* pLambert = (FbxSurfaceLambert*)pMaterial;

				// 環境光
				Color = pLambert->Ambient.Get();
				Factor = pLambert->AmbientFactor.Get();
				meshdeta.m[i].Ambient.x = static_cast<float>(Color[0] * Factor);
				meshdeta.m[i].Ambient.y = static_cast<float>(Color[1] * Factor);
				meshdeta.m[i].Ambient.z = static_cast<float>(Color[2] * Factor);
				meshdeta.m[i].Ambient.w = 0.0f;

				// 拡散反射光
				Color = pLambert->Diffuse.Get();
				Factor = pLambert->DiffuseFactor.Get();
				Alpha = pLambert->TransparentColor.Get();
				AlphaFactor = pLambert->TransparencyFactor.Get();
				meshdeta.m[i].Difuse.x = static_cast<float>(Color[0] * Factor);
				meshdeta.m[i].Difuse.y = static_cast<float>(Color[1] * Factor);
				meshdeta.m[i].Difuse.z = static_cast<float>(Color[2] * Factor);
				meshdeta.m[i].Difuse.w = static_cast<float>(1.0 - Alpha[0] * AlphaFactor);
				// 発光色
				Color = pLambert->Emissive.Get();
				Factor = pLambert->EmissiveFactor.Get();
				meshdeta.m[i].Emmisive.w = static_cast<float>(Factor);
				meshdeta.m[i].Emmisive.x = static_cast<float>(Color[0] * Factor);
				meshdeta.m[i].Emmisive.y = static_cast<float>(Color[1] * Factor);
				meshdeta.m[i].Emmisive.z = static_cast<float>(Color[2] * Factor);


			}

			FbxProperty lProperty;
			lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
			int lTextureCount = lProperty.GetSrcObjectCount<FbxFileTexture>();
			FbxFileTexture* lFileTexture = nullptr;
			char* pszFName = nullptr;
			size_t uFName = 0;
			for (int j = 0; j < lTextureCount; ++j) {
				lFileTexture = lProperty.GetSrcObject<FbxFileTexture>(j);
				if (!lFileTexture)
					continue;
				FbxUTF8ToAnsi(lFileTexture->GetRelativeFileName(), pszFName, &uFName);
				break;	// 先頭の1つだけ読み込む
			}

			if (pszFName) {
				// テクスチャ作成
				CreateTextureFromFile(Device, pszFName, &meshdeta.m[i].Texture);
				FbxFree(pszFName);
				pszFName = nullptr;

				uFName = 0;
				FbxUTF8ToAnsi(lFileTexture->GetFileName(), pszFName, &uFName);
				if (FAILED(CreateTextureFromFile(Device, pszFName, &meshdeta.m[i].Texture))) {
					char fname[_MAX_PATH];
					char ext[_MAX_EXT];
					_splitpath_s(pszFName, nullptr, 0, nullptr, 0,
						fname, _countof(fname), ext, _countof(ext));
					strcat_s(fname, _countof(fname), ext);
					if (FAILED(CreateTextureFromFile(Device, fname, &meshdeta.m[i].Texture))) {
						MessageBoxA(0, "テクスチャ読み込み失敗", fname, MB_OK);
						delete[] pvVB;

					}
				}
				if (pszFName) {
					FbxFree(pszFName);
					pszFName = nullptr;

				}
				meshdeta.m[i].usetex = true;

			}

			if (meshdeta.m[i].usetex)meshdeta.m[i].Ambient.w = 1.0;

			// マテリアルの数だけインデックスバッファを作成
			int* pIndex = new int[meshdeta.NumFace * 3];	// とりあえず、メッシュ内のポリゴン数でメモリ確保 (個々のポリゴングループはかならずこれ以下になる)
			int iCount = 0;					// そのマテリアルであるインデックス配列内の開始インデックスを調べる　さらにインデックスの個数も調べる

			for (DWORD k = 0; k < meshdeta.NumFace; ++k) {
				FbxLayerElementMaterial* mat = _mesh->GetLayer(0)->GetMaterials();	// レイヤーが1枚だけを想定
				int matId = mat->GetIndexArray().GetAt(k);



				if (matId == i) {
					if (meshdeta.Numvert < meshdeta.NumUV) {
						pIndex[iCount] = _mesh->GetTextureUVIndex(k, 0, FbxLayerElement::eTextureDiffuse);
						pIndex[iCount + 1] = _mesh->GetTextureUVIndex(k, 1, FbxLayerElement::eTextureDiffuse);
						pIndex[iCount + 2] = _mesh->GetTextureUVIndex(k, 2, FbxLayerElement::eTextureDiffuse);

					}
					else {
						pIndex[iCount] = _mesh->GetPolygonVertex(k, 0);
						pIndex[iCount + 1] = _mesh->GetPolygonVertex(k, 1);
						pIndex[iCount + 2] = _mesh->GetPolygonVertex(k, 2);
					}
					iCount += 3;
				}
			}

			if (iCount > 0)
				createindexBuffer(sizeof(int)*iCount, pIndex, &meshdeta.indexBuffer[i]);

			meshdeta.m[i].NumFace = iCount / 3;	// そのマテリアル内のポリゴン数		

		}


		polyTable* PolyTable = new polyTable[meshdeta.Numvert];
		for (DWORD k = 0; k < meshdeta.NumFace; ++k) {
			for (int m = 0; m < 3; ++m) {
				int i = _mesh->GetPolygonVertex(k, m);
				if (PolyTable[i].NumRef >= MAX_REF_POLYGON) {
					delete[] PolyTable;
					delete[] pvVB;
					return;
				}
				PolyTable[i].PolygonIndex[PolyTable[i].NumRef] = k;
				PolyTable[i].index123[PolyTable[i].NumRef] = m;
				PolyTable[i].NumRef++;
			}
		}

		getSkininfo(_mesh, pvVB, PolyTable);


		// 頂点データ用バッファの設定
		if (meshdeta.Numvert < meshdeta.NumUV) meshdeta.Numvert = meshdeta.NumUV;

		if (Col != nullptr)
			createColision(pvVB);

		CD3D11_BUFFER_DESC bd_vertex(sizeof(Vertex_3D) * meshdeta.Numvert, D3D11_BIND_VERTEX_BUFFER);
		D3D11_SUBRESOURCE_DATA data_vertex;
		ZeroMemory(&data_vertex, sizeof(data_vertex));
		data_vertex.pSysMem = pvVB;

		Device->CreateBuffer(&bd_vertex, &data_vertex, &meshdeta.vertexBuffer);

	}


	//createindexBuffer関数
	//インデックスデータからインデックスバッファを作る
	void Mesh_Fbx::createindexBuffer(DWORD dwSize, int* pIndex, ID3D11Buffer** ppIndexBuffer)
	{
		// インデックスデータの取り出しとバッファの設定
		D3D11_BUFFER_DESC bd_index;
		bd_index.ByteWidth = dwSize;
		bd_index.Usage = D3D11_USAGE_DEFAULT;
		bd_index.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd_index.CPUAccessFlags = 0;
		bd_index.MiscFlags = 0;
		bd_index.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA data_index;
		data_index.pSysMem = pIndex;
		data_index.SysMemPitch = 0;
		data_index.SysMemSlicePitch = 0;

		Device->CreateBuffer(&bd_index, &data_index, ppIndexBuffer);

	}


	//pointnode関数
	//FbxNodeを再帰的に辿ってメッシュを取り出す関数
	void Mesh_Fbx::pointnode(FbxNode* _node, std::vector<FbxMesh*> &_nodeMeshlist)
	{

		int artribute = _node->GetNodeAttributeCount();
		int NodeChild = _node->GetChildCount();
		int myindex = -1;

		for (int i = 0; i < artribute; i++)
		{
			FbxNodeAttribute* attribute = _node->GetNodeAttributeByIndex(i);
			const char* nodename = _node->GetName();

			if (attribute->GetAttributeType() == FbxNodeAttribute::eMesh)
				_nodeMeshlist.push_back(_node->GetMesh());

		}

		for (int i = 0; i < NodeChild; i++)
			pointnode(_node->GetChild(i), _nodeMeshlist);


	}


	//getSkininfo関数
	//FbxMeshクラスからボーンの情報を取り出しスキンメッシュの準備をする
	void Mesh_Fbx::getSkininfo(FbxMesh* _mesh, Vertex_3D* _pvVB, polyTable* _polygonteble)
	{
		int nSkinCount = _mesh->GetDeformerCount(FbxDeformer::eSkin);
		if (nSkinCount == 0) return;

		FbxSkin* Skin = (FbxSkin*)_mesh->GetDeformer(0);
		BoneNum = Skin->GetClusterCount();
		Bonelist = new Bone[BoneNum];

		Vertex_3D* _bvp = 0;
		int Colboxindex = 0;

		for (int i = 0; i < BoneNum; i++)
			Bonelist[i].Cluster = Skin->GetCluster(i);

		XMFLOAT4X4 m(
			-1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		for (int i = 0; i < BoneNum; ++i) {
			FbxAMatrix mtx;
			Bonelist[i].Cluster->GetTransformLinkMatrix(mtx);
			for (int x = 0; x < 4; ++x) {
				for (int y = 0; y < 4; ++y) {
					Bonelist[i].BindPose(y, x) = (float)mtx.Get(y, x);
				}
			}
			XMStoreFloat4x4(&Bonelist[i].BindPose,
				XMLoadFloat4x4(&Bonelist[i].BindPose) * XMLoadFloat4x4(&m));
		}

		if (meshdeta.Numvert >= meshdeta.NumUV)
		{
			for (int i = 0; i < BoneNum; i++)
			{
				int indexNum = Bonelist[i].Cluster->GetControlPointIndicesCount();
				int* iIndex = Bonelist[i].Cluster->GetControlPointIndices();
				double* Weight = Bonelist[i].Cluster->GetControlPointWeights();

				for (int k = 0; k < indexNum; ++k)
				{
					int m;
					for (m = 0; m < 4; ++m) {
						if (_pvVB[iIndex[k]].Boneindex[m] == i) {
							if (i == 0 && _pvVB[iIndex[k]].weightBone[m] <= 0.0f) {
								continue;
							}
							break;
						}
					}
					if (m < 4) continue;	// 設定済ならスキップ
					for (m = 0; m < 4; ++m) {	// 5本以上の場合は、重みの大きい順に4本に絞る
						if (Weight[k] > _pvVB[iIndex[k]].weightBone[m]) {
							for (int n = 4 - 1; n > m; --n) {
								_pvVB[iIndex[k]].Boneindex[n] = _pvVB[iIndex[k]].Boneindex[n - 1];
								_pvVB[iIndex[k]].weightBone[n] = _pvVB[iIndex[k]].weightBone[n - 1];
							}
							_pvVB[iIndex[k]].Boneindex[m] = i;
							_pvVB[iIndex[k]].weightBone[m] = static_cast<float>(Weight[k]);
							break;
						}
					}

				}

			}

		}
		else
		{
			int PolyIndex = 0, UVIndex = 0;

			for (int i = 0; i < BoneNum; ++i)
			{
				int indexNum = Bonelist[i].Cluster->GetControlPointIndicesCount();
				int* iIndex = Bonelist[i].Cluster->GetControlPointIndices();
				double* Weight = Bonelist[i].Cluster->GetControlPointWeights();


				if (Col != nullptr&&Col->Bboxnum != 1)
				{
					_bvp = new Vertex_3D[indexNum];

					for (int bi = 1; bi < Col->Bboxnum; bi++)
						if (i == Col->box[bi].boneindex)Colboxindex = bi;

				}

				// 頂点側からインデックスをたどって、頂点サイドで整理する
				for (int k = 0; k < indexNum; ++k) {
					// その頂点を含んでいるポリゴンすべてに、このボーンとウェイトを適用
					for (int p = 0; p < _polygonteble[iIndex[k]].NumRef; ++p) {
						// 頂点→属すポリゴン→そのポリゴンのUVインデックス と逆引き
						PolyIndex = _polygonteble[iIndex[k]].PolygonIndex[p];
						UVIndex = _mesh->GetTextureUVIndex(PolyIndex, _polygonteble[iIndex[k]].index123[p], FbxLayerElement::eTextureDiffuse);
						if (UVIndex < 0) continue;
						int m;
						for (m = 0; m < 4; ++m) {
							if (_pvVB[UVIndex].Boneindex[m] == i) {
								if (i == 0 && _pvVB[UVIndex].weightBone[m] <= 0.0f) {
									continue;
								}
								break;
							}
						}
						if (m < 4) continue;	// 設定済ならスキップ
						for (m = 0; m < 4; ++m) {	// 5本以上の場合は、重みの大きい順に4本に絞る
							if (Weight[k] > _pvVB[UVIndex].weightBone[m]) {
								for (int n = 4 - 1; n > m; --n) {
									_pvVB[UVIndex].Boneindex[n] = _pvVB[UVIndex].Boneindex[n - 1];
									_pvVB[UVIndex].weightBone[n] = _pvVB[UVIndex].weightBone[n - 1];
								}
								_pvVB[UVIndex].Boneindex[m] = i;
								_pvVB[UVIndex].weightBone[m] = static_cast<float>(Weight[k]);
								break;
							}
						}
					}

					if (Col != nullptr&&Col->Bboxnum != 1)
						_bvp[k] = _pvVB[k];

				}

				if (Col != nullptr&&Col->Bboxnum != 1)
					createColision(_bvp, Colboxindex);

			}

		}

		// コンスタントバッファ ボーン用 作成
		D3D11_BUFFER_DESC cb;
		ZeroMemory(&cb, sizeof(cb));
		cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cb.ByteWidth = sizeof(CONSTANT_BUFFER_BONE);
		cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cb.MiscFlags = 0;
		cb.Usage = D3D11_USAGE_DYNAMIC;
		Device->CreateBuffer(&cb, nullptr, &ConstantBufferBone);

	}


	//updateBonemtx関数
	//指定されたアニメーションフレームからボーンマトリックスを設定する
	void Mesh_Fbx::updateBonemtx()
	{
		XMFLOAT4X4 m(
			-1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		FbxTime time;

		time.SetTime(0, 0, 0, (sreve == nullptr) ? master->anime.nowflame : sreve->anime.nowflame, 0, 0, FbxTime::eFrames60);	// 60フレーム/秒 と推定 厳密には状況ごとに調べる必要あり

		for (int i = 0; i < BoneNum; ++i) {
			FbxMatrix mtx = Bonelist[i].Cluster->GetLink()->EvaluateGlobalTransform(time);
			for (int x = 0; x < 4; ++x) {
				for (int y = 0; y < 4; ++y) {
					Bonelist[i].NewPose(y, x) = static_cast<float>(mtx.Get(y, x));
				}
			}
			XMStoreFloat4x4(&Bonelist[i].NewPose,
				XMLoadFloat4x4(&Bonelist[i].NewPose) * XMLoadFloat4x4(&m));//FBX右手座標系なのでｘが逆　補正する	
		}


		D3D11_MAPPED_SUBRESOURCE pData;
		CONSTANT_BUFFER_BONE cb;

		if (SUCCEEDED(DeviceContext->Map(ConstantBufferBone, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			for (int i = 0; i < BoneNum; i++) {
				XMMATRIX inv;
				XMFLOAT4X4 ret;
				inv = XMMatrixInverse(0, XMLoadFloat4x4(&Bonelist[i].BindPose));	// FBXのバインドポーズは初期姿勢（絶対座標）
				XMStoreFloat4x4(&ret, inv * XMLoadFloat4x4(&Bonelist[i].NewPose));
				cb.Bone[i] = XMMatrixTranspose(XMLoadFloat4x4(&ret));
			}

			memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
			DeviceContext->Unmap(ConstantBufferBone, 0);

		}

		DeviceContext->VSSetConstantBuffers(3, 1, &ConstantBufferBone);
		DeviceContext->PSSetConstantBuffers(3, 1, &ConstantBufferBone);

	}


	//createColision関数
	//取り出した頂点情報から当たり判定に必要なデータを探す
	void Mesh_Fbx::createColision(Vertex_3D* _pvB, int _num, int id)
	{
		XMFLOAT3 size[2] = { XMFLOAT3(1e10f,1e10f,1e10f),XMFLOAT3(-1e10f,-1e10f,-1e10f) };

		if (_num == 0)
		{
			for (int i = 0; i < (int)meshdeta.Numvert; i++)
			{
				size[0].x = min(size[0].x, _pvB[i].Pos.x);
				size[0].y = min(size[0].y, _pvB[i].Pos.y);
				size[0].z = min(size[0].z, _pvB[i].Pos.z);
				size[1].x = max(size[1].x, _pvB[i].Pos.x);
				size[1].y = max(size[1].y, _pvB[i].Pos.y);
				size[1].z = max(size[1].z, _pvB[i].Pos.z);

			}
		}

		Col->creatCol(size, id);

	}


	//setColdate関数
	//当たり判定に必要な情報を当たり判定クラスに埋め込む
	void Mesh_Fbx::setColdate()
	{
		if (Col != nullptr&&perent)
		{

			//if (Col->Bboxnum != 1)
			//{
			//	for (int i = 1; i < Col->Bboxnum; i++)
			//	{
			//		XMFLOAT4X4 rot;
			//		XMMATRIX mat = getBonePos(Col->box[i].boneindex);
			//		XMStoreFloat4x4(&rot, mat);
			//	
			//		Col->box[i].Colpos.x = (Col->box[i].Center.x + rot._41)* Size.x;
			//		Col->box[i].Colpos.y = (Col->box[i].Center.y + rot._42)* Size.y;
			//		Col->box[i].Colpos.z = (Col->box[i].Center.z + rot._43)* Size.z;
			//
			//		rot._41 = rot._42 = rot._43 = 0;
			//		Col->box[i].rot = XMLoadFloat4x4(&rot);
			//				 
			//		Col->box[i].Size.x = Col->box[i].size.x*Size.x;
			//		Col->box[i].Size.y = Col->box[i].size.y*Size.y;
			//		Col->box[i].Size.z = Col->box[i].size.z*Size.z;
			//
			//	}
			//
			//}

			XMFLOAT4X4 rot;
			XMStoreFloat4x4(&rot, World);
			Col->box->Colpos.x = Col->box->Center.x* psize.x* psize.x* Size.x + rot._41;// + (Position.x+pPos.x)* psize.x;//
			Col->box->Colpos.y = Col->box->Center.y* psize.y* psize.y* Size.y + rot._42;// + (Position.y+pPos.y)* psize.y;//
			Col->box->Colpos.z = Col->box->Center.z* psize.z* psize.z* Size.z + rot._43;// + (Position.z+pPos.z)* psize.z;//

			XMStoreFloat4x4(&rot, perentWorld);
			rot._41 = rot._42 = rot._43 = 0;
			Col->box->rot = XMLoadFloat4x4(&rot);
			Col->box->rot *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(angle.x), XMConvertToRadians(angle.y), XMConvertToRadians(angle.z));

			Col->box->Size.x = (Col->box->size.x * Size.x) * psize.x;
			Col->box->Size.y = (Col->box->size.y * Size.y) * psize.y;
			Col->box->Size.z = (Col->box->size.z * Size.z) * psize.z;


		}

	}


	//-----------------------------------------

	//Mesh_Fbx_animeクラス-----------------------------------------

	//コンストラクタ
	//引数のポインタからアニメーションデータを整理する
	Mesh_Fbx_anime::Mesh_Fbx_anime(FbxImporter* _inp)
	{
		anime.animecount = _inp->GetAnimStackCount();

		if (anime.animecount != 0)
		{
			animeflame = new anime_flame[(anime.animecount < 2) ? anime.animecount : anime.animecount - 1];
			int oneFrameValue = (int)FbxTime::GetOneFrameValue(FbxTime::eFrames60);

			int stert, fin;

			for (int i = 1; i < anime.animecount; i++)
			{
				FbxTakeInfo* TakeInfo = _inp->GetTakeInfo(i);

				stert = (int)TakeInfo->mLocalTimeSpan.GetStart().Get();
				fin = (int)TakeInfo->mLocalTimeSpan.GetStop().Get();
				animeflame[i - 1].Flamenum = int((fin - stert) / oneFrameValue);

			}

			anime.animecount--;

			for (int i = 1; i < anime.animecount; i++)
				animeflame[i].Flamestert = animeflame[i - 1].Flamenum + animeflame[i - 1].Flamestert + 1;

		}

	}


	//コンストラクタ
	//引数のポインタからアニメーションデータをコピーする
	Mesh_Fbx_anime::Mesh_Fbx_anime(Mesh_Fbx_anime* _master)
	{
		anime.animecount = _master->anime.animecount;
		if (anime.animecount != 0)
		{
			animeflame = new anime_flame[anime.animecount];

			for (int i = 1; i < anime.animecount; i++)
			{
				animeflame[i].Flamestert = _master->animeflame[i].Flamestert;
				animeflame[i].Flamenum = _master->animeflame[i].Flamenum;

			}

		}

	}


	//setanime関数
	//アニメーションのインデックスを設定する
	void Mesh_Fbx_anime::setanime(int _animeid, bool arry)
	{

		if (anime.animecount == 0 || anime.animecount < _animeid) return;

		if (_animeid != -1 && anime.nowanime != _animeid && (arry || (anime.nowflame >= animeflame[anime.nowanime].Flamestert + animeflame[anime.nowanime].Flamenum)))
		{
			animeflame[anime.nowanime].useanime = false;
			anime.nowanime = _animeid;
			anime.nowflame = animeflame[anime.nowanime].Flamestert;

		}
		else if (_animeid == -1)
		{
			if (anime.nowflame >= animeflame[anime.nowanime].Flamestert + animeflame[anime.nowanime].Flamenum)
				anime.nowflame = animeflame[anime.nowanime].Flamestert;
			else
			{
				anime.nowflame++;
				animeflame[anime.nowanime].useanime = true;
			}

		}

	}


	//getuseanime関数
	//指定したアニメーションが再生中か取得する
	bool Mesh_Fbx_anime::getuseanime(int _id)
	{
		if (_id > anime.animecount) return false;

		if (!useanime) animeflame[_id].useanime = false;

		return animeflame[_id].useanime;

	}


	//getmaxanimefleme関数
	//各アニメーションの最大フレームを取得する
	int Mesh_Fbx_anime::getmaxanimefleme(int _id)
	{
		return animeflame[_id].Flamenum;
	}


	//getanimefureme関数
	//初期フレームを取得する
	int Mesh_Fbx_anime::getanimefureme(int _id)
	{
		return anime.nowflame - animeflame[_id].Flamestert;
	}

	//-----------------------------------------
}
