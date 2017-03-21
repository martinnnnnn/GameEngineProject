#pragma once



#include <d3d11.h>
#include <directxmath.h>
#include <fstream>
#include <vector>

#include "Component.h"


namespace GameEngineProject
{

	typedef enum
	{
		BUMP_SHADER,
		LIGHT_SHADER,
		FOG_SHADER
	} ShaderType;



	class GraphicsComponent : public Component
	{

	private:

		struct VertexType
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT2 texture;
			DirectX::XMFLOAT3 normal;
			DirectX::XMFLOAT3 tangent;
			DirectX::XMFLOAT3 binormal;
		};


		struct ModelType
		{
			float x, y, z;
			float tu, tv;
			float nx, ny, nz;
			float tx, ty, tz;
			float bx, by, bz;
		};

		struct TempVertexType
		{
			float x, y, z;
			float tu, tv;
			float nx, ny, nz;
		};

		struct VectorType
		{
			float x, y, z;
		};


	public:
		GraphicsComponent();
		GraphicsComponent(const GraphicsComponent &);
		virtual ~GraphicsComponent();
		void operator=(const GraphicsComponent &);
		virtual bool operator==(const GraphicsComponent &);
		virtual void Swap(const GraphicsComponent &);
		virtual void Reset();

		
		bool Initialize(ID3D11Device*, ID3D11DeviceContext*, std::vector<wchar_t*>&, char*, ShaderType);
		void Shutdown();
		void Render(ID3D11DeviceContext*);

		int GetIndexCount();
		ShaderType GetShaderType();
		ID3D11ShaderResourceView** GetTextures();


	private:
		bool InitializeBuffers(ID3D11Device*);
		void ShutdownBuffers();
		void RenderBuffers(ID3D11DeviceContext*);

		bool LoadTextures(ID3D11Device*, ID3D11DeviceContext*, std::vector<wchar_t*>&);
		void ReleaseTextures();

		bool LoadModel(char*);
		void ReleaseModel();

		void CalculateModelVectors();
		void CalculateTangentBinormal(TempVertexType, TempVertexType, TempVertexType, VectorType&, VectorType&);
		void CalculateNormal(VectorType, VectorType, VectorType&);

	private:
		int _ID;
		ShaderType _shaderType;
		ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
		int m_vertexCount, m_indexCount;
		ModelType* m_model;
		ID3D11ShaderResourceView** _textureViews;
		int _textureViewsNumber;




	};

}