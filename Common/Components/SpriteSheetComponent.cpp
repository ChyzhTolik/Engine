#include "SpriteSheetComponent.hpp"

namespace Engine
{
    void to_json(json& j, const SpriteSheetInfo& p) 
    {
        j=json{
            {"file_name", p.file_name}
        };
    }

    void from_json(const json& j, SpriteSheetInfo& p) 
    {
        j.at("file_name").get_to(p.file_name);
    }

    json SpriteSheetComponentTestHelper::get_json(const SpriteSheetInfo& input)
    {
        json result;
        result = input;
        return result;
    }

    SpriteSheetInfo SpriteSheetComponentTestHelper::get_from_json(const json& j)
    {
        SpriteSheetInfo info{};
        info = j;
        return info;
    }
} // namespace Engine
