#include "Blur.hpp"
#include <Geode/modify/CCEGLViewProtocol.hpp>
#include <Geode/modify/GameManager.hpp>

class $modify(CCEGLViewProtocol)
{
    void setFrameSize(float width, float height)
    {
        CCEGLViewProtocol::setFrameSize(width, height);
        if (!CCDirector::get()->getOpenGLView())
            return;
        cleanupPostProcess();
        setupPostProcess();
    }
};

class $modify(GameManager)
{
    void reloadAllStep5()
    {
        GameManager::reloadAllStep5();
        cleanupPostProcess();
        setupPostProcess();
    }
};

$on_mod(Loaded)
{
    Loader::get()->queueInMainThread([]()
    {
        cleanupPostProcess();
        setupPostProcess();
    });
}