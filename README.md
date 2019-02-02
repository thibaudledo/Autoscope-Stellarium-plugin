# Autoscope plugin for Stellarium

This plugin is use by Stellarium for controlling or telescope called Autoscope.

<br>

## Description

This plugin allow the user to control the Autoscope through Stellarium. It's use for positionning the Autoscope, take picture, and retreive them.

<br>

## Dependencies

This plugin depends on:

* URI: https://github.com/Stellarium/stellarium
  * branch: master
  
  <br>
  
## Usage
  
### Download Stellarium sources:
```
~ $
    mkdir DEV
    cd DEV
    git clone https://github.com/Stellarium/stellarium.git
    cd stellarium
```
  
### Download Autoscope plugin sources:
  
```
~/DEV/stellarium/ $
    cd plugins
    git clone https://github.com/thibaudledo/Autoscope-Stellarium-plugin.git
```
  
<br>
  
### Openning Stellarium
  
To open Stellarium, I recommand to use QtCreator with CMake. After the installation, you can open Stellarium in QtCreator with the following file: ~/DEV/stellarium/CMakeLists.txt
  
  
### Adding Autoscope plugin to Stellarium
  
* In the file CMakeLists.txt, append ```ADD_PLUGIN(Autoscope 1)``` at the line 323
* In the file StelApp.cpp, append the following lines at the line 96:
```
    #ifdef USE_STATIC_PLUGIN_AUTOSCOPE
    Q_IMPORT_PLUGIN(AutoscopeStelPluginInterface)
    #endif
```
  
### Build Stellarium
  
After all these steps, you can use QtCreator to build and run Stellarium with the Autoscope plugin in it!
  
  
  
  
