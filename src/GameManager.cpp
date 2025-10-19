#include "GameManager.hpp"
#include <camera.hpp>
#include <memory>

GameManager::GameManager() : player(std::make_shared<Player>()), camera(std::make_shared<GameFr::Camera2D>(GameFr::Camera2D::Modes::FOLLOW, player, 1000, 1000)){}
