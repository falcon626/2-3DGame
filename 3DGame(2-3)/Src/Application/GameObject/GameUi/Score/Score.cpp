#include "Score.h"
#include "../../../System/Counter/Counter.h"

Score::Score()
{
	m_spTex = FlDataStorage::Instance().GetTexture("Numbers/numbersBox.png");

	m_spCounter = std::make_shared<Counter>(m_spTex);
}

void Score::DrawSprite()
{
	m_spCounter->DrawSpriteCounter();
}
