#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "Configuration/Configuration.hpp"
#include "Window/Window.hpp"
#include "Game.hpp"
#include "Map/TileTemplate.hpp"
#include "Map/TileSetTemplate.hpp"
#include "Map/KnightTiles.hpp"
#include "Map/IsoTiles.hpp"
#include "Map/MapLayerTemplate.hpp"
#include "Map/LayeredMap.hpp"

#include "Animations/AnimatedSprite.hpp"
#include "Animations/SpriteSheetTemplate.hpp"
#include "CommonHeaders/AnimationTypes.hpp"
#include "Animations/Anim_Directional.hpp"
#include "Entities/Character.hpp"
#include "Entities/Player.hpp"
#include "SharedContext.hpp"
#include "InfoBox/InfoBox.hpp"
#include "EntityState.hpp"

#include "Components/CollidableComponent.hpp"
#include "Components/ControllerComponent.hpp"
#include "Components/MovableComponent.hpp"
#include "Components/PositionComponent.hpp"
#include "Components/SpriteSheetComponent.hpp"
#include "Components/StateComponent.hpp"

#include "EntitiesManager/EntitiesManager.hpp"
#include "SystemManager.hpp"
#include "RendererSystem.hpp"
#include "MovementSystem.hpp"
#include "StateSystem.hpp"
#include "ControllerSystem.hpp"
#include "SpriteSheetSystem.hpp"
#include "CollisionSystem.hpp"
#include "CommonHeaders/AnimationsToStateConverter.hpp"

#include <nlohmann/json.hpp>
using nlohmann::json;