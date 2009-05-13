#ifndef SIMPLENET_H
#define SIMPLENET_H

#include <iostream.h>

class SimpleNet {
 public:
  SimpleNet() { _ip = _mask = 0; _isCIDR = true; };
  SimpleNet(char*, char*);
  // Destructor not needed

  void setIP(int, int, int, int);
  bool setIP(const char*);
  void setNetmask(int);
  bool setNetmask(const char*);

  char *getIP() { return getIPDotted(); };
  char *getIPDotted() { return unsignedToDotted(_ip); };
  char *getIPBinary() { return unsignedToBinary(_ip); };
  char *getMinHostDotted() { return unsignedToDotted((_ip&_mask) + 1); };
  char *getMaxHostDotted() { return unsignedToDotted((_ip|~_mask) - 1); };
  char *getNetmaskDotted() { return unsignedToDotted(_mask); };
  char *getNetmaskBinary() { return unsignedToBinary(_mask); };
  char *getNetworkDotted() { return unsignedToDotted(_ip & _mask); };
  char *getNetworkBinary() { return unsignedToBinary(_ip & _mask); };
  char *getRevMaskDotted() { return unsignedToDotted(~_mask); };
  char *getBroadcastDotted() { return unsignedToDotted(_ip | ~_mask); };

  friend ostream &operator<< (ostream &of, const SimpleNet &sn);

 private:
  char *unsignedToDotted(unsigned int);
  char *unsignedToBinary(unsigned int);

  static const int MAXIPBINARY = 32 + 3 + 1;
  static const int MAXIP = 12 + 3 + 1;

  unsigned int _ip;
  unsigned int _mask;
  bool _isCIDR;
};

#endif
