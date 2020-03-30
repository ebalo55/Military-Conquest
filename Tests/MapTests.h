//
// Created by ebalo on 30/03/20.
//

#ifndef TD_TOWERDEFENSE_ASSETSMAPTESTS_H
#define TD_TOWERDEFENSE_ASSETSMAPTESTS_H

#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "../../Classes/Maps/AssetsMap.h"
#include "../../Classes/Maps/RenderableMap.h"
#include "../Classes/Maps/MapEasy.h"
#include "../Classes/Maps/MapHard.h"

TEST(Maps, Assets) {
    AssetsMap::listAll();
    std::vector<std::string> names = AssetsMap::listNamesAutomated(),
        paths = AssetsMap::listPathsAutomated();

    std::fstream handle;
    ASSERT_EQ(names.size(), paths.size());
    int offset;
    for(int i = 0; i < names.size(); i++) {
        ASSERT_EQ(AssetsMap::get(names[i]), paths[i]);
        handle.open(paths[i], std::fstream::in | std::ifstream::binary);
        ASSERT_EQ(handle.good(), true);
        offset = handle.tellg();
        handle.seekg(0, std::fstream::end);
        std::cout << "Found '" << names[i] << "' at '" << paths[i] << "' with a filesize of: " << (int)handle.tellg() - offset << " bits" << std::endl;
        handle.close();
    }
}

TEST(Maps, Renderable) {
    RenderableMap map;

    // Check standard initialization
    EXPECT_EQ(map.has(RenderableMap::Maps::textures, "texture_test"), false);
    auto texture = map.initTexture("texture_test");
    EXPECT_EQ(texture, map.getTexture("texture_test"));
    EXPECT_EQ(map.has(RenderableMap::Maps::textures, "texture_test"), true);
    // Check fallback initialization on get*
    EXPECT_EQ(map.has(RenderableMap::Maps::textures, "test"), false);
    EXPECT_NE(texture, map.getTexture("test"));
    EXPECT_EQ(map.has(RenderableMap::Maps::textures, "test"), true);
    // Check clear
    map.clear(RenderableMap::Maps::textures, {"texture_test", "test"});
    EXPECT_EQ(map.has(RenderableMap::Maps::textures, "texture_test"), false);
    EXPECT_EQ(map.has(RenderableMap::Maps::textures, "test"), false);
    EXPECT_EQ(map.has(RenderableMap::Maps::textures, "non-existent"), false);
    map.clear(RenderableMap::Maps::textures, {"non-existent"});
    EXPECT_EQ(map.has(RenderableMap::Maps::textures, "non-existent"), false);

    // Check standard initialization
    EXPECT_EQ(map.has(RenderableMap::Maps::sprites, "sprite_test"), false);
    auto sprite = map.initSprite("sprite_test");
    EXPECT_EQ(sprite, map.getSprite("sprite_test"));
    EXPECT_EQ(map.has(RenderableMap::Maps::sprites, "sprite_test"), true);
    // Check fallback initialization on get*
    EXPECT_EQ(map.has(RenderableMap::Maps::sprites, "test"), false);
    EXPECT_NE(sprite, map.getSprite("test"));
    EXPECT_EQ(map.has(RenderableMap::Maps::sprites, "test"), true);
    // Check clear
    map.clear(RenderableMap::Maps::sprites, {"sprite_test", "test"});
    EXPECT_EQ(map.has(RenderableMap::Maps::sprites, "sprite_test"), false);
    EXPECT_EQ(map.has(RenderableMap::Maps::sprites, "test"), false);
    EXPECT_EQ(map.has(RenderableMap::Maps::sprites, "non-existent"), false);
    map.clear(RenderableMap::Maps::sprites, {"non-existent"});
    EXPECT_EQ(map.has(RenderableMap::Maps::sprites, "non-existent"), false);

    // Check standard initialization
    EXPECT_EQ(map.has(RenderableMap::Maps::rect_buttons, "btn_test"), false);
    auto btn_rect = map.initButtonRect("btn_test");
    EXPECT_EQ(btn_rect, map.getButtonRect("btn_test"));
    EXPECT_EQ(map.has(RenderableMap::Maps::rect_buttons, "btn_test"), true);
    // Check fallback initialization on get*
    EXPECT_EQ(map.has(RenderableMap::Maps::rect_buttons, "test"), false);
    EXPECT_NE(btn_rect, map.getButtonRect("test"));
    EXPECT_EQ(map.has(RenderableMap::Maps::rect_buttons, "test"), true);
    // Check clear
    map.clear(RenderableMap::Maps::rect_buttons, {"btn_test", "test"});
    EXPECT_EQ(map.has(RenderableMap::Maps::rect_buttons, "btn_test"), false);
    EXPECT_EQ(map.has(RenderableMap::Maps::rect_buttons, "test"), false);
    EXPECT_EQ(map.has(RenderableMap::Maps::rect_buttons, "non-existent"), false);
    map.clear(RenderableMap::Maps::rect_buttons, {"non-existent"});
    EXPECT_EQ(map.has(RenderableMap::Maps::rect_buttons, "non-existent"), false);

    // Check standard initialization
    EXPECT_EQ(map.has(RenderableMap::Maps::texts, "text_test"), false);
    auto text = map.initText("text_test");
    EXPECT_EQ(text, map.getText("text_test"));
    EXPECT_EQ(map.has(RenderableMap::Maps::texts, "text_test"), true);
    // Check fallback initialization on get*
    EXPECT_EQ(map.has(RenderableMap::Maps::texts, "test"), false);
    EXPECT_NE(text, map.getText("test"));
    EXPECT_EQ(map.has(RenderableMap::Maps::texts, "test"), true);
    // Check clear
    map.clear(RenderableMap::Maps::texts, {"text_test", "test"});
    EXPECT_EQ(map.has(RenderableMap::Maps::texts, "text_test"), false);
    EXPECT_EQ(map.has(RenderableMap::Maps::texts, "test"), false);
    EXPECT_EQ(map.has(RenderableMap::Maps::texts, "non-existent"), false);
    map.clear(RenderableMap::Maps::texts, {"non-existent"});
    EXPECT_EQ(map.has(RenderableMap::Maps::texts, "non-existent"), false);

    // Check standard initialization
    EXPECT_EQ(map.has(RenderableMap::Maps::icons_button, "btn_test"), false);
    auto btn_icon = map.initButtonIcon("btn_test");
    EXPECT_EQ(btn_icon, map.getButtonIcon("btn_test"));
    EXPECT_EQ(map.has(RenderableMap::Maps::icons_button, "btn_test"), true);
    // Check fallback initialization on get*
    EXPECT_EQ(map.has(RenderableMap::Maps::icons_button, "test"), false);
    EXPECT_NE(btn_icon, map.getButtonIcon("test"));
    EXPECT_EQ(map.has(RenderableMap::Maps::icons_button, "test"), true);
    // Check clear
    map.clear(RenderableMap::Maps::icons_button, {"btn_test", "test"});
    EXPECT_EQ(map.has(RenderableMap::Maps::icons_button, "btn_test"), false);
    EXPECT_EQ(map.has(RenderableMap::Maps::icons_button, "test"), false);
    EXPECT_EQ(map.has(RenderableMap::Maps::icons_button, "non-existent"), false);
    map.clear(RenderableMap::Maps::icons_button, {"non-existent"});
    EXPECT_EQ(map.has(RenderableMap::Maps::icons_button, "non-existent"), false);

    // Check drawable registration
    EXPECT_EQ(map.hasDrawable("btn"), false);
    EXPECT_EQ(map.isDrawableLocked("btn"), false);
    map.registerDrawable("btn", map.initButtonIcon("btn"));
    EXPECT_EQ(map.hasDrawable("btn"), true);
    EXPECT_EQ(map.isDrawableLocked("btn"), false);
    // Locking
    EXPECT_EQ(map.lockDrawable("btn"), true);
    EXPECT_EQ(map.isDrawableLocked("btn"), true);
    // Standard delete
    EXPECT_EQ(map.deleteDrawable("btn"), false);
    EXPECT_EQ(map.hasDrawable("btn"), true);
    // Forced delete
    EXPECT_EQ(map.deleteDrawable("btn", true), true);
    EXPECT_EQ(map.hasDrawable("btn"), false);
}

TEST(Maps, MapsValidity) {
    MapEasy easy;
    MapHard hard;

    int *map = easy.getMap();
    for(int i = 0; i < easy.getMapWidth() * easy.getMapHeight(); i++) {
        ASSERT_LE(map[i], 4);
    }

    map = hard.getMap();
    for(int i = 0; i < hard.getMapWidth() * hard.getMapHeight(); i++) {
        ASSERT_LE(map[i], 4);
    }
}

#endif //TD_TOWERDEFENSE_ASSETSMAPTESTS_H
