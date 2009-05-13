/***************************************************************************
  Copyright: (C) 2002 by Kyle VanderBeek <kylev@kylev.com>
  $Id: ipwidget.h,v 1.11 2002/05/01 01:41:39 kylev Exp $
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef IPWIDGET_H
#define IPWIDGET_H

#include "simplenet.h"

#include <krestrictedline.h>

#include <qwidget.h>
#include <qspinbox.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qstring.h>

class IPWidget : public QWidget
{
  Q_OBJECT
public:
  IPWidget(QWidget *parent);
private:
  KRestrictedLine *ipField, *netmaskField;
  QLabel *ipHexField, *ipBinField, *minHostField, *maxHostField, *networkDottedField, *networkBinaryField,
      *broadcastDottedField, *netmaskDottedField, *netmaskBinField, *netmaskReverseField;
  QSpinBox *netmaskCIDRField;
  SimpleNet sn;
  QVBoxLayout *vbox;
  void updateReadFields();
private slots:
  void slotIPUpdated();
  void slotIPEdited(const QString&);
  void slotNetmaskUpdated();
  void slotNetmaskEdited(const QString&);
  void slotCIDRUpdated(int);
};

#endif
