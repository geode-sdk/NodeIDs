#include <Geode/Geode.hpp>
#include <Geode/modify/ConfigureHSVWidget.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(ConfigureHSVWidget) {
	this->m_hueLabel->setID("hue-label");
	this->m_saturationLabel->setID("saturation-label");
	this->m_brightnessLabel->setID("brightness-label");

	this->m_hueSlider->setID("hue-slider");
	this->m_saturationSlider->setID("saturation-slider");
	this->m_brightnessSlider->setID("brightness-slider");

	setIDSafe<CCScale9Sprite>(this, 0, "background");
	auto menu = setIDSafe<CCMenu>(this, 0, "button-menu");
	if (menu) {
		setIDSafe<CCMenuItemToggler>(menu, 0, "add-saturation-toggle");
		setIDSafe<CCMenuItemToggler>(menu, 1, "add-brightness-toggle");
		setIDSafe<CCMenuItemSpriteExtra>(menu, 0, "reset-button");
	}
}

struct ConfigureHSVWidgetIDs : Modify<ConfigureHSVWidgetIDs, ConfigureHSVWidget> {
	static void onModify(auto& self) {
		if (!self.setHookPriority("ConfigureHSVWidget::init", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set ConfigureHSVWidget::init hook priority, node IDs may not work properly");
		}
	}

	bool init(ccHSVValue hsv, bool noBackground, bool addInputs) {
		if (!ConfigureHSVWidget::init(hsv, noBackground, addInputs)) return false;

		NodeIDs::get()->provide(this);

		return true;
	}
};
