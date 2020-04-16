//
// Created by ebalo on 31/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_DRAWABLEFACTORYTEST_H
#define TD_TOWERDEFENSE_SFML_DRAWABLEFACTORYTEST_H

#include <memory>
#include "../Classes/Elements/DrawableFactory.h"

/* Note in this test class not all the "instantiate*" are called, especially the "instantiateTexture" and "instantiateSprite"
 * this because they are almost an alias of the RenderableMap functions "initTexture" and "initSprite"
 */

class DrawableFactoryTest : public ::testing::Test {
protected:
    GAME_STATE game_state = GAME_STATE::initial_screen;
    sptr<sf::RenderWindow> window;
    sptr<EventHandler> event_handler;
    DrawableFactory factory;

    void SetUp() override {
        sf::VideoMode mode = sf::VideoMode::getDesktopMode();
        window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1, 1, mode.bitsPerPixel), "TD-TowerDefense", sf::Style::None);

        event_handler = std::make_shared<EventHandler>(window, std::make_shared<GAME_STATE>(game_state));

        factory.setWindow(window);
        factory.setEventHandler(event_handler);
    }

    void TearDown() override {
        event_handler.reset();
        window.reset();
    }
};

class PlaceholderEvent : public Event {
public:
    PlaceholderEvent(sptr<Button> btn) : Event(btn) {}

    void callback() override {};
};

TEST_F(DrawableFactoryTest, Text) {
    EXPECT_EQ(factory.has(RenderableMap::Maps::texts, "text"), false);
    auto text = factory.instantiateText("text", nullptr);
    ASSERT_EQ(text, factory.getText("text"));
    EXPECT_EQ(factory.has(RenderableMap::Maps::texts, "text"), true);
    EXPECT_EQ(text->getFont(), nullptr);
    EXPECT_EQ(text->getCharacterSize(), 14);
    EXPECT_EQ(text->getString(), "");
    EXPECT_EQ(text->getStyle(), sf::Text::Style::Regular);
    EXPECT_EQ(text->getFillColor(), sf::Color(0, 0, 0));
    EXPECT_EQ(text->getPosition(), (sf::Vector2f {0, 0}));
}

TEST_F(DrawableFactoryTest, ButtonRect) {
    EXPECT_EQ(factory.has(RenderableMap::Maps::rect_buttons, "btn"), false);
    auto btn = factory.instantiateButtonRect("btn", {0,0}, nullptr);
    ASSERT_EQ(btn, factory.getButtonRect("btn"));
    EXPECT_EQ(factory.has(RenderableMap::Maps::rect_buttons, "btn"), true);
    EXPECT_EQ(btn->getSize(), (sf::Vector2f {0,0}));
    EXPECT_EQ(btn->getColor(), sf::Color(0, 0, 0));
    EXPECT_EQ(btn->getLabelColor(), sf::Color(0, 0, 0));
    EXPECT_EQ(btn->getPosition(), (sf::Vector2f {0, 0}));
    EXPECT_EQ(btn->getLabel()->getFont(), nullptr);
    EXPECT_EQ(btn->getLabel()->getCharacterSize(), 14);
    EXPECT_EQ(btn->getLabel()->getString(), "");
    EXPECT_EQ(btn->hasObserver(OBSERVERS_TYPE_ID::mouse_motion_out), false);
    EXPECT_EQ(btn->hasObserver(OBSERVERS_TYPE_ID::mouse_motion_hover), false);
    EXPECT_EQ(btn->hasObserver(OBSERVERS_TYPE_ID::mouse_click_left), false);

    factory.linkEvent(btn, new PlaceholderEvent(btn), new PlaceholderEvent(btn), new PlaceholderEvent(btn));
    EXPECT_EQ(btn->hasObserver(OBSERVERS_TYPE_ID::mouse_motion_out), true);
    EXPECT_EQ(btn->hasObserver(OBSERVERS_TYPE_ID::mouse_motion_hover), true);
    EXPECT_EQ(btn->hasObserver(OBSERVERS_TYPE_ID::mouse_click_left), true);
    btn->deleteObserver(OBSERVERS_TYPE_ID::mouse_motion_out);
    btn->deleteObserver(OBSERVERS_TYPE_ID::mouse_motion_hover);
    btn->deleteObserver(OBSERVERS_TYPE_ID::mouse_click_left);
    EXPECT_EQ(btn->hasObserver(OBSERVERS_TYPE_ID::mouse_motion_out), false);
    EXPECT_EQ(btn->hasObserver(OBSERVERS_TYPE_ID::mouse_motion_hover), false);
    EXPECT_EQ(btn->hasObserver(OBSERVERS_TYPE_ID::mouse_click_left), false);
}

TEST_F(DrawableFactoryTest, ButtonIcon) {
    EXPECT_EQ(factory.has(RenderableMap::Maps::icons_button, "btn"), false);

    // instantiate a texture for testing, the loaded texture makes no difference
    factory.instantiateTexture("texture", AssetsMap::get("ribbon"));

    auto btn = factory.instantiateButtonIcon("btn", "texture");
    ASSERT_EQ(btn, factory.getButtonIcon("btn"));
    EXPECT_EQ(factory.has(RenderableMap::Maps::icons_button, "btn"), true);
    EXPECT_EQ(btn->getPosition(), (sf::Vector2f {0, 0}));
    EXPECT_EQ(btn->hasObserver(OBSERVERS_TYPE_ID::mouse_motion_out), false);
    EXPECT_EQ(btn->hasObserver(OBSERVERS_TYPE_ID::mouse_motion_hover), false);
    EXPECT_EQ(btn->hasObserver(OBSERVERS_TYPE_ID::mouse_click_left), false);

    factory.linkEvent(btn, new PlaceholderEvent(btn), new PlaceholderEvent(btn), new PlaceholderEvent(btn));
    EXPECT_EQ(btn->hasObserver(OBSERVERS_TYPE_ID::mouse_motion_out), true);
    EXPECT_EQ(btn->hasObserver(OBSERVERS_TYPE_ID::mouse_motion_hover), true);
    EXPECT_EQ(btn->hasObserver(OBSERVERS_TYPE_ID::mouse_click_left), true);
    btn->deleteObserver(OBSERVERS_TYPE_ID::mouse_motion_out);
    btn->deleteObserver(OBSERVERS_TYPE_ID::mouse_motion_hover);
    btn->deleteObserver(OBSERVERS_TYPE_ID::mouse_click_left);
    EXPECT_EQ(btn->hasObserver(OBSERVERS_TYPE_ID::mouse_motion_out), false);
    EXPECT_EQ(btn->hasObserver(OBSERVERS_TYPE_ID::mouse_motion_hover), false);
    EXPECT_EQ(btn->hasObserver(OBSERVERS_TYPE_ID::mouse_click_left), false);
}

#endif //TD_TOWERDEFENSE_SFML_DRAWABLEFACTORYTEST_H
