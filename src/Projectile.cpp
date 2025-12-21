#include "Projectile.hpp"
#include "util/TextureArrays.hpp"
#include "GameManager.hpp"
#include <assert.h>

ProjectileFactory::ProjectileFactory(){
	eventInterface.AssignQueue(Global::eventQueue);
}

void Projectile::OnCollision(){
	switch (type){
		case Types::NORMAL: break;

		case Types::EXPLOSIVE:
			if (sender == Senders::PLAYER){
				for (auto& enemy : Global::game->enemies.array){
					if (CollidingCircle(*enemy, 100)){
						GameFr::Util::EventDataPoint data(position, {});
						GameFr::Event ev (GameFr::Event::Types::COLLISION, GetPtr(), enemy, data);
						eventInterface.queue->CreateEvent(std::make_shared<const GameFr::Event>(ev));
					}
					
				}
			}
			else if (sender != Senders::PLAYER && CollidingCircle(*player, 100)){
				GameFr::Util::EventDataPoint data(position, {});
				GameFr::Event ev (GameFr::Event::Types::COLLISION, GetPtr(), player, data);
				eventInterface.queue->CreateEvent(std::make_shared<const GameFr::Event>(ev));
			}
			//create the explosion effect
			Global::game->vfx.push_back(std::make_shared<Vfx>(Util::TextureArrays::decorations[2], std::chrono::milliseconds(2000), position));

		break;
		case Types::IDK: break;
	}
}

void ProjectileFactory::Update(){
	{
		auto ev = eventInterface.Listen(GameFr::Event::Types::SHOOT);
		while (ev){
			if (projectileList.size() >= 750){
				//just give it some rest if there are a lot of shoot events in the queue
				break;
			}
			if (ev->dataPoint.additionalData[2] == 0){
				projectileList.emplace_back(std::make_shared<Projectile>((Projectile::Types)ev->dataPoint.additionalData[0], ev->dataPoint.position, ev->sender->position, Global::game->camera, (Projectile::Senders)ev->dataPoint.additionalData[1]));
			}
			else{
				projectileList.emplace_back(std::make_shared<Projectile>((Projectile::Types)ev->dataPoint.additionalData[0], ev->dataPoint.position, ev->sender->position, Global::game->camera, (Projectile::Senders)ev->dataPoint.additionalData[1], ev->dataPoint.additionalData[2]));
			}
			ev = eventInterface.Listen(GameFr::Event::Types::SHOOT);
			
		}
		if (projectileList.size() >= 700) {
			projectileList.erase(projectileList.begin(), projectileList.begin() + (projectileList.size() - 699));
		}
		for (size_t i = 0; i < projectileList.size(); i++){
			auto& projectile = projectileList[i];
			if (std::chrono::system_clock::now() - projectile->creationTime >= std::chrono::seconds(10)){
				assert(i < projectileList.size());
				projectileList.erase(projectileList.begin() + i);
				i--;
				continue;
			}
			projectileList[i]->Update();
		}
	}
	{
		auto ev = eventInterface.Listen(GameFr::Event::Types::COLLISION);
		if (ev){
			auto sender = std::dynamic_pointer_cast<const Projectile>(ev->sender);
			if (sender){
				//check if original ptr still exitsts in vector
				auto i = std::find(projectileList.begin(), projectileList.end(), sender);
				if (i != projectileList.end()){
					projectileList.erase(i);
				}
			}
		}
	}
}

Projectile::Projectile(const Projectile& other) : type(other.type), random(other.random), creationTime(other.creationTime), player(Global::game->player), sender(other.sender){
	eventInterface = other.eventInterface;
	camera = other.camera;
	speed = other.speed;
	position = other.position;
	targetDirection = other.targetDirection;
	renderingPosition = other.renderingPosition;
	texture = other.texture;
}

Projectile::Projectile(const Types t, const GameFr::Vector2 target, const GameFr::Vector2 startingPosition, const std::shared_ptr<GameFr::Camera2D> cam, const Senders send) : type(t), targetDirection(target), random(8, 16), creationTime(std::chrono::system_clock::now()), player(Global::game->player), sender(send){
	eventInterface.AssignQueue(Global::eventQueue);
	position = startingPosition;
	camera = cam;
	speed = random.GetRandomNumber();
	width = 39;
	height = 16;
	targetDirection.Normalize();
	texture = Util::TextureArrays::enemies[1];
	rotation = std::acos(targetDirection.X / (targetDirection.Magnitude())) * 57 + 180;
	rotation = (targetDirection.Y < 0) ? -rotation : rotation;
}

Projectile::Projectile(const Types t, const GameFr::Vector2 target, const GameFr::Vector2 startingPosition, const std::shared_ptr<GameFr::Camera2D> cam, const Senders send, const int p_Speed) : type(t), targetDirection(target), random(4, 7), creationTime(std::chrono::system_clock::now()), player(Global::game->player), sender(send){
	eventInterface.AssignQueue(Global::eventQueue);
	position = startingPosition;
	camera = cam;
	width = 39;
	height = 16;
	speed = p_Speed;
	targetDirection.Normalize();
	texture = Util::TextureArrays::enemies[1];
	rotation = std::acos(targetDirection.X / (targetDirection.Magnitude())) * 57 + 180;
	rotation = (targetDirection.Y < 0) ? -rotation : rotation;
}

void Projectile::Collide(){

	for (auto& decoration : Global::game->decorations.array){
		if (CollidingCircle(*decoration, 30)){
			GameFr::Util::EventDataPoint data(position, {});
			GameFr::Event ev (GameFr::Event::Types::COLLISION, GetPtr(), decoration, data);
			eventInterface.queue->CreateEvent(std::make_shared<const GameFr::Event>(ev));
			OnCollision();
		}
	}

	if (CollidingCircle(*player, 50) && sender != Senders::PLAYER){
		GameFr::Util::EventDataPoint data(position, {});
		GameFr::Event ev (GameFr::Event::Types::COLLISION, GetPtr(), player, data);
		eventInterface.queue->CreateEvent(std::make_shared<const GameFr::Event>(ev));
		OnCollision();
	}
	if (sender == Senders::PLAYER){
		for (auto& enemy : Global::game->enemies.array){
			if (CollidingCircle(*enemy, 45)){
				GameFr::Util::EventDataPoint data(position, {});
				GameFr::Event ev (GameFr::Event::Types::COLLISION, GetPtr(), enemy, data);
				eventInterface.queue->CreateEvent(std::make_shared<const GameFr::Event>(ev));
				OnCollision();
				break;
			}
		}
	}

}

void Projectile::Update(){
	GetRenderingPosition(*camera);
	if (onScreen) {
		DrawTextureEx(texture->texture, (Vector2){renderingPosition.X + width, renderingPosition.Y + height}, rotation, 1, WHITE);
	}
	Collide();
	Push(targetDirection, speed);
}
