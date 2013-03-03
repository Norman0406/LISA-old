# Introduction

LISA is an acronym for "Lightweight Integrated System for Amateur Radio". It may also refer to the intelligent little girl from the Simpsons TV show - it's up to you. LISA provides a GUI framework for different modules related to amateur radio and linking them together in one integrated application environment.

All of this is based on the famous Qt libraries which ensure that LISA can be run on Windows, OSX and of course Linux.

# Components
LISA will provide the following components

- **Core** Provides the core framework on which the application is based upon. It serves as a main hub to host all used modules and manages the dependencies and inter-module communication.
- **Application** Provides the main application window and is itself a module. All the other modules add gui components to the main application to provide a seamless gui integration.
- **Logging** This module manages a logbook and provides functionality like distributed logbook-hosting, syncronization with web-services (dropbox, Google Drive, ...) and callsign lookup with various online/offline ressources.
- **Digital** Provides all features to be used during digital operation such as encoding/decoding digital protocols like PSK31, RTTY, etc. 
- **Control** Provides the functionality to control various kinds of transceivers.

# Build LISA

## Windows:

- You probably need to open QtCreator with administrator priviliges.
- When using VS2012, you might need to change the platform toolset from v110 to v100.

## Linux (Ubuntu)

First install the Qt SDK and libfftw 
`sudo apt-get install qt-sdk libfftw3-3`

**Notice** Currently the ubuntu package maintainer did not update the `qt-sdk` package. Please consider downloading the follwing [bash scripts](http://qt-project.org/downloads).

# Contributing
LISA is currently in the pre-alpha state which means that concepts and APIs may change frequently. But if you want to contribute feel free to contact us. We are looking for OSX developers which will test the code on their machines and help us hunting (plattform-specific) bugs.

#Licensing
LISA is licensed under the [GNU General Public License](http://www.gnu.org/licenses/gpl-3.0.en.html, "GPLv3") originated by the [Free Software Foundation](http://www.fsf.org).

##Motivation
During a spontaneous discussion about software for radio amateurs, Norman DM6LN and Patrik DO9PSE complained about the current situation. Of course, there are a lot of software packages available but they all suffer from at least one of the following issues:

- not open source software
- too pricy
- hard to extend or modify
- not plattform independent
- inconsistent gui interaction
- hard to learn for beginners
- based on pretty old binaries which may (often) require ancient operating systems (XP is dead, deal with it...)

At the end of this discussion we both decided to create something new. Free of charge, open source, easy to extend and maintain and last but not least cross-plattform compatible because we rely on the Qt framework.
