#include "Projectile.hpp"
#include "util/TextureArrays.hpp"
#include "GameManager.hpp"

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
}

void ProjectileFactory::Update(){
	{
		auto ev = eventInterface.Listen(GameFr::Event::Types::SHOOT);
		while (ev){
			if (headPtr >= projectileList.size()) headPtr = 0;
			if (ev->dataPoint.additionalData[2] == 0){
				projectileList[headPtr] = std::make_shared<Projectile>((Projectile::Types)ev->dataPoint.additionalData[0], ev->dataPoint.position, ev->sender->position, Global::game->camera, (Projectile::Senders)ev->dataPoint.additionalData[1]);
				headPtr++;
			}
			else{
				projectileList[headPtr] = std::make_shared<Projectile>((Projectile::Types)ev->dataPoint.additionalData[0], ev->dataPoint.position, ev->sender->position, Global::game->camera, (Projectile::Senders)ev->dataPoint.additionalData[1], ev->dataPoint.additionalData[2]);
				headPtr++;
			}
			ev = eventInterface.Listen(GameFr::Event::Types::SHOOT);
			
		}
		
	}
	//Destroy old projectiles and update the rest
	for (uint16_t ptr = 0; ptr < projectileList.size(); ptr++){
		if (!projectileList[ptr]) continue;
		if (std::chrono::system_clock::now() - projectileList[ptr]->creationTime >= std::chrono::seconds(10)){
			projectileList[ptr] = nullptr;
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
				auto i = std::find(projectileList.begin(), projectileList.end(), ev->sender);
				*i = nullptr;
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
