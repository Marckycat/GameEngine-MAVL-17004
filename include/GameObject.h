#pragma once
#include "raylib.h"
#include "Component.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

typedef std::shared_ptr<Component> ptrComponent;

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
	int id;

	Vector2 position;
	Vector2 velocity;
	Color color;
	void setVelocity(Vector2 vel);

	static GameObject* Spawn(Vector2 pos, Vector2 vel, std::string _name);

	void Start();
	void Update(float deltaTime);
	void Draw(float deltaTime);

	void AddComponent(ptrComponent newComp);
	void RemoveComponent();

private:
	std::vector<ptrComponent> components;

	//unsigned int id;
	std::string name;
	static unsigned int nextId;

	friend class Component;
};

