#pragma once
#include <entityx\entityx.h>

using namespace entityx;

namespace px
{
	class TransformSystem : public System<TransformSystem>
	{
	public:
		explicit TransformSystem();

	public:
		virtual void update(EntityManager &es, EventManager &events, TimeDelta dt) override;
	};
}