#pragma once
#include <array>
#include <cstdint>
#include "util/vectors.hpp"
#include <memory>
#include <vector>

namespace GameFr{
class Entity2D;

	namespace Util{
		struct EventDataPoint{
			const Vector2 position;
			const std::array<int, 10> additionalData;
			EventDataPoint(const EventDataPoint& dataPoint);
			EventDataPoint(const Vector2& pos, const std::array<int, 10>& additionalData);
		};
	}

	struct Event{
		enum struct Types;
		const Types type;
		const std::shared_ptr<const Entity2D> sender;
		const std::shared_ptr<const Entity2D> receiver;
		const Util::EventDataPoint dataPoint;
		Event(const Types t, const std::shared_ptr<const Entity2D> s, const std::shared_ptr<const Entity2D> r, const Util::EventDataPoint d);
	};

	struct EventQueue{
		std::vector<std::shared_ptr<const Event>> queue;
		void CreateEvent(std::shared_ptr<const Event> event);
		uint64_t qp = 0; //queue pointer
	};

	class EventInterface{
		uint64_t localQp = 0;
	public:
		std::shared_ptr<EventQueue> queue;
		EventInterface();
		EventInterface(const EventInterface& other);
		std::shared_ptr<const Event> Listen(const std::shared_ptr<const Entity2D> parent);
		void AssignQueue(const std::shared_ptr<EventQueue> q);
	};

	enum struct Event::Types{
		COLLISION,
		MOVEMENT,
	};

}
