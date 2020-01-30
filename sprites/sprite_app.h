#ifndef _sprite_app_H
#define _sprite_app_H

#include <system/application.h>
#include <BetterSprite.h>
#include <maths/vector4.h>
#include <vector>

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
}

class SpriteApp : public gef::Application
{
public:
	SpriteApp(gef::Platform& platform);
	void Init();
	void CleanUp();
	bool Update(float frame_time);
	void Render();
private:
	void InitFont();
	void CleanUpFont();
	void DrawHUD();

	gef::SpriteRenderer* sprite_renderer_;
	gef::Font* font_;

	float fps_;
	float addTime;
	float destroyTime;
	std::vector<gef::BetterSprite> my_sprites;
};

#endif // _sprite_app_H
