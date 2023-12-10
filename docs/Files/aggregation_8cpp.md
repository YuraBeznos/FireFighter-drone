---
title: src/aggregation.cpp

---

# src/aggregation.cpp



## Namespaces

| Name           |
| -------------- |
| **[std](Namespaces/namespacestd.md)**  |

## Functions

|                | Name           |
| -------------- | -------------- |
| void | **[get_coordinates](Files/aggregation_8cpp.md#function-get-coordinates)**() |
| void | **[set_coordinates](Files/aggregation_8cpp.md#function-set-coordinates)**(string new_coordinate) |
| bool | **[check_coordinates_validity](Files/aggregation_8cpp.md#function-check-coordinates-validity)**(string gps, string ins) |
| int | **[main](Files/aggregation_8cpp.md#function-main)**(int argc, char ** argv) |

## Attributes

|                | Name           |
| -------------- | -------------- |
| string | **[me](Files/aggregation_8cpp.md#variable-me)**  |
| string | **[coordinate](Files/aggregation_8cpp.md#variable-coordinate)**  |
| [Broker](Classes/classBroker.md) * | **[broker](Files/aggregation_8cpp.md#variable-broker)**  |


## Functions Documentation

### function get_coordinates

```cpp
void get_coordinates()
```


### function set_coordinates

```cpp
void set_coordinates(
    string new_coordinate
)
```


### function check_coordinates_validity

```cpp
bool check_coordinates_validity(
    string gps,
    string ins
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
string me = "aggregation";
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
#include <map>
#include <memory>
#include <mosquittopp.h>
#include <stdio.h>
#include <string>
#include <string_view>
#include <unistd.h>
#include <vector>

/*
 * Aggregation - Комплексирование
 */

using namespace std;

string me = "aggregation";
string coordinate = "0";

Broker* broker;
void
get_coordinates()
{
  packet out_pkt = { me.c_str(), "navigation", "get_coordinates" };
  broker->to_monitor(out_pkt);
}

void
set_coordinates(string new_coordinate)
{
  coordinate = new_coordinate;
}

bool
check_coordinates_validity(string gps, string ins)
{
  if (gps == ins) {
    set_coordinates(ins);
    return true;
  }
  return false;
}

void
Broker::on_packet(packet pkt)
{
  if (pkt.method == "get_coordinates") {
    packet out_pkt = { pkt.to, pkt.from, "coordinates", coordinate };
    broker->to_monitor(out_pkt);
  } else if (pkt.method == "coordinates") {
    check_coordinates_validity(pkt.val1, pkt.val2);
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
    get_coordinates();
    sleep(10);
  }
  mosqpp::lib_cleanup();
  return 0;
}
```


-------------------------------

Updated on 2023-12-10 at 12:51:12 +0300
