#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

void helpGeodeUpdate() {
    auto* mod = Loader::get()->getLoadedMod("geode.loader");
    auto value = mod->getSavedValue<std::string>("last-modified-auto-update-check");
    if (value.ends_with('\r')) {
        mod->setSavedValue("last-modified-auto-update-check", value.substr(0, value.size() - 1));
    }
}

$on_mod(Loaded) {
    helpGeodeUpdate();
}