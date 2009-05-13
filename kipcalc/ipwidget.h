#ifndef IPWIDGET_H
#define IPWIDGET_H

#include "simplenet.h"

#include <krestrictedline.h>

#include <qwidget.h>
#include <qspinbox.h>
#include <qlabel.h>
#include <qlayout.h>

class IPWidget : public QWidget
{
  Q_OBJECT
public:
  IPWidget(QWidget *parent);
private:
  KRestrictedLine *ipField, *netmaskField;
  QLabel *ipBinField, *minHostField, *maxHostField, *networkDottedField, *networkBinaryField,
      *broadcastDottedField, *netmaskDottedField, *netmaskBinField, *netmaskReverseField;
  QSpinBox *netmaskCIDRField;
  SimpleNet sn;
  QVBoxLayout *vbox;
  void updateReadFields();
private slots:
  void slotIPUpdated();
  void slotNetmaskUpdated();
  void slotCIDRUpdated(int);
};

#endif
