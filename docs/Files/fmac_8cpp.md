---
title: src/fmac.cpp

---

# src/fmac.cpp



## Functions

|                | Name           |
| -------------- | -------------- |
| bool | **[is_authentic_task](Files/fmac_8cpp.md#function-is-authentic-task)**(string task) |
| int | **[main](Files/fmac_8cpp.md#function-main)**(int argc, char ** argv) |

## Attributes

|                | Name           |
| -------------- | -------------- |
| string | **[me](Files/fmac_8cpp.md#variable-me)**  |
| vector< string > | **[authentic_tasks](Files/fmac_8cpp.md#variable-authentic-tasks)**  |
| [Broker](Classes/classBroker.md) * | **[broker](Files/fmac_8cpp.md#variable-broker)**  |


## Functions Documentation

### function is_authentic_task

```cpp
bool is_authentic_task(
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
string me = "fmac";
```


### variable authentic_tasks

```cpp
vector< string > authentic_tasks = { "A", "C" };
```


### variable broker

```cpp
Broker * broker;
```



## Source code

```cpp
#include "broker.h"
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>

/*
 * FMAC (Flight mission authenticity control) - Контроль аутентичности полётного задания
 */

using namespace std;

string me = "fmac";
vector<string> authentic_tasks = { "A", "C" };

Broker* broker;

bool
is_authentic_task(string task)
{
  if (find(authentic_tasks.begin(), authentic_tasks.end(), task) !=
      authentic_tasks.end()) {
    cout << "authentic task: " << task << endl;
    return true;
  }
  cout << "not authentic task: " << task << endl;
  return false;
}

void
Broker::on_packet(packet pkt)
{
  if (pkt.method == "start") {
    string task = pkt.val1;
    if (is_authentic_task(task)) {
      packet out_pkt = { me.c_str(), "eaic", "execute", task };
      broker->to_monitor(out_pkt);
      out_pkt = { me.c_str(), "ccu", "execute", task };
      broker->to_monitor(out_pkt);
    } else {
      packet out_pkt = { me.c_str(), "communication", "not_authentic_task", task };
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
