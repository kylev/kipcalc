/***************************************************************************
  Copyright: (C) 2002 by Kyle VanderBeek <kylev@kylev.com>
  $Id: ipwidget.cpp,v 1.23 2002/05/01 01:41:33 kylev Exp $
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "ipwidget.h"

#ifdef NDEBUG
#undef NDEBUG
#endif
#include <kdebug.h>

#include <qlabel.h>
#include <qtabwidget.h>
#include <qvbox.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qstring.h>

IPWidget::IPWidget(QWidget *parent) : QWidget(parent)
{
  // Main layout with a little spacing
  vbox = new QVBoxLayout(this, 3);

  //-- IP box --
  QGroupBox *hostBox = new QGroupBox(2, Horizontal, "Host", this, "hostBox");
  vbox->addWidget(hostBox);

  QLabel *ipFieldLabel = new QLabel(hostBox);
  ipFieldLabel->setText("Dot");

  ipField = new KRestrictedLine(hostBox, "IP Address", "1234567890.");
  ipField->setContextMenuEnabled(false);
  ipField->setTrapReturnKey(true);
  ipField->setMaxLength(15);
  connect(ipField, SIGNAL(returnPressed()), this, SLOT(slotIPUpdated()));
  connect(ipField, SIGNAL(textChanged(const QString&)), this, SLOT(slotIPEdited(const QString&)));

  QLabel *ipHexFieldLabel = new QLabel("Hex", hostBox);
  ipHexField = new QLabel(hostBox, "ipHex");
  ipHexField->setMinimumWidth(ipHexField->fontMetrics().width("0") * 11);

  QLabel *ipBinFieldLabel = new QLabel("Bin", hostBox);
  ipBinField = new QLabel(hostBox, "ipBin");
  ipBinField->setMinimumWidth(ipBinField->fontMetrics().width("0") * 15);

  //-- NETMASK box --
  QGroupBox *nmBox = new QGroupBox(2, Horizontal, "Netmask", this, "nmBox");
  vbox->addWidget(nmBox);

  QLabel *netmaskFieldLabel = new QLabel("Dot", nmBox);
  netmaskField = new KRestrictedLine(nmBox, "Netmask", "1234567890.");
  netmaskField->setTrapReturnKey(true);
  netmaskField->setMaxLength(15);
  connect(netmaskField, SIGNAL(returnPressed()), this, SLOT(slotNetmaskUpdated()));
  connect(netmaskField, SIGNAL(textChanged(const QString&)), this, SLOT(slotNetmaskEdited(const QString&)));

  QLabel *netmaskBinFieldLabel = new QLabel("Bin", nmBox);
  netmaskBinField = new QLabel(nmBox, "NetmaskBin");
  netmaskBinField->setMinimumWidth(netmaskBinField->fontMetrics().width("0") * 35);

  QLabel *netmaskCIDRFieldLabel = new QLabel("CIDR", nmBox);
  netmaskCIDRField = new QSpinBox(1, 31, 1, nmBox, "netmaskCIDRField");
  connect(netmaskCIDRField, SIGNAL(valueChanged(int)),
          this, SLOT(slotCIDRUpdated(int)));

  QLabel *netmaskReverseFieldLabel = new QLabel("Rev", nmBox);
  netmaskReverseField = new QLabel(nmBox, "netmaskReverseField");
  netmaskReverseField->setMinimumWidth(netmaskReverseField->fontMetrics().width("0") * 15);

  //-- NETWORK box --
  QGroupBox *netBox = new QGroupBox(2, Horizontal, "Network", this, "netBox");
  vbox->addWidget(netBox);

  QLabel *minHostFieldLabel = new QLabel("First", netBox);
  minHostField = new QLabel(netBox, "minHostField");
  minHostField->setMinimumWidth(minHostField->fontMetrics().width("0") * 15);

  QLabel *maxHostFieldLabel = new QLabel("Last", netBox);
  maxHostField = new QLabel(netBox, "maxHostField");
  maxHostField->setMinimumWidth(maxHostField->fontMetrics().width("0") * 15);

  QLabel *networkDottedFieldLabel = new QLabel("Dot", netBox);
  networkDottedField = new QLabel(netBox, "networkDottedField");
  networkDottedField->setMinimumWidth(networkDottedField->fontMetrics().width("0") * 15);

  QLabel *networkBinaryFieldLabel = new QLabel("Bin", netBox);
  networkBinaryField = new QLabel(netBox, "networkBinaryField");
  networkBinaryField->setMinimumWidth(networkBinaryField->fontMetrics().width("0") * 35);

  QLabel *broadcastDottedFieldLabel = new QLabel("Bcast", netBox);
  broadcastDottedField = new QLabel(netBox, "broadcastDottedField");
  broadcastDottedField->setMinimumWidth(broadcastDottedField->fontMetrics().width("0") * 15);

  // Trigger defaults
  sn.setIP("192.168.1.1");
  sn.setNetmask(24);
  ipField->setText("192.168.1.1");
  netmaskField->setText(sn.getNetmaskDotted().c_str());
  netmaskCIDRField->setValue(sn.getNetmaskCIDRInt());
  updateReadFields();
}


void IPWidget::slotIPUpdated()
{
  // FIXME these return bool's, check and do dialogs
  if (! sn.setIP(ipField->text().latin1()) ) {
    kdDebug(4) << "SHitty" << endl;
  }
  updateReadFields();
}

void IPWidget::slotIPEdited(const QString &s)
{
  if (! sn.setIP(ipField->text().latin1()) )
    return;
  updateReadFields();
}

void IPWidget::slotNetmaskUpdated()
{
  // FIXME these return bool's, check and do dialogs
  sn.setNetmask(netmaskField->text().latin1());
  netmaskCIDRField->setValue(sn.getNetmaskCIDRInt());
  updateReadFields();
}

void IPWidget::slotNetmaskEdited(const QString &s)
{
  kdDebug(5) << "NM edit" << s << endl;
  if (! sn.setNetmask(netmaskField->text().latin1()))
    return;
  netmaskCIDRField->setValue(sn.getNetmaskCIDRInt());
  updateReadFields();
}

void IPWidget::slotCIDRUpdated(int i)
{
  sn.setNetmask(i);
  netmaskField->setText(sn.getNetmaskDotted().c_str());
  updateReadFields();
}

void IPWidget::updateReadFields()
{
  // set all fields, using implicit QString creation from const char *'s
  ipHexField->setText(sn.getIPHex().c_str());
  ipBinField->setText(sn.getIPBinary().c_str());

  netmaskBinField->setText(sn.getNetmaskBinary().c_str());
  netmaskReverseField->setText(sn.getRevMaskDotted().c_str());

  minHostField->setText(sn.getMinHostDotted().c_str());
  maxHostField->setText(sn.getMaxHostDotted().c_str());
  networkDottedField->setText(sn.getNetworkDotted().c_str());
  networkBinaryField->setText(sn.getNetworkBinary().c_str());
  broadcastDottedField->setText(sn.getBroadcastDotted().c_str());
}
