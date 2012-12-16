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
 * @file LoadingScreen.cpp
 * @author Bogdan Iusco
 *
 * @brief NativeUI Screen used to show an ActivityIndicatior.
 * It does not interact with the user, used only when the application
 * is reading data from files.
 */

#define LOADING_LABEL_TEXT "Loading..."
#define SPACER_HEIGHT 15

#include <NativeUI/ActivityIndicator.h>

#include "LoadingScreen.h"
#include "ViewUtils.h"

namespace EuropeanCountries
{

	/**
	 * Constructor.
	 */
	LoadingScreen::LoadingScreen():
		mMainLayout(NULL)
	{
		this->createUI();
	}

	/**
	 * Create screen's UI.
	 */
	void LoadingScreen::createUI()
	{
		mMainLayout = new NativeUI::VerticalLayout();
		this->setMainWidget(mMainLayout);

		mMainLayout->addChild(new NativeUI::VerticalLayout);
		NativeUI::ActivityIndicator* activityIndicator =
			new NativeUI::ActivityIndicator();
		mMainLayout->addChild(activityIndicator);

		if (isWindowsPhone())
		{
			NativeUI::Label* loading = new NativeUI::Label(LOADING_LABEL_TEXT);
			loading->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
			loading->fillSpaceHorizontally();
			mMainLayout->addChild(loading);

			mMainLayout->addChild(createSpacer(SPACER_HEIGHT));
			activityIndicator->fillSpaceHorizontally();
		}
		else
		{
			mMainLayout->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);
		}

		mMainLayout->addChild(new NativeUI::VerticalLayout);
		activityIndicator->show();
	}

} // end of EuropeanCoutnries
