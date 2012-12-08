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

#include <conprint.h>

#include "Controller.h"
#include "../Model/DatabaseManager.h"
#include "../Model/Country.h"
#include "../View/CountriesListScreen.h"
#include "../View/CountryInfoScreen.h"
#include "../View/ViewUtils.h"

namespace EuropeanCountries
{
	/**
	 * Constructor.
	 */
	Controller::Controller():
		mDatabaseManager(NULL),
		mCountriesListScreen(NULL),
		mCountryInfoScreen(NULL)
	{
		initScreenSizeConstants();

		mDatabaseManager = new DatabaseManager();
		mDatabaseManager->readDataFromFiles();
		mCountriesListScreen = new CountriesListScreen(*mDatabaseManager, *this);
		mCountryInfoScreen = new CountryInfoScreen(*this);

		mCountriesListScreen->show();
	}

	/**
	 * Destructor.
	 */
	Controller::~Controller()
	{
		delete mDatabaseManager;
		delete mCountriesListScreen;
		delete mCountryInfoScreen;
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
		mCountryInfoScreen->show();
	}

	/**
	 * Show countries list screen.
	 * Called when user taps the back button.
	 * From CountryInfoScreenObserver.
	 */
	void Controller::showCountriesListScreen()
	{
		mCountriesListScreen->show();
	}

} // end of EuropeanCountries

