#!/usr/bin/python

import sys

from PyKDE4 import kdecore
from PyKDE4 import kdeui

from PyQt4.QtGui import QLabel, QGroupBox


class IPWidget(kdeui.KVBox):
    def __init__(self, parent=None):
        super(IPWidget, self).__init__(parent)

        host_box = QGroupBox("Host", self)
        QLabel('Dot', host_box)
        dot_entry = kdeui.KRestrictedLine(host_box)
        dot_entry.setValidChars('1234567890.')

        nm_box = QGroupBox("NetMask", self)


class Kipcalc(kdeui.KMainWindow):
    def __init__ (self):
        super(Kipcalc, self).__init__()
        #kdeui.KMainWindow.__init__(self)
        self.help = QLabel(kdecore.i18n("Some Help"), self)

        menu = self.menuBar()

        f_menu = kdeui.KMenu("File", menu)
        f_menu.addAction("Quit")

        self.setCentralWidget(IPWidget(self))

    def blah(self):
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

    mainWindow = Kipcalc()
    mainWindow.show()
    app.exec_()
