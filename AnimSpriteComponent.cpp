#include"AnimSpriteComponent.h"
#include"BackgroundSpriteComponent.h"
#include"Actor.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* ownerP, const vector<Texture*>& textureP, int drawOrderP) :
	SpriteComponent(ownerP, *textureP[0], drawOrderP),
	currentFrame(0.0f),
	animFPS(24.0f)
{
	setAnimTextures(textureP);
}
AnimSpriteComponent::~AnimSpriteComponent()
{

}
void AnimSpriteComponent::setAnimTextures(const vector<Texture*>& texturesP)
{
	animTextures = texturesP;
	if (animTextures.size() > 0)
	{
		currentFrame = 0.f;
		setTexture(*animTextures[0]);
	}
}
void AnimSpriteComponent::setAnimFPS(float animFPSP)
{
	animFPS = animFPSP;
}
void AnimSpriteComponent::update(float dt)
{
	SpriteComponent::update(dt);

	if (animTextures.size() > 0)
	{
		currentFrame += animFPS * dt;
		while (currentFrame >= animTextures.size())
		{
			currentFrame -= animTextures.size();
		}
		setTexture(*animTextures[static_cast<int>(currentFrame)]);
	}
}
BackgroundSpriteComponent::BackgroundSpriteComponent(Actor* ownerP, const vector<Texture*>& texturesP, int drawOrderP) :
	SpriteComponent(ownerP, *texturesP[0], drawOrderP),
	scrollSpeed(0.0f),
	screenSize(Vector2(WINDOW_WIDTH, WINDOW_HEIGHT))
{
	setTextures(texturesP);
}
BackgroundSpriteComponent::~BackgroundSpriteComponent()
{

}
void BackgroundSpriteComponent::update(float dt)
{
	SpriteComponent::update(dt);
	for (auto& bg : textures)
	{
		bg.offset.x += scrollSpeed * dt;
		//If thi is completely off the screen, reset offset to the right of the last bg
		if (bg.offset.x < -screenSize.x)
		{
			bg.offset.x = (textures.size() - 1) * screenSize.x - 1;
		}
	}
}
void BackgroundSpriteComponent::draw(Renderer& renderer)
{
	for (auto& bg : textures)
	{
		owner.setPosition(Vector2(bg.offset.x, bg.offset.y));
		renderer.drawSprite(owner, bg.texture, Rectangle::nullRect, Vector2::zero, Renderer::Flip::None);
	}
}
void BackgroundSpriteComponent::setTextures(const vector<Texture*>& texturesP)
{
	int count = 0;
	for (auto tex : texturesP)
	{
		BGTexture temp{ *tex, Vector2(count * screenSize.x, 0) };
		textures.emplace_back(temp);
		count++;
	}
}
void BackgroundSpriteComponent::setScreenSize(const Vector2& screenSizeP)
{
	screenSize = screenSizeP;
}
void BackgroundSpriteComponent::setScrollSpeed(float scrollSpeedP)
{
	scrollSpeed = scrollSpeedP;
}