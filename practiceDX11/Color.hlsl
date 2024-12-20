
struct VS_INPUT {

	float4 position:POSITION;
	float4 color:COLOR;
    //float2 uv : TEXCOORD;
	
};
cbuffer TransformData : register(b0)
{
    //float4 offset;
    row_major matrix matWorld;
    row_major matrix matView;
    row_major matrix matProjection;
	
}



struct VS_OUTPUT {

	float4 position:SV_POSITION;// systemvalue 반드시알아야함.
	float4 color:COLOR;
    //float2 uv : TEXCOORD;
	
};

VS_OUTPUT VS(VS_INPUT input) {// 정점단위 실행.

	VS_OUTPUT output;
	
	//WVP
    float4 position = mul(input.position, matWorld);//w
    position = mul(position, matView);//v
    position = mul(position, matProjection);//p
	
	
	
	
    output.position = position; //offset;
	//output.uv = input.uv;// before color->uv
    output.color = input.color;


	return output;
}




Texture2D texture0 : register(t0);
//Texture2D texture1 : register(t1);
SamplerState sampler0 : register(s0);


float4 PS(VS_OUTPUT input) : SV_Target{

    float4 color = input.color;
	
	
	// img file 로드해 cpu->리소스화->gpu->연결
	
	
	return color;
}
// 렌더타겟하는 곳에 사용해야함.