
Texture2D g_Texture;
sampler g_TextureSampler = sampler_state
{
	Texture = <g_Texture>;
};

/*
Texture2D g_Lightmap;
sampler g_LightmapSampler = sampler_state
{
	Texture = <g_Lightmap>;
};
*/

struct VertexIn
{
	float4 position : POSITION0;
	float4 center : POSITION1;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD0;
};

struct VertexOut
{
	float4 position : POSITION0;
	float4 center : POSITION1;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD0;
};

float4x4 g_Projection;

VertexOut vShader(VertexIn Input)
{
	VertexOut Vert = (VertexOut)0;
	
	Vert.position = mul(Input.position, g_Projection);
	Vert.center = Input.center;
	Vert.color = Input.color;
	Vert.texcoord = Input.texcoord;
	
    return Vert;
}

float4 pShader(float2 vPosition : VPOS, VertexOut Vert) : COLOR
{
	//return float4(1, 1, 1, 1);
	//return tex2D(g_LightmapSampler, float2(0, 0));
	//return tex2D(g_TextureSampler, Vert.texcoord) * Vert.color * tex2D(g_LightmapSampler, Vert.texcoord);
	return tex2D(g_TextureSampler, Vert.texcoord) * Vert.color;
}

technique FirstTechnique
{
    pass FirstPass
    {
        VertexShader = compile vs_3_0 vShader();
		PixelShader = compile ps_3_0 pShader();
    }
}