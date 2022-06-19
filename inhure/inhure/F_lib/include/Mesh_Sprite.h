#pragma once
#include "Mesh.h"

typedef struct
{
	XMFLOAT3 Pos;
	XMFLOAT2 TexUV;

} Vertex_2D;

struct CONSTANT_BUFFER_2D
{
	XMMATRIX WVP;
	XMMATRIX Tex;
	XMFLOAT4 Color;
};

namespace F_lib_Render
{

	//
	class Mesh_Sprite : public Mesh
	{
	public:
		Mesh_Sprite(ID3D11Device* _Device, ID3D11DeviceContext* _DeviceContext, Camera* _Camera);
		HRESULT InitModel();

		void Draw() override;
		void RDraw(bool);

		void setTexture(ID3D11ShaderResourceView* _Texture) { Texture = _Texture; M_Tex._44 = (Texture) ? 1.0f : 0.0f; }
		void setSize(XMFLOAT2 _Size) { Size.x = _Size.x; Size.y = _Size.y; }
		void setSize(float _Size) { Size.x = Size.y = _Size; }
		void setSize(float _x, float _y) { Size.x = _x; Size.y = _y; }
		void setPosition(XMFLOAT2 _pos) { Position.x = _pos.x; Position.y = _pos.y; Position.z = 0; }
		void setPosition(float _x, float _y) { Position.x = _x; Position.y = _y; Position.z = 0; }
		void setUVF(XMFLOAT2 _uv) { textureFream = _uv; }
		void setUVF(float _u, float _v) { textureFream.x = _u; textureFream.y = _v; }
		void setUVF() { textureFream.x = 1; textureFream.y = 1; }
		void setUV(XMFLOAT2 _uv) { texureUV = _uv; }
		void setUV(float _u, float _v) { texureUV.x = _u; texureUV.y = _v; }
		void setUV() { texureUV.x = 0; texureUV.y = 0; }
		void setangle(float _angle) { angle.z = _angle; }
		void setColor(XMFLOAT4 _Color) { Color = _Color; }
		void setColor(XMFLOAT3 _Color) { Color.x = _Color.x; Color.y = _Color.y; Color.z = _Color.z; }
		void setColor(float _r, float _g, float _b) { Color.x = _r, Color.y = _g, Color.z = _b; }
		void setalph(float _a) { Color.w = _a; }
		void reset();

		void setRenderingEngine(class RenderingEngine* _engine) { Engine = _engine; }

		XMFLOAT4 getColor() { return Color; }
		XMFLOAT2 getUV() { return texureUV; }
		XMFLOAT2 getUVF() { return textureFream; }
		XMFLOAT4 getcolor() { return Color; }
		ID3D11ShaderResourceView* getTexture() { return Texture; }

	protected:
		HRESULT InitConstantBuffer();
		
		class RenderingEngine* Engine;
		XMFLOAT2 texureUV, textureFream;
		ID3D11ShaderResourceView* Texture;
		XMFLOAT4X4 M_Tex;
		XMFLOAT4 Color;

	};

}