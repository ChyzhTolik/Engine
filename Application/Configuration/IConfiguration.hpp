#pragma once

namespace Engine
{
    template<typename T>
    class IConfiguration
    {
    public:
        virtual static void Initialize();
		virtual static void clear();

	protected:
		virtual static void init_textures();
		virtual static void init_inputs();
		virtual static void init_musics();
    };
} // namespace Engine
