#pragma once
#include <array>
#include <inttypes.h>
#include <memory>
#include <entities.hpp>

namespace Util{
	template<uint32_t n>
	struct ObjectArray{
		std::array<std::shared_ptr<GameFr::Entity2D>, n> array;
		void UpdateAll(){
			for (auto& entity : array){
				entity->Update();
			}
		}
	};
}
