/***************************************************************************
  Copyright: (C) 2002 by Kyle VanderBeek <kylev@kylev.com>
  $Id: ipwidget.cpp,v 1.18 2002/04/20 20:55:58 kylev Exp $
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

#include <qlabel.h>
#include <qtabwidget.h>
#include <qvbox.h>
#include <qpushbutton.h>

#include <stdlib.h>
#include <iostream.h>

IPWidget::IPWidget(QWidget *parent) : QWidget(parent)
{
  vbox = new QVBoxLayout(this, 3);

  // IP label/field
  QLabel *ipFieldLabel = new QLabel(this);
  ipFieldLabel->setText("IP Address");
  vbox->addWidget(ipFieldLabel);
  ipField = new KRestrictedLine(this, "IP Address", "1234567890.");
  ipField->setContextMenuEnabled(false);
  ipField->setMaxLength(15);
  vbox->addWidget(ipField);

  // Netmask label/field 
  QLabel *netmaskFieldLabel = new QLabel(this);
  netmaskFieldLabel->setText("Netmask");
  vbox->addWidget(netmaskFieldLabel);
  netmaskField = new KRestrictedLine(this, "Netmask", "1234567890.");
  vbox->addWidget(netmaskField);

  // Go button
  QPushButton *goButton = new QPushButton("&Go!", this);
  connect(goButton, SIGNAL(clicked()),
          this, SLOT(slotUpdated()));
  vbox->addWidget(goButton);

  // Results are displayed in tabs
  QTabWidget *tabs = new QTabWidget(this, "Results Tabs");
  vbox->addWidget(tabs);
  
  // Host page
  QWidget *hostPage = new QWidget(tabs);
  QGridLayout *hostLayout = new QGridLayout(hostPage, 3, 3, 3);
  tabs->addTab(hostPage, "H&osts");

  QLabel *ipBinFieldLabel = new QLabel(hostPage);
  ipBinFieldLabel->setText("Binary:");
  hostLayout->addWidget(ipBinFieldLabel, 0, 0, AlignRight);

  ipBinField = new QLabel(hostPage, "ipbin");
  ipBinField->setMinimumWidth(ipBinField->fontMetrics().width("0") * 15);
  hostLayout->addWidget(ipBinField, 0, 1, AlignLeft);

  QLabel *minHostFieldLabel = new QLabel(hostPage);
  minHostFieldLabel->setText("First:");
  hostLayout->addWidget(minHostFieldLabel, 1, 0, AlignRight);

  minHostField = new QLabel(hostPage, "ipbin");
  minHostField->setMinimumWidth(minHostField->fontMetrics().width("0") * 15);
  hostLayout->addWidget(minHostField, 1, 1, AlignLeft);

  QLabel *maxHostFieldLabel = new QLabel(hostPage);
  maxHostFieldLabel->setText("Last:");
  hostLayout->addWidget(maxHostFieldLabel, 2, 0, AlignRight);

  maxHostField = new QLabel(hostPage, "ipbin");
  maxHostField->setMinimumWidth(maxHostField->fontMetrics().width("0") * 15);
  hostLayout->addWidget(maxHostField, 2, 1, AlignLeft);

  // Network Page
  QWidget *networkPage = new QWidget(tabs);
  QGridLayout *networkLayout = new QGridLayout(networkPage, 3, 3, 3);
  tabs->addTab(networkPage, "&Network");

  QLabel *networkDottedFieldLabel = new QLabel(networkPage);
  networkDottedFieldLabel->setText("Dotted:");
  networkLayout->addWidget(networkDottedFieldLabel, 0, 0, AlignRight);

  networkDottedField = new QLabel(networkPage);
  networkDottedField->setMinimumWidth(networkDottedField->fontMetrics().width("0") * 15);
  networkLayout->addWidget(networkDottedField, 0, 1, AlignLeft);

  QLabel *networkBinaryFieldLabel = new QLabel(networkPage);
  networkBinaryFieldLabel->setText("Binary:");
  networkLayout->addWidget(networkBinaryFieldLabel, 1, 0, AlignRight);

  networkBinaryField = new QLabel(networkPage);
  networkBinaryField->setMinimumWidth(networkBinaryField->fontMetrics().width("0") * 35);
  networkLayout->addWidget(networkBinaryField, 1, 1, AlignLeft);

  QLabel *broadcastDottedFieldLabel = new QLabel(networkPage);
  broadcastDottedFieldLabel->setText("Broadcast:");
  networkLayout->addWidget(broadcastDottedFieldLabel, 2, 0, AlignRight);

  broadcastDottedField = new QLabel(networkPage);
  broadcastDottedField->setMinimumWidth(broadcastDottedField->fontMetrics().width("0") * 15);
  networkLayout->addWidget(broadcastDottedField, 2, 1, AlignLeft);

  // Netmask Page
  QWidget *netmaskPage = new QWidget(tabs);
  QGridLayout *netmaskLayout = new QGridLayout(netmaskPage, 4, 4, 3);
  tabs->addTab(netmaskPage, "Netm&ask");
  
  QLabel *netmaskDottedFieldLabel = new QLabel(netmaskPage);
  netmaskDottedFieldLabel->setText("Dotted:");
  netmaskLayout->addWidget(netmaskDottedFieldLabel, 0, 0, AlignRight);

  netmaskDottedField = new QLabel(netmaskPage, "netmaskDottedField");
  netmaskDottedField->setMinimumWidth(netmaskDottedField->fontMetrics().width("0") * 15);
  netmaskLayout->addWidget(netmaskDottedField, 0, 1, AlignLeft);

  QLabel *netmaskBinFieldLabel = new QLabel(netmaskPage);
  netmaskBinFieldLabel->setText("Binary:");
  netmaskLayout->addWidget(netmaskBinFieldLabel, 1, 0, AlignRight);

  netmaskBinField = new QLabel(netmaskPage, "NetmaskBin");
  netmaskBinField->setMinimumWidth(netmaskBinField->fontMetrics().width("0") * 35);
  netmaskLayout->addWidget(netmaskBinField, 1, 1, AlignLeft);

  QLabel *netmaskCIDRFieldLabel = new QLabel(netmaskPage);
  netmaskCIDRFieldLabel->setText("CIDR:");
  netmaskLayout->addWidget(netmaskCIDRFieldLabel, 2, 0, AlignRight);

  netmaskCIDRField = new QLabel(netmaskPage, "netmaskReverseField");
  netmaskCIDRField->setMinimumWidth(netmaskCIDRField->fontMetrics().width("0") * 2);
  netmaskLayout->addWidget(netmaskCIDRField, 2, 1, AlignLeft);

  QLabel *netmaskReverseFieldLabel = new QLabel(netmaskPage);
  netmaskReverseFieldLabel->setText("Reverse:");
  netmaskLayout->addWidget(netmaskReverseFieldLabel, 3, 0, AlignRight);

  netmaskReverseField = new QLabel(netmaskPage, "netmaskReverseField");
  netmaskReverseField->setMinimumWidth(netmaskReverseField->fontMetrics().width("0") * 15);
  netmaskLayout->addWidget(netmaskReverseField, 3, 1, AlignLeft);
}

void IPWidget::slotUpdated()
{
  // FIXME these return bool's, check and do dialogs
  sn.setIP(ipField->text().latin1());
  sn.setNetmask(netmaskField->text().latin1());

  // set all fields, using implicit QString creation from const char *'s
  ipBinField->setText(sn.getIPBinary().c_str());
  minHostField->setText(sn.getMinHostDotted().c_str());
  maxHostField->setText(sn.getMaxHostDotted().c_str());

  networkDottedField->setText(sn.getNetworkDotted().c_str());
  networkBinaryField->setText(sn.getNetworkBinary().c_str());
  broadcastDottedField->setText(sn.getBroadcastDotted().c_str());

  netmaskDottedField->setText(sn.getNetmaskDotted().c_str());
  netmaskCIDRField->setText(sn.getNetmaskCIDR().c_str());
  netmaskBinField->setText(sn.getNetmaskBinary().c_str());
  netmaskReverseField->setText(sn.getRevMaskDotted().c_str());
}
