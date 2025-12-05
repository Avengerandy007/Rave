#pragma once
#include <event.hpp>
#include <memory>
class GameManager;
namespace Global{
	const int nrOfDecorations = 50, nrOfEnemies = 100;
	extern std::shared_ptr<GameFr::EventQueue> eventQueue;
	extern std::unique_ptr<GameManager> game;
}
