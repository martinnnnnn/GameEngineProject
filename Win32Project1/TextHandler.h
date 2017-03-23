#pragma once




#include <d3d11.h>
#include <directxmath.h>

namespace GameEngineProject
{

	class FontShader;
	class FontHandler;

	class TextHandler
	{
	private:

		struct SentenceType
		{
			ID3D11Buffer *vertexBuffer, *indexBuffer;
			int vertexCount, indexCount, maxLength;
			float red, green, blue;
		};

		struct VertexType
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT2 texture;
		};

	public:
		TextHandler();
		TextHandler(const TextHandler&);
		~TextHandler();

		bool Initialize(ID3D11Device*, ID3D11DeviceContext*, HWND, int, int, DirectX::XMMATRIX);
		void Shutdown();
		bool Render(ID3D11DeviceContext*, DirectX::XMMATRIX, DirectX::XMMATRIX);
		bool SetMousePosition(int, int, ID3D11DeviceContext*);
		bool SetFps(int, ID3D11DeviceContext*);
		bool SetCpu(int, ID3D11DeviceContext*);
		bool SetText(const char*, ID3D11DeviceContext*);
	private:
		bool InitializeSentence(SentenceType**, int, ID3D11Device*);
		bool UpdateSentence(SentenceType*, char*, int, int, float, float, float, ID3D11DeviceContext*);
		void ReleaseSentence(SentenceType**);
		bool RenderSentence(ID3D11DeviceContext*, SentenceType*, DirectX::XMMATRIX, DirectX::XMMATRIX);

	private:
		FontHandler* m_Font;
		FontShader* m_FontShader;
		int m_screenWidth, m_screenHeight;
		DirectX::XMMATRIX m_baseViewMatrix;

		SentenceType* m_sentence1;
		SentenceType* m_sentence2;
	};
}