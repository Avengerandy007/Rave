#pragma once
#include <array>
#include <cstdint>
#include "util/vectors.hpp"
#include <memory>
#include "util/SmartCounter.hpp"

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
		const Types type;				//do I really need to explain this?
		const std::shared_ptr<const Entity2D> sender; 	//object who created this
		const std::shared_ptr<const Entity2D> receiver; //object for whom it's meant for
		const Util::EventDataPoint dataPoint;		//additional data to send along
		Event(const Types t, const std::shared_ptr<const Entity2D> s, const std::shared_ptr<const Entity2D> r, const Util::EventDataPoint d);
	};

	struct EventQueue{
		std::array<std::shared_ptr<const Event>, 10000> queue;
		void CreateEvent(const std::shared_ptr<const Event>& event); //append an event object ptr at qp in queue
		Util::SmartCounter<uint16_t, 0, 9999, 1> qp;
	};

	//Object to interface to queue
	class EventInterface{
		//queue ptr (where should it start iterating from on Listen)
		Util::SmartCounter<uint16_t, 0, 9999, 1> qp;
	public:
		std::shared_ptr<EventQueue> queue;	//ptr to assigned queue
		EventInterface();
		EventInterface(const EventInterface& other);

		//iterates over elements >= qp and <= queue->qp in queue->queue, returns nullptr if nothing is foun
		std::shared_ptr<const Event> Listen(const std::shared_ptr<const Entity2D> parent); //returns first element to match parent argument in Event::receiver
		std::shared_ptr<const Event> Listen(const Event::Types desiredType); //returns first element to match desired type

		void AssignQueue(const std::shared_ptr<EventQueue> q);
	};

	//You can add new event types here
	enum struct Event::Types{
		COLLISION,
		SHOOT,
		MOVEMENT,
		PLAYER_DEATH
	};

}
