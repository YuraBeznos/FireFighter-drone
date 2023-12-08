#include "utils.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int
count(string str, char sep)
{
  long unsigned int count = 0;

  for (long unsigned int i = 0; i < str.size(); i++)
    if (str[i] == sep)
      count++;
  return count;
}

packet
explode(string val)
{
  packet pkt;
  char sep = ',';
  long unsigned int num_fields = count(val, sep);
  vector<string> vec;
  for (long unsigned int i = 0; i < val.length(); i++) {
    int pos = val.find(sep, i);
    if (pos < 0) {
      vec.push_back(val.substr(i));
      break;
    }
    int cnt = pos - i;
    vec.push_back(val.substr(i, cnt));
    i = pos;
  }

  for (long unsigned int i = 0; i < num_fields; i++) {

    // cout << "vec[" << i << "]=" << vec[i];
    switch (i) {
      case 0:
        pkt.from = vec[0];
        break;
      case 1:
        pkt.to = vec[1];
        break;
      case 2:
        pkt.method = vec[2];
        break;
      case 3:
        pkt.val1 = vec[3];
        break;
      case 4:
        pkt.val2 = vec[4];
        break;
      case 5:
        pkt.val3 = vec[5];
        break;
      default:
        break;
    }
  }
  return pkt;
}
