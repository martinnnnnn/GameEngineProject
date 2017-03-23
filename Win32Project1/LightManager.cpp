#include "LightManager.h"



using namespace GameEngineProject;
using namespace DirectX;

LightManager::LightManager()
{
}


LightManager::LightManager(const LightManager& other)
{
}


LightManager::~LightManager()
{
}


void LightManager::SetAmbientColor(float red, float green, float blue, float alpha)
{
	m_ambientColor = XMFLOAT4(red, green, blue, alpha);
	return;
}

void LightManager::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = XMFLOAT4(red, green, blue, alpha);
	return;
}

void LightManager::SetSpecularColor(float red, float green, float blue, float alpha)
{
	m_specularColor = XMFLOAT4(red, green, blue, alpha);
	return;
}

void LightManager::SetSpecularPower(float value)
{
	m_specularPower = value;
	return;
}

void LightManager::SetDirection(float x, float y, float z)
{
	m_direction = XMFLOAT3(x, y, z);
	return;
}

XMFLOAT4 LightManager::GetAmbientColor()
{
	return m_ambientColor;
}

XMFLOAT4 LightManager::GetDiffuseColor()
{
	return m_diffuseColor;
}

XMFLOAT4 LightManager::GetSpecularColor()
{
	return m_specularColor;
}

float LightManager::GetSpecularPower()
{
	return m_specularPower;
}


XMFLOAT3 LightManager::GetDirection()
{
	return m_direction;
}

