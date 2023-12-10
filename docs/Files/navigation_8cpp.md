---
title: src/navigation.cpp

---

# src/navigation.cpp



## Functions

|                | Name           |
| -------------- | -------------- |
| int | **[main](Files/navigation_8cpp.md#function-main)**(int argc, char ** argv) |

## Attributes

|                | Name           |
| -------------- | -------------- |
| const string | **[me](Files/navigation_8cpp.md#variable-me)**  |
| string | **[coordinate](Files/navigation_8cpp.md#variable-coordinate)**  |
| [Broker](Classes/classBroker.md) * | **[broker](Files/navigation_8cpp.md#variable-broker)**  |


## Functions Documentation

### function main

```cpp
int main(
    int argc,
    char ** argv
)
```



## Attributes Documentation

### variable me

```cpp
static const string me = "navigation";
```


### variable coordinate

```cpp
string coordinate = "0";
```


### variable broker

```cpp
Broker * broker;
```



## Source code

```cpp
#include "broker.h"
#include "utils.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>

/*
 * Navigation system - Навигация GNSS + ИНС
 */

using namespace std;

static const string me = "navigation";
string coordinate = "0";

Broker* broker;

void
Broker::on_packet(packet pkt)
{
  if (pkt.method == "get_coordinates") {
    packet out_pkt = { pkt.to, pkt.from, "coordinates", coordinate };
    broker->to_monitor(out_pkt);
  }
}

int
main(int argc, char** argv)
{
  cout << "start: " << me << endl;

  mosqpp::lib_init();
  broker = new Broker(me);
  broker->subscribe(NULL, me.c_str());
  broker->loop_forever();
  mosqpp::lib_cleanup();
  return 0;
}
```


-------------------------------

Updated on 2023-12-10 at 12:51:12 +0300
