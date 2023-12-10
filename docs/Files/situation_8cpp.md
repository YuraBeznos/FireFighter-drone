---
title: src/situation.cpp

---

# src/situation.cpp



## Functions

|                | Name           |
| -------------- | -------------- |
| int | **[main](Files/situation_8cpp.md#function-main)**(int argc, char ** argv) |

## Attributes

|                | Name           |
| -------------- | -------------- |
| string | **[me](Files/situation_8cpp.md#variable-me)**  |
| bool | **[running](Files/situation_8cpp.md#variable-running)**  |
| [Broker](Classes/classBroker.md) * | **[broker](Files/situation_8cpp.md#variable-broker)**  |


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
string me = "situation";
```


### variable running

```cpp
bool running = true;
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
 * Situation control - Контроль обстановки
 */

using namespace std;

string me = "situation";
bool running = true;


Broker* broker;
void
Broker::on_packet(packet pkt)
{
  if (pkt.method == "is_action_running") {
    packet out_pkt = { me.c_str(), pkt.from, "action_is_running" };
    broker->to_monitor(out_pkt);
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
