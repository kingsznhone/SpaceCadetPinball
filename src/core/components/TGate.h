#pragma once
#include "core/TCollisionComponent.h"
namespace scp {

class TGate :
	public TCollisionComponent
{
public:
	TGate(TPinballTable* table, int groupIndex);
	int Message(MessageCode code, float value) override;

	int SoundIndex4;
	int SoundIndex3;
};
} // namespace scp
