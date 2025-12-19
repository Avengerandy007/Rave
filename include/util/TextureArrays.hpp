#pragma once
#include <array>
#include <memory>
#include "Texture.hpp"

namespace Util::TextureArrays{
	extern std::array<std::shared_ptr<Util::Texture>, 3> decorations;
	extern std::array<std::shared_ptr<Util::Texture>, 2> enemies;
}
