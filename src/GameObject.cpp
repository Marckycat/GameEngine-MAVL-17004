#include "GameObject.h"

unsigned int GameObject::nextId = 0;

GameObject::GameObject()
{
	name = "GameObject";
	id = 0;
}

GameObject::~GameObject()
{
}

void GameObject::init()
{
	std::cout << "GameObject::init()" << std::endl;
	position = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
	position = { 0,0 };
	color = RED;
	//init(position, { 0,0 }, color);
}

void GameObject::init(Vector2 pos, Vector2 vel)
{
	position = pos;
	velocity = vel;
	color = RED;
}

void GameObject::init(Vector2 pos, Vector2 vel, Color c)
{
	position = pos;
	velocity = vel;
	color = c;
}

void GameObject::update()
{
	position.x += velocity.x * GetFrameTime();
	position.y += velocity.y * GetFrameTime();
	if (position.x > GetScreenWidth()) {
		position.x = 0;
	} if (position.x < 0) {
		position.x = GetScreenWidth();
	} if (position.y > GetScreenHeight()) {
		position.y = 0;
	} if (position.y < 0) {
		position.y = GetScreenHeight();
	}
}

void GameObject::draw()
{
	DrawCircle(position.x, position.y, 10, color);
}

void GameObject::setVelocity(Vector2 vel)
{
	velocity = vel;
}

GameObject* GameObject::Spawn(Vector2 pos, Vector2 vel, std::string _name)
{
	GameObject* obj = new GameObject();
	obj->init(pos, vel);
	obj->name = _name;
	obj->color = RED;
	nextId++;
	std::cout << "Objeto Creado" << obj->id << ":" << obj->name << std::endl;
	return obj;
}
