#include "inc_KdStandardShader.hlsli"
#include "../inc_KdCommon.hlsli"

//================================
// 頂点シェーダ (スキンメッシュ対応)
//================================
VSOutput main(
	float4 pos : POSITION,  // 頂点座標
	float2 uv : TEXCOORD0,  // テクスチャUV座標
	float4 color : COLOR,   // 頂点カラー
	float3 normal : NORMAL, // 法線
	float3 tangent : TANGENT,      // 接線
    uint4  skinIndex : SKININDEX,  // スキンメッシュのBoneIndex（何番目のBoneに影響しているか）
	float4 skinWeight : SKINWEIGHT, // Boneの影響度
	uint instanceID : SV_InstanceID // インスタンシング対応
)
{
	// スキンメッシュ対応　（スキニング---＞）
	if (g_IsSkinMeshObj)
	{
		// 行列を合成
		row_major float4x4 mBones = 0;
		[unroll]
		for (int i = 0; i < 4; i++)
		{
			mBones += g_mBones[skinIndex[i]] * skinWeight[i];
		}
		// 座標と法線に適応
		pos = mul(pos, mBones);
		normal = mul(normal, (float3x3) mBones);

	}
	//＜----スキニング
	
	VSOutput Out;

	if(g_EnableInstancingDraw)
	{
		// インスタンスごとのワールド行列を取得
		row_major float4x4 instanceWorld = g_mInstanceWorlds[instanceID];

		// 座標変換 (インスタンスごとのワールド行列を使用)
		Out.Pos = mul(pos, instanceWorld); // ローカル座標系 -> インスタンスのワールド座標系へ変換
		Out.wPos = Out.Pos.xyz; // ワールド座標を別途保存
		Out.Pos = mul(Out.Pos, g_mView); // ワールド座標系 -> ビュー座標系へ変換
		Out.Pos = mul(Out.Pos, g_mProj); // ビュー座標系 -> 射影座標系へ変換

		// 頂点色
		Out.Color = color;

		// 法線
		Out.wN = normalize(mul(normal, (float3x3) instanceWorld));
		// 接線
		Out.wT = normalize(mul(tangent, (float3x3) instanceWorld));
		// 従接線
		float3 binormal = cross(normal, tangent);
		Out.wB = normalize(mul(binormal, (float3x3) instanceWorld));
	}
	else
	{
		// 座標変換
		Out.Pos = mul(pos, g_mWorld); // ローカル座標系	-> ワールド座標系へ変換
		Out.wPos = Out.Pos.xyz; // ワールド座標を別途保存
		Out.Pos = mul(Out.Pos, g_mView); // ワールド座標系	-> ビュー座標系へ変換
		Out.Pos = mul(Out.Pos, g_mProj); // ビュー座標系	-> 射影座標系へ変換

		// 頂点色
		Out.Color = color;

		// 法線
		Out.wN = normalize(mul(normal, (float3x3) g_mWorld));
		// 接線
		Out.wT = normalize(mul(tangent, (float3x3) g_mWorld));
		// 従接線
		float3 binormal = cross(normal, tangent);
		Out.wB = normalize(mul(binormal, (float3x3) g_mWorld));
	}
	
    // UV座標
	Out.UV = uv * g_UVTiling + g_UVOffset;

	// アウトライン描画チェック
	if (g_EnableOutLineDraw)
	{
		// 頂点座標を「法線方向」に少しずらす
		pos.xyz = pos.xyz + normal * 0.03;
	}
	
    // 出力
	return Out;
}
