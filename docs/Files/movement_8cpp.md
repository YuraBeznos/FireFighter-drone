---
title: src/movement.cpp

---

# src/movement.cpp



## Functions

|                | Name           |
| -------------- | -------------- |
| bool | **[to_position](Files/movement_8cpp.md#function-to-position)**(string task) |
| int | **[main](Files/movement_8cpp.md#function-main)**(int argc, char ** argv) |

## Attributes

|                | Name           |
| -------------- | -------------- |
| string | **[me](Files/movement_8cpp.md#variable-me)**  |
| [Broker](Classes/classBroker.md) * | **[broker](Files/movement_8cpp.md#variable-broker)**  |


## Functions Documentation

### function to_position

```cpp
bool to_position(
    string task
)
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
string me = "movement";
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
 * Movement control - Управление перемещением
 */

using namespace std;

string me = "movement";

Broker* broker;

bool
to_position(string task)
{
  cout << "going to position of: " << task;
  sleep(5); // TODO: logic of movement to coordinates
  return true;
}

void
Broker::on_packet(packet pkt)
{
  if (pkt.method == "move") {
    string task = pkt.val1;
    if (to_position(task)) {
      packet out_pkt = { me.c_str(), pkt.from, "done", task };
      broker->to_monitor(out_pkt);
    }
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

Updated on 2023-12-13 at 13:54:01 +0300
