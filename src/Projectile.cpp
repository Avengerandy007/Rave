#include "Projectile.hpp"
#include "util/Globals.hpp"
#include "util/TextureArrays.hpp"
#include "GameManager.hpp"
#include <chrono>
#include <memory>
#include <util/GFmath.hpp>
#include <util/vectors.hpp>

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
			else if (CollidingCircle(*player, 100)){
				GameFr::Util::EventDataPoint data(position, {});
				GameFr::Event ev (GameFr::Event::Types::COLLISION, GetPtr(), player, data);
				eventInterface.queue->CreateEvent(std::make_shared<const GameFr::Event>(ev));
			}
			//create the explosion effect
			Global::game->vfx.push_back(std::make_shared<AnimatedVfx>(Util::TextureArrays::decorations[2], std::chrono::milliseconds(225), position, 5));

		break;
		case Types::IDK: break;
	}
	active = false;
}

void ProjectileFactory::OverrideProjectile(std::shared_ptr<Projectile>& projectile, const Projectile::Types type, const GameFr::Vector2 targetPos, const GameFr::Vector2 startPos, const Projectile::Senders senderType, const int p_speed){
	if (!projectile) projectile = std::make_shared<Projectile>();
	projectile->creationTime = std::chrono::system_clock::now();
	projectile->type = type;
	projectile->sender = senderType;
	if (senderType == Projectile::Senders::ENEMY){
		projectile->speed = projectile->random.GetRandomNumber();
	}else{
		projectile->speed = p_speed;
	}
	projectile->targetDirection = targetPos;
	projectile->targetDirection.Normalize();
	projectile->rotation = GameFr::Util::Math::AngleBetweenVectors(targetPos, GameFr::Vector2(1, 0)) + 180;
	projectile->rotation = (projectile->targetDirection.Y < 0) ? -projectile->rotation : projectile->rotation;
	projectile->position = startPos;
	projectile->active = true;
}

void ProjectileFactory::Update(){
	{
		auto ev = eventInterface.Listen(GameFr::Event::Types::SHOOT);
		while (ev){
			if (headPtr >= projectileList.size()) headPtr = 0;
			if (ev->dataPoint.additionalData[2] == 0){
				OverrideProjectile(projectileList[headPtr], (Projectile::Types)ev->dataPoint.additionalData[0], ev->dataPoint.position, ev->sender->position, (Projectile::Senders)ev->dataPoint.additionalData[1], 30);
				headPtr++;
			}
			else{
				OverrideProjectile(projectileList[headPtr], (Projectile::Types)ev->dataPoint.additionalData[0], ev->dataPoint.position, ev->sender->position, (Projectile::Senders)ev->dataPoint.additionalData[1], ev->dataPoint.additionalData[2]);
				headPtr++;
			}
			ev = eventInterface.Listen(GameFr::Event::Types::SHOOT);
			
		}
		
	}
	//Destroy old projectiles and update the rest
	for (uint16_t ptr = 0; ptr < projectileList.size(); ptr++){
		if (!projectileList[ptr]) continue;
		if (std::chrono::system_clock::now() - projectileList[ptr]->creationTime >= std::chrono::seconds(10)){
			projectileList[ptr]->active = false;
			continue;
		}
		projectileList[ptr]->Update();
	}
	//Destroy projectiles that have collided with something
	{
		auto ev = eventInterface.Listen(GameFr::Event::Types::COLLISION);
		if (ev){
			auto sender = std::dynamic_pointer_cast<const Projectile>(ev->sender);
			if (sender){
				std::shared_ptr<Projectile>* i = std::find(projectileList.begin(), projectileList.end(), ev->sender);
				i->get()->active = false;
			}
		}
	}
}

Projectile::Projectile(const Projectile& other) : type(other.type), random(other.random), creationTime(other.creationTime), player(Global::game->player), sender(other.sender), camera(Global::game->camera){
	eventInterface = other.eventInterface;
	speed = other.speed;
	position = other.position;
	targetDirection = other.targetDirection;
	renderingPosition = other.renderingPosition;
	texture = other.texture;
}

Projectile::Projectile() : random(8, 16), player(Global::game->player), camera(Global::game->camera){
	eventInterface.AssignQueue(Global::eventQueue);
	texture = Util::TextureArrays::enemies[1];
	active = false;
	width = 39;
	height = 16;
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
			if (CollidingCircle(*enemy, 60)){
				GameFr::Util::EventDataPoint data(position, {});
				GameFr::Event ev (GameFr::Event::Types::COLLISION, GetPtr(), enemy, data);
				eventInterface.queue->CreateEvent(std::make_shared<const GameFr::Event>(ev));
				player->killCount++;
				if (player->killCount % 5 == 0){
					Weapons::Upgrade up;
					player->gun.ApplyUpgrade(up);
				}
				OnCollision();
				break;
			}
		}
	}

}

void Projectile::Update(){
	if (!active) return;
	GetRenderingPosition(*camera);
	if (onScreen) {
		DrawTexturePro(
			texture->texture, 
			(Rectangle){0, 0, (float)width, (float)height}, //part to draw from the texture
			(Rectangle){renderingPosition.X, renderingPosition.Y, (float)width, (float)height}, //where to draw said texture
			Vector2((float)width / 2, (float)height / 2), //origin of texture and pivot point
			rotation,
			WHITE);
	}
	Collide();
	Push(targetDirection, speed);
}
