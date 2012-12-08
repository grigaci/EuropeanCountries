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
 * @file CountryInfoScreen.cpp
 * @author Bogdan Iusco
 *
 * @brief NativeUI Screen used to show country info.
 */

#define PADDING_LEFT_PERCENTAGE 2

#define POPULATION_LABEL_TEXT "Population"
#define AREA_LABEL_TEXT "Area"
#define LANGUAGES_LABEL_TEXT "Languages"
#define GOVERNMENT_LABEL_TEXT "Government"
#define CAPITAL_LABEL_TEXT "Capital"


#include <NativeUI/HorizontalLayout.h>
#include <NativeUI/Label.h>
#include <NativeUI/Image.h>
#include <NativeUI/ImageButton.h>
#include <NativeUI/RelativeLayout.h>
#include <NativeUI/VerticalLayout.h>

#include "MAHeaders.h"
#include "ViewUtils.h"
#include "CountryInfoScreen.h"
#include "CountryInfoScreenObserver.h"
#include "../Model/Country.h"

namespace EuropeanCountries
{
	/**
	 * Constructor.
	 * @param observer Will be notified when user taps the back button.
	 */
	CountryInfoScreen::CountryInfoScreen(CountryInfoScreenObserver& observer):
		mObserver(observer),
		mMainLayout(NULL),
		mTitleBarLayout(NULL),
		mInfoLayout(NULL),
		mNameLabel(NULL),
		mBackButton(NULL),
		mPopulationLabel(NULL),
		mAreaLabel(NULL),
		mLanguagesLabel(NULL),
		mGovernmentLabel(NULL),
		mCapitalLabel(NULL)
	{
		gScreenWidth = this->getWidth();
		gScreenHeight = this->getHeight();

		this->createUI();
		mBackButton->addButtonListener(this);
	}

	/**
	 * Destructor.
	 */
	CountryInfoScreen::~CountryInfoScreen()
	{
		mBackButton->removeButtonListener(this);
	}

	/**
	 * Show a screen.
	 */
	void CountryInfoScreen::show()
	{
		mInfoLayoutRelative->setContentOffset(0, 0);
		NativeUI::Screen::show();
	}

	/**
	 * Set displayed country.
	 * Labels will be filled with data from a given country.
	 * @param country Country to display.
	 */
	void CountryInfoScreen::setDisplayedCountry(const Country& country)
	{
		mNameLabel->setText(country.getName());
		mPopulationLabel->setText(country.getPopulation());
		mAreaLabel->setText(country.getArea());
		mLanguagesLabel->setText(country.getLanguages());
		mGovernmentLabel->setText(country.getGovernment());
		mCapitalLabel->setText(country.getCapital());
	}

	/**
	 * This method is called if the touch-up event was inside the
	 * bounds of the button.
	 * From ButtonListener.
	 * @param button The button object that generated the event.
	 */
	void CountryInfoScreen::buttonClicked(NativeUI::Widget* button)
	{
		mObserver.showCountriesListScreen();
	}

	/**
	 * Create screen UI.
	 */
	void CountryInfoScreen::createUI()
	{
		mMainLayout = new NativeUI::RelativeLayout();
		this->setMainWidget(mMainLayout);

		this->createImageWidget();
		this->createTitleBar();
		this->createInfoLayout();

		this->createPopulationLabel();
		this->createAreaLabel();
		this->createLanguagesLabel();
		this->createGovernmentLabel();
		this->createCapitalLabel();

		mInfoLayout->addChild(createSpacer());
	}

	/**
	 * Create and add an Image widget to the screen's main layout.
	 */
	void CountryInfoScreen::createImageWidget()
	{
		NativeUI::Image* image = new NativeUI::Image();
		image->setHeight(this->getHeight());
		image->setWidth(gScreenWidth);
		image->setTopPosition(0);
		image->setLeftPosition(0);
		image->setImage(R_COUNTRIES_LIST_SCREEN_BG);
		image->setScaleMode(NativeUI::IMAGE_SCALE_XY);
		mMainLayout->addChild(image);
	}

	/**
	 * Create and add an HorizontalLayout to the screen's main layout.
	 * The layout will contain an back button.
	 */
	void CountryInfoScreen::createTitleBar()
	{
		int barHeight = gScreenHeight / 11;
		mTitleBarLayout = new NativeUI::HorizontalLayout();
		mTitleBarLayout->setLeftPosition(0);
		mTitleBarLayout->setTopPosition(0);
		mTitleBarLayout->setWidth(gScreenWidth);
		mTitleBarLayout->setHeight(barHeight);
		mTitleBarLayout->setProperty(MAW_WIDGET_BACKGROUND_COLOR, "50000000");
		mMainLayout->addChild(mTitleBarLayout);

		mBackButton = new NativeUI::ImageButton();
		mBackButton->setHeight(barHeight);
		mBackButton->setImage(R_BACK_BUTTON);
		mTitleBarLayout->addChild(mBackButton);

		mNameLabel = new NativeUI::Label();
		mNameLabel->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
		mNameLabel->fillSpaceHorizontally();
		mNameLabel->fillSpaceVertically();
		mNameLabel->setFontColor(COLOR_WHITE);
		mTitleBarLayout->addChild(mNameLabel);

		mTitleBarLayout->addChild(
			createSpacer(mNameLabel->getHeight(), mBackButton->getWidth()));
	}

	/**
	 * Create and add an VerticalLayout widget to the screen's main layout.
	 * The widget will be transparent.
	 */
	void CountryInfoScreen::createInfoLayout()
	{
		int titleBarHeight = mTitleBarLayout->getHeight();
		mInfoLayoutRelative = new NativeUI::RelativeLayout();
		mInfoLayoutRelative->setTopPosition(titleBarHeight);
		mInfoLayoutRelative->setLeftPosition(0);
		int height = gScreenHeight - titleBarHeight;
		mInfoLayoutRelative->setHeight(height);
		mInfoLayoutRelative->setWidth(gScreenWidth);
		mInfoLayoutRelative->setScrollable(true);
		mMainLayout->addChild(mInfoLayoutRelative);

		int paddingLeft = gScreenWidth * PADDING_LEFT_PERCENTAGE / 100;
		printf("paddingLeft = %d", paddingLeft);

		mInfoLayout = new NativeUI::VerticalLayout();
		mInfoLayout->setWidth(gScreenWidth - paddingLeft);
		mInfoLayout->wrapContentVertically();
		mInfoLayout->setTopPosition(0);
		mInfoLayout->setLeftPosition(paddingLeft);
		mInfoLayout->setProperty(MAW_WIDGET_BACKGROUND_COLOR, "00000000");
		mInfoLayoutRelative->addChild(mInfoLayout);
	}

	/**
	 * Create and add two labels: first with "Population" text and second
	 * with country's population.
	 */
	void CountryInfoScreen::createPopulationLabel()
	{
		mInfoLayout->addChild(createSpacer());
		NativeUI::Label* countryTextLabel = createLabel(
			POPULATION_LABEL_TEXT, COLOR_LABEL_INFO);
		mInfoLayout->addChild(countryTextLabel);
		mInfoLayout->addChild(createSpacer());

		mPopulationLabel = createLabel("", COLOR_LABEL_DATA, gScreenWidth);
		mInfoLayout->addChild(mPopulationLabel);
	}

	/**
	 * Create and add two labels: first with "Area" text and second
	 * with country's area.
	 */
	void CountryInfoScreen::createAreaLabel()
	{
		mInfoLayout->addChild(createSpacer());
		NativeUI::Label* areaTextLabel = createLabel(AREA_LABEL_TEXT, COLOR_LABEL_INFO);
		mInfoLayout->addChild(areaTextLabel);
		mInfoLayout->addChild(createSpacer());

		mAreaLabel = createLabel("", COLOR_LABEL_DATA, gScreenWidth);
		mInfoLayout->addChild(mAreaLabel);
	}

	/**
	 * Create and add two labels: first with "Languages" text and second
	 * with country's languages.
	 */
	void CountryInfoScreen::createLanguagesLabel()
	{
		mInfoLayout->addChild(createSpacer());
		NativeUI::Label* languagesTextLabel = createLabel(
			LANGUAGES_LABEL_TEXT, COLOR_LABEL_INFO);
		mInfoLayout->addChild(languagesTextLabel);
		mInfoLayout->addChild(createSpacer());

		mLanguagesLabel = createLabel("", COLOR_LABEL_DATA, gScreenWidth);
		mInfoLayout->addChild(mLanguagesLabel);
	}

	/**
	 * Create and add two labels: first with "Government" text and second
	 * with country's government.
	 */
	void CountryInfoScreen::createGovernmentLabel()
	{
		mInfoLayout->addChild(createSpacer());
		NativeUI::Label* governmentTextLabel = createLabel(
			GOVERNMENT_LABEL_TEXT, COLOR_LABEL_INFO);
		mInfoLayout->addChild(governmentTextLabel);
		mInfoLayout->addChild(createSpacer());

		mGovernmentLabel = createLabel("", COLOR_LABEL_DATA, gScreenWidth);
		mInfoLayout->addChild(mGovernmentLabel);
	}

	/**
	 * Create and add two labels: first with "Capital" text and second
	 * with country's capital.
	 */
	void CountryInfoScreen::createCapitalLabel()
	{
		mInfoLayout->addChild(createSpacer());
		NativeUI::Label* capitalTextLabel = createLabel(
			CAPITAL_LABEL_TEXT, COLOR_LABEL_INFO);
		mInfoLayout->addChild(capitalTextLabel);
		mInfoLayout->addChild(createSpacer());

		mCapitalLabel = createLabel("", COLOR_LABEL_DATA, gScreenWidth);
		mInfoLayout->addChild(mCapitalLabel);
	}

} // end of EuropeanCountries

