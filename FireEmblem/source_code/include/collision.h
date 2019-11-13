#ifndef COLLISION_H_
#define COLLISION_H_


class Collision
{
private:
	XMFLOAT3 position;
	float radius;
public:
	static bool OnCollisionEnter(const Collision* pA,const Collision* pB)
	{
		//return XMVector3LengthSq(&(pA.position - pB.position)) < (abr * abr);

		float abr = pA->radius + pB->radius;
		//float ll = (pA->position.x - pB->position.x) * (pA->position.x - pB->position.x)
		//	+ (pA->position.y - pB->position.y) * (pA->position.y - pB->position.y)
		//	+ (pA->position.z - pB->position.z) * (pA->position.z - pB->position.z);

		XMVECTOR LL = XMLoadFloat3(&pA->position) - XMLoadFloat3(&pB->position);
		float ll = XMVectorGetW(XMVector3Dot(LL, LL));

		return (abr * abr) > ll;
	}

	void SetPosition(XMFLOAT3 Position) { position = Position; }
	void SetRadius(float Radius) { radius = Radius; }

};

#endif // !COLLISION_H_
