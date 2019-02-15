#ifndef COMMANDPARSER_HPP
#define COMMANDPARSER_HPP

#include <QString>
#include <QDebug>

class CommandParser
{
public:
    CommandParser();

    QString trackCommand(QString objectName, QString azimuth, QString altitude);

    QString moveToCommand(double azimuth, double altitude);

    QString zoomCommand(int zoomValue);

    QString initCommand(void);

    QString takePictureCommand(void);

    QString exposureTimeCommand(double time);

    QString numberOfPictureCommand(int value);
private:
    QString str_trackCommand;

    QString str_moveToCommand;

    QString str_zoomCommand;

    QString str_initCommand;

    QString str_takePictureCommand;

    QString str_exposureTimeCommand;

    QString str_numberOfPictureCommand;

};

#endif // COMMANDPARSER_HPP
