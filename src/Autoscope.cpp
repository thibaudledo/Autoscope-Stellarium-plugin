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
    info.contact = "thibauledo@gmail.com";
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
}

/*************************************************************************
 Destructor
*************************************************************************/
Autoscope::~Autoscope()
{
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

        StelGui* gui = dynamic_cast<StelGui*>(StelApp::getInstance().getGui());
        if (gui != Q_NULLPTR)
        {

            toolBarButton = new StelButton(Q_NULLPTR,
                                           QPixmap(":/Autoscope/telescope_on.png"),
                                           QPixmap(":/Autoscope/telescope_off.png"),
                                           QPixmap(":/graphicGui/glow32x32.png"),
                                           "actionTracking");
            gui->getButtonBar()->addButton(toolBarButton, "065-pluginsGroup");
        }
        connect(toolBarButton, SIGNAL(triggered()), this, SLOT(trackObjectChanged()));
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

void Autoscope::trackObjectChanged()
{
    qDebug() << "clicked!!";

    newSelected = objectMgr->getSelectedObject();

    if(!newSelected.isEmpty())
    {
        if(newSelected[0]->getEnglishName()!=StelApp::getInstance().getCore()->getCurrentLocation().planetName)
        {
            qDebug() << "is tracking";
            trackObject = newSelected[0];
        }
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

    qDebug() << newSelected[0]->getEnglishName() << " Az./Alt. : " << cxt << "  " << cyt;
}

void Autoscope::update(double t)
{
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
