/***************************************************************************
  Copyright: (C) 2002 by Kyle VanderBeek <kylev@kylev.com>
  $Id: simplenet.h,v 1.9 2002/04/20 20:51:34 kylev Exp $
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef SIMPLENET_H
#define SIMPLENET_H

#include <iostream>
#include <string>
#include <sys/types.h>

class SimpleNet {
 public:
  SimpleNet() { _ip = _mask = 0; _isCIDR = true; };
  SimpleNet(const string&, const string&);
  // Destructor not needed

  void setIP(int, int, int, int);
  bool setIP(const string &);
  bool setNetmask(const int);
  bool setNetmask(const string &);

  string getIP() const { return getIPDotted(); };
  string getIPDotted() const { return toDotted(_ip); };
  string getIPBinary() const { return toBinary(_ip); };
  string getMinHostDotted() const { return toDotted((_ip&_mask) + 1); };
  string getMaxHostDotted() const { return toDotted((_ip|~_mask) - 1); };
  string getNetmaskDotted() const { return toDotted(_mask); };
  string getNetmaskBinary() const { return toBinary(_mask); };
  string getNetmaskCIDR() const { return toCIDR(_mask); };
  string getNetworkDotted() const { return toDotted(_ip & _mask); };
  string getNetworkBinary() const { return toBinary(_ip & _mask); };
  string getRevMaskDotted() const { return toDotted(~_mask); };
  string getBroadcastDotted() const { return toDotted(_ip | ~_mask); };

  friend ostream &operator<< (ostream &of, const SimpleNet &sn);

 private:
  string toDotted(u_int32_t) const;
  string toBinary(u_int32_t) const;
  string toCIDR(u_int32_t) const;
  
  u_int32_t _ip;
  u_int32_t _mask;
  bool _isCIDR;
};

#endif
