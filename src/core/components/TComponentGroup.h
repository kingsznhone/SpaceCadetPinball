#pragma once
#include "core/TPinballComponent.h"
namespace scp {


class TComponentGroup :
	public TPinballComponent
{
public:
	TComponentGroup(TPinballTable* table, int groupIndex);
	~TComponentGroup() override;
	int Message(MessageCode code, float value) override;
	static void NotifyTimerExpired(int timerId, void* caller);

	std::vector<TPinballComponent*> List;
	int Timer;
};
} // namespace scp
