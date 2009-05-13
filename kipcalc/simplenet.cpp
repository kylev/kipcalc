/***************************************************************************
  Copyright: (C) 2002 by Kyle VanderBeek <kylev@kylev.com>
  $Id: simplenet.cpp,v 1.11 2002/04/25 00:59:55 kylev Exp $
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <sstream>

#include "simplenet.h"

SimpleNet::SimpleNet(const string &ip, const string &netmask) {
  // Best effort to set, not recommended since I can't return a bool
  setIP(ip);
  setNetmask(netmask);
}

SimpleNet::SimpleNet(const string &ip, int nm) {
  // Best effort to set, not recommended since I can't return a bool
  setIP(ip);
  setNetmask(nm);
}

void SimpleNet::setIP(int o1, int o2, int o3, int o4) {
  _ip = (o1 << 24) + (o2 << 16) + (o3 << 8) + (o4);
}

bool SimpleNet::setIP(const string &s) {
  u_int32_t tempip = 0;

  // count the number of dots (should be 3)
  string::const_iterator end = s.begin();
  int dotcount = 0;
  while (end != s.end()) {
    if (*end == '.')
      dotcount++;
    end++;
  }

  if (dotcount != 3)
    return false;

  // FIXME this parsing plugs ahead, we should check iis.bad() and/or iis.eof()
  istringstream iss(s);
  int temppart = -1;
  char dot;
  for (int i = 3; i >= 0; i--) {
    iss >> temppart;
    if (temppart < 0 || temppart > 255)
      return false;

    tempip += temppart << (8 * i);

    iss >> dot;
    if (dot != '.')
      return false;
    //    end++;
  }

  // Note that we ignore trailing garbage if possible
  _ip = tempip;
  return true;
}

bool SimpleNet::setNetmask(const int nm) {
  // FIXME this should actually convert from CIDR
  if (nm < 0 || nm > 32)
    return false;

  for (int i = _mask = 0; i < 32; i++) {
    _mask = (_mask << 1);
    if (i < nm)
      _mask++;
  }

  _isCIDR = true;
  return true;
}

bool SimpleNet::setNetmask(const string &nm) {
  u_int32_t tempmask = 0;
  int i, j;

  // count the number of dots (should be 3)
  int dotcount = 0;
  for (string::const_iterator c = nm.begin(); c != nm.end(); c++)
    if (*c == '.')
      dotcount++;

  istringstream iss(nm);
  if (dotcount == 0) {
    // looks like CIDR!
    iss >> tempmask;
    if (tempmask >= 0 && tempmask <= 32) {
      _mask = ~0 << (32-tempmask);
      _isCIDR = true;
      return true;
    } else
      return false;
  } else if (dotcount == 3) {
    // dotted notation
    int temppart;
    char dot;
    for (i = 3; i >= 0; i--) {
      iss >> temppart;
      if (temppart < 0 || temppart > 255)
	return false;
      
      // check each bit of the part from left to right
      for (j = 0x80; j > 0; j = j >> 1) 
	if (j & temppart)
	  tempmask++;
	else
	  break;

      // we didn't make it to the end of the part with ones
      if (j)
	break;

      // move past the dot
      iss >> dot;
      if (dot != '.')
        return false;
    }
    
    _mask = ~0 << (32-tempmask);
    _isCIDR = false;
    return true;
  } else
    // Wrong number of dots
    return false;
}

string SimpleNet::toDotted(u_int32_t u) const
{
  ostringstream oss;
  
  oss <<
    ((u & 0xff000000) >> 24) << '.' <<
    ((u & 0xff0000) >> 16) << '.' <<
    ((u & 0xff00) >> 8) << '.' <<
    (u & 0xff);

  return oss.str();
}

string SimpleNet::toHex(u_int32_t u) const
{
  ostringstream oss;

  // FIXME I'd like to zero-fill to 2 digits
  oss << hex <<
    ((u & 0xff000000) >> 24) << ':' <<
    ((u & 0xff0000) >> 16) << ':' <<
    ((u & 0xff00) >> 8) << ':' <<
    (u & 0xff);

  return oss.str();
}

string SimpleNet::toBinary(u_int32_t u) const
{
  ostringstream oss;
  u_int32_t slidemask = 0x80000000;

  while (slidemask) {
    oss << ((slidemask & u) ? '1' : '0');

    if (slidemask & 0x01010100)
      oss << '.';

    slidemask >>= 1;
  }

  return oss.str();
}

string SimpleNet::toCIDR(u_int32_t u) const
{
  ostringstream oss;
  
  oss << (int)toCIDRInt(u);
  return oss.str();
}

int SimpleNet::toCIDRInt(u_int32_t u) const
{
  u_int32_t tempmask = 0x80000000;
  int i, cidr = 0;
  
  for (i = 0; tempmask; tempmask >>= 1)
    if (tempmask & u)
      cidr++;
  
  return cidr;
}

ostream &operator << (ostream &of, const SimpleNet &sn)
{
  of << sn.getIPDotted() << '/' << sn.getNetmaskCIDR();
  return of;
}
