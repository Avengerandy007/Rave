#include "Decoration.hpp"
#include "GameManager.hpp"
#include "util/TextureArrays.hpp"
#include "Player.hpp"
#include <event.hpp>
#include <util/vectors.hpp>

Decoration::Decoration(const std::shared_ptr<GameFr::Camera2D> cam) : camera(cam), random(-GetScreenWidth(), GetScreenWidth()){
	eventInterface.AssignQueue(Global::eventQueue);
	position.X = random.GetRandomNumber();
	position.Y = random.GetRandomNumber();
	random.ChangeRange(0, 1);
	texture = Util::TextureArrays::decorations[random.GetRandomNumber()];
	player = std::reinterpret_pointer_cast<Player>(camera->entity);
}

void Decoration::DetectCollisions() {
	if (CollidingCircle(*player, 100)){
		GameFr::Util::EventDataPoint dataPoint(position, std::array<int, 10>());
		const std::shared_ptr<GameFr::Event> ev = std::make_shared<GameFr::Event>(GameFr::Event::Types::COLLISION, GetPtr(), player, dataPoint);
		if (!ev) return;
		eventInterface.queue->CreateEvent(ev);
	}

	for (auto enemy : Global::game->enemies.array){
		if (CollidingCircle(*enemy, 50)){
			const GameFr::Util::EventDataPoint data(position, {});
			const std::shared_ptr<const GameFr::Event> ev = std::make_shared<const GameFr::Event>(GameFr::Event::Types::COLLISION, GetPtr(), enemy, data);
			if (!ev) return; 
			eventInterface.queue->CreateEvent(ev);
		}
	}

}

void Decoration::Update(){
	Regenerate();
	GetRenderingPosition(*camera);
	DetectCollisions();
	if (onScreen && texture){
		DrawTexture(texture->texture, renderingPosition.X, renderingPosition.Y, WHITE);
	}
}

void Decoration::Regenerate(){
	//check if distance between this and player is larger than the resolution on X
	if (std::abs(player->position.X - position.X) > camera->resolutionX){
		//make sure that the player's direction is positive so the random minimum is smaller than the max
		if (player->direction.X >= 0){
			random.ChangeRange((int)(player->position.X + camera->resolutionX), (int)(player->position.X  + (camera->resolutionX + 600)));
		}else{
			random.ChangeRange((int)(player->position.X - (camera->resolutionX + 600)), (int)(player->position.X - camera->resolutionX));
		}
		position.X = random.GetRandomNumber();
		random.ChangeRange(0, 1);
		texture = Util::TextureArrays::decorations[random.GetRandomNumber()];
	}
	//check if distance between this and player is larger than the resolution on Y
	if (std::abs(player->position.Y - position.Y) > camera->resolutionY){
		//make sure that the player's direction is positive so the random minimum is smaller than the max
		if (player->direction.Y >= 0) {
			random.ChangeRange((int)(player->position.Y +  camera->resolutionY), (int)(player->position.Y +  (camera->resolutionY + 600)));
		} else {
			random.ChangeRange((int)(player->position.Y - (camera->resolutionY + 600)), (int)(player->position.Y - camera->resolutionY));
		}
		position.Y = random.GetRandomNumber();
		random.ChangeRange(0, 1);
		texture = Util::TextureArrays::decorations[random.GetRandomNumber()];
	}
}
