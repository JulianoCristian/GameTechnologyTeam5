#ifndef UI_MANAGER_H_
#define UI_MANAGER_H_

#pragma once
#include <OgreBillboardSet.h>
#include "BaseApplication.h"
#include "SdkTrays.h"
#include "CharacterStats.h"


class UIManager
{
public:
	UIManager();

	void init();
	void setupUI();

	void adjustHealthBar(Ogre::Real, Ogre::Real);
	void adjustStaminaBar(Ogre::Real, Ogre::Real);
	void adjustTimer(Ogre::Real);
	void createDialog(Ogre::String);
	void createPrincessDialog(Ogre::String);
	void createEnemyDialog(Ogre::String);
	void destroyDialog();
	void destroyPrincessDialog();
	void destroyEnemyDialog();
	void appendDialogText(Ogre::String);
	void setStandardEventLogText();
	void setStandardEventLogActive();
	void setNPCEventLogText();
	void setPickUpEventLogText();
	void setPrincessEventLogText();
	void updateStatsPanel(CharacterStats*);
	static Ogre::Real calcBarSize(Ogre::Real, Ogre::Real, Ogre::Real);

private:
	OgreBites::SdkTrayManager*	_mSdkTrayMgr;
	OgreBites::SdkTrayListener* _mSdkTrayListener;

	Ogre::RenderWindow*			_mWindow;

	OgreBites::InputContext     _mInputContext;

	OgreBites::TextBox*			_mDialogTextArea;
	OgreBites::DecorWidget*		_healthBarWidget;
	OgreBites::DecorWidget*		_staminaBarWidget;
	OgreBites::Slider*		_karmaBarWidget;
	OgreBites::ParamsPanel*		_gameTimer;
	OgreBites::ParamsPanel*		_statsPanel;
	OgreBites::TextBox*         _eventLogTextBox;
	Ogre::SceneNode*			_uiNode;

	Ogre::Real					_maxWidthBar;
	Ogre::Real					_heightBar;
	Ogre::StringVector			_ParamValues;
	Ogre::StringVector			_ParamNames;

	bool _isStandardDialogActive;
	bool _isNPCDialogActive;
	bool _isPickUpActive;
};

#endif
