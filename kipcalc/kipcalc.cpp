/***************************************************************************
                          kipcalc.cpp  -  description
                             -------------------
    begin                : Thu Apr  4 01:23:07 PST 2002
    copyright            : (C) 2002 by Kyle VanderBeek
    email                : kylev@kylev.com
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
#include <kiconloader.h>

#include <iostream.h>

Kipcalc::Kipcalc(QWidget *parent, const char *name) : KMainWindow(parent, name)
{
  // File menu, which is basically just "Quit"
  KPopupMenu *file = new KPopupMenu();
  file->insertItem(SmallIcon("exit"), "&Quit", this, SLOT(slotExit()), CTRL+Key_Q);
  menuBar()->insertItem("&File", file);

  // Simple Help menu
  KPopupMenu *help = helpMenu( "Kipcalc\nby Kyle VanderBeek\nkylev@kylev.com", false );
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
