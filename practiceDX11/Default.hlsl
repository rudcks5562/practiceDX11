
struct VS_INPUT {

	float4 position:POSITION;
	//float4 color:COLOR;
    float2 uv : TEXCOORD;
	
};
cbuffer TransformData : register(b0)
{
    float4 offset;
	
	
}



struct VS_OUTPUT {

	float4 position:SV_POSITION;// systemvalue �ݵ�þ˾ƾ���.
	//float4 color:COLOR;
    float2 uv : TEXCOORD;
	
};

VS_OUTPUT VS(VS_INPUT input) {// �������� ����.

	VS_OUTPUT output;
	output.position = input.position+offset;
	output.uv = input.uv;// before color->uv



	return output;
}




Texture2D texture0 : register(t0);
Texture2D texture1 : register(t1);
SamplerState sampler0 : register(s0);


float4 PS(VS_OUTPUT input) : SV_Target{

    float4 color = texture0.Sample(sampler0, input.uv);
	
	// img file �ε��� cpu->���ҽ�ȭ->gpu->����
	
	
	return color;
}
// ����Ÿ���ϴ� ���� ����ؾ���.