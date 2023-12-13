---
title: src/utils.h

---

# src/utils.h



## Classes

|                | Name           |
| -------------- | -------------- |
| struct | **[packet](Classes/structpacket.md)**  |

## Functions

|                | Name           |
| -------------- | -------------- |
| int | **[count](Files/utils_8h.md#function-count)**(string str, char sep) |
| [packet](Classes/structpacket.md) | **[explode](Files/utils_8h.md#function-explode)**(string val) |
| bool | **[is_allowed](Files/utils_8h.md#function-is-allowed)**([packet](Classes/structpacket.md) pkt, vector< tuple< string, string, string > > allowed) |


## Functions Documentation

### function count

```cpp
int count(
    string str,
    char sep
)
```


### function explode

```cpp
packet explode(
    string val
)
```


### function is_allowed

```cpp
bool is_allowed(
    packet pkt,
    vector< tuple< string, string, string > > allowed
)
```




## Source code

```cpp
#ifndef _UTILS_H
#define _UTILS_H

#include <string>
#include <tuple>
#include <vector>

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
bool
is_allowed(packet pkt, vector<tuple<string, string, string>> allowed);

#endif // _UTILS_H
```


-------------------------------

Updated on 2023-12-13 at 13:54:01 +0300
