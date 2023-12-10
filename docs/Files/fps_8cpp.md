---
title: src/fps.cpp

---

# src/fps.cpp



## Functions

|                | Name           |
| -------------- | -------------- |
| void | **[start_task](Files/fps_8cpp.md#function-start-task)**() |
| int | **[main](Files/fps_8cpp.md#function-main)**(int argc, char ** argv) |

## Attributes

|                | Name           |
| -------------- | -------------- |
| string | **[me](Files/fps_8cpp.md#variable-me)**  |
| vector< string > | **[tasks](Files/fps_8cpp.md#variable-tasks)**  |
| bool | **[start_send](Files/fps_8cpp.md#variable-start-send)**  |
| [Broker](Classes/classBroker.md) * | **[broker](Files/fps_8cpp.md#variable-broker)**  |


## Functions Documentation

### function start_task

```cpp
void start_task()
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
string me = "fps";
```


### variable tasks

```cpp
vector< string > tasks = { "A", "B", "C", "D", "E", "F", "G" };
```


### variable start_send

```cpp
bool start_send = false;
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
#include <string>
#include <unistd.h>
#include <vector>

/*
 * FPS (Flight Plan Server) - Источник полётного задания
 */

using namespace std;

string me = "fps";
vector<string> tasks = { "A", "B", "C", "D", "E", "F", "G" };
bool start_send = false;

Broker* broker;
void
Broker::on_packet(packet pkt)
{
  if (pkt.method == "started") {
    cout << pkt.method << " task at " << pkt.val1 << endl;
    start_send = false;
  } else if (pkt.method == "not_started") {
    cout << pkt.method << " task at " << pkt.val1 << endl;
    start_send = false;
  }
}

void
start_task()
{
  if (!tasks.empty()) {
    string task = tasks.front();
    tasks.erase(tasks.begin());
    packet out_pkt = { me.c_str(), "communication", "start", task };
    broker->to_monitor(out_pkt);
    start_send = true;
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
    if (!start_send) {
      start_task();
    }
    cout << "working" << endl;
    sleep(10);
  }
  return 0;
}
```


-------------------------------

Updated on 2023-12-10 at 12:51:12 +0300
