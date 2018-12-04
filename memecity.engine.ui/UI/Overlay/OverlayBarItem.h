﻿#ifndef OVERLAYBARITEM_H
#define OVERLAYBARITEM_H
#include "OverlayItem.h"

class OverlayBarItem : public memecity::engine::ui::overlay::OverlayItem<int>
{
private:
public:
	OverlayBarItem(memecity::engine::MultimediaManager& multimedia_manager,
		memecity::engine::ui::overlay::Overlay& parent, int value, int size, float x, float y)
		: OverlayItem<int>(multimedia_manager, parent, value, size, x, y)
	{
	}

	void render() override;
};
#endif // OVERLAYBARITEM_H
