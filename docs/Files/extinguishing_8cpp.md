---
title: src/extinguishing.cpp

---

# src/extinguishing.cpp



## Functions

|                | Name           |
| -------------- | -------------- |
| void | **[proceed_action](Files/extinguishing_8cpp.md#function-proceed-action)**() |
| void | **[stop_action](Files/extinguishing_8cpp.md#function-stop-action)**() |
| int | **[main](Files/extinguishing_8cpp.md#function-main)**(int argc, char ** argv) |

## Attributes

|                | Name           |
| -------------- | -------------- |
| string | **[me](Files/extinguishing_8cpp.md#variable-me)**  |
| bool | **[action](Files/extinguishing_8cpp.md#variable-action)**  |
| [Broker](Classes/classBroker.md) * | **[broker](Files/extinguishing_8cpp.md#variable-broker)**  |


## Functions Documentation

### function proceed_action

```cpp
void proceed_action()
```


### function stop_action

```cpp
void stop_action()
```


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
string me = "extinguishing";
```


### variable action

```cpp
bool action = false;
```


### variable broker

```cpp
Broker * broker;
```



## Source code

```cpp
#include "broker.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>

/*
 * Extinguishing - Процедура тушения
 */

using namespace std;

string me = "extinguishing";
bool action = false;

Broker* broker;

void
proceed_action()
{
  action = true;
  cout << "action (fire/extinguishing) has been started" << endl;
}

void
stop_action()
{
  action = false;
  cout << "action (fire/extinguishing) has been stopped" << endl;
}

void
Broker::on_packet(packet pkt)
{
  if (pkt.method == "action") {
    packet out_pkt = { me.c_str(), "eaic", "action" };
    broker->to_monitor(out_pkt);
  } else if (pkt.method == "start_action") {
    proceed_action();

  } else if (pkt.method == "stop_action") {
    stop_action();
    packet out_pkt = { me.c_str(), "eaic", "stop_action" };
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
