#include "BetterSprite.h"

gef::BetterSprite::BetterSprite()
	: m_speed(0,0,0,0)
{

}

gef::Vector4 gef::BetterSprite::getSpeed()
{
	return m_speed;
}

void gef::BetterSprite::setSpeed(gef::Vector4 _newspeed)
{
	m_speed = _newspeed;
}
