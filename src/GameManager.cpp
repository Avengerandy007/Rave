#include "GameManager.hpp"
#include "Enemy.hpp"

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
			player->position.X = 0;
			player->position.Y = 0;
			for (auto entity : enemies.array){
				auto enemy = std::dynamic_pointer_cast<Enemy>(entity);
				enemy->Respawn();
			}
			for (auto entity : decorations.array){
				auto deco = std::dynamic_pointer_cast<Decoration>(entity);
				deco->Update();
			}
			projectileFactory.projectileList.clear();
		}
	}

}

void GameManager::Update(){
	BeginDrawing();
	ClearBackground(WHITE);

	enemies.UpdateAll();
	projectileFactory.Update();
	decorations.UpdateAll();
	player->Update();
	camera->Update();
	ListenForEvents();

	for (uint32_t i = 0; i < vfx.size(); i++){
		if (vfx[i]->ShouldDestroy()){
			vfx.erase(vfx.begin() + i);
			i--;
			continue;
		}
		vfx[i]->Update();
	}

	EndDrawing();
}

void GameManager::InitEntities(){
	player->SetCamera(camera);
}
