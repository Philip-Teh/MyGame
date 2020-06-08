using namespace std;

void CPlayer::Init()
{
	mAnimation[0] = "asset/model/Hidle.fbx";
	mAnimation[1] = "asset/model/Hjump.fbx";
	mAnimation[2] = "asset/model/Hrun.fbx";

	m_Position = XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.5f, 0.5f, 0.5f);

	//ポインタ作成
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
	//待機アニメーション更新
	mFrame++;
	mpModelA->Update(0, mFrame);

	Move();
	Direction();

	//CMeshfield* field = CSceneManager::GetScene()->GetGameObject<CMeshfield>(WORLD);
	//m_Position.y = field->GetHeight(m_Position);
}

void CPlayer::Draw(XMFLOAT3 position)
{
	// マトリクス設定																
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(position.x, position.y + 1.0f, position.z);

	CCamera* camera = CSceneManager::GetScene()->GetGameObject<CCamera>();

	XMFLOAT4X4 view, projection;
	XMStoreFloat4x4(&view, camera->GetViewMatrix());
	XMStoreFloat4x4(&projection, camera->GetProjectionMatrix());

	//シェーダ設定
	mpShader->SetCameraPosition(XMFLOAT4(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z, 0.0f));
	mpShader->SetViewMatrix(&view);
	mpShader->SetProjectionMatrix(&projection);
	//mpShader->SetPlayerPosition(m_Position);
	 
	//描画
	mpModelA->Draw(world);
}

void CPlayer::Move()
{
	mMove = false;
	mPull = false;

	//キー入力操作
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
	//移動アニメーション更新
	if(move)
		mpModelA->Update(2, mFrame);
}

void CPlayer::Direction()
{
	//向き操作
	switch (mDirection)
	{
	//下から
	case CDirection::Down:
		//左へ回転
		if (mCurrentDirection == CDirection::Left)
		{
			m_Rotation.y -= mTurnSpeed;
			if (m_Rotation.y <= mCurrentRotation.down)
				mCurrentDirection = CDirection::Down;
		}
		//右へ回転
		else if (mCurrentDirection == CDirection::Right)
		{
			m_Rotation.y += mTurnSpeed;
			if (m_Rotation.y >= mCurrentRotation.down1)
			{
				mCurrentDirection = CDirection::Down;
				m_Rotation.y = mCurrentRotation.down;
			}
		}
		//上へ回転
		else if (mCurrentDirection == CDirection::Up)
		{
			m_Rotation.y -= mTurnSpeed;
			if (m_Rotation.y <= mCurrentRotation.down)
				mCurrentDirection = CDirection::Down;
		}
		else
			m_Rotation.y = mCurrentRotation.down;
		break;
		
	//上から
	case CDirection::Up:
		//左へ回転
		if (mCurrentDirection == CDirection::Left)
		{
			m_Rotation.y += mTurnSpeed;
			if (m_Rotation.y >= mCurrentRotation.up)
				mCurrentDirection = CDirection::Up;
		}
		//右へ回転
		else if (mCurrentDirection == CDirection::Right)
		{
			m_Rotation.y -= mTurnSpeed;
			if (m_Rotation.y <= mCurrentRotation.up)
				mCurrentDirection = CDirection::Up;
		}
		//下へ回転
		else if (mCurrentDirection == CDirection::Down)
		{
			m_Rotation.y += mTurnSpeed;
			if (m_Rotation.y >= mCurrentRotation.up)
				mCurrentDirection = CDirection::Up;
		}
		else
			m_Rotation.y = mCurrentRotation.up;
		break;
	//左から
	case CDirection::Left:
		//下へ回転
		if (mCurrentDirection == CDirection::Down)
		{
			m_Rotation.y += mTurnSpeed;
			if (m_Rotation.y >= mCurrentRotation.left)
				mCurrentDirection = CDirection::Left;
		}
		//右へ回転
		else if (mCurrentDirection == CDirection::Right)
		{
			m_Rotation.y -= mTurnSpeed;
			if (m_Rotation.y <= mCurrentRotation.left)
				mCurrentDirection = CDirection::Left;
		}
		//上へ回転
		else if (mCurrentDirection == CDirection::Up)
		{
			m_Rotation.y -= mTurnSpeed;
			if (m_Rotation.y <= mCurrentRotation.left)
				mCurrentDirection = CDirection::Left;
		}
		else
			m_Rotation.y = mCurrentRotation.left;
		break;
	//右から
	case CDirection::Right:
		//下へ回転
		if (mCurrentDirection == CDirection::Down)
		{
			m_Rotation.y -= mTurnSpeed;
			if (m_Rotation.y <= mCurrentRotation.right1)
			{
				mCurrentDirection = CDirection::Right;
				m_Rotation.y = mCurrentRotation.right;
			}
		}
		//左へ回転
		else if (mCurrentDirection == CDirection::Left)
		{
			m_Rotation.y += mTurnSpeed;
			if (m_Rotation.y >= mCurrentRotation.right)
				mCurrentDirection = CDirection::Right;
		}
		//上へ回転
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