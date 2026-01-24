#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/ColorSelectLiveOverlay.hpp>
#include <Geode/modify/HSVLiveOverlay.hpp>
#include <Geode/modify/CCScene.hpp>
#include <Geode/modify/OptionsLayer.hpp>
#include "BlurAPI.hpp"

using namespace geode::prelude;

class $modify (MenuLayer)
{
    virtual bool init()
    {
        if (!MenuLayer::init())
            return false;

        auto test = CCScale9Sprite::create("GJ_square01.png");
        test->setOpacity(100);
        test->setColor(ccc3(0, 0, 0));
        test->setPosition(ccp(250, 50));

        BlurAPI::addBlur(test);
        BlurAPI::getOptions(test)->forcePasses = true;
        BlurAPI::getOptions(test)->passes = 5;
        addChild(test, 10);

        auto test2 = CCScale9Sprite::create("GJ_square01.png");
        test2->setOpacity(100);
        test2->setColor(ccc3(0, 0, 0));
        test2->setPosition(ccp(250, 150));

        BlurAPI::addBlur(test2);
        BlurAPI::getOptions(test2)->forcePasses = true;
        BlurAPI::getOptions(test2)->passes = 9;
        addChild(test2, 10);

        /*
        auto test2 = CCScale9Sprite::create("GJ_square01.png");
        test2->setOpacity(100);
        test2->setColor(ccc3(0, 0, 0));

        auto test3 = CCScale9Sprite::create("GJ_square01.png");
        test3->setOpacity(100);
        test3->setColor(ccc3(0, 0, 0));

        auto test4 = CCScale9Sprite::create("GJ_square01.png");
        test4->setOpacity(100);
        test4->setColor(ccc3(0, 0, 0));

        auto test5 = CCScale9Sprite::create("GJ_square01.png");
        test5->setOpacity(100);
        test5->setColor(ccc3(0, 0, 0));

        auto test6 = CCScale9Sprite::create("GJ_square01.png");
        test6->setOpacity(100);
        test6->setColor(ccc3(0, 0, 0));

        BlurAPI::addBlur(test2);
        BlurAPI::addBlur(test3);
        BlurAPI::addBlur(test4);
        BlurAPI::addBlur(test5);
        BlurAPI::addBlur(test6);
        addChild(test2);
        addChild(test3);
        addChild(test4);
        addChild(test5);
        addChild(test6);*/
        return true;
    }
};

class $modify (OptionsLayer)
{
    virtual void customSetup()
    {
        OptionsLayer::customSetup();

        BlurAPI::addBlur(this);
    }
};

class $modify (EditorUI)
{
    bool init(LevelEditorLayer* editorLayer)
    {
        if (!EditorUI::init(editorLayer))
            return false;

        if (auto spr = getChildByType<CCSprite>(0))
        {
            BlurAPI::addBlur(spr);
        }

        return true;
    }
};

class $modify (ColorSelectLiveOverlay)
{
    bool init(ColorAction* baseAction, ColorAction* detailAction, EffectGameObject* object)
    {
        if (!ColorSelectLiveOverlay::init(baseAction, detailAction, object))
            return false;

        if (auto layer = getChildByType<CCLayer>(0))
        {
            if (auto bg = layer->getChildByType<CCScale9Sprite>(0))
            {
                BlurAPI::addBlur(bg);
            }
        }

        return true;
    }
};

class $modify (HSVLiveOverlay)
{
    bool init(GameObject* object, cocos2d::CCArray* objects)
    {
        if (!HSVLiveOverlay::init(object, objects))
            return false;

        if (auto layer = m_widget)
        {
            if (auto bg = layer->getChildByType<CCScale9Sprite>(0))
            {
                BlurAPI::addBlur(bg);
            }
        }

        return true;
    }
};