#ifndef IPWIDGET_H
#define IPWIDGET_H

#include "simplenet.h"

#include <krestrictedline.h>

#include <qwidget.h>
#include <qlabel.h>
#include <qlayout.h>

class IPWidget : public QWidget
{
  Q_OBJECT
public:
  IPWidget(QWidget *parent);
private:
  KRestrictedLine *ipField, *netmaskField;
  QLabel *ipBinField, *minHostField, *maxHostField, *networkDottedField, *networkBinaryField, *broadcastDottedField,
      *netmaskDottedField, *netmaskBinField, *netmaskCIDRField, *netmaskReverseField;
  SimpleNet sn;
  QVBoxLayout *vbox;
private slots:
  void slotUpdated();
};

#endif
