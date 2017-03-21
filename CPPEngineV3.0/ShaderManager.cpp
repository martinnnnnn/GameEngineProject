#include "ShaderManager.h"

#include "TextureShader.h"
#include "LightShader.h"
#include "BumpShader.h"
#include "MultiTextureShader.h"
#include "FogShader.h"


using namespace GameEngineProject;
using namespace DirectX;

ShaderManager::ShaderManager()
{
	m_TextureShader = 0;
	m_LightShader = 0;
	m_BumpMapShader = 0;
	m_MultiTextureShader = 0;
	m_FogShader = 0;
}


ShaderManager::ShaderManager(const ShaderManager& other)
{
}


ShaderManager::~ShaderManager()
{
}


bool ShaderManager::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}


	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}


	// Create the bump map shader object.
	m_BumpMapShader = new BumpMapShaderClass;
	if (!m_BumpMapShader)
	{
		return false;
	}

	// Initialize the bump map shader object.
	result = m_BumpMapShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bump map shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the multitexture shader object.
	m_MultiTextureShader = new MultiTextureShaderClass;
	if (!m_MultiTextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_MultiTextureShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the fog shader object.
	m_FogShader = new FogShaderClass;
	if (!m_FogShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_FogShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void ShaderManager::Shutdown()
{
	if (m_BumpMapShader)
	{
		m_BumpMapShader->Shutdown();
		delete m_BumpMapShader;
		m_BumpMapShader = 0;
	}

	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	if (m_MultiTextureShader)
	{
		m_MultiTextureShader->Shutdown();
		delete m_MultiTextureShader;
		m_MultiTextureShader = 0;
	}

	if (m_FogShader)
	{
		m_FogShader->Shutdown();
		delete m_FogShader;
		m_FogShader = 0;
	}
}

bool ShaderManager::RenderTextureShader(ID3D11DeviceContext* device, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture)
{
	bool result;


	// Render the model using the texture shader.
	result = m_TextureShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture);
	if (!result)
	{
		return false;
	}

	return true;
}


bool ShaderManager::RenderLightShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, XMFLOAT3 lightDirection, XMFLOAT4 ambient, XMFLOAT4 diffuse,
	XMFLOAT3 cameraPosition, XMFLOAT4 specular, float specularPower)
{
	bool result;


	// Render the model using the light shader.
	result = m_LightShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, ambient, diffuse, cameraPosition,
		specular, specularPower);
	if (!result)
	{
		return false;
	}

	return true;
}


bool ShaderManager::RenderBumpMapShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture, XMFLOAT3 lightDirection,
	XMFLOAT4 diffuse)
{
	bool result;

	ID3D11ShaderResourceView* textureArray[2];
	textureArray[0] = colorTexture;
	textureArray[1] = normalTexture;
	// Render the model using the bump map shader.
	result = m_BumpMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, textureArray, lightDirection, diffuse);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderMultiTextureShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture1, ID3D11ShaderResourceView* texture2)
{
	ID3D11ShaderResourceView* textureArray[2];
	textureArray[0] = texture1;
	textureArray[1] = texture2;
	bool result;
	result = m_MultiTextureShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, textureArray);
	if (!result)
	{
		return false;
	}
}


bool ShaderManager::RenderFogShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, float fogStart, float fogEnd)
{
	bool result;
	result = m_FogShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, fogStart, fogEnd);
	if (!result)
	{
		return false;
	}
}