# Autoscope plugin for Stellarium

This plugin is used by Stellarium to controlling our automated telescope called Autoscope

More informations about this project on the main repository :

- https://github.com/thibaudledo/Autoscope

<br>

## Usage

[//]: # (### Installation from binary package)
[//]: # (Dowload package :)

[//]: # (```)
[//]: # (/opt/ #)
[//]: # (	wget https://raw.githubusercontent.com/thibaudledo/Autoscope/master/Stellarium-0.19.0-Linux.tar.gz)
[//]: # (	tar -xzf Stellarium-0.19.0-Linux.tar.gz)
[//]: # (```)
  
[//]: # (### Run Stellarium)

[//]: # (```)
[//]: # (~ $)
[//]: # (	/opt/Stellarium-0.19.0-Linux/bin/stellarium)
[//]: # (```)

### Installation from sources

Install dependancies (Debian/Ubuntu) :

```
~ $
	sudo apt-get install build-essential cmake zlib1g-dev libgl1-mesa-dev gcc g++
	sudo apt-get install graphviz doxygen gettext git
```

Build Qt dependancies :

```
~ $
	mkdir DEV/
	cd DEV/
	wget http://download.qt.io/archive/qt/5.5/5.5.0/qt-opensource-linux-x64-5.5.0-2.run
	chmod +x qt-opensource-linux-x64-5.5.0-2.run
	./qt-opensource-linux-x64-5.5.0-2.run
	#enter a shitty email address (e.g. qt.qt@yopmail.com)
	#install in /opt/Qt5.5.0/

	git clone https://github.com/qt/qtftp
	cd qtftp/
	/opt/Qt5.5.0/5.5/gcc_64/bin/syncqt.pl -version 5.5.0
	/opt/Qt5.5.0/5.5/gcc_64/bin/qmake
	make
	sudo make install
```

Download Stellarium & Autoscope plugin sources :

```
~/DEV/ $
	wget https://github.com/Stellarium/stellarium/releases/download/v0.19.0/stellarium-0.19.0.tar.gz
	tar -xzf stellarium-0.19.0.tar.gz
	cd stellarium-0.19.0/plugins/
	git clone https://github.com/thibaudledo/Autoscope-Stellarium-plugin.git plugins/Autoscope
```

Enable Autoscope plugin :

```
~/DEV/Stellarium-0.19.0/ $
	git init
	git add CMakeLists.txt src/core/StelApp.cpp
	git apply plugins/Autoscope/0001-enable-autoscope-plugin.patch

	### OR APPEND MANUALLY ###
	line 369 : CMakeLists.txt
		ADD_PLUGIN(Autoscope 1)
	line 94 : src/core/StelApp.cpp
		#ifdef USE_STATIC_PLUGIN_AUTOSCOPE
		Q_IMPORT_PLUGIN(AutoscopeStelPluginInterface)
		#endif
```

Export variables :

```
	export QTDIR=/opt/Qt5.5.0/5.5/gcc_64
	export PATH=/opt/Qt5.5.0/5.5/gcc_64/bin:${PATH}
	export LD_LIBRARY_PATH=${QTPATH}/lib:${LD_LIBRARY_PATH}
```

Build Stellarium :

```
~/DEV/Stellarium-0.19.0/ $
	mkdir -p builds/unix/
	cd builds/unix/
	cmake -DCMAKE_BUILD_MODE=Release -DCMAKE_INSTALL_PREFIX=/opt/stellarium ../../
	make -j4
```

Install Stellarium :

```
~/DEV/Stellarium-0.19.0/builds/unix $
	sudo make install
```

### Build binary distribution packages

```
~/DEV/Stellarium-0.19.0/builds/unix $
	make package_source
	make package
	cpack -G DEB
	cpack -G RPM
```

<br>

## Dependencies

This plugin depends on:

* URI: https://github.com/Stellarium/stellarium
  * branch: master

