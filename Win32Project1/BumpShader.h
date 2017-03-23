#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <d3dcompiler.h>

namespace GameEngineProject
{

	class BumpShader
	{

	private:
		struct MatrixBufferType
		{
			DirectX::XMMATRIX world;
			DirectX::XMMATRIX view;
			DirectX::XMMATRIX projection;
		};

		struct LightBufferType
		{
			DirectX::XMFLOAT4 diffuseColor;
			DirectX::XMFLOAT3 lightDirection;
			float padding;
		};

	public:
		BumpShader();
		BumpShader(const BumpShader&);
		~BumpShader();

		bool Initialize(ID3D11Device*, HWND);
		void Shutdown();
		bool Render(ID3D11DeviceContext*, int, DirectX::XMMATRIX, DirectX::XMMATRIX, DirectX::XMMATRIX, ID3D11ShaderResourceView**, DirectX::XMFLOAT3,
			DirectX::XMFLOAT4);
		bool Render(ID3D11DeviceContext*, int, DirectX::XMMATRIX, DirectX::XMMATRIX, DirectX::XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, DirectX::XMFLOAT3,
			DirectX::XMFLOAT4);

	private:
		bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
		void ShutdownShader();
		void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

		bool SetShaderParameters(ID3D11DeviceContext*, DirectX::XMMATRIX, DirectX::XMMATRIX, DirectX::XMMATRIX, ID3D11ShaderResourceView**, DirectX::XMFLOAT3,
			DirectX::XMFLOAT4);
		void RenderShader(ID3D11DeviceContext*, int);

	private:
		ID3D11VertexShader* m_vertexShader;
		ID3D11PixelShader* m_pixelShader;
		ID3D11InputLayout* m_layout;
		ID3D11Buffer* m_matrixBuffer;
		ID3D11SamplerState* m_sampleState;
		ID3D11Buffer* m_lightBuffer;
	};
}
