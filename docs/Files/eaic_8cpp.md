---
title: src/eaic.cpp

---

# src/eaic.cpp



## Functions

|                | Name           |
| -------------- | -------------- |
| bool | **[action_is_allowed](Files/eaic_8cpp.md#function-action-is-allowed)**(string coordinates) |
| void | **[position_control](Files/eaic_8cpp.md#function-position-control)**() |
| int | **[main](Files/eaic_8cpp.md#function-main)**(int argc, char ** argv) |

## Attributes

|                | Name           |
| -------------- | -------------- |
| string | **[me](Files/eaic_8cpp.md#variable-me)**  |
| string | **[task](Files/eaic_8cpp.md#variable-task)**  |
| [Broker](Classes/classBroker.md) * | **[broker](Files/eaic_8cpp.md#variable-broker)**  |


## Functions Documentation

### function action_is_allowed

```cpp
bool action_is_allowed(
    string coordinates
)
```


### function position_control

```cpp
void position_control()
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
string me = "eaic";
```


### variable task

```cpp
string task;
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
 * EAIC (extinguishing and ignition circuits controller) - Контроль активации
 * цепей тушения и поджига
 */

using namespace std;
string me = "eaic";

string task;

bool
action_is_allowed(string coordinates)
{
  return true;
}

void
position_control()
{
}

Broker* broker;
void
Broker::on_packet(packet pkt)
{
  if (pkt.method == "execute_action") { // step 4
    task = pkt.val1;
  } else if (pkt.method == "action_request") {                 // step 15
    packet out_pkt = { me, "aggregation", "get_coordinates" }; // step 18
    broker->to_monitor(out_pkt);
  } else if (pkt.method == "coordinates") {
    if (action_is_allowed(pkt.val1)) {
      packet out_pkt = { me, "extinguishing", "start_action" }; // step 21
      broker->to_monitor(out_pkt);
      position_control(); // 23
    }
  } else if (pkt.method == "stop_action") { // 28
    task = "";                              // 29
  }
}

int
main(int argc, char** argv)
{
  cout << "start: " << argv[0] << endl;
  while (1) {
    cout << "working: " << argv[0] << endl;
    sleep(10);
  }
  return 0;
}
```


-------------------------------

Updated on 2023-12-10 at 12:51:12 +0300
