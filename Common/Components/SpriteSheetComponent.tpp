template<typename T>
std::shared_ptr<Component> SpriteSheetComponentCreator<T>::create()
{
    return std::make_shared<SpriteSheetComponent<T>>();
}

template<typename T>
SpriteSheetComponentCreator<T>::SpriteSheetComponentCreator()
{

}

template<typename T>
SpriteSheetComponent<T>::SpriteSheetComponent() : DrawableComponentInterface(ComponentType::SpriteSheet), m_sprite_sheet{nullptr}
{

};

template<typename T>
std::shared_ptr<SpriteSheet> SpriteSheetComponent<T>::get_sprite_sheet()
{
    return m_sprite_sheet;
}

template<typename T>
template<class Animation>
void SpriteSheetComponent<T>::create(Configuration::Textures id, const std::string& file_name)
{
    if (m_sprite_sheet)
    {
        return;
    }

    m_sprite_sheet = std::make_shared<SpriteSheetTemplate<T>>();

    m_sprite_sheet->template load_sheet<Animation>(file_name != "" ? file_name : m_sprite_sheet_info.file_name, id);
}

template<typename T>
void SpriteSheetComponent<T>::update_position(const sf::Vector2f& l_vec)
{
    m_sprite_sheet->SetSpritePosition(l_vec);
}

template<typename T>
const sf::Vector2i SpriteSheetComponent<T>::get_size()
{
    return m_sprite_sheet->GetSpriteSize();
}

template<typename T>
void SpriteSheetComponent<T>::draw(sf::RenderWindow& l_wind)
{
    m_sprite_sheet->Draw(l_wind);
}

template<typename T>
void SpriteSheetComponent<T>::read_in(json data)
{
    m_sprite_sheet_info = SpriteSheetComponentTestHelper::get_from_json(data);
}

template<typename T>
void SpriteSheetComponent<T>::update(float time)
{
    m_sprite_sheet->Update(time);
}