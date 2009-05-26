#!/usr/bin/python

from PyKDE4 import kdecore
from PyKDE4 import kdeui

from PyQt4.QtCore import SIGNAL, Qt
from PyQt4.QtGui import QAction, QLabel, QGroupBox


class IPWidget(kdeui.KVBox):
    def __init__(self, parent=None):
        super(IPWidget, self).__init__(parent)

        self.host_box = QGroupBox("Host", self)
        # TODO Lay all the stuff out.
        #QLabel('Dot', self.host_box)
        #dot_entry = kdeui.KRestrictedLine(host_box)
        #dot_entry.setValidChars('1234567890.')

        self.nm_box = QGroupBox("NetMask", self)


class Kipcalc(kdeui.KMainWindow):
    def __init__ (self):
        super(Kipcalc, self).__init__()
        self.resize(640, 480)

        self.create_actions()
        self.create_menus()
        self.setCentralWidget(IPWidget(self))

    def print_(self):
        pass

    def create_actions(self):
        self.action_quit = QAction('&Quit', self)
        self.action_quit.setIcon(kdeui.KIcon('exit'))
        self.action_quit.setShortcut(self.tr('Ctrl+Q'))
        self.connect(self.action_quit, SIGNAL('triggered()'), self.close)

        self.action_print = QAction('&Print', self)
        #self.action_print.setIcon(kdeui.KIcon('print'))
        self.connect(self.action_quit, SIGNAL('triggered()'), self.print_)

    def create_menus(self):
        self.file_menu = self.menuBar().addMenu("&File")
        self.file_menu.addAction(self.action_quit)
        self.file_menu.addAction(self.action_print)


if '__main__' == __name__:
    import sys

    appName = "kipcalc"
    catalog = ""
    programName = kdecore.ki18n("kipcalc")
    version = "0.7"
    description = kdecore.ki18n("IP Subnet Calculator")
    license = kdecore.KAboutData.License_GPL
    copyright = kdecore.ki18n("(c) 2009 Kyle VanderBeek")
    text = kdecore.ki18n("none")
    homePage = "www.kylev.com"
    bugEmail = "kylev@kylev.com"

    aboutData   = kdecore.KAboutData(appName, catalog, programName, version,
                                     description, license, copyright, text,
                                     homePage, bugEmail)
    kdecore.KCmdLineArgs.init(sys.argv, aboutData)

    app = kdeui.KApplication()
    mainWindow = Kipcalc()
    mainWindow.show()
    app.connect(app, SIGNAL("lastWindowClosed()"), app.quit)
    sys.exit(app.exec_())
