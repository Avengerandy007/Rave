#pragma once
#include <inttypes.h>
#include <entities.hpp>

namespace Util{
	template<uint32_t n>
	struct ObjectArray{
		std::array<std::shared_ptr<GameFr::Entity2D>, n> array;
		void UpdateAll(){
			for (std::shared_ptr<GameFr::Entity2D> entity : array){
				if (entity) entity->Update();
			}
		}
	};
}
