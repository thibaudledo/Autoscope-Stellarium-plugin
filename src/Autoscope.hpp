/*
 * Copyright (C) 2007 Fabien Chereau
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
 */

#ifndef AUTOSCOPE_HPP
#define AUTOSCOPE_HPP

#include "StelModule.hpp"
#include "StelGui.hpp"
#include "VecMath.hpp"
#include "StelFader.hpp"
#include <QFont>

#include "StelMovementMgr.hpp"
#include "StelObjectMgr.hpp"
#include "StelObjectType.hpp"

#include "network/CommandParser.hpp"
#include "AutoscopeFtpDialog.hpp"

#include <QHostAddress>

class StelButton;
class QPixmap;
class AutoscopeWindowForm;
class AutoscopePictureWindowForm;
class TcpClient;

/*!
 * \file Autoscope.hpp
 * \brief Main plugin class
 * \author thibaud-ledoledec
 */

/*!
 * \class Autoscope
 * \brief This class is use to retrieve and compute data for sending to the telescope, and call user interfaces windows
 */
class Autoscope : public StelModule
{
    Q_OBJECT
public:
    /*!
     * \brief Builder of the Autoscope class
     */
    Autoscope();

    /*!
     * \brief Destroyer of the Autoscope class
     */
    virtual ~Autoscope();

	///////////////////////////////////////////////////////////////////////////
	// Methods defined in the StelModule class

    /*!
     * \brief Init method is inherited form StelModule class and is use to initialize components sush as StelButton
     * \see StelModule
     */
	virtual void init();

    /*!
     * \brief Update method is inherited form StelModule class and is use to update components or methods.
     * It's automatically called by StelModuleMgr
     * \see StelModule
     */
    virtual void update(double);

    /*!
     * \brief Draw method is inherited form StelModule class and is use to draw components on the user interface
     * \param core The object given by StelModuleMgr to draw forms
     * \see StelModule
     */
	virtual void draw(StelCore* core);

    /*!
     * \brief getCallOrder method
     * \param actionName
     * \see StelModule
     * \return
     */
	virtual double getCallOrder(StelModuleActionName actionName) const;

    /*!
     * \brief ConfigureGui method is inherited from StelModule class and is use to show the user interface through the plugin manager
     * \param show If show is true, set the gui visible, else set it invisible
     * \return true if it doesn't crash!
     * \see StelModule
     */
    virtual bool configureGui(bool show);

    /*!
     * \brief Method used to retrieve the configuration of the plugin
     */
    void loadConfiguration();

    /*!
     * \brief Method used to restore the default configuration of the plugin
     */
    void restoreDefaultConfiguration();

    /*!
     * \brief Method used to retrieve the altitude and the azimuth of an object
     * \param object The object that we want to retrieve data from
     */
    void getAltAzi(StelObjectP object);

    /*!
     * \brief Method used to search an object by it's name
     * \param objectName The name of the object
     * \return A string to display in the searchMessenger
     */
    QString searchAnObject(QString objectName);

    /*!
     * \brief Method used to modify the object that the Autoscope should track
     * \param object The object to track
     */
    void setTrackObject(StelObjectP object);

    /*!
     * \brief Method used to tarck the object selected by the user
     */
    void trackSelectedObject(void);

    /*!
     * \brief Method used to tarck the object search by the user
     * \return A string to display in the searchMessenger
     */
    QString trackSearchedObject(void);

    /*!
     * \brief Method used to clear the current tracked object
     */
    void clearTrackedObject(void);

    /*!
     * \brief Method used to move the view in Stellarium to an object
     * \param object
     */
    void moveObserverToObject(StelObjectP object);

    /*!
     * \brief Getter which allow any class which have an instance of Autoscope class to retrieve an instance of the configuration window
     * \return An instance of the configuration window
     */
    AutoscopeWindowForm* getAutoscopeWindow(void){if(m_autoscopeWindow!=nullptr)return m_autoscopeWindow;}

    /*!
     * \brief Getter which allow any class which have an instance of Autoscope class to retrieve an instance of the picture window
     * \return An instance of the picture window
     */
    AutoscopePictureWindowForm* getAutoscopePictureWindow(void){if(m_autoscopePictureWindow!=nullptr)return m_autoscopePictureWindow;}

    CommandParser* getCommandParser(void){if(m_parser!=nullptr)return m_parser;}

    /*!
     * \brief Getter allow any class which have an instance of Autoscope class to retrieve the width of the screen
     * \return The width of the screen
     */
    int getScreenWidth(void){return m_screenWidth;}

    /*!
     * \brief Getter allow any class which have an instance of Autoscope class to retrieve the height of the screen
     * \return The height of the screen
     */
    int getScreenHeight(void){return m_screenHeight;}

    /*!
     * \brief Setter used to set the IP address of the Autoscope
     * \param addr The IP address of the Autoscope
     */
    void setIpAddress(QString addr){m_autoscopeIp = QHostAddress(addr);}

    /*!
     * \brief Setter used to set the port of the Autoscope
     * \param port The port of the Autoscope
     */
    void setPort(int port){m_autoscopePort = port;}

    /*!
     * \brief Method used to connect the plugin to the Autoscope
     */
    void connectToAutoscope(void);

    /*!
     * \brief Method used to disconnect the plugin from the Autoscope
     */
    void deconnectFromAutoscope(void);

    void sendToServer(QString);

    /*!
     * \brief An instance of Stellarium movement manager and it's use to move the view in Stellarium
     * \see StelMovementMgr
     */
    StelMovementMgr* mvMgr;

    /*!
     * \brief An instance of Stellarium object manager and it's use to retrieve selected object or search object by name
     * \see StelObjectMgr
     */
    StelObjectMgr* objectMgr;

private:
	// Font used for displaying our text
    QSettings* conf;    /*!< An instance of QSettings */
    StelGui* gui;   /*!< An instance of StelGui */

    /*!
     * \brief An instance of AutoscopeWindowForm class
     * \see AutoscopeWindowForm
     */
    AutoscopeWindowForm* m_autoscopeWindow;

    /*!
     * \brief An instance of AutoscopePictureWindowForm class
     * \see AutoscopePictureWindowForm
     */
    AutoscopePictureWindowForm* m_autoscopePictureWindow;

    AutoscopeFtpDialog* m_autoscopeFtpDialog;

    /*!
     * \brief An instance of StelCore
     */
    StelCore* m_core;

    QTimer* m_timer;

    CommandParser* m_parser;

    Vec3f markColor;
    LinearFader markFader;
    bool displayedAtStartup;

    bool guiIsVisible = false;  /*!< A flag which represent the visibility of the configuration window */

    StelButton* menuButton;             /*!< An instance of StelButton */
    StelButton* trackButton;            /*!< An instance of StelButton */
    StelButton* unTrackButton;          /*!< An instance of StelButton */
    StelButton* EnablePictureDisplay;   /*!< An instance of StelButton */
    StelButton* takePicture;            /*!< An instance of StelButton */

    QFont font; /*!< An instance of Qfont */

    StelObjectP Sun;    /*!< An instance of StelObjectP */
    StelObjectP trackObject;    /*!< An instance of StelObjectP */
    StelObjectP selectedObject; /*!< An instance of StelObjectP */
    StelObjectP searchedObject; /*!< An instance of StelObjectP */

    Vec3d objectPosition;   /*!< An instance of Vec3d */
    QList<StelObjectP> newSelected; /*!< A list of StelObjectP */

    bool searchObjectFound = false; /*!< A flag which indicates if the searched object has been found */

    int m_screenWidth;  /*!< The screen width */
    int m_screenHeight; /*!< The screen height */

    /*!
     * \brief An instance of TcpClient class
     * \see TcpClient
     */
    TcpClient* m_client;

    QHostAddress m_autoscopeIp; /*!< The Autoscope IP address */

    int m_autoscopePort = 4444; /*!< The Autoscope IP port */

public slots:

    /*!
     * \brief Enable the configuration menu
     */
    void showGui(void);

    /*!
     * \brief Start tracking the selected object
     */
    void slotTrackObject(void);

    /*!
     * \brief Stop tracking the tracked object
     */
    void slotUnTrackOject(void);

    /*!
     * \brief Toggle the visibility of the picture display
     */
    void slotEnablePictureDispaly(void);

    /*!
     * \brief Send a command to the Autoscope to take a picture
     */
    void slotTakePicture(void);

    /*!
     * \brief Triggered when the plugin succeed to connect to the Autoscope
     */
    void slotConnected(void);

    void slotUpdateAltAz(void);

    /*!
     * \brief Method used to disconnect the plugin from the Autoscope
     */
    void slotDeconnectFromAutoscope(void);
};


#include <QObject>
#include "StelPluginInterface.hpp"

//! This class is used by Qt to manage a plug-in interface
class AutoscopeStelPluginInterface : public QObject, public StelPluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID StelPluginInterface_iid)
	Q_INTERFACES(StelPluginInterface)
public:
	virtual StelModule* getStelModule() const;
	virtual StelPluginInfo getPluginInfo() const;
	virtual QObjectList getExtensionList() const { return QObjectList(); }
};

#endif /* HELLOSTELMODULE_HPP */
