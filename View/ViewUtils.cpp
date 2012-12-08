/*
 Copyright (C) 2012 MoSync AB

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License,
 version 2, as published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 MA 02110-1301, USA.
 */

/**
 * @file ViewUtils.cpp
 * @author Bogdan Iusco
 *
 * @brief Util methods and constants for NativeUI widgets.
 */

#include <NativeUI/Label.h>
#include <NativeUI/VerticalLayout.h>

#include "ViewUtils.h"

namespace EuropeanCountries
{

	/**
	 * Screen size.
	 */
	int gScreenWidth = 0;
	int gScreenHeight = 0;

	/**
	 * Create an NativeUI Label object with given values.
	 * @param text Text to set.
	 * @param fontColor Text font color.
	 * @param width Label's width in pixels or size constant.
	 * @param height Label's height in pixels or size constant.
	 * @return The created label object. Its ownership is passed to the caller.
	 */
	NativeUI::Label* createLabel(
		const MAUtil::String& text,
		const int fontColor,
		const int width,
		const int height)
	{
		NativeUI::Label* label = new NativeUI::Label();
		label->setText(text);
		label->setWidth(width);
		label->setHeight(height);
		label->setFontColor(fontColor);
		label->setMaxNumberOfLines(0);
		return label;
	}

	/**
	 * Create an empty transparent VerticalLayout widget.
	 * @param height Layout's height.
	 * @param width Layout's width.
	 * @return The layout. Its ownership is passed to the caller.
	 */
	NativeUI::VerticalLayout* createSpacer(
		const int height,
		const int width)
	{
		NativeUI::VerticalLayout* layout = new NativeUI::VerticalLayout();
		layout->setHeight(height);
		layout->setWidth(width);
		layout->setProperty(MAW_WIDGET_BACKGROUND_COLOR, "00000000");
		return layout;
	}

} // end of EuropeanCountries
