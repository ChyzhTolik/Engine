#include "SharedContext.hpp"

#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace Engine
{
    SharedContext::SharedContext()
            :m_wind(nullptr)
            ,m_eventManager(nullptr)
            ,m_game_map(nullptr)
            ,m_system_manager(nullptr)
            ,m_entities_manager(nullptr)
            ,m_log_file(spdlog::basic_logger_mt<spdlog::async_factory>("async_file_logger", "logs/async_log.txt"))    
        {

        }
} // namespace Engine
