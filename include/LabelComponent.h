#pragma once
#include "Component.h"

class LabelComponent : public Component
{
public:
	~LabelComponent() override = default;
	void Start() override;
	void Update(float deltaTime) override;
	void Draw(float deltaTime) override;
};

