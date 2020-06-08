
void CEnemyStateMove::ActionTime()
{
	mRand = std::rand() / 100;
}

CAction CEnemyStateMove:: Action(CEnemyTroop* p)
{
	mFrame++;

	if (mFrame >= mRand)
	{
		//‘Ò‹@ó‘Ô‚Ö
		p->ChangeState(new CEnemyStateIdle());
		return CAction::Idle;
	}
	else
		return CAction::Move;
}