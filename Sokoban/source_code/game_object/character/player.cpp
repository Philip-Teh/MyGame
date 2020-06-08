using namespace std;

void CPlayer::Init()
{
	mAnimation[0] = "asset/model/Hidle.fbx";
	mAnimation[1] = "asset/model/Hjump.fbx";
	mAnimation[2] = "asset/model/Hrun.fbx";

	m_Position = XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.5f, 0.5f, 0.5f);

	//�|�C���^�쐬
	mpShader = make_shared<CShader>();
	mpShader->Init("shader_3d_vs.cso", "shader_3d_ps.cso");

	mpModelA = make_unique<CModelAnimation>();
	mpModelA->Load(mAnimation, mpShader);

	mMove = false;
	mPull = false;
	mPullEnable = true;

	mDirection = CDirection::Down;
	mCurrentDirection = CDirection::Down;
}

void CPlayer::Uninit()
{
	mpModelA->Unload();

	if (mpShader)
		mpShader->Uninit();
}

void CPlayer::Update()
{
	//�ҋ@�A�j���[�V�����X�V
	mFrame++;
	mpModelA->Update(0, mFrame);

	Move();
	Direction();

	//CMeshfield* field = CSceneManager::GetScene()->GetGameObject<CMeshfield>(WORLD);
	//m_Position.y = field->GetHeight(m_Position);
}

void CPlayer::Draw(XMFLOAT3 position)
{
	// �}�g���N�X�ݒ�																
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(position.x, position.y + 1.0f, position.z);

	CCamera* camera = CSceneManager::GetScene()->GetGameObject<CCamera>();

	XMFLOAT4X4 view, projection;
	XMStoreFloat4x4(&view, camera->GetViewMatrix());
	XMStoreFloat4x4(&projection, camera->GetProjectionMatrix());

	//�V�F�[�_�ݒ�
	mpShader->SetCameraPosition(XMFLOAT4(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z, 0.0f));
	mpShader->SetViewMatrix(&view);
	mpShader->SetProjectionMatrix(&projection);
	//mpShader->SetPlayerPosition(m_Position);
	 
	//�`��
	mpModelA->Draw(world);
}

void CPlayer::Move()
{
	mMove = false;
	mPull = false;

	//�L�[���͑���
	if (CInput::GetKeyPress('W')) {
		mDirection = CDirection::Up;
		mMove = true;
	}
	if (CInput::GetKeyPress('S')) {
		mDirection = CDirection::Down;
		mMove = true;
	}
	if (CInput::GetKeyPress('A')) {
		mDirection = CDirection::Left;
		mMove = true;
	}
	if (CInput::GetKeyPress('D')){
		mDirection = CDirection::Right;
		mMove = true;
	}
	if (mPullEnable && CInput::GetKeyPress(VK_SPACE)) {
		mPull = true;
	}
}

void CPlayer::MoveAnimation(bool move)
{
	//�ړ��A�j���[�V�����X�V
	if(move)
		mpModelA->Update(2, mFrame);
}

void CPlayer::Direction()
{
	//��������
	switch (mDirection)
	{
	//������
	case CDirection::Down:
		//���։�]
		if (mCurrentDirection == CDirection::Left)
		{
			m_Rotation.y -= mTurnSpeed;
			if (m_Rotation.y <= mCurrentRotation.down)
				mCurrentDirection = CDirection::Down;
		}
		//�E�։�]
		else if (mCurrentDirection == CDirection::Right)
		{
			m_Rotation.y += mTurnSpeed;
			if (m_Rotation.y >= mCurrentRotation.down1)
			{
				mCurrentDirection = CDirection::Down;
				m_Rotation.y = mCurrentRotation.down;
			}
		}
		//��։�]
		else if (mCurrentDirection == CDirection::Up)
		{
			m_Rotation.y -= mTurnSpeed;
			if (m_Rotation.y <= mCurrentRotation.down)
				mCurrentDirection = CDirection::Down;
		}
		else
			m_Rotation.y = mCurrentRotation.down;
		break;
		
	//�ォ��
	case CDirection::Up:
		//���։�]
		if (mCurrentDirection == CDirection::Left)
		{
			m_Rotation.y += mTurnSpeed;
			if (m_Rotation.y >= mCurrentRotation.up)
				mCurrentDirection = CDirection::Up;
		}
		//�E�։�]
		else if (mCurrentDirection == CDirection::Right)
		{
			m_Rotation.y -= mTurnSpeed;
			if (m_Rotation.y <= mCurrentRotation.up)
				mCurrentDirection = CDirection::Up;
		}
		//���։�]
		else if (mCurrentDirection == CDirection::Down)
		{
			m_Rotation.y += mTurnSpeed;
			if (m_Rotation.y >= mCurrentRotation.up)
				mCurrentDirection = CDirection::Up;
		}
		else
			m_Rotation.y = mCurrentRotation.up;
		break;
	//������
	case CDirection::Left:
		//���։�]
		if (mCurrentDirection == CDirection::Down)
		{
			m_Rotation.y += mTurnSpeed;
			if (m_Rotation.y >= mCurrentRotation.left)
				mCurrentDirection = CDirection::Left;
		}
		//�E�։�]
		else if (mCurrentDirection == CDirection::Right)
		{
			m_Rotation.y -= mTurnSpeed;
			if (m_Rotation.y <= mCurrentRotation.left)
				mCurrentDirection = CDirection::Left;
		}
		//��։�]
		else if (mCurrentDirection == CDirection::Up)
		{
			m_Rotation.y -= mTurnSpeed;
			if (m_Rotation.y <= mCurrentRotation.left)
				mCurrentDirection = CDirection::Left;
		}
		else
			m_Rotation.y = mCurrentRotation.left;
		break;
	//�E����
	case CDirection::Right:
		//���։�]
		if (mCurrentDirection == CDirection::Down)
		{
			m_Rotation.y -= mTurnSpeed;
			if (m_Rotation.y <= mCurrentRotation.right1)
			{
				mCurrentDirection = CDirection::Right;
				m_Rotation.y = mCurrentRotation.right;
			}
		}
		//���։�]
		else if (mCurrentDirection == CDirection::Left)
		{
			m_Rotation.y += mTurnSpeed;
			if (m_Rotation.y >= mCurrentRotation.right)
				mCurrentDirection = CDirection::Right;
		}
		//��։�]
		else if (mCurrentDirection == CDirection::Up)
		{
			m_Rotation.y += mTurnSpeed;
			if (m_Rotation.y >= mCurrentRotation.right)
				mCurrentDirection = CDirection::Right;
		}
		else
			m_Rotation.y = mCurrentRotation.right;
		break;
	}
}