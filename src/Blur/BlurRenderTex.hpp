#pragma once

#include <Geode/Geode.hpp>
#include "../BlurAPI.hpp"

class BlurRenderTex : public cocos2d::CCRenderTexture
{
    public:
        BlurAPI::BlurOptions* options = nullptr;

        static BlurRenderTex* create(int width, int height);

        virtual void visit();
};