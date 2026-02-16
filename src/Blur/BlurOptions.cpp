#include "BlurOptions.hpp"
#include <Geode/Geode.hpp>
#include <Geode/loader/SettingV3.hpp>

using namespace geode::prelude;

$on_mod(Loaded)
{
    listenForSettingChanges<bool>("enabled", [](bool value)
    {
        BlurAPIOptions::enabled = value;
    });

    listenForSettingChanges<int>("passes", [](int value)
    {
        BlurAPIOptions::passes = value;
    });

    BlurAPIOptions::enabled = Mod::get()->getSettingValue<bool>("enabled");
    BlurAPIOptions::passes = Mod::get()->getSettingValue<int>("passes");
}