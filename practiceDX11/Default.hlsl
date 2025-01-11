
struct VS_INPUT {
 
	float4 position:POSITION;
	//float4 color:COLOR;
    float2 uv : TEXCOORD;
	
}; 
cbuffer CameraData : register(b0)	
{
    //float4 offset;

    row_major matrix matView;
    row_major matrix matProjection;
	
}
cbuffer TransformData : register(b1)
{
    //float4 offset;
    row_major matrix matWorld;

	
}
cbuffer AnimationData : register(b2){


float2 spriteOffset;
float2 spriteSize;
float2 textureSize;
float useAnimation;
}


struct VS_OUTPUT {

	float4 position:SV_POSITION;// systemvalue �ݵ�þ˾ƾ���.
	//float4 color:COLOR;
    float2 uv : TEXCOORD;
	
};

VS_OUTPUT VS(VS_INPUT input) {// �������� ����.

	VS_OUTPUT output;
	
	//WVP
    float4 position = mul(input.position, matWorld);//w
    position = mul(position, matView);//v
    position = mul(position, matProjection);//p
	
	
	
	
    output.position = position; //offset;
	output.uv = input.uv;// before color->uv

if(useAnimation == 1.0f){
output.uv *= spriteSize/textureSize;
output.uv += spriteOffset/textureSize;

}

	return output;
}




Texture2D texture0 : register(t0);
//Texture2D texture1 : register(t1);
SamplerState sampler0 : register(s0);


float4 PS(VS_OUTPUT input) : SV_Target{

    float4 color = texture0.Sample(sampler0, input.uv);
	
	// img file �ε��� cpu->���ҽ�ȭ->gpu->����
	
	
	return color;
}
// ����Ÿ���ϴ� ���� ����ؾ���.