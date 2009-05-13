/***************************************************************************
  Copyright: (C) 2002 by Kyle VanderBeek <kylev@kylev.com>
  $Id: simplenet.cpp,v 1.7 2002/04/20 20:51:32 kylev Exp $
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#include "simplenet.h"

SimpleNet::SimpleNet(const string &ip, const string &netmask) {
  // Best effort to set, not recommended since I can't return a bool
  setIP(ip);
  setNetmask(netmask);
}

void SimpleNet::setIP(int o1, int o2, int o3, int o4) {
  _ip = (o1 << 24) + (o2 << 16) + (o3 << 8) + (o4);
}

bool SimpleNet::setIP(const string &s) {
  u_int32_t tempip = 0;
  string::const_iterator end = s.begin();
  int dotcount = 0;

  // count the number of dots (should be 3)
  while (end != s.end()) {
    if (*end == '.')
      dotcount++;
    end++;
  }

  if (dotcount != 3)
    return false;

  end = s.begin();
  for (int i = 3; i >= 0; i--) {
    int temppart = atoi(end);
    if (temppart < 0 || temppart > 255)
      return false;

    tempip += temppart << (8 * i);

    while (end != s.end() && *end != '.')
      end++;
    end++;
  }

  // Note that we ignore trailing garbage if possible
  _ip = tempip;
  return true;
}

bool SimpleNet::setNetmask(const int nm) {
  // FIXME this should actually convert from CIDR
  if (nm < 0 || nm > 32)
    return false;
  _mask = nm;
  _isCIDR = true;
  return true;
}

bool SimpleNet::setNetmask(const string &nm) {
  u_int32_t tempmask = 0;
  int i, j;
  string::const_iterator c;

  // count the number of dots (should be 3)
  int dotcount = 0;
  for (c = nm.begin(); c != nm.end(); c++)
    if (*c == '.')
      dotcount++;

  if (dotcount == 0) {
    // looks like CIDR!
    tempmask = atoi(nm.c_str());
    if (tempmask >= 0 && tempmask <= 32) {
      _mask = ~0 << (32-tempmask);
      _isCIDR = true;
      return true;
    } else
      return false;
  } else if (dotcount == 3) {
    // dotted notation
    c = nm.begin();
    for (i = 3; i >= 0; i--) {
      int temppart = atoi(c);
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
      while (c != nm.end() && *c != '.')
	c++;
      c++;
    }
    
    _mask = ~0 << (32-tempmask);
    _isCIDR = false;
    return true;
  }    

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
  u_int32_t tempmask = 0x80000000;
  int i, cidr = 0;
  ostringstream oss;
  
  for (i = 0; tempmask; tempmask >>= 1)
    if (tempmask & u)
      cidr++;
  
  oss << cidr;
  return oss.str();
}

ostream &operator << (ostream &of, const SimpleNet &sn)
{
  of << sn.getIPDotted() << '/' << sn.getNetmaskCIDR();
  return of;
}
