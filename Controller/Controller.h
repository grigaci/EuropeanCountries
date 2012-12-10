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
 * @file Controller.h
 * @author Bogdan Iusco
 *
 * @brief Application controller.
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../View/CountriesListScreenObserver.h"
#include "../View/CountryInfoScreenObserver.h"

namespace NativeUI
{
	class Screen;
}

namespace EuropeanCountries
{

	class Country;
	class CountriesListScreen;
	class CountryInfoScreen;
	class DatabaseManager;

	class Controller:
		public CountriesListScreenObserver,
		public CountryInfoScreenObserver
	{
	public:
		/**
		 * Constructor.
		 */
		Controller();

		/**
		 * Destructor.
		 */
		virtual ~Controller();

		/**
		 * Handle the back button action.
		 */
		void backButtonPressed();

		/**
		 * Show country info.
		 * Called after the user selects an country from the list.
		 * From CountriesListScreenObserver.
		 * @param countryID Country's id to show.
		 */
		virtual void showCountryInfoScreen(const int countryID);

		/**
		 * Show countries list screen.
		 * Called when user taps the back button.
		 * From CountryInfoScreenObserver.
		 */
		virtual void showCountriesListScreen();

	private:
		/**
		 * Show a given NativeUI Screen.
		 * @param screen Screen to show.
		 */
		void showScreen(NativeUI::Screen& screen);

	private:
		/**
		 * Used to read data from files.
		 */
		DatabaseManager* mDatabaseManager;

		/**
		 * Screen used to display all countries in a list.
		 */
		CountriesListScreen* mCountriesListScreen;

		/**
		 * Screen used to display country info.
		 */
		CountryInfoScreen* mCountryInfoScreen;

		/**
		 * Points to the currently visible screen.
		 * Not owns the pointed object.
		 */
		NativeUI::Screen* mCurrentlyShownScreen;

	}; // end of Controller

} // end of EuropeanCountries

#endif /* CONTROLLER_H_ */
