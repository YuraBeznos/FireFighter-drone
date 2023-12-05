#ifndef _UTILS_H
#define _UTILS_H

#include <string>

using namespace std;

struct packet
{
  string from;
  string to;
  string method;
  string val1;
  string val2;
  string val3;
  string str()
  {
    return from + "," + to + "," + method + "," + val1 + "," + val2 + "," +
           val3;
  }
};

int
count(string str, char sep);
packet
explode(string val);

#endif // _UTILS_H
