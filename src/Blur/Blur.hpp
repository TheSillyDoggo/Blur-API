#pragma once

#include <numbers>
#include <Geode/Geode.hpp>
#include "../BlurAPI.hpp"

using namespace geode::prelude;

void setupPostProcess();
void cleanupPostProcess();

namespace Blur
{
    void drawBlurredNode(CCNode* node, BlurAPI::BlurOptions* options);
    std::string getShaderPath(bool vertexShader);
};