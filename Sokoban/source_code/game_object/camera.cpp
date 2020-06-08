
#define SPEED (0.1f)

void CCamera::Init()
{
	m_Position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_Rotation = XMFLOAT3(1.0f, 0.0f, 0.0f);

	eye = XMVectorSet(m_Position.x, m_Position.y, m_Position.z, 0);
	focus = XMVectorSet(0, 0, 0, 0);

	m_Viewport.left = 0;
	m_Viewport.top = 0;
	m_Viewport.right = SCREEN_WIDTH;
	m_Viewport.bottom = SCREEN_HEIGHT;

	vectorF = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVector3TransformCoord(vectorF, m_ViewMatrix);
	XMStoreFloat3(&front,vectorF);

	vectorR = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVector3TransformCoord(vectorR, m_ViewMatrix);
	XMStoreFloat3(&right, vectorR);

	vectorU = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVector3TransformCoord(vectorU, m_ViewMatrix);
	XMStoreFloat3(&up, vectorU);

	mLength = 10.0f;
}

void CCamera::Uninit()
{
	
}

void CCamera::Update()
{
	//入力回転
	vectorF = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	vectorR = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	vectorU = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	if (CInput::GetKeyPress('E'))
		m_Rotation.y += 0.05f;

	if (CInput::GetKeyPress('Q'))
		m_Rotation.y -= 0.05f;

	if (CInput::GetKeyPress('H'))
		m_Rotation.z+= 0.05f;

	if (CInput::GetKeyPress('K'))
		m_Rotation.z -= 0.05f;

	if (CInput::GetKeyPress('J'))
		m_Rotation.x += 0.05f;

	if (CInput::GetKeyPress('U'))
		m_Rotation.x -= 0.05f;

	m_ViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

	vectorF = XMVector3TransformCoord(vectorF, m_ViewMatrix);
	XMStoreFloat3(&front, vectorF);
	vectorR = XMVector3TransformCoord(vectorR, m_ViewMatrix);
	XMStoreFloat3(&right, vectorR);
	vectorU = XMVector3TransformCoord(vectorU, m_ViewMatrix);
	XMStoreFloat3(&up, vectorU);

	//入力移動
	if (CInput::GetKeyPress(VK_UP))
	{
		m_Position.z += front.z * SPEED;
		m_Position.x += front.x * SPEED;
		m_Position.y += front.y * SPEED;
	}

	if (CInput::GetKeyPress(VK_DOWN))
	{
		m_Position.z -= front.z * SPEED;
		m_Position.x -= front.x * SPEED;
		m_Position.y -= front.y * SPEED;
	}

	if (CInput::GetKeyPress(VK_LEFT))
	{
		m_Position.z -= right.z * SPEED;
		m_Position.x -= right.x * SPEED;
		m_Position.y -= right.y * SPEED;
	}

	if (CInput::GetKeyPress(VK_RIGHT))
	{
		m_Position.z += right.z * SPEED;
		m_Position.x += right.x * SPEED;
		m_Position.y += right.y * SPEED;
	}

	if (CInput::GetKeyPress('O'))
	{
		m_Position.z += up.z * SPEED;
		m_Position.x += up.x * SPEED;
		m_Position.y += up.y * SPEED;
	}

	if (CInput::GetKeyPress('L'))
	{
		m_Position.z -= up.z * SPEED;
		m_Position.x -= up.x * SPEED;
		m_Position.y -= up.y * SPEED;
	}

	m_ViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	eye = XMVectorSet(m_Position.x, m_Position.y + 30, m_Position.z - 20, 0);

	XMFLOAT3 f;
	f.x = (front.x * mLength) + mCenter.x;
	f.y = (front.y * mLength) + mCenter.y;
	f.z = (front.z * mLength) + mCenter.z;

	focus = XMVectorSet(f.x, f.y, f.z, 0);
}

void CCamera::Draw()
{
	XMMATRIX	m_InvViewMatrix;

	// ビューポート設定
	D3D11_VIEWPORT dxViewport;
	dxViewport.Width = (float)(m_Viewport.right - m_Viewport.left);
	dxViewport.Height = (float)(m_Viewport.bottom - m_Viewport.top);
	dxViewport.MinDepth = 0.0f;
	dxViewport.MaxDepth = 1.0f;
	dxViewport.TopLeftX = (float)m_Viewport.left;
	dxViewport.TopLeftY = (float)m_Viewport.top;

	CRenderer::GetDeviceContext()->RSSetViewports(1, &dxViewport);

	// ビューマトリクス設定
	m_InvViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	m_InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMVECTOR det;
	m_ViewMatrix = XMMatrixInverse(&det, m_InvViewMatrix);
	m_ViewMatrix = XMMatrixLookAtLH(eye, focus, vectorU);

	// プロジェクションマトリクス設定
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(1.0f, dxViewport.Width / dxViewport.Height, 1.0f, 1000.0f);

}

bool CCamera::Getvisivility(XMFLOAT3 Position)
{
	XMVECTOR worldPos, viewPos, projPos;
	XMFLOAT3 projPosF;
	worldPos = XMLoadFloat3(&Position);

	// カメラ座標変換
	viewPos = XMVector3TransformCoord(worldPos, m_ViewMatrix);

	// 描画座標変換
	projPos = XMVector3TransformCoord(viewPos, m_ProjectionMatrix);

	XMStoreFloat3(&projPosF, projPos);
	if (-1.0f < projPosF.x && projPosF.x < 1.0f &&
		-1.0f < projPosF.y && projPosF.y < 1.0f &&
		-1.0f < projPosF.z && projPosF.z < 1.0f)
	{
		return true;
	}
	return false;
}