TEMPLATE = subdirs

SUBDIRS = core

# build must be last
CONFIG += ordered

SUBDIRS += application
SUBDIRS += logbook
SUBDIRS += digital

# necessary?
application.depends = core
logbook.depends = core
digital.depends = core
