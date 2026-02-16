#include <Geode/Geode.hpp>
#include <Geode/modify/CCNode.hpp>
#include <Geode/modify/CCLayerColor.hpp>
#include "../BlurAPI.hpp"
#include "BlurRenderTex.hpp"
#include "BlurOptions.hpp"

using namespace geode::prelude;
using namespace BlurAPI;

CCRect getWorldSpaceBoundingBox(CCNode* node)
{
	auto parent = node->getParent();
	auto bounding_box = node->boundingBox();
	CCPoint bb_min(bounding_box.getMinX(), bounding_box.getMinY());
	CCPoint bb_max(bounding_box.getMaxX(), bounding_box.getMaxY());

	auto min = parent ? parent->convertToWorldSpace(bb_min) : bb_min;
	auto max = parent ? parent->convertToWorldSpace(bb_max) : bb_max;

	return CCRectMake(min.x, min.y, max.x - min.x, max.y - min.y);
}

class $modify (CCLayerColor)
{
    virtual void draw()
    {
        if (!BlurAPI::getOptions(this))
            return CCLayerColor::draw();

        auto c = getColor();
        auto o = getOpacity();

        ccBlendFunc(getBlendFunc());
        ccDrawSolidRect(ccp(0, 0), getContentSize(), ccc4f(c.r / 255.0f, c.g / 255.0f, c.b / 255.0f, o / 255.0f));
    }
};

class $modify (CCNode)
{
    virtual void visit()
    {
        if (!BlurAPIOptions::enabled)
            return CCNode::visit();

        static bool isCapturingScene = false;
        static bool shouldStopCapturing = false;
        static CCNode* capturingSceneStopAt = nullptr;

        if (isCapturingScene)
        {
            if (this == capturingSceneStopAt || shouldStopCapturing)
            {
                shouldStopCapturing = true;
            }
            else
            {
                if (auto shader = typeinfo_cast<ShaderLayer*>(this))
                    return;

                CCNode::visit();
            }

            return;
        }

        if (auto blur = typeinfo_cast<BlurOptions*>(getUserObject(BLUR_TAG)))
        {
            isCapturingScene = true;
            capturingSceneStopAt = this;
            shouldStopCapturing = false;

            if (static_cast<CCNode*>(this) == CCScene::get())
                capturingSceneStopAt = nullptr;

            if (!blur->rTex)
            {
                auto size = CCDirector::get()->getWinSize();
                blur->rTex = BlurRenderTex::create((int)(size.width), (int)(size.height));
                static_cast<BlurRenderTex*>(blur->rTex)->options = blur;
                blur->clip = CCClippingNode::create(this);
                this->release(); // we dont want clippingnode to retain our node, its a child so it'll just cause it to be retained forever and leak memory
                blur->clip->setAlphaThreshold(blur->alphaThreshold);
                blur->clip->addChild(blur->rTex);
            }

            auto rTex = blur->rTex;

            rTex->beginWithClear(0, 0, 0, 0);
            CCScene::get()->visit();
            rTex->end();

            isCapturingScene = false;

            auto rec = getWorldSpaceBoundingBox(this);

            if (rec.getMinX() < 0)
                rec += CCRectMake(-rec.getMinX(), 0, 0, 0);

            if (rec.getMinY() < 0)
                rec += CCRectMake(0, -rec.getMinY(), 0, 0);

            auto scX = (1.0f / CCDirector::get()->getWinSize().width) * CCEGLView::get()->getFrameSize().width;
            auto scY = (1.0f / CCDirector::get()->getWinSize().height) * CCEGLView::get()->getFrameSize().height;

            auto uiBL = ccp(rec.getMinX() * scX, rec.getMinY() * scY);
            auto uiTR = ccp(rec.getMaxX() * scX, rec.getMaxY() * scY);

            auto shadow = 30 * BlurAPIOptions::passes;

            auto sciz = glIsEnabled(GL_SCISSOR_TEST);
            glEnable(GL_SCISSOR_TEST);
            glScissor(uiBL.x - shadow, uiBL.y - shadow, uiTR.x + shadow, uiTR.y + shadow);

            blur->clip->visit();

            if (!sciz)
                glDisable(GL_SCISSOR_TEST);

            if (!getParent()) // its a scene, so we dont wanna render the original
                return;
        }

        CCNode::visit();
    }
};