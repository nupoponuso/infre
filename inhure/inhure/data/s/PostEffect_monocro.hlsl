Texture2D texColor : register(t0);
SamplerState samLinear : register(s0);

//グローバル
cbuffer global
{
	matrix WVP; //ワールドから射影までの変換行列
	matrix TEX;
	float4 DEF;
};

//バーテックスシェーダー出力構造体
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};


//バーテックスシェーダー/

VS_OUTPUT VS(float4 Pos : POSITION, float2 Tex : TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.Pos = mul(Pos, WVP);
	output.Tex = mul(float4(Tex, 0.0f, 1.0f), TEX).xy;

	return output;
}


//ピクセルシェーダー
//
float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 Color = DEF;

	if (TEX._44 > 0.0f)Color *= texColor.Sample(samLinear, input.Tex);

	float4 Y = 0.299*Color.r + 0.587f*Color.g + 0.114f*Color.b;
	Color.r = Color.g = Color.b = Y;

	return Color;
}
