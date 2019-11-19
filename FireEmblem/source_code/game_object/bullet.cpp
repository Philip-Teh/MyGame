

void CBullet::Init()
{
	m_Position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	mpCollision = new Collision();
	mpCollision->SetPosition(m_Position);
	mpCollision->SetRadius(0.5f);

	mpModel = new CModel();
	mpModel->Load("asset/miku_01.obj");

	//CBullet::enable = false;
}

void CBullet::Uninit()
{
	delete mpCollision;

	mpModel->Unload();
	delete mpModel;
}

void CBullet::Update()
{
	//if (CBullet::enable)
	{
		m_Position.z += 0.1f;
		mpCollision->SetPosition(m_Position);
	}


	//一つオブジェクトの当たり判定
	//CEnemy* enemy;
	//enemy = CManager::GetScene()->GetGameObject<CEnemy>(CHARACTER);
	//
	//if (enemy != nullptr)
	//{
	//	XMFLOAT3 enemyPosition = enemy->GetPosition();
	//
	//	if (Collision::OnCollisionEnter(collision,enemy->collision))
	//	{
	//		CManager::GetScene()->DestroyGameObject(enemy);
	//		CManager::GetScene()->DestroyGameObject(this);
	//		return;
	//	}
	//}

	//複数オブジェクトの当たり判定
	std::vector<CBEnemy*>enemys;
	enemys = CSceneManager::GetScene()->GetGameObjects<CBEnemy>(CHARACTER);
	
	for (CBEnemy* enemy : enemys)
	{
		//XMFLOAT3 enemyPosition = enemy->GetPosition();
	
		if(Collision::OnCollisionEnter(mpCollision,enemy->GetCollision()))
		{
			CSceneManager::GetScene()->DestroyGameObject(enemy);
			CSceneManager::GetScene()->DestroyGameObject(this);
			return;
		}
	}


	if (m_Position.z > WORLD_Z)
	{
		CSceneManager::GetScene()->DestroyGameObject(this);
		return;
	}
	if (m_Position.x > WORLD_X)
	{
		CSceneManager::GetScene()->DestroyGameObject(this);
		return;
	}
}

void CBullet::Draw()
{
	//if (CBullet::enable)
	{
		// マトリクス設定																
		XMMATRIX world;
		world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
		CRenderer::SetWorldMatrix(&world);

		mpModel->Draw();
	}
}

void CBullet::Create(XMFLOAT3 position)
{
	m_Position = position;
	//CBullet::enable = true;
}