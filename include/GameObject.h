#pragma once
#include "raylib.h"
#include <iostream>
#include <string>

class GameObject {
public:
	GameObject();
	~GameObject();
	void init(); //o setup
	void init(Vector2 pos, Vector2 vel);
	void init(Vector2 pos, Vector2 vel, Color c);
	void update();
	void draw();

	//Si se debe updeatear este objeto
	bool enabled;

	Vector2 position;
	Vector2 velocity;
	Color color;
	void setVelocity(Vector2 vel);

	static GameObject* Spawn(Vector2 pos, Vector2 vel, std::string _name);

private:
	unsigned int id;
	std::string name;
	static unsigned int nextId;

	friend class GameObject;
};

