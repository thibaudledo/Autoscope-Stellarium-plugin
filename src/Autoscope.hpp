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

#include <QHostAddress>

class StelButton;
class QPixmap;
class AutoscopeWindowForm;
class AutoscopePictureWindowForm;
class TcpClient;

//! This is an example of a plug-in which can be dynamically loaded into stellarium
class Autoscope : public StelModule
{
    Q_OBJECT
public:
    Autoscope();
    virtual ~Autoscope();

	///////////////////////////////////////////////////////////////////////////
	// Methods defined in the StelModule class
	virtual void init();
    virtual void update(double);
	virtual void draw(StelCore* core);
	virtual double getCallOrder(StelModuleActionName actionName) const;
    virtual bool configureGui(bool show);

    void loadConfiguration();
    void restoreDefaultConfiguration();

    void getAltAzi(StelObjectP object);
    QString searchAnObject(QString objectName);

    void setTrackObject(StelObjectP object);
    void trackSelectedObject(void);
    QString trackSearchedObject(void);

    void clearTrackedObject(void);

    void moveObserverToObject(StelObjectP object);

    AutoscopeWindowForm* getAutoscopeWindow(void){if(m_autoscopeWindow!=nullptr)return m_autoscopeWindow;}
    AutoscopePictureWindowForm* getAutoscopePictureWindow(void){if(m_autoscopePictureWindow!=nullptr)return m_autoscopePictureWindow;}

    StelMovementMgr* mvMgr;
    StelObjectMgr* objectMgr;

    int getScreenWidth(void){return m_screenWidth;}
    int getScreenHeight(void){return m_screenHeight;}

    void setIpAddress(QString addr){m_autoscopeIp = QHostAddress(addr);}
    void setPort(int port){m_autoscopePort = port;}

    void connectToAutoscope(void);
    void deconnectFromAutoscope(void);

private:
	// Font used for displaying our text
    QSettings* conf;
    StelGui* gui;
    AutoscopeWindowForm* m_autoscopeWindow;
    AutoscopePictureWindowForm* m_autoscopePictureWindow;

    StelCore* m_core;
    Vec3f markColor;
    LinearFader markFader;
    bool displayedAtStartup;
    bool guiIsVisible = false;

    StelButton* menuButton;
    StelButton* trackButton;
    StelButton* unTrackButton;
    StelButton* EnablePictureDisplay;
    StelButton* takePicture;

	QFont font;

    StelObjectP Sun;
    StelObjectP trackObject;
    Vec3d objectPosition;
    QList<StelObjectP> newSelected;
    StelObjectP selectedObject;

    StelObjectP searchedObject;
    bool searchObjectFound = false;

    int m_screenWidth;
    int m_screenHeight;

    TcpClient* m_client;

    QHostAddress m_autoscopeIp;

    int m_autoscopePort = 4444;

public slots:
    void showGui(void);
    void slotTrackObject(void);
    void slotUnTrackOject(void);
    void slotEnablePictureDispaly(void);
    void slotTakePicture(void);
    void slotConnected(void);
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
