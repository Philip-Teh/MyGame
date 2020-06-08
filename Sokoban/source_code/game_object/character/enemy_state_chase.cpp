

void CEnemyStateChase::ActionTime()
{
	mRand = std::rand() / 100;
}

CAction CEnemyStateChase::Action(CEnemyTroop* p)
{
	mFrame++;

	if (mFrame >= mRand)
	{
		//ˆÚ“®ó‘Ô‚Ö
		p->ChangeState(new CEnemyStateMove());
		return CAction::Move;
	}
	else
		return CAction::Idle;
}