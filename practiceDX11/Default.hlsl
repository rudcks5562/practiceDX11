
struct VS_INPUT {

	float4 position:POSITION;
	float4 color:COLOR;

};


struct VS_OUTPUT {

	float4 position:SV_POSITION;// systemvalue 반드시알아야함.
	float4 color:COLOR;

};

VS_OUTPUT VS(VS_INPUT input) {// 정점단위 실행.

	VS_OUTPUT output;
	output.position = input.position;
	output.color = input.color;



	return output;
}


float4 PS(VS_OUTPUT input) : SV_Target{


	return input.color;
}
// 렌더타겟하는 곳에 사용해야함.