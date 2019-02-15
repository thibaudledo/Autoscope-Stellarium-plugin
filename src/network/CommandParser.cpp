#include "CommandParser.hpp"

CommandParser::CommandParser()
{

}

QString CommandParser::trackCommand(QString objectName, QString azimuth, QString altitude)
{
    str_trackCommand = QString("Az./Alt.: "+objectName+" "+azimuth+" "+altitude);
    qDebug() << str_trackCommand;
    return str_trackCommand;
}

QString CommandParser::moveToCommand(double azimuth, double altitude)
{
    str_moveToCommand = QString("Az./Alt.: "+QString::number(azimuth)+"° "+QString::number(altitude)+"°");
    qDebug() << str_moveToCommand;
    return str_moveToCommand;
}

QString CommandParser::zoomCommand(int zoomValue)
{
    str_zoomCommand = QString("Zoom: "+QString::number(zoomValue));
    qDebug() << str_zoomCommand;
    return str_zoomCommand;
}

QString CommandParser::initCommand()
{
    str_initCommand = QString("Init");
    qDebug() << str_initCommand;
    return str_initCommand;
}

QString CommandParser::takePictureCommand()
{
    str_takePictureCommand = QString("TakePicture");
    qDebug() << str_takePictureCommand;
    return str_takePictureCommand;
}

QString CommandParser::exposureTimeCommand(double time)
{
    str_exposureTimeCommand = QString("ExposureTime: "+QString::number(time));
    qDebug() << str_exposureTimeCommand;
    return str_exposureTimeCommand;
}

QString CommandParser::numberOfPictureCommand(int value)
{
    str_numberOfPictureCommand = QString("NumberOfPicture: "+QString::number(value));
    qDebug() << str_numberOfPictureCommand;
    return str_numberOfPictureCommand;
}
