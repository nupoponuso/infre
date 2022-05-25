Texture2D texColor : register(t0);
SamplerState samLinear : register(s0);

//�O���[�o��
cbuffer global
{
	matrix WVP; //���[���h����ˉe�܂ł̕ϊ��s��
	matrix TEX;
	float4 DEF;
};

//�o�[�e�b�N�X�V�F�[�_�[�o�͍\����
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};


//�o�[�e�b�N�X�V�F�[�_�[/

VS_OUTPUT VS(float4 Pos : POSITION, float2 Tex : TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.Pos = mul(Pos, WVP);
	output.Tex = mul(float4(Tex, 0.0f, 1.0f), TEX).xy;

	return output;
}


//�s�N�Z���V�F�[�_�[
//
float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 Color = DEF;

	if (TEX._44 > 0.0f)Color *= texColor.Sample(samLinear, input.Tex);

	float4 Y = 0.299*Color.r + 0.587f*Color.g + 0.114f*Color.b;
	Color.r = Color.g = Color.b = Y;

	return Color;
}
