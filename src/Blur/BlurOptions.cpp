#include "BlurOptions.hpp"
#include <Geode/Geode.hpp>
#include <Geode/loader/SettingV3.hpp>

using namespace geode::prelude;

$on_mod(Loaded)
{
    listenForSettingChanges("enabled", [](bool value)
    {
        BlurAPIOptions::enabled = value;
    });

    listenForSettingChanges("passes", [](int value)
    {
        BlurAPIOptions::passes = value;
    });

    BlurAPIOptions::enabled = Mod::get()->getSettingValue<bool>("enabled");
    BlurAPIOptions::passes = Mod::get()->getSettingValue<int>("passes");
}