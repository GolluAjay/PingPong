#pragma once
#include <vector>
#include <memory>

class Component;

class Entity
{
public:
	void addComponent(std::shared_ptr<Component> component);
	template <typename T>
	std::shared_ptr<T> getComponent();

private:
	std::vector<std::shared_ptr<Component>> components;
};

template <typename T>
std::shared_ptr<T> Entity::getComponent()
{
	for (auto &component : components)
	{
		if (std::shared_ptr<T> comp = std::dynamic_pointer_cast<T>(component))
		{
			return comp;
		}
	}
	return nullptr;
}
