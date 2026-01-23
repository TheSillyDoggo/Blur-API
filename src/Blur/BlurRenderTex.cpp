#include "BlurRenderTex.hpp"
#include "Blur.hpp"

using namespace geode::prelude;

BlurRenderTex* BlurRenderTex::create(int width, int height)
{
    auto pRet = new BlurRenderTex();

    if (pRet && pRet->initWithWidthAndHeight(width, height, kCCTexture2DPixelFormat_RGBA8888))
    {
        pRet->init();
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return nullptr;
}

void BlurRenderTex::visit()
{
    kmGLPushMatrix();
    kmGLLoadIdentity();

    getSprite()->setPosition(CCDirector::get()->getWinSize() / 2);
    Blur::drawBlurredNode(getSprite(), options);

    kmGLPopMatrix();
}