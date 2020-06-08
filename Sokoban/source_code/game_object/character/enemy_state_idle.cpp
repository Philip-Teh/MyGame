

void CEnemyStateIdle::ActionTime()
{
	mRand = std::rand() / 100;


}

CAction CEnemyStateIdle::Action(CEnemyTroop* p)
{
	mFrame++;

	if (mFrame >= mRand)
	{
		//�ړ���Ԃ�
		p->ChangeState(new CEnemyStateMove());
		return CAction::Move;
	}
	else
		return CAction::Idle;
}