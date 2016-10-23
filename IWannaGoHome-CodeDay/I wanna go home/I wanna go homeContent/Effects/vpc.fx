float4x4 W;
float4x4 P;

struct VSI { float4 Pos : POSITION0; float4 Col : COLOR0; };
struct VSO { float4 Pos : POSITION0; float4 Col : COLOR0; };
struct PSI { float4 Col : COLOR0; };
struct PSO { float4 Col : COLOR0; };

void VS(in VSI In, out VSO Out)
{
	Out.Pos = mul(mul(In.Pos, W), P);
	Out.Col = In.Col;
}

void PS(in PSI In, out PSO Out)
{
	Out.Col = In.Col;
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