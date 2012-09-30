/** Transformation **/
float4x4 modelview_matrix : register (c0);
float4x4 projection_matrix : register (c8);

struct VertexShaderInput
{
    float4 Position : POSITION0;	// model xyzw
    float2 uv0: TEXCOORD0;			// texture 0 uv
	float2 uv1: TEXCOORD1;			// texture 1 uv
	float4 color: COLOR;			// color
};

struct VertexShaderOutput
{
    float4 Position : POSITION0;	// model xyzw
    float2 uv0: TEXCOORD0;			// texture 0 uv
	float2 uv1: TEXCOORD1;			// texture 1 uv
	float4 color: COLOR;			// color
};


VertexShaderOutput vs_main(VertexShaderInput input)
{
    VertexShaderOutput output;
    // gl_Position = projection_matrix * modelview_matrix * vec4(vertex, 1.0);
	float4x4 MVP = mul(projection_matrix, modelview_matrix);
    output.Position = mul(MVP, input.Position);
	output.uv0 = input.uv0;
	output.uv1 = input.uv1;
	output.color = input.color;
    return output;
}


struct PixelShaderInput
{
	float2 uv0: TEXCOORD0;			// texture 0 uv
	float2 uv1: TEXCOORD1;			// texture 1 uv
	float4 color: COLOR;			// color
};

float4 ps_main(PixelShaderInput input): COLOR {
    return input.color;
}
