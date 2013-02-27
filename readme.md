# Introduction

# Components
LISA will provide the following components

- **Core** Provides the core framework on which the application is based upon. It serves as a main hub to host all used modules and manages the dependencies and inter-module communication.
- **Logging** This module manages a logbook and will provide functionality like distributed logbook-hosting, syncronization with web-services (dropbox, Google Drive, ...) and callsign lookup with various online/offline ressources.
- **Digital** Provides all features to be used during digital operation such as encoding/decoding digital protocols like PSK31, RTTY,  etc. 
- **Network** Enables LISA to communicate over networks. Required by module **Logging**. This module is supposed to be used by **Core** only which will act as a proxy object and redirects all network requests.

# Build LISA

## WIN32:

- You probably need to open QtCreator with administrator priviliges.
- When using VS2012, you probably need to change the platform toolset from v110 to v100.

## Linux (Ubuntu)

First install the Qt SDK 
`sudo apt-get install qt-sdk`
