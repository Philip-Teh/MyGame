

void CBullet::Init()
{
	m_Position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	collision = new Collision();
	collision->SetPosition(m_Position);
	collision->SetRadius(0.5f);

	model = new CModel();
	model->Load("asset/miku_01.obj");

	//CBullet::enable = false;
}

void CBullet::Uninit()
{
	delete collision;

	model->Unload();
	delete model;
}

void CBullet::Update()
{
	//if (CBullet::enable)
	{
		m_Position.z += 0.1f;
		collision->SetPosition(m_Position);
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
	std::vector<CEnemy*>enemys;
	enemys = CSceneManager::GetScene()->GetGameObjects<CEnemy>(CHARACTER);
	
	for (CEnemy* enemy : enemys)
	{
		//XMFLOAT3 enemyPosition = enemy->GetPosition();
	
		if(Collision::OnCollisionEnter(collision,enemy->GetCollision()))
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

		model->Draw();
	}
}

void CBullet::Create(XMFLOAT3 position)
{
	m_Position = position;
	//CBullet::enable = true;
}