#include "GameManager.hpp"
#include "Enemy.hpp"
#include "Decoration.hpp"
#include "util/Globals.hpp"
#include "util/ObjectArray.hpp"

GameManager::GameManager() : player(std::make_shared<Player>()), camera(std::make_shared<GameFr::Camera2D>(GameFr::Camera2D::Modes::FOLLOW, player, GetScreenWidth(), GetScreenHeight())){
	eventInterface.AssignQueue(Global::eventQueue);
	SetObjectArrays();
}

void GameManager::SetObjectArrays(){
	for (auto& a : decorations.array){
		a = std::make_shared<Decoration>(camera);
	}
	for(auto& a : enemies.array){
		a = std::make_shared<Enemy>(player, camera);
	}
}

void GameManager::ListenForEvents(){
	//Act upon player death
	{
		const std::shared_ptr<const GameFr::Event> ev = eventInterface.Listen(GameFr::Event::Types::PLAYER_DEATH);
		if (ev){
			player->position = GameFr::Vector2();
			SetObjectArrays();
			projectileFactory.projectileList.clear();
		}
	}

}

void GameManager::Update(){
	BeginDrawing();
	ClearBackground(WHITE);

	projectileFactory.Update();
	decorations.UpdateAll();
	enemies.UpdateAll();
	player->Update();
	camera->Update();
	ListenForEvents();

	EndDrawing();
}

void GameManager::InitEntities(){
	player->SetCamera(camera);
	player->SetTexture();
}
