######################################################################
# Automatically generated by qmake (2.01a) dim. 12. fvr. 12:31:29 2012
######################################################################

CONFIG += debug_and_release
TEMPLATE = app
QT += sql
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
# Input

CONFIG(debug, debug|release) {
	DESTDIR =debug
} else {
	DESTDIR = release
}

HEADERS += FenIntroClient.h \
           FenIntrodate.h \
           FenJournalVente.h \
           FenPayement.h \
           FenPrincipale.h \
           FenVente.h \
           FenCaisse.h \
                   FenACaisse.h \
                   FenClient.h \
		   FenIntroFacture.h \
    FenImpression.h
FORMS += ImpJournalVente.ui \
         IntroClientWindow.ui \
                 IntroFactureWindow.ui \
         JournalVente.ui \
         MainWindow.ui \
         PayementWindow.ui \
         VenteWindow.ui \
                 CaisseWindow.ui \
                 ACaisseWindow.ui \
		 ClientWindow.ui \
    Dialogimpression.ui
SOURCES += FenIntroClient.cpp \
           FenIntrodate.cpp \
           FenJournalVente.cpp \
           FenPayement.cpp \
           FenPrincipale.cpp \
           FenVente.cpp \
           main.cpp \
                   FenCaisse.cpp \
                   FenACaisse.cpp \
                   FenClient.cpp \
		   FenIntroFacture.cpp \
    FenImpression.cpp
