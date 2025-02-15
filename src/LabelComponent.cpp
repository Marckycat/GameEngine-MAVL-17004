#include "LabelComponent.h"

void LabelComponent::Start()
{
}

void LabelComponent::Update(float deltaTime)
{
}

void LabelComponent::Draw(float deltaTime)
{
	DrawText("holamundo", 100, 100, 16, BLACK);
}
