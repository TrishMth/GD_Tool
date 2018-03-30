
//--------------------------------------------------------------------------------------
// Input / Output structures
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
   	float3 vPosition    : POSITION;
	//float4 vColor : COLOR; 


};

struct VS_OUTPUT
{
	float4 vPosition    : SV_POSITION;
	//float4 vColor: COLOR;

};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VSMain( VS_INPUT Input )
{
    VS_OUTPUT Output;
    	
	Output.vPosition = float4(Input.vPosition,1);

    
    return Output;
}