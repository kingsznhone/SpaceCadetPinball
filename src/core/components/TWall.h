#pragma once

#include "core/TCollisionComponent.h"
namespace scp {

class TWall :
	public TCollisionComponent
{
public:
	TWall(TPinballTable* table, int groupIndex);
	int Message(MessageCode code, float value) override;
	void Collision(TBall* ball, vector2* nextPosition, vector2* direction, float distance,
	               TEdgeSegment* edge) override;

	static void TimerExpired(int timerId, void* caller);

	int Timer{};
};
} // namespace scp
