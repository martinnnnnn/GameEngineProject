#pragma once

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "D3DHandler.h"
#include "DirectXMath.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: ShaderManagerClass
////////////////////////////////////////////////////////////////////////////////

namespace GameEngineProject
{

	class TextureShader;
	class LightShader;
	class BumpShader;
	class MultiTextureShader;
	class FogShader;

	class ShaderManager
	{
	public:
		ShaderManager();
		ShaderManager(const ShaderManager&);
		~ShaderManager();

		bool Initialize(ID3D11Device*, HWND);
		void Shutdown();

		bool RenderTextureShader(ID3D11DeviceContext*, int, DirectX::XMMATRIX, DirectX::XMMATRIX, DirectX::XMMATRIX, ID3D11ShaderResourceView*);

		bool RenderLightShader(ID3D11DeviceContext*, int, DirectX::XMMATRIX, DirectX::XMMATRIX, DirectX::XMMATRIX, ID3D11ShaderResourceView*,
			DirectX::XMFLOAT3, DirectX::XMFLOAT4, DirectX::XMFLOAT4, DirectX::XMFLOAT3, DirectX::XMFLOAT4, float);

		bool RenderBumpMapShader(ID3D11DeviceContext*, int, DirectX::XMMATRIX, DirectX::XMMATRIX, DirectX::XMMATRIX, ID3D11ShaderResourceView*,
			ID3D11ShaderResourceView*, DirectX::XMFLOAT3, DirectX::XMFLOAT4);

		bool RenderMultiTextureShader(ID3D11DeviceContext*, int, DirectX::XMMATRIX, DirectX::XMMATRIX, DirectX::XMMATRIX,
			ID3D11ShaderResourceView*, ID3D11ShaderResourceView*);

		bool RenderFogShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, float, float);

	private:

		TextureShader* m_TextureShader;
		LightShader* m_LightShader;
		BumpShader* m_BumpMapShader;
		MultiTextureShader* m_MultiTextureShader;
		FogShader* m_FogShader;
	};

}
