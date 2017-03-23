#pragma once

#include <d3d11.h>
#include <directxmath.h>


namespace GameEngineProject
{

	class TextureClass;

	class FontHandler
	{
	private:

		struct FontType
		{
			float left, right;
			int size;
		};

		struct VertexType
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT2 texture;
		};

	public:
		FontHandler();
		FontHandler(const FontHandler&);
		~FontHandler();

		bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, char*);

		void Shutdown();

		ID3D11ShaderResourceView* GetTexture();

		void BuildVertexArray(void*, char*, float, float);

	private:
		bool LoadFontData(char*);
		void ReleaseFontData();
		bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
		void ReleaseTexture();

	private:
		FontType* m_Font;
		TextureClass* m_Texture;
	};

}
