float4x4 W;
float4x4 P;

texture Texture;
sampler Sampler = sampler_state
{
	Texture = <Texture>;
	MinFilter = Linear;
	MagFilter = Linear;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VSI { float4 Pos : POSITION0; float2 Tex : TEXCOORD0; };
struct VSO { float4 Pos : POSITION0; float2 Tex : TEXCOORD0; };
struct PSI { float2 Tex : TEXCOORD0; };
struct PSO { float4 Col : COLOR0; };

void VS(in VSI In, out VSO Out)
{
	Out.Pos = mul(mul(In.Pos, W), P);
	Out.Tex = In.Tex;
}

void PS(in PSI In, out PSO Out)
{
	Out.Col = tex2D(Sampler, In.Tex);
}

technique t
{
	pass p
	{
		AlphaBlendEnable = True;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
	
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}