#pragma once

#include <graphics/sprite.h>

namespace gef
{
	class BetterSprite : public Sprite
	{

	public:

		BetterSprite();

		gef::Vector4 getSpeed();

		void setSpeed(gef::Vector4 _newspeed);

	protected:

		gef::Vector4 m_speed;

	};
}