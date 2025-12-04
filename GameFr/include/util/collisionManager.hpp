#include "event.hpp"
#include "entities.hpp"
#include <cstdint>
#include <memory>
#include <vector>

namespace GameFr::Util{
	class CollisionManager{
	public:
		virtual void Update();
		void AddEntities(const std::vector<std::shared_ptr<Entity2D>>& additions);
		void AddEntities(const std::shared_ptr<Entity2D>& addition);
		template<int n>
		void AddEntities(const std::array<std::shared_ptr<Entity2D>, n>& additions);
		void SetCollisionMode(const bool useAABBCollision);
		void AssignEventQueue(const std::shared_ptr<EventQueue> eventQueue);
		CollisionManager(const bool useAABBCollision, const std::shared_ptr<EventQueue> eventQueue, const std::vector<std::shared_ptr<Entity2D>>& list);
		CollisionManager();

		template<int n>
		CollisionManager(const bool useAABBCollision, const std::shared_ptr<EventQueue> eventQueue, const std::array<std::shared_ptr<Entity2D>, n>& list);
	private:
		EventInterface eventInterface;
		bool useAABB;
		std::vector<std::shared_ptr<Entity2D>> entities;
		uint32_t iterations;
		virtual bool CheckCollision(const std::shared_ptr<Entity2D>& first, const std::shared_ptr<Entity2D>& second);
	};
}
