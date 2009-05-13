#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "simplenet.h"

SimpleNet::SimpleNet(char* ip, char* netmask) {
  cout << "Got called with IP " << ip << " and netmask " << netmask << endl;
}

void SimpleNet::setIP(int o1, int o2, int o3, int o4) {
  _ip = (o1 << 24) + (o2 << 16) + (o3 << 8) + (o4);
}

bool SimpleNet::setIP(const char *ip) {
  unsigned int tempip = 0;
  char *end = (char *)ip;
  int dotcount = 0;

  // count the number of dots (should be 3)
  for (char *c = (char *)ip; *c != '\0'; c++)
    if (*c == '.')
      dotcount++;
  if (dotcount != 3)
    return false;

  for (int i = 3; i >= 0; i--) {
    int temppart = strtol(end, &end, 10);
    cout << temppart << endl;
    if (temppart < 0 || temppart > 255)
      return false;

    tempip += temppart << (8 * i);

    if (*end == '.')
      end++;
  }
  
  // Note that we ignore trailing garbage if possible
  _ip = tempip;
  return true;
}

void SimpleNet::setNetmask(int nm) {
  _mask = nm;
}

bool SimpleNet::setNetmask(const char *nm) {
  unsigned int tempmask = 0;
  int i, j;

  // count the number of dots (should be 3)
  int dotcount = 0;
  for (char *c = (char *)nm; *c != 0; c++)
    if (*c == '.')
      dotcount++;

  if (dotcount == 0) {
    // must be CIDR!
    tempmask = atoi(nm);
    if (tempmask >= 0 && tempmask <= 32) {
      _mask = ~0 << (32-tempmask);
      _isCIDR = true;
      return true;
    } else
      return false;
  } else if (dotcount == 3) {
    // dotted notation
    char *end = (char *)nm;
    for (i = 3; i >= 0; i--) {
      int temppart = strtol(end, &end, 10);
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
      if (*end == '.')
	end++;
    }
    
    _mask = ~0 << (32-tempmask);
    _isCIDR = false;
    return true;
  }    
  
  // Wrong number of dots
  return false;
}

char *SimpleNet::unsignedToDotted(unsigned int u) {
  char *b = (char *)malloc(MAXIP);
  
  if (!b) 
    return NULL;

  if (0 > snprintf(b, MAXIP, "%d.%d.%d.%d", (u & 0xff000000) >> 24, (u &0xff0000) >> 16,
		   (u & 0xff00) >> 8, u & 0xff) ) {
    free(b);
    return NULL;
  }
  return b;
}

char *SimpleNet::unsignedToBinary(unsigned int u) {
  char *b = (char *)malloc(MAXIPBINARY);
  char *p = b;
  unsigned int slidemask = 0x80000000;

  if (!b) 
    return NULL;
  
  while (slidemask) {
    *p = (slidemask & u) ? '1' : '0';
    p++;

    if (slidemask & 0x01010100) {
      *p++ = '.';
    }

    slidemask >>= 1;
  }
  *p = '\0';

  return b;
}

ostream &operator << (ostream &of, const SimpleNet &sn) {
  of << ((sn._ip & 0xff000000) >> 24) << '.' <<
    ((sn._ip & 0xff0000) >> 16) << '.' <<
    ((sn._ip & 0xff00) >> 8) << '.' <<
    (sn._ip & 0xff) <<
    '/' << sn._mask;
  return of;
}
