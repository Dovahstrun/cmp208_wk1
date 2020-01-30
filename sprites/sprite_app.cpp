#include "sprite_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <maths/math_utils.h>
//#include <stdlib.h>     /* srand, rand */


SpriteApp::SpriteApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	font_(NULL),
	my_sprites(),
	addTime(0.0f),
	destroyTime(0.0f)
{
	srand(time(NULL));
}

void SpriteApp::Init()
{
	// create a sprite renderer to draw your sprites
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);

	InitFont();

	gef::BetterSprite newSprite;
	newSprite.set_position(platform_.width()*0.5f, platform_.height()*0.5f, 0.0f);
	newSprite.set_width(32.0f);
	newSprite.set_height(32.0f);
	my_sprites.push_back(newSprite);
}

void SpriteApp::CleanUp()
{
	CleanUpFont();

	// destroy sprite renderer once you've finished using it
	delete sprite_renderer_;
	sprite_renderer_ = NULL;
}

bool SpriteApp::Update(float frame_time)
{
	// frame rate = 1 second / frame_delta_time
	fps_ = 1.0f / frame_time;

	//Add sprites to screen
	addTime += frame_time;
	if (addTime > 0.5f)
	{
		gef::BetterSprite newSprite;
		newSprite.set_position(rand() % 961, rand() % 545, 0.0f);
		newSprite.set_width(32.0f);
		newSprite.set_height(32.0f);
		my_sprites.push_back(newSprite);
		addTime = 0.0f;
	}

	//Destroy sprites
	destroyTime += frame_time;
	if (destroyTime > 10.0f)
	{
		my_sprites.clear();
		destroyTime = 0.0f;
	}

	// move the sprite along the x-axis

	// get a copy of the current position of the sprite
	std::vector<gef::Vector4> sprite_positions;
	for (int i = 0; i < my_sprites.size(); ++i)
	{
		sprite_positions.push_back(my_sprites[i].position());
	}

	// update the sprite with the new position
	for (int i = 0; i < my_sprites.size(); ++i)
	{
		my_sprites[i].set_position(sprite_positions[i] + my_sprites[i].getSpeed());
	}

	return true;
}

void SpriteApp::Render()
{
	// draw all sprites between the Begin() and End() calls
	sprite_renderer_->Begin();

	// draw my sprite here
	for (int i = 0; i < my_sprites.size(); ++i)
	{
		sprite_renderer_->DrawSprite(my_sprites[i]);
	}

	DrawHUD();
	sprite_renderer_->End();
}


void SpriteApp::InitFont()
{
	// create a Font object and load in the comic_sans font data
	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");
}

void SpriteApp::CleanUpFont()
{
	// destroy the Font object
	delete font_;
	font_ = NULL;
}

void SpriteApp::DrawHUD()
{
	if(font_)
	{
		// display frame rate
		font_->RenderText(
			sprite_renderer_,						// sprite renderer to draw the letters
			gef::Vector4(650.0f, 510.0f, -0.9f),	// position on screen
			1.0f,									// scale
			0xffffffff,								// colour ABGR
			gef::TJ_LEFT,							// justification
			"FPS: %.1f xpos: %.1f",							// string of text to render
			fps_,									// any variables used in formatted text string http://www.cplusplus.com/reference/cstdio/printf/
			my_sprites[0].position().x()
			);
	}
}

