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

#define LABEL_MAX_LINES 100

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
	 * Init global screen size constants.
	 * On Android and WP7 platforms should be used with default param value,
	 * while on iOS should be called with screen width and height values.
	 * @param width Width to set. If it's zero, maGetScrSize() syscall will be used
	 * to get the real value.
	 * @param height Height to set. If it's zero, maGetScrSize() syscall will be used
	 * to get the real value.
	 */
	void initScreenSizeConstants(
		const int width,
		const int height)
	{
		MAExtent screenSize = maGetScrSize();
		gScreenWidth = width;
		if  (gScreenWidth == 0)
		{
			gScreenWidth = EXTENT_X(screenSize);
		}

		gScreenHeight = height;
		if (gScreenHeight == 0)
		{
			gScreenHeight = EXTENT_Y(screenSize);
		}
		printf("gScreenWidth = %d gScreenHeight = %d", gScreenWidth, gScreenHeight);
	}

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
		label->setMaxNumberOfLines(LABEL_MAX_LINES);
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

	/**
	 * Detects if the current platform is Android.
	 * @return true if the platform is Android, false otherwise.
	 */
	bool isAndroid()
	{
		char platform[NativeUI::BUF_SIZE];
		maGetSystemProperty("mosync.device.OS", platform, NativeUI::BUF_SIZE);
		if ( strcmp(platform,"Android") == 0 )
		{
			return true;
		}

		return false;
	}

	/**
	 * Detects if the current platform is iOS.
	 * @return true if the platform is iOS, false otherwise.
	 */
	bool isIOS()
	{
		char platform[NativeUI::BUF_SIZE];
		maGetSystemProperty("mosync.device.OS", platform, NativeUI::BUF_SIZE);
		for (unsigned int i = 0; i < strlen(platform); i++)
		{
			platform[i] = tolower(platform[i]);
		}
		if (strstr(platform,"iphone") != NULL)
		{
			return true;
		}

		return false;
	}

	/**
	 * Detects if the current platform is Windows Phone.
	 * @return true if the platform is Windows Phone, false otherwise.
	 */
	bool isWindowsPhone()
	{
		char platform[NativeUI::BUF_SIZE];
		maGetSystemProperty("mosync.device.OS", platform, NativeUI::BUF_SIZE);
		for (unsigned int i = 0; i < strlen(platform); i++)
		{
			platform[i] = tolower(platform[i]);
		}
		if (strstr(platform,"microsoft") != NULL &&
			strstr(platform,"windows") != NULL)
		{
			return true;
		}

		return false;
	}

} // end of EuropeanCountries
