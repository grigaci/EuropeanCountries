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
 * @file Controller.cpp
 * @author Bogdan Iusco
 *
 * @brief Application controller.
 */

#include <NativeUI/Screen.h>
#include <MAUtil/Moblet.h>
#include <conprint.h>

#include "Controller.h"
#include "../Model/DatabaseManager.h"
#include "../Model/Country.h"
#include "../View/CountriesListScreen.h"
#include "../View/CountryInfoScreen.h"
#include "../View/DisclaimerScreen.h"
#include "../View/LoadingScreen.h"
#include "../View/ViewUtils.h"

namespace EuropeanCountries
{
	/**
	 * Constructor.
	 */
	Controller::Controller():
		mDatabaseManager(NULL),
		mCountriesListScreen(NULL),
		mCountryInfoScreen(NULL),
		mDisclaimerScreen(NULL),
		mCurrentlyShownScreen(NULL)
	{
		initScreenSizeConstants();

		LoadingScreen* loadingScreen = new LoadingScreen();
		if (isWindowsPhone())
		{
			loadingScreen->show();
		}

		mDatabaseManager = new DatabaseManager();
		mDatabaseManager->readDataFromFiles();
		mCountriesListScreen = new CountriesListScreen(*mDatabaseManager, *this);
		mCountryInfoScreen = new CountryInfoScreen(*this);
		mDisclaimerScreen = new DisclaimerScreen(*this);

		this->showScreen(*mCountriesListScreen);
		delete loadingScreen;
	}

	/**
	 * Destructor.
	 */
	Controller::~Controller()
	{
		delete mDatabaseManager;
		delete mCountriesListScreen;
		delete mCountryInfoScreen;
		delete mDisclaimerScreen;
	}

	/**
	 * Handle the back button action.
	 */
	void Controller::backButtonPressed()
	{
		if (mCurrentlyShownScreen == mCountryInfoScreen)
		{
			this->showScreen(*mCountriesListScreen);
		}
		else if (mCurrentlyShownScreen == mDisclaimerScreen)
		{
			this->showScreen(*mCountryInfoScreen);
		}
		else
		{
			MAUtil::Moblet::close();
		}
	}

	/**
	 * Show country info.
	 * Called after the user selects an country from the list.
	 * From CountriesListScreenObserver.
	 * @param countryID Country's id to show.
	 */
	void Controller::showCountryInfoScreen(const int countryID)
	{
		Country* country = mDatabaseManager->getCountryByID(countryID);
		if (!country)
		{
			printf("Controller::showCountryInfoScreen Invalid countryID %d", countryID);
			return;
		}
		mCountryInfoScreen->setDisplayedCountry(*country);
		this->showScreen(*mCountryInfoScreen);
	}

	/**
	 * Show countries list screen.
	 * Called when user taps the back button.
	 * From CountryInfoScreenObserver.
	 */
	void Controller::showCountriesListScreen()
	{
		this->showScreen(*mCountriesListScreen);
	}

	/**
	 * Show disclaimer screen.
	 * Called when user taps the info button.
	 * From CountryInfoScreenObserver.
	 */
	void Controller::showDisclaimerScreen()
	{
		this->showScreen(*mDisclaimerScreen);
	}

	/**
	 * Show country info screen.
	 * Called when user taps the back button.
	 * From DisclaimerScreenObserver.
	 */
	void Controller::showCountryInfoScreen()
	{
		this->showScreen(*mCountryInfoScreen);
	}

	/**
	 * Show a given NativeUI Screen.
	 * @param screen Screen to show.
	 */
	void Controller::showScreen(NativeUI::Screen& screen)
	{
		mCurrentlyShownScreen = &screen;
		mCurrentlyShownScreen->show();
	}

} // end of EuropeanCountries
