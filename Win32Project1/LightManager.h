#pragma once


#include <DirectXMath.h>



namespace GameEngineProject
{
	class LightManager
	{
	public:
		LightManager();
		LightManager(const LightManager&);
		~LightManager();

		void SetDiffuseColor(float, float, float, float);
		void SetAmbientColor(float, float, float, float);
		void SetSpecularColor(float, float, float, float);
		void SetSpecularPower(float);
		void SetDirection(float, float, float);

		DirectX::XMFLOAT4 GetDiffuseColor();
		DirectX::XMFLOAT4 GetAmbientColor();
		DirectX::XMFLOAT4 GetSpecularColor();
		float GetSpecularPower();
		DirectX::XMFLOAT3 GetDirection();

	private:
		DirectX::XMFLOAT4 m_diffuseColor;
		DirectX::XMFLOAT4 m_ambientColor;
		DirectX::XMFLOAT4 m_specularColor;
		float m_specularPower;
		DirectX::XMFLOAT3 m_direction;
	};

}
