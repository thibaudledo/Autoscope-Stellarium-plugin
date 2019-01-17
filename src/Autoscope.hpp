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

#ifndef HELLOSTELMODULE_HPP
#define HELLOSTELMODULE_HPP

#include "StelModule.hpp"
#include "VecMath.hpp"
#include "StelFader.hpp"
#include <QFont>

#include "StelMovementMgr.hpp"
#include "StelObjectMgr.hpp"
#include "StelObjectType.hpp"

class StelButton;
class QPixmap;

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

    void loadConfiguration();
    void restoreDefaultConfiguration();

    void getAltAzi(Vec3d Position);

    QString oldSelected = "";

    StelMovementMgr* mvMgr;
    StelObjectMgr* objectMgr;
    StelObjectP Sun;
    StelObjectP trackObject;
    Vec3d objectPosition;
    QList<StelObjectP> newSelected;
private:
	// Font used for displaying our text

    StelCore* m_core;
    QSettings* conf;
    Vec3f markColor;
    LinearFader markFader;
    bool displayedAtStartup;

    StelButton* toolBarButton;
	QFont font;

public slots:
    void trackObjectChanged(void);
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