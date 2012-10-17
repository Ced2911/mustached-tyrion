/** Transformation **/
float4x4 modelview_matrix : register (c0);
float4x4 projection_matrix : register (c8);

struct VertexShaderInput
{
    float4 Position : POSITION0;	// model xyzw
    float2 uv0: TEXCOORD0;			// texture 0 uv
	float2 uv1: TEXCOORD1;			// texture 1 uv
	float4 color: COLOR0;			// color
};

struct VertexShaderOutput
{
    float4 Position : POSITION0;	// model xyzw
    float2 uv0: TEXCOORD0;			// texture 0 uv
	float2 uv1: TEXCOORD1;			// texture 1 uv
	float4 color: COLOR0;			// color
};

VertexShaderOutput vs_main(VertexShaderInput input)
{
    VertexShaderOutput output;
    // gl_Position = projection_matrix * modelview_matrix * vec4(vertex, 1.0);
    //output.Position = mul(input.Position, MVP);//mul(MVP, input.Position);
	//output.Position = input.Position;
	
	output.Position = mul(mul(projection_matrix, modelview_matrix), input.Position); // OGL
	//output.Position = mul(input.Position, mul(projection_matrix, modelview_matrix)); // DX
	output.uv0 = input.uv0;
	output.uv1 = input.uv1;
	output.color = input.color;
	
    return output;
}

VertexShaderOutput post_process_main(VertexShaderInput input)
{
	VertexShaderOutput output;
	output.Position = input.Position;
	output.uv0 = input.uv0;
	output.uv1 = input.uv1;
	output.color = input.color;
	return output;
}

sampler2D texture0 : register(s0); 
sampler2D texture1 : register(s1); 

struct PixelShaderInput
{
	float2 uv0: TEXCOORD0;			// texture 0 uv
	float2 uv1: TEXCOORD1;			// texture 1 uv
	float4 color: COLOR;			// color
};

float4 ps_color(PixelShaderInput input): COLOR {
    return input.color;
}

float4 ps_modulate(PixelShaderInput input): COLOR {
    return input.color * tex2D(texture0, input.uv0);
}

float4 ps_texture(PixelShaderInput input): COLOR {
    return tex2D(texture0, input.uv0);
}
float4 ps_modulate_2(PixelShaderInput input): COLOR {
    return (input.color * tex2D(texture0, input.uv0)) * tex2D(texture1, input.uv1);
}

float4 ps_replace_modulate(PixelShaderInput input): COLOR {
    //return tex2D(texture0, input.uv0) + tex2D(texture1, input.uv1);
	return tex2D(texture0, input.uv0) * tex2D(texture1, input.uv1);
	//return float4(1,0,1,1);
}

float bloom_color_effect : register (c4);
float4 ps_bloom(PixelShaderInput input): COLOR {

	float2 texcoord = input.uv0 * 4;
	float4 col = tex2D(texture0, input.uv0);
	col += tex2D(texture0, texcoord + float2(1,0));
	col += tex2D(texture0, texcoord + float2(0,1));
	col += tex2D(texture0, texcoord + float2(1,1));
	col *= 0.25f;

    return col;
}