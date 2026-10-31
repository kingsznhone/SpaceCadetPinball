#pragma once
#include "core/TPinballComponent.h"
namespace scp {

class TSound :
	public TPinballComponent
{
public:
	TSound(TPinballTable* table, int groupIndex);
	float Play(TPinballComponent *soundSource, const char* info);

	int SoundIndex;
};
} // namespace scp
