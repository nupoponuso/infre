
//グローバル
cbuffer global_Light : register(b0)
{
	float4 LightPos;
	float4 eyePos;

};

cbuffer global_mtx : register(b1)
{
	matrix World;
	matrix WVP; //ワールドから射影までの変換行列
	matrix WLP;
	matrix WLPT;

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

struct VS_DEPTH_INPUT
{
	float3 Pos : POSITION;
};

struct VS_DEPTH_SKIN_INPUT
{
	float3 Pos : POSITION;
	uint4  Bonei  : BONEINDEX;
	float4 Weight : BONEWEIGHT;

};

struct SKIN
{
	float4 Pos;
	float3 Normal;

};

struct VS_DEPTH_OUTPUT
{
	float4 Pos   : SV_POSITION;
	float4 Depth : POSITION;

};


//
SKIN SkinVert(VS_DEPTH_SKIN_INPUT input)
{
	SKIN output;
	float4 Pos = float4 (input.Pos, 1.0f);

	if (input.Weight.x == 0.0f)
	{
		output.Pos = Pos;

	}
	else
	{
		uint  Bone = input.Bonei.x;
		float weight = input.Weight.x;
		matrix m = BoneWorld[Bone];
		output.Pos = mul(Pos, m);

		Bone = input.Bonei.y;
		weight = input.Weight.y;
		m = BoneWorld[Bone];
		output.Pos += weight * mul(Pos, m);

		Bone = input.Bonei.z;
		weight = input.Weight.z;
		m = BoneWorld[Bone];
		output.Pos += weight * mul(Pos, m);

		Bone = input.Bonei.w;
		weight = input.Weight.w;
		m = BoneWorld[Bone];
		output.Pos += weight * mul(Pos, m);

	}

	return output;
}


//
VS_DEPTH_OUTPUT VS_Depth(VS_DEPTH_INPUT input)
{
	VS_DEPTH_OUTPUT output = (VS_DEPTH_OUTPUT)0;
	output.Pos = mul(float4(input.Pos,1.0), WLP);
	output.Depth = output.Pos;

	return output;
}


//
VS_DEPTH_OUTPUT VS_Depth_Skin(VS_DEPTH_SKIN_INPUT input)
{
	VS_DEPTH_OUTPUT output = (VS_DEPTH_OUTPUT)0;
	SKIN Skinned = SkinVert(input);

	output.Pos = mul(Skinned.Pos, World);
	output.Depth = output.Pos;

	return output;
}


//
float4 PS_Depth(VS_DEPTH_OUTPUT input) : SV_Target
{
	float4 color = input.Depth.z / input.Depth.w;
	return color;
}