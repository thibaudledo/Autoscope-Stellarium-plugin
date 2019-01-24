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

#include "StelProjector.hpp"
#include "StelPainter.hpp"
#include "StelApp.hpp"
#include "StelCore.hpp"
#include "StelLocaleMgr.hpp"
#include "StelModuleMgr.hpp"
#include "Autoscope.hpp"

#include "StelUtils.hpp"
#include "StelObjectType.hpp"
#include "StelMovementMgr.hpp"
#include "StelObjectMgr.hpp"

#include "StelGui.hpp"
#include "StelGuiItems.hpp"
#include "StelFileMgr.hpp"
#include <QPixmap>
#include <QSettings>

#include "AutoscopeWindowForm.hpp"

#include <QDebug>

/*************************************************************************
 This method is the one called automatically by the StelModuleMgr just
 after loading the dynamic library
*************************************************************************/
StelModule* AutoscopeStelPluginInterface::getStelModule() const
{
    return new Autoscope();
}

StelPluginInfo AutoscopeStelPluginInterface::getPluginInfo() const
{
    Q_INIT_RESOURCE(Autoscope);

    StelPluginInfo info;
    info.id = "Autoscope";
    info.displayedName = "Autoscope plugin";
    info.authors = "Thibaud Le Doledec";
    info.contact = "thibaudledo@gmail.com";
    info.description = "A plugin for the control of our version of open source telescope";
    return info;
}

/*************************************************************************
 Constructor
*************************************************************************/
Autoscope::Autoscope()
{
    qDebug() << "Autoscope constructor";
    setObjectName("Autoscope");
    font.setPixelSize(25);
    conf = StelApp::getInstance().getSettings();
    gui = dynamic_cast<StelGui*>(StelApp::getInstance().getGui());
    m_autoscopeWindow = new AutoscopeWindowForm();
}

/*************************************************************************
 Destructor
*************************************************************************/
Autoscope::~Autoscope()
{
    delete m_autoscopeWindow;
}

/*************************************************************************
 Reimplementation of the getCallOrder method
*************************************************************************/
double Autoscope::getCallOrder(StelModuleActionName actionName) const
{
    if (actionName==StelModule::ActionDraw)
        return StelApp::getInstance().getModuleMgr().getModule("NebulaMgr")->getCallOrder(actionName)+10.;
    return 0;
}

bool Autoscope::configureGui(bool show)
{
    if(show)
    {
        m_autoscopeWindow->setVisible(true);
    }
    return true;
}

/*************************************************************************
 Init our module
*************************************************************************/
void Autoscope::init()
{
    qDebug() << "init called for Autoscope";

    /**********************************
 init of all manager
***********************************/
    mvMgr = GETSTELMODULE(StelMovementMgr);
    objectMgr = GETSTELMODULE(StelObjectMgr);
    m_core = GETSTELMODULE(StelCore);

    Q_ASSERT(conf);

    if (!conf->childGroups().contains("Autoscope"))
        restoreDefaultConfiguration();

    loadConfiguration();

    try
    {
        if (gui != Q_NULLPTR)
        {

            toolBarButton = new StelButton(Q_NULLPTR,
                                           QPixmap(":/Autoscope/telescope_on.png"),
                                           QPixmap(":/Autoscope/telescope_off.png"),
                                           QPixmap(":/graphicGui/glow32x32.png"),
                                           "actionTracking");
            gui->getButtonBar()->addButton(toolBarButton, "065-pluginsGroup");
        }
        connect(toolBarButton, SIGNAL(triggered()), this, SLOT(showGui()));
    }
    catch (std::runtime_error& e)
    {
        qWarning() << "WARNING: unable create toolbar button for CompassMarks plugin: " << e.what();
    }
}

void Autoscope::loadConfiguration()
{
    Q_ASSERT(conf);
    conf->beginGroup("Autoscope");
    markColor = StelUtils::strToVec3f(conf->value("mark_color", "1,0,0").toString());
    font.setPixelSize(conf->value("font_size", 10).toInt());
    displayedAtStartup = conf->value("enable_at_startup", false).toBool();
    conf->endGroup();
}

void Autoscope::restoreDefaultConfiguration()
{
    Q_ASSERT(conf);
    // Remove the whole section from the configuration file
    conf->remove("Autoscope");
    // Load the default values...
    loadConfiguration();
    // But this doesn't save the color, so...
    conf->beginGroup("Autoscope");
    conf->setValue("mark_color", "1,0,0");
    conf->endGroup();
}

void Autoscope::showGui()
{
    qDebug() << "clicked!!";

    if(guiIsVisible)
    {
        m_autoscopeWindow->setVisible(false);
        guiIsVisible = false;
    }else{
        m_autoscopeWindow->setVisible(true);
        guiIsVisible = true;
    }
}

void Autoscope::getAltAzi(Vec3d Position)
{
    QString cxt,cyt;
    double cx, cy;

    StelUtils::rectToSphe(&cy,&cx,m_core->j2000ToAltAz(Position, StelCore::RefractionAuto));

    float direction = 3.;
    cy = direction*M_PI - cy;
    if(cy > M_PI*2)
        cy -= M_PI*2;

    cxt = StelUtils::radToDecDegStr(cy);
    cyt = StelUtils::radToDecDegStr(cx);

    qDebug() << trackObject->getEnglishName() << " Az./Alt. : " << cxt << "  " << cyt;
}

// ne fonctionne pas encore
QString Autoscope::searchAnObject(QString objectName)
{
    searchedObject = objectMgr->searchByName(objectName);

    if(searchedObject.isNull())
    {
        searchObjectFound = false;
        return QString("Unable to find it!");
    }else {
        searchObjectFound = true;
        return QString("Found it!");
    }
}

void Autoscope::setTrackObject(StelObjectP object)
{
    if(!object.isNull())
    {
        if(object->getEnglishName()!=StelApp::getInstance().getCore()->getCurrentLocation().planetName)
        {
            qDebug() << "Autoscope is tracking " << object->getEnglishName();
            trackObject = object;
        }
    }
}

void Autoscope::trackSelectedObject()
{
    newSelected = objectMgr->getSelectedObject();

    if(!newSelected.isEmpty())
    {
        selectedObject = newSelected[0];
        setTrackObject(selectedObject);
    }
}

QString Autoscope::trackSearchedObject(void)
{
    if(searchObjectFound)
    {
        setTrackObject(searchedObject);
        moveObserverToObject(searchedObject);
        return "Searching";
    }else{
        return "This object doesn't exist";
    }
}

void Autoscope::clearTrackedObject()
{
    trackObject = nullptr;
}

void Autoscope::moveObserverToObject(StelObjectP object)
{
    objectMgr->setSelectedObject(object);
    mvMgr->moveToObject(object, mvMgr->getAutoMoveDuration());
    mvMgr->setFlagTracking(true);
}

void Autoscope::update(double t)
{
    m_autoscopeWindow->update();
    m_autoscopeWindow->getAutoscopePictureWindowForm()->update();

    if(guiIsVisible)
    {
        m_autoscopeWindow->updateGuiSize();
        m_autoscopeWindow->updateGuiPosition();
    }

    if(!trackObject.isNull())
    {
        getAltAzi(trackObject->getJ2000EquatorialPos(m_core));
    }
}

/*************************************************************************
 Draw our module. This should print "Hello world!" in the main window
*************************************************************************/
void Autoscope::draw(StelCore* core)
{
    if(m_core==Q_NULLPTR)
    {
        m_core = core;
    }
}

