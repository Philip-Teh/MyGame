
void CEnemyStateMove::ActionTime()
{
	mRand = std::rand() / 100;
}

CAction CEnemyStateMove:: Action(CEnemyTroop* p)
{
	mFrame++;

	if (mFrame >= mRand)
	{
		//待機状態へ
		p->ChangeState(new CEnemyStateIdle());
		return CAction::Idle;
	}
	else
		return CAction::Move;
}