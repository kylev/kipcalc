/***************************************************************************
  Copyright: (C) 2002 by Kyle VanderBeek <kylev@kylev.com>
  $Id: kipcalc.cpp,v 1.15 2002/04/23 01:04:37 kylev Exp $
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "kipcalc.h"
#include "ipwidget.h"

#include <kmenubar.h>
#include <kpopupmenu.h>
#include <kiconloader.h>

Kipcalc::Kipcalc(QWidget *parent, const char *name) : KMainWindow(parent, name)
{
  // File menu, which is basically just "Quit"
  KPopupMenu *file = new KPopupMenu();
  file->insertItem(SmallIcon("exit"), "&Quit", this, SLOT(slotExit()), CTRL+Key_Q);
  menuBar()->insertItem("&File", file);

  // Simple Help menu
  KPopupMenu *help = helpMenu( PACKAGE " v" VERSION "\nby Kyle VanderBeek\nkylev@kylev.com", false );
  menuBar()->insertItem( "&Help", help );

  QWidget *main = new IPWidget(this);
  setCentralWidget(main);
}

Kipcalc::~Kipcalc()
{
}

void Kipcalc::slotExit()
{
  close();
}
