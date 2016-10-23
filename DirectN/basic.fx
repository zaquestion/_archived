float4x4 W;
float4x4 P;
texture Texture;

sampler2D Sampler = sampler_state
{
	Texture = <Texture>;
	MinFilter = point;
	MagFilter = point;
	AddressU = Clamp;
	AddressV = Clamp;
};

struct VS_I
{
	float4 Pos : POSITION0;
	float2 Tex : TEXCOORD0;
};

struct VS_O
{
	float4 Pos : POSITION0;
	float2 Tex : TEXCOORD0;
};

struct PS_I
{
	float4 Tex : TEXCOORD0;
};

struct PS_O
{
	float4 Col : COLOR0;
};

void VS(in VS_I In, out VS_O Out)
{
	Out.Pos = mul(mul(In.Pos, W), P);
	Out.Tex = In.Tex;
}

void PS(in PS_I In, out PS_O Out)
{
	Out.Col = tex2D(Sampler, In.Tex);
}

technique T0
{
    pass P0
    {

        VertexShader = compile vs_3_0 VS();
        PixelShader = compile ps_3_0 PS();
    }
}