#include "Player.hpp"
#include "Enemy.hpp"
#include "util/Globals.hpp"
#include "Projectile.hpp"
#include "util/Texture.hpp"
#include "util/TextureArrays.hpp"
#include <thread>
#define TO_DEGREES * 57 + 180

Player::Player(){
	eventInterface.AssignQueue(Global::eventQueue); 

	width = 75;
	height = 75;

	texture = Util::TextureArrays::decorations[1];

	//init gun proprieties
	//gun.projectileType = (uint8_t)Projectile::Types::NORMAL;
	gun.projectileType = (uint8_t)Projectile::Types::EXPLOSIVE;
	gun.firingSpeed = std::chrono::milliseconds(200);
	gun.recoil = 0;
	gun.projectileSpeed = 50;
}

void Player::GetDirection(){

	direction.X = 0;
	direction.Y = 0;

	if (IsKeyDown(KEY_A)){
		direction.X = -1;
	}if (IsKeyDown(KEY_S)){
		direction.Y = 1;
	}if (IsKeyDown(KEY_W)){
		direction.Y = -1;
	}if (IsKeyDown(KEY_D)){
		direction.X = 1;
	}

	if (IsKeyDown(KEY_LEFT_SHIFT)) speed = 10;
	else if (IsKeyDown(KEY_LEFT_CONTROL)) speed = 4;
	else if (speed != 8) speed = 8;
}

void Player::StopMovementBasedOnDirection(const std::shared_ptr<const Decoration> other){
	if (other->position.X < position.X && direction.X == -1) direction.X = 1;
	else if (other->position.X > position.X && direction.X == 1) direction.X = -1;
	if (other->position.Y < position.Y && direction.Y == -1) direction.Y = 1;
	else if (other->position.Y > position.Y && direction.Y == 1) direction.Y = -1;
}

//TODO: Figure out a way to implement inaccuracy
void Player::Shoot(){
	//check if enough time has passed since the last time we shot
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && std::chrono::system_clock::now() - gun.lastShot >= gun.firingSpeed){
		texture = Util::TextureArrays::decorations[3];
		playShootingAnimation = true;
		GameFr::Vector2 mousePosition(GetMouseX() + gun.inaccuracy, GetMouseY() + gun.inaccuracy);
		GameFr::Vector2 projectileDirection(camera->position.X + mousePosition.X - position.X, camera->position.Y + mousePosition.Y - position.Y); //Convert from camera's cartesian system to game and then get vector connecting them
		GameFr::Util::EventDataPoint data(projectileDirection, {(int)gun.projectileType, (int)Projectile::Senders::PLAYER, gun.projectileSpeed});
		GameFr::Event ev(GameFr::Event::Types::SHOOT, GetPtr(), nullptr, data);
		eventInterface.queue->CreateEvent(std::make_shared<const GameFr::Event>(ev));
		gun.lastShot = std::chrono::system_clock::now();

		//Apply recoil
		if (gun.recoil != 0){
			position.X += (projectileDirection.X < 0) ? gun.recoil : -gun.recoil;
			position.Y += (projectileDirection.Y < 0) ? gun.recoil : -gun.recoil;
		}
	}
}

void Player::Died(){
	GameFr::Util::EventDataPoint data (position, {});
	GameFr::Event ev(GameFr::Event::Types::PLAYER_DEATH, GetPtr(), nullptr, data);
	eventInterface.queue->CreateEvent(std::make_shared<const GameFr::Event>(ev));
	killCount = 0;
}

void Player::CollideAndMove(){
	GetDirection();
	std::shared_ptr<const GameFr::Event> ev;
	do{
		ev = eventInterface.Listen(GetPtr());
		if (!ev) break;
		if (ev->type == GameFr::Event::Types::COLLISION){
			//check collisions with decorations
			{
				auto sender = std::dynamic_pointer_cast<const Decoration>(ev->sender);
				if (sender){
					StopMovementBasedOnDirection(sender);
					continue;
				}
			}
			
			//check collisions with enemies
			{
				auto sender = std::dynamic_pointer_cast<const Enemy>(ev->sender);
				if (sender){
					Died();
					continue;
				}
			}
			//check collisions with projectiles
			{
				auto sender = std::dynamic_pointer_cast<const Projectile>(ev->sender);
				if (sender){
					Died();
					continue;
				}
			}
		}
	}while(ev);
	Push(direction, speed);
}

void Player::RotateTexture(){
	GameFr::Vector2 mousePosition(GetMouseX(), GetMouseY());
	GameFr::Vector2 mouseDirection(camera->position.X + mousePosition.X - position.X, camera->position.Y + mousePosition.Y - position.Y); //Convert from camera's cartesian system to game and then get vector connecting them
	rotation = std::acos(mouseDirection.X / mouseDirection.Magnitude()) TO_DEGREES;
	rotation = (mouseDirection.Y < 0) ? -rotation : rotation;
}

void Player::Update(){
	std::thread collideAndMove(&Player::CollideAndMove, this);
	GetRenderingPosition(*camera);
	Shoot();
	RotateTexture();
	//handle switch between animated texture and static one
	if (playShootingAnimation){
		auto reinterpretedTexture = std::reinterpret_pointer_cast<Util::AnimatedTexture>(texture);
		reinterpretedTexture->Update();
		if (reinterpretedTexture->Finished()){
			texture = Util::TextureArrays::decorations[1];
			playShootingAnimation = false;
		}
	}
	if (onScreen){
		DrawTexturePro(
			texture->texture, 
			(Rectangle){0, 0, (float)width, (float)height}, //part to draw from the texture
			(Rectangle){renderingPosition.X, renderingPosition.Y, (float)width, (float)height}, //where to draw said texture
			Vector2((float)width / 2, (float)height / 2), //origin of texture and pivot point
			rotation,
			WHITE);
	}
	
	collideAndMove.join();
}

void Player::SetCamera(const std::shared_ptr<GameFr::Camera2D> cam){
	camera = cam;
}


Weapons::Upgrade::Upgrade() : random(10, 60){
	projectileSpeed = random.GetRandomNumber();
	random.ChangeRange(40, 150);
	firingSpeed = std::chrono::milliseconds(random.GetRandomNumber());
	random.ChangeRange(-50, 50);
	inaccuracy = random.GetRandomNumber();
	random.ChangeRange(10, 20);
	recoil = random.GetRandomNumber();
}

void Weapons::Gun::ApplyUpgrade(const Upgrade& up){
	firingSpeed = up.firingSpeed;
	projectileSpeed = up.projectileSpeed;
	inaccuracy = up.inaccuracy;
	recoil = up.recoil;
}
