#pragma once
#include "core/TPinballComponent.h"
namespace scp {

class TTimer :
	public TPinballComponent
{
public:
	TTimer(TPinballTable* table, int groupIndex);
	int Message(MessageCode code, float value) override;
	static void TimerExpired(int timerId, void* caller);

	int Timer;
};
} // namespace scp
