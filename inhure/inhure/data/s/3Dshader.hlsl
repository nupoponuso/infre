
Texture2D texColor : register(t0);
Texture2D texDepth : register(t1);
SamplerState samLinear : register(s0);
SamplerState samLinear1 : register(s1);


//グローバル
cbuffer global_Light : register(b0)
{
	float4 LightPos;
	float4 eyePos;
	float4 LightAnbient;

};

cbuffer global_mtx : register(b1)
{
	matrix World;
	matrix WVP; //ワールドから射影までの変換行列

};

cbuffer global_mat : register(b2)
{
	float4 Diffuse;
	float4 Ambient;
	float4 Specular;
	float4 Emmisive;

}

cbuffer global_bone :register(b3)
{
	matrix BoneWorld[256];
};

struct VS_INPUT
{
	float3 Pos : POSITION;
	float3 nor : NORMAL;
	float2 Tex : TEXCOORD;

};

struct VS_INPUT_SKIN
{
	float3 Pos    : POSITION;
	float3 nor    : NORMAL;
	float2 Tex    : TEXCOORD;
	uint4  Bonei  : BONEINDEX;
	float4 Weight : BONEWEIGHT;

};

//バーテックスシェーダー出力構造体
struct VS_OUTPUT
{
	float4 Pos	  : SV_POSITION;
	float3 Normal : TEXCOORD0;
	float2 Tex    : TEXCOORD1;
	float3 EyeVector : TEXCOORD2;

};


struct SKIN
{
	float4 Pos;
	float3 Normal;

};

SKIN SkinVert(VS_INPUT_SKIN input)
{
	SKIN output;
	float4 Pos = float4 (input.Pos, 1.0f);
	float3 Norm = input.nor;

	if (input.Weight.x == 0.0f)
	{
		output.Pos = Pos;
		output.Normal = Norm;

	}
	else
	{
		uint  Bone = input.Bonei.x;
		float weight = input.Weight.x;
		matrix m = BoneWorld[Bone];
		output.Pos = mul(Pos, m);
		output.Normal = mul(Norm, (float3x3)m);

		Bone = input.Bonei.y;
		weight = input.Weight.y;
		m = BoneWorld[Bone];
		output.Pos += weight * mul(Pos, m);
		output.Normal += weight * mul(Norm, (float3x3)m);

		Bone = input.Bonei.z;
		weight = input.Weight.z;
		m = BoneWorld[Bone];
		output.Pos += weight * mul(Pos, m);
		output.Normal += weight * mul(Norm, (float3x3)m);

		Bone = input.Bonei.w;
		weight = input.Weight.w;
		m = BoneWorld[Bone];
		output.Pos += weight * mul(Pos, m);
		output.Normal += weight * mul(Norm, (float3x3)m);

	}

	return output;
}

//バーテックスシェーダー
VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	float4 Pos4 = float4(input.Pos, 1.0);
	output.Pos = mul(Pos4, WVP);

	output.Normal = mul((float3x3)World, input.nor);
	output.Normal = normalize(output.Normal);

	output.Tex = input.Tex;

	float3 PosWorld = mul(Pos4, World);
	output.EyeVector = float3(eyePos - PosWorld);
	output.EyeVector = normalize(output.EyeVector);
	return output;
}

//バーテックスシェーダー/
VS_OUTPUT VS_SKIN(VS_INPUT_SKIN input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	SKIN Skinned = SkinVert(input);
	output.Pos = mul(Skinned.Pos, WVP);

	output.Normal = mul((float3x3)World, input.nor);
	output.Normal = normalize(output.Normal);

	output.Tex = input.Tex;

	float3 PosWorld = mul(input.Pos, World);
	output.EyeVector = float3(eyePos - PosWorld);

	return output;
}


//ピクセルシェーダー
//
float4 PS(VS_OUTPUT input) : SV_Target
{

	float4 Color;
	if (Ambient.w > 0.0f)Color = texColor.Sample(samLinear, input.Tex);
	else 
	{
		float NL = saturate(dot(input.Normal, LightPos));
		Color = LightAnbient * Ambient + (Diffuse * NL);

	}

	if (Emmisive.w > 1.1f)
		Color.xyz += Emmisive.xyz + (Emmisive.xyz *Emmisive.w);

	return Color;
}
