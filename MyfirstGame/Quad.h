#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>

//�R���X�^���g�o�b�t�@�[
struct CONSTANT_BUFFER
{
	DirectX::XMMATRIX	matWVP;
};

class Quad
{
public:
	Quad();
	~Quad();
	HRESULT Initialize();
	void Draw(DirectX::XMMATRIX& worldMatrix);
	void Release();
private:
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
};

