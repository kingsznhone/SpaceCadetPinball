#pragma once
#include "core/components/TRollover.h"
namespace scp {

class TTripwire :
	public TRollover
{
public:
	TTripwire(TPinballTable* table, int groupIndex);
	~TTripwire() override = default;
	void Collision(TBall* ball, vector2* nextPosition, vector2* direction, float distance,
	               TEdgeSegment* edge) override;
};
} // namespace scp
