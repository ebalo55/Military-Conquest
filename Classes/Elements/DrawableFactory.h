//
// Created by ebalo on 26/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_DRAWABLEFACTORY_H
#define TD_TOWERDEFENSE_SFML_DRAWABLEFACTORY_H

#include <SFML/Graphics.hpp>
#include "../Maps/RenderableMap.h"
#include "../EventHandler.h"
#include "../Interface/Event.h"
#include "../Observers/MouseOutObserver.h"
#include "../Observers/MouseHoverObserver.h"
#include "../Observers/MouseClickObserver.h"

class DrawableFactory : public RenderableMap {
private:
    EventHandler *event_handler;
    sf::RenderWindow *window;
public:
    DrawableFactory() {};
    void setEventHandler(EventHandler *event_handler);
    void setWindow(sf::RenderWindow *window);

    /**
     * Instantiate an instance of sf::Text into the map of texts.
     * The instance can be recovered using the inherited method "getText" and rendered dereferencing it.
     * @param std::string name A name used to recover the instantiated instance
     * @param sf::Font* font A pointer to an instance of sf::Font, used to render the text
     * @param std::string content The text to be displayed, NOTE: new lines ('\n') are allowed
     * @param sf::Vector2f position An instance of sf::Vector2f representing the coordinates of the top left corner of this widget, coordinates computed from top-left corner to bottom-right one
     * @param int size A number representing the font size
     * @param sf::Color color An instance of sf::Color representing the text color
     * @param sf::Uint32 style An unsigned integer representing the style of the text, multiple styles can be linked OR-ing them. Codes located at sf::Text::Style.
     * @return
     */
    sf::Text *instantiateText(const std::string& name,
            sf::Font *font,
            const std::string& content = "",
            sf::Vector2f position = sf::Vector2f {0, 0},
            int size = 14,
            sf::Color color = sf::Color(0, 0, 0),
            sf::Uint32 style = sf::Text::Style::Regular);

    /**
     * Instantiate an instance of ButtonRect into the map of buttons.
     * The instance can be recovered using the inherited method "getButtonRect" and rendered dereferencing it.
     * @param std::string name A name used to recover the instantiated instance
     * @param sf::Vector2i dimension An instance of sf::Vector2i representing the real size of the button
     * @param sf::Font* font A pointer to an instance of sf::Font, used to render the label
     * @param std::string label The label to be displayed, NOTE: new lines ('\n') are allowed
     * @param int size A number representing the font size
     * @param sf::Color btn_color An instance of sf::Color representing the button color
     * @param sf::Color label_color An instance of sf::Color representing the label color
     * @param sf::Vector2f position An instance of sf::Vector2f representing the coordinates of the top left corner of this widget, coordinates computed from top-left corner to bottom-right one
     * @param bool activate A true/false switch indicating whether to immediately register the button to the event-handler or not
     * @param Event* mouse_out_event In case "activate" is true this will link the event to the mouse-out-observer
     * @param Event* mouse_hover_event In case "activate" is true this will link the event to the mouse-hover-observer
     * @param Event* mouse_click_event In case "activate" is true this will link the event to the mouse-click-observer
     * @return
     */
    ButtonRect *instantiateButtonRect(const std::string& name,
            sf::Vector2i dimension,
            sf::Font *font,
            const std::string& label = "",
            int size = 14,
            sf::Color btn_color = sf::Color(0, 0, 0),
            sf::Color label_color = sf::Color(0, 0, 0),
            sf::Vector2f position = {0, 0},
            bool activate = false,
            Event *mouse_out_event = nullptr,
            Event *mouse_hover_event = nullptr,
            Event *mouse_click_event = nullptr);

    /**
     * Instantiate an instance of ButtonIcon into the map of buttons.
     * The instance can be recovered using the inherited method "getButtonIcon" and rendered dereferencing it.
     * @param std::string name A name used to recover the instantiated instance
     * @param sf::Texture* texture A pointer to an instance of sf::Texture to be rendered into the button
     * @param sf::IntRect clip An instance of sf::IntRect representing the coordinates and the size of the area of the texture to be rendered into the button
     * @param sf::Vector2f position An instance of sf::Vector2f representing the coordinates of the top left corner of this widget, coordinates computed from top-left corner to bottom-right one
     * @param bool activate A true/false switch indicating whether to immediately register the button to the event-handler or not
     * @param Event* mouse_out_event In case "activate" is true this will link the event to the mouse-out-observer
     * @param Event* mouse_hover_event In case "activate" is true this will link the event to the mouse-hover-observer
     * @param Event* mouse_click_event In case "activate" is true this will link the event to the mouse-click-observer
     * @return
     */
    ButtonIcon *instantiateButtonIcon(const std::string& name,
            sf::Texture *texture_name,
            sf::Vector2f position = {0, 0},
            sf::IntRect clip = {0, 0, -1, -1},
            bool activate = false,
            Event *mouse_out_event = nullptr,
            Event *mouse_hover_event = nullptr,
            Event *mouse_click_event = nullptr);
    /**
     * Instantiate an instance of ButtonIcon into the map of buttons.
     * The instance can be recovered using the inherited method "getButtonIcon" and rendered dereferencing it.
     * @param std::string name A name used to recover the instantiated instance
     * @param std::string texture_name A string pointing to an instance of sf::Texture to be rendered into the button
     * @param sf::IntRect clip An instance of sf::IntRect representing the coordinates and the size of the area of the texture to be rendered into the button
     * @param sf::Vector2f position An instance of sf::Vector2f representing the coordinates of the top left corner of this widget, coordinates computed from top-left corner to bottom-right one
     * @param bool activate A true/false switch indicating whether to immediately register the button to the event-handler or not
     * @param Event* mouse_out_event In case "activate" is true this will link the event to the mouse-out-observer
     * @param Event* mouse_hover_event In case "activate" is true this will link the event to the mouse-hover-observer
     * @param Event* mouse_click_event In case "activate" is true this will link the event to the mouse-click-observer
     * @return
     */
    ButtonIcon *instantiateButtonIcon(const std::string& name,
            const std::string& texture_name,
            sf::Vector2f position = {0, 0},
            sf::IntRect clip = {0, 0, -1, -1},
            bool activate = false,
            Event *mouse_out_event = nullptr,
            Event *mouse_hover_event = nullptr,
            Event *mouse_click_event = nullptr);

    /**
     * Register the button to the event handler and all the non null events to their respective observer.
     * @param Button* btn A pointer to an instance of a button
     * @param Event* mouse_out_event Link the event to the mouse-out-observer
     * @param Event* mouse_hover_event Link the event to the mouse-hover-observer
     * @param Event* mouse_click_event Link the event to the mouse-click-observer
     */
    void linkEvent(Button *btn,
            Event *mouse_out_event = nullptr,
            Event *mouse_hover_event = nullptr,
            Event *mouse_click_event = nullptr);

    /**
     * Delete the provided button from the event handler observers list and clear the button instance
     * @param Button* btn A pointer to an instance of the button to remove
     */
    void purgeButton(Button *btn);
    /**
     * Delete the button associated with the provided name from the event handler observers list and clear the button instance
     * @param std::string name The name of the button to remove
     * @param bool rect A true/false switch indicating whether to search the button in the rect button list or in the icon button one
     */
    void purgeButton(const std::string& name, bool rect = true);
    /**
     * Delete the buttons associated with the provided names from the event handler observers list and clear the button instance
     * @param std::vector<std::string> names A vector of names of the buttons to remove
     * @param bool rect A true/false switch indicating whether to search the buttons in the rect button list or in the icon button one
     */
    void purgeButton(const std::vector<std::string>& names, bool rect = true);
    /**
     * Delete the provided button from the event handler observers list
     * @param Button* btn A pointer to an instance of the button to remove
     */
    void unlinkButton(Button *btn);
    /**
     * Delete the button associated with the provided name from the event handler observers list
     * @param std::string name The name of the button to remove
     * @param bool rect A true/false switch indicating whether to search the button in the rect button list or in the icon button one
     */
    void unlinkButton(const std::string& name, bool rect = true);
    /**
     * Delete the buttons associated with the provided names from the event handler observers list
     * @param std::vector<std::string> names A vector of names of the buttons to remove
     * @param bool rect A true/false switch indicating whether to search the buttons in the rect button list or in the icon button one
     */
    void unlinkButton(const std::vector<std::string>& names, bool rect = true);

    /**
     * Add the button associated with the provided name to the event handler observers list
     * @param Button* btn A pointer to an instance of the button to add
     */
    void linkButton(Button *btn);
    /**
     * Add the button associated with the provided name to the event handler observers list
     * @param std::string name The name of the button to add
     * @param bool rect A true/false switch indicating whether to search the button in the rect button list or in the icon button one
     */
    void linkButton(const std::string& name, bool rect = true);
    /**
     * Add the buttons associated with the provided names to the event handler observers list
     * @param std::vector<std::string> names A vector of names of the buttons to add
     * @param bool rect A true/false switch indicating whether to search the button in the rect button list or in the icon button one
     */
    void linkButton(const std::vector<std::string>& names, bool rect = true);

    /**
     * Instantiate an instance of sf::Texture into the map of textures.
     * The instance can be recovered using the inherited method "getButtonRect" and passed to sprites dereferencing it.
     * @param std::string name A name used to recover the instantiated instance
     * @param std::string filename The file from where the texture should be loaded
     * @return
     */
    sf::Texture *instantiateTexture(const std::string& name, const std::string& filename);

    /**
     * Instantiate an instance of sf::Sprite into the map of sprites.
     * The instance can be recovered using the inherited method "getSprite" and rendered dereferencing it.
     * @param std::string name A name used to recover the instantiated instance
     * @param sf::Texture* texture A pointer to an instance of sf::Texture to be rendered into the sprite
     * @param sf::Vector2f position An instance of sf::Vector2f representing the coordinates of the top left corner of this widget, coordinates computed from top-left corner to bottom-right one
     * @param sf::IntRect clip An instance of sf::IntRect representing the coordinates and the size of the area of the texture to be rendered into the sprite
     * @return
     */
    sf::Sprite *instantiateSprite(const std::string& name,
            sf::Texture *texture,
            sf::Vector2f position = sf::Vector2f {0, 0},
            sf::IntRect clip = sf::IntRect {0, 0, -1, -1});
    sf::Sprite *instantiateSprite(const std::string& name,
            const sf::Texture *texture,
            sf::Vector2f position = sf::Vector2f {0, 0},
            sf::IntRect clip = sf::IntRect {0, 0, -1, -1});
    /**
     * Instantiate an instance of sf::Sprite into the map of sprites.
     * The instance can be recovered using the inherited method "getSprite" and rendered dereferencing it.
     * @param std::string name A name used to recover the instantiated instance
     * @param std::string texture_name A string pointing to an instance of sf::Texture to be rendered into the sprite
     * @param sf::Vector2f position An instance of sf::Vector2f representing the coordinates of the top left corner of this widget, coordinates computed from top-left corner to bottom-right one
     * @param sf::IntRect clip An instance of sf::IntRect representing the coordinates and the size of the area of the texture to be rendered into the sprite
     * @return
     */
    sf::Sprite *instantiateSprite(const std::string& name,
            const std::string& texture_name,
            sf::Vector2f position = sf::Vector2f {0, 0},
            sf::IntRect clip = sf::IntRect {0, 0, -1, -1});
};


#endif //TD_TOWERDEFENSE_SFML_DRAWABLEFACTORY_H
