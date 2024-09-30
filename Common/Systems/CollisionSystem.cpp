#include "CollisionSystem.hpp"
#include "SystemManager.hpp"
#include "EntitiesManager.hpp"

namespace Engine
{
    CollisionSystem::CollisionSystem(std::shared_ptr<SystemManager> system_manager) : System(SystemType::Collision, system_manager)
    {
        ComponentBitSet mask;
        mask.set(static_cast<size_t>(ComponentType::Position));
        mask.set(static_cast<size_t>(ComponentType::Collidable));

        m_required_components.push_back(mask);
        m_map = nullptr;
    }
    
    CollisionSystem::~CollisionSystem()
    {
    }

    void CollisionSystem::set_map(std::shared_ptr<LayeredMap> map)
    {
        m_map = map;
    }

    void CollisionSystem::subscribe()
    {

    }

    void CollisionSystem::update(float time)
    {
        if (!m_map)
        {
            return;
        }

        auto entities_manager = m_system_manager->get_entity_manager();
        
        for (auto &&entity : m_entities)
        {
            auto position_component = entities_manager->get_component<PositionComponent>(entity, ComponentType::Position);
            auto collidable_component = entities_manager->get_component<CollidableComponent>(entity, ComponentType::Collidable);

            collidable_component->set_position(position_component->get_position());
            collidable_component->resset_collision_flags();

            // m_system_manager->get_infobox()->Add("Bounding box left="+std::to_string(collidable_component->get_bounding_box().left)+
            //     ", top="+std::to_string(collidable_component->get_bounding_box().top));
            // m_system_manager->get_infobox()->Add("Bounding box width="+std::to_string(collidable_component->get_bounding_box().width)+
            //     ", height="+std::to_string(collidable_component->get_bounding_box().height));

            check_out_of_bounds(position_component, collidable_component);
            map_collisions(entity, position_component, collidable_component);
        }
        
    }

    void CollisionSystem::check_out_of_bounds(std::shared_ptr<PositionComponent> position, std::shared_ptr<CollidableComponent> collidable)
    {
        auto tile_size = m_map->get_tile_size();

        if (position->get_position().x<0)
        {
            position->set_position({0.f, position->get_position().y});
        }
        else if (position->get_position().x>m_map->get_map_size().x*m_map->get_tile_size().x)
        {
            position->set_position({static_cast<float>(m_map->get_map_size().x*m_map->get_tile_size().x), static_cast<float>(position->get_position().y)});
        }
        else if (position->get_position().y<0)
        {
            position->set_position({position->get_position().x, 0.f});
        }
        else if (position->get_position().y>m_map->get_map_size().y*m_map->get_tile_size().y)
        {
            position->set_position({static_cast<float>(position->get_position().x), static_cast<float>(m_map->get_map_size().y*m_map->get_tile_size().y)});
        }
        
        collidable->set_position(position->get_position());        
    }

    void CollisionSystem::map_collisions(EntityId entity, std::shared_ptr<PositionComponent> position, std::shared_ptr<CollidableComponent> collidable)
    {
        auto tile_size = m_map->get_tile_size();
        std::vector<CollisionInfo> collisions;
        auto entity_rect = collidable->get_bounding_box();

        uint32_t from_x = floor(entity_rect.left / m_map->get_tile_size().x);
        uint32_t to_x = floor((entity_rect.left + entity_rect.width) / m_map->get_tile_size().x);
        uint32_t from_y = floor(entity_rect.top / m_map->get_tile_size().y);
        uint32_t to_y = floor((entity_rect.top + entity_rect.height) / m_map->get_tile_size().y);

        m_system_manager->get_infobox()->Add("Tile: "+std::to_string(from_x)+","+std::to_string(from_y));

        for (uint32_t x = from_x; x<= to_x; x++)
        {
            for (uint32_t y = from_y; y <= to_y; y++)
            {
                auto tile = m_map->get_tile(position->get_elevation(), {static_cast<int>(x), static_cast<int>(y)});

                if (!tile)
                {
                    continue;
                }
                

                if (!m_map->is_solid(position->get_elevation()))
                {
                    continue;
                }

                sf::FloatRect tile_rect(sf::Vector2f(x*m_map->get_tile_size().x, y*m_map->get_tile_size().y),static_cast<sf::Vector2f>(m_map->get_tile_size()));
                
                auto intersection = entity_rect.findIntersection(tile_rect);
                if (!intersection.has_value())
                {
                    continue;
                }
                
                float square = intersection.value().width*intersection.value().height;

                CollisionInfo element = {square, tile, tile_rect};
                collisions.emplace_back(element);
                break;
            }
        }
        
        if (collisions.empty())
        {
            return;
        }

        std::sort(collisions.begin(),collisions.end(),[](CollisionInfo& l1, CollisionInfo& l2)
        {
            return l1.area > l2.area;
        });
        
        for (auto &&collision : collisions)
        {
            entity_rect = collidable->get_bounding_box();

            if (!entity_rect.findIntersection(collision.tile_bounds).has_value())
            {
                continue;
            }
            
            float x_diff = entity_rect.left + entity_rect.width/2 - (collision.tile_bounds.left + collision.tile_bounds.width/2);
            float y_diff = entity_rect.top + entity_rect.height/2 - (collision.tile_bounds.top + collision.tile_bounds.height/2);

            float resolve = 0;

            if (std::abs(x_diff) > std::abs(y_diff))
            {
                if (x_diff>0)
                {
                    resolve = collision.tile_bounds.left + tile_size.x - entity_rect.left; 
                }
                else
                {
                    resolve = -(entity_rect.left + entity_rect.width - collision.tile_bounds.left); 
                }
                
                position->move_by({resolve, 0.f});
                collidable->set_position(position->get_position());

                m_system_manager->add_event(entity, EntityEvent::Colliding_X);
                collidable->collide_on_x();
            }
            else
            {
                if (y_diff>0)
                {
                    resolve = collision.tile_bounds.top + tile_size.x - entity_rect.top; 
                }
                else
                {
                    resolve = -(entity_rect.top + entity_rect.height - collision.tile_bounds.top); 
                }
                
                position->move_by({0.f, resolve});
                collidable->set_position(position->get_position());

                m_system_manager->add_event(entity, EntityEvent::Colliding_Y);
                collidable->collide_on_y();
            }
        }
    }

    void CollisionSystem::entity_collisions()
    {
        auto entities_manager = m_system_manager->get_entity_manager();

        for (auto itr = m_entities.begin(); itr < m_entities.end(); itr++)
        {
            for (auto itr2 = m_entities.begin(); itr2 < m_entities.end(); itr2++)
            {
                auto collidable_component1 = entities_manager->get_component<CollidableComponent>(*itr, ComponentType::Collidable);
                auto collidable_component2 = entities_manager->get_component<CollidableComponent>(*itr2, ComponentType::Collidable);  

                if (collidable_component1->get_bounding_box().findIntersection(collidable_component2->get_bounding_box()).has_value())
                {
                    /* code */
                }
                  
            }
        }
        
    }

    void CollisionSystem::handle_event(EntityId entity, EntityEvent event)
    {
        
    }

    void CollisionSystem::notify(const Message& message)
    {
        
    }

} // namespace Engine
