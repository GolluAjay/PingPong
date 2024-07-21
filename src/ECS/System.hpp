#pragma once
#include <vector>
#include <memory>
#include "Entity.hpp"

class System
{
public:
	virtual ~System() = default;
	void addEntity(std::shared_ptr<Entity> entity);
	virtual void update(float deltaTime) = 0;

protected:
	 std::vector<std::shared_ptr<Entity>> entities;
};

inline void System::addEntity(std::shared_ptr<Entity> entity) {
    entities.push_back(entity);
}
