#pragma once
#include "../Systems/SoundSystem.h"
class SoundComponent
{
public:
	enum SFX_Type
	{
		WALK,
		ATTACK,
		DIE
	};
	SoundComponent();
	void PlaySFX(SFX_Type);
private:
	SoundSystem* m_sound_system;
};

