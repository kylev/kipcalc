#!/usr/bin/python

import sys

from PyKDE4 import kdecore # import ki18n, KAboutData, KCmdLineArgs
from PyKDE4 import kdeui # import KApplication

from PyQt4.QtGui import QLabel


class MainWindow(kdeui.KMainWindow):
    def __init__ (self):
        super(MainWindow, self).__init__()

        self.resize(640, 480)
        label = QLabel("This is a simple PyKDE4 program", self)
        label.setGeometry (10, 10, 200, 20)


if '__main__' == __name__:
    appName = "kipcalc"
    catalog = ""
    programName = kdecore.ki18n("kipcalc")
    version = "0.7"
    description = kdecore.ki18n("IP Subnet Calculator")
    license = kdecore.KAboutData.License_GPL
    copyright = kdecore.ki18n("(c) 2009 Kyle VanderBeek")
    text = kdecore.ki18n("none")
    homePage = "www.kylev.com"
    bugEmail = "kylev@kylev..com"

    aboutData   = kdecore.KAboutData(appName, catalog, programName, version,
                                     description, license, copyright, text,
                                     homePage, bugEmail)
    kdecore.KCmdLineArgs.init(sys.argv, aboutData)
    app = kdeui.KApplication()

    mainWindow = MainWindow()
    mainWindow.show()
    app.exec_()
