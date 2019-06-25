#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <memory>
#include <vector>

class Component;
class Entity;
class Manager;

using ComponentId = std::size_t;
using Group = std::size_t;

inline ComponentId
getComponentId()
{
  static ComponentId lastId = 0;

  return lastId++;
}

template<typename T>
inline ComponentId
getComponentTypeId() noexcept
{
  static ComponentId typeId = getComponentId();

  return typeId;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using GroupBitset = std::bitset<maxGroups>;

using ComponentBitset = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
  Entity* entity;

  virtual void init() {}
  virtual void update() {}
  virtual void draw() {}

  virtual ~Component() {}
};

class Entity
{
private:
  bool active = true;
  std::vector<std::unique_ptr<Component>> components;

  ComponentArray componentArray;
  ComponentBitset componentBitset;

  GroupBitset groupBitset;

  Manager* m;

public:
  Entity(Manager& manager)
    : m(&manager)
  {}

  void update()
  {
    for (auto& c : components) {
      c->update();
    }
  }

  void draw()
  {
    for (auto& c : components) {
      c->draw();
    }
  }

  inline bool isActive() const { return active; }
  inline void destroy() { active = false; }
  inline bool hasGroup(Group g) { return groupBitset[g]; }
  void addGroup(Group g);
  void removeGroup(Group g) { groupBitset[g] = false; }

  template<typename T>
  bool hasComponent() const
  {
    return componentBitset[getComponentTypeId<T>()];
  }

  template<typename T, typename... Args>
  T& addComponent(Args&&... params)
  {
    std::unique_ptr<T> c = std::make_unique<T>(std::forward<Args>(params)...);
    c->entity = this;

    componentBitset[getComponentTypeId<T>()] = true;
    componentArray[getComponentTypeId<T>()] = c.get();

    c->init();

    components.emplace_back(std::move(c));

    return static_cast<T&>(*componentArray[getComponentTypeId<T>()]);
  }

  template<typename T>
  T& getComponent() const
  {
    return static_cast<T&>(*componentArray[getComponentTypeId<T>()]);
  }
};

class Manager
{
private:
  std::vector<std::unique_ptr<Entity>> entities;
  std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:
  Manager() {}

  void update()
  {
    for (int i = 0; i < entities.size(); ++i)
      entities[i]->update();
  }

  void draw()
  {
    for (auto& e : entities)
      e->draw();
  }

  void refresh()
  {
    for (auto i = 0; i < maxGroups; ++i) {
      auto& v = groupedEntities[i];
      auto beginEraseIterator =
        std::remove_if(v.begin(), v.end(), [i](Entity* e) {
          return !e->isActive() || !e->hasGroup(i);
        });
      v.erase(beginEraseIterator, v.end());
    }

    // erase remove idiom
    auto beginEraseIt =
      std::remove_if(entities.begin(),
                     entities.end(),
                     [](std::unique_ptr<Entity>& e) { return !e->isActive(); });
    entities.erase(beginEraseIt, entities.end());
  }

  void addToGroup(Entity* e, Group g) { groupedEntities[g].emplace_back(e); }

  std::vector<Entity*>& getGroup(Group g) { return groupedEntities[g]; }

  Entity& addEntity(Entity*& e)
  {
    entities.emplace_back(std::move(e));
    auto entityPtr = entities.back().get();
    for (auto i = 0; i < maxGroups; ++i) {
      if (entityPtr->hasGroup(i))
        groupedEntities[i].push_back(entityPtr);
    }

    return *entityPtr;
  }

  Entity& addEntity()
  {
    auto e = std::make_unique<Entity>(*this);

    entities.emplace_back(std::move(e));

    return *entities.back();
  }
};
