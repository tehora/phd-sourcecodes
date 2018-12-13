typedef unsigned char uchr;

struct osoba {
  uchr rozmiar;
  uchr padding;
  uchr org1, org2, usr1, usr2;
  uchr goodtime;
  uchr badtime;
  short reg;
  uchr ineryx, padding2;
  osoba() { 
    rozmiar = org1 = org2 = usr1 = usr2 = goodtime = badtime = padding = 0; 
    ineryx = padding2 = 0;
    reg = 32767;
    }
  };

#pragma pack(push, 1)
struct edge {
  unsigned int efrom : 24;
  unsigned int eto : 24;
  int eflags: 16;
  };
#pragma pack(pop)

