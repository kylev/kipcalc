/***************************************************************************
  Copyright: (C) 2002 by Kyle VanderBeek <kylev@kylev.com>
  $Id: main.cpp,v 1.3 2002/04/22 19:43:49 kylev Exp $
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <kcmdlineargs.h>
#include <kaboutdata.h>
#include <klocale.h>

#include "kipcalc.h"

static const char *description =
	I18N_NOOP("Kipcalc");
// INSERT A DESCRIPTION FOR YOUR APPLICATION HERE
	
	
static KCmdLineOptions options[] =
{
  { 0, 0, 0 }
  // INSERT YOUR COMMANDLINE OPTIONS HERE
};

int main(int argc, char *argv[])
{

  KAboutData aboutData( "kipcalc", I18N_NOOP("Kipcalc"),
    VERSION, description, KAboutData::License_GPL,
    "(c) 2002, Kyle VanderBeek", 0, 0, "kylev@kylev.com");
  aboutData.addAuthor("Kyle VanderBeek",0, "kylev@kylev.com");
  KCmdLineArgs::init( argc, argv, &aboutData );
  KCmdLineArgs::addCmdLineOptions( options ); // Add our own options.

  KApplication a;
  Kipcalc *kipcalc = new Kipcalc();
  a.setMainWidget(kipcalc);
  kipcalc->show();  

  return a.exec();
}
