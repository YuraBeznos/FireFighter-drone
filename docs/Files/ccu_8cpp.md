---
title: src/ccu.cpp

---

# src/ccu.cpp



## Functions

|                | Name           |
| -------------- | -------------- |
| int | **[main](Files/ccu_8cpp.md#function-main)**(int argc, char ** argv) |

## Attributes

|                | Name           |
| -------------- | -------------- |
| string | **[me](Files/ccu_8cpp.md#variable-me)**  |
| string | **[destination](Files/ccu_8cpp.md#variable-destination)**  |
| bool | **[is_action_running](Files/ccu_8cpp.md#variable-is-action-running)**  |
| [Broker](Classes/classBroker.md) * | **[broker](Files/ccu_8cpp.md#variable-broker)**  |


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
string me = "ccu";
```


### variable destination

```cpp
string destination;
```


### variable is_action_running

```cpp
bool is_action_running = false;
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
 * CCU (Central control unit) - Центральная система управления
 */

using namespace std;

string me = "ccu";
string destination;
bool is_action_running = false;

Broker* broker;
void
Broker::on_packet(packet pkt)
{
  packet out_pkt;
  if (pkt.method == "execute") { // step 5
    destination = pkt.val1;
    out_pkt = { me.c_str(), "aggregation", "get_coordinates" }; // step 9
    broker->to_monitor(out_pkt);
  } else if (pkt.method == "coordinates") {                    // step 10
    out_pkt = { me.c_str(), "movement", "move", destination }; // step 11
    broker->to_monitor(out_pkt);
  } else if (pkt.method == "done") {                  // step 13
    out_pkt = { me.c_str(), "extinguishing", "start_action" }; // step 14
    is_action_running = true;
    broker->to_monitor(out_pkt);
  } else if (pkt.method == "action_is_running") { // step 26
    is_action_running = false;
    out_pkt = { me.c_str(), "extinguishing", "stop_action" }; // step 27
    broker->to_monitor(out_pkt);

    packet out_pkt = {
      me.c_str(), "communication", "started", destination
    }; // step 30
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
  broker->loop_start();

  while (1) {
    if (is_action_running) {
      packet out_pkt = {
        me.c_str(), "situation", "is_action_running", destination
      };                           // step 24
      broker->to_monitor(out_pkt); // step 30
    }
    cout << "working" << endl;
    sleep(10);
  }
  return 0;
}
```


-------------------------------

Updated on 2023-12-13 at 13:54:01 +0300
