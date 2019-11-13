

#define SPEED (0.1f)

void CCamera::Init()
{
	m_Position = XMFLOAT3(0.0f, 5.0f, -20.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);

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

	pp = player.GetPosition();
}

void CCamera::Uninit()
{
	
}

void CCamera::Update()
{
	vectorF = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	vectorR = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	vectorU = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	if (CInput::GetKeyPress('E'))
		m_Rotation.y += 0.05f;

	if (CInput::GetKeyPress('Q'))
		m_Rotation.y -= 0.05f;

	if (CInput::GetKeyPress('J'))
		m_Rotation.z+= 0.05f;

	if (CInput::GetKeyPress('L'))
		m_Rotation.z -= 0.05f;

	if (CInput::GetKeyPress('K'))
		m_Rotation.x += 0.05f;

	if (CInput::GetKeyPress('I'))
		m_Rotation.x -= 0.05f;

	m_ViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

	vectorF = XMVector3TransformCoord(vectorF, m_ViewMatrix);
	XMStoreFloat3(&front, vectorF);
	vectorR = XMVector3TransformCoord(vectorR, m_ViewMatrix);
	XMStoreFloat3(&right, vectorR);
	vectorU = XMVector3TransformCoord(vectorU, m_ViewMatrix);
	XMStoreFloat3(&up, vectorU);


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

	pp = player.GetPosition();

	m_ViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	eye = XMVectorSet(pp.x, pp.y+2, pp.z-10, 0);
	focus = XMVectorSet(pp.x, pp.y, pp.z, 0);
}

void CCamera::Draw()
{
	XMMATRIX	m_InvViewMatrix;
	XMMATRIX	m_ProjectionMatrix;

	// �r���[�|�[�g�ݒ�
	D3D11_VIEWPORT dxViewport;
	dxViewport.Width = (float)(m_Viewport.right - m_Viewport.left);
	dxViewport.Height = (float)(m_Viewport.bottom - m_Viewport.top);
	dxViewport.MinDepth = 0.0f;
	dxViewport.MaxDepth = 1.0f;
	dxViewport.TopLeftX = (float)m_Viewport.left;
	dxViewport.TopLeftY = (float)m_Viewport.top;

	CRenderer::GetDeviceContext()->RSSetViewports(1, &dxViewport);

	// �r���[�}�g���N�X�ݒ�
	m_InvViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	m_InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMVECTOR det;
	m_ViewMatrix = XMMatrixInverse(&det, m_InvViewMatrix);
	m_ViewMatrix = XMMatrixLookAtLH(eye, focus, vectorU);

	CRenderer::SetViewMatrix(&m_ViewMatrix);


	// �v���W�F�N�V�����}�g���N�X�ݒ�
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(1.0f, dxViewport.Width / dxViewport.Height, 1.0f, 1000.0f);

	CRenderer::SetProjectionMatrix(&m_ProjectionMatrix);
}