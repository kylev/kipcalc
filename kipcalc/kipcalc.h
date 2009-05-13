/***************************************************************************
                          kipcalc.h  -  description
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

#ifndef KIPCALC_H
#define KIPCALC_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <kapp.h>
#include <kmainwindow.h>

/** Kipcalc is the base class of the project */
class Kipcalc : public KMainWindow
{
  Q_OBJECT 
  public:
    /** construtor */
    Kipcalc(QWidget* parent=0, const char *name=0);
    /** destructor */
    ~Kipcalc();
  private slots:
    void slotExit();
};

#endif
