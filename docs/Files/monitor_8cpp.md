---
title: src/monitor.cpp

---

# src/monitor.cpp



## Functions

|                | Name           |
| -------------- | -------------- |
| int | **[main](Files/monitor_8cpp.md#function-main)**(int argc, char ** argv) |

## Attributes

|                | Name           |
| -------------- | -------------- |
| const string | **[me](Files/monitor_8cpp.md#variable-me)**  |
| [Broker](Classes/classBroker.md) * | **[broker](Files/monitor_8cpp.md#variable-broker)**  |
| vector< tuple< string, string, string > > | **[allowed](Files/monitor_8cpp.md#variable-allowed)**  |


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
static const string me = "monitor";
```


### variable broker

```cpp
Broker * broker;
```


### variable allowed

```cpp
vector< tuple< string, string, string > > allowed = {
  { "communication", "fmac", "start" },                    
  { "fmac", "eaic", "execute" },                             
  { "fmac", "ccu", "execute" },                              
  { "aggregation", "navigation", "get_coordinates" }, 
  { "navigation", "aggregation", "coordinates" },     
  { "ccu", "aggregation", "get_coordinates" },                       
  { "aggregation", "ccu", "coordinates" },                       
  { "ccu", "movement", "move" },                          
  { "movement", "ccu", "done" },                          
  { "ccu", "extinguishing", "start_action" },                     
  { "extinguishing", "eaic", "confirm_action" },                    
  { "eaic", "aggregation", "get_coordinates" },                      
  { "aggregation", "eaic", "coordinates" },                      
  { "eaic", "extinguishing", "start_action" },                    
  { "ccu", "situation", "is_action_running" },                         
  { "situation", "ccu", "action_is_running" },                         
  { "ccu", "extinguishing", "stop_action" },                     
  { "extinguishing", "eaic", "stop_action" },                    
  { "ccu", "communication", "started" },                     
  { "fmac", "communication", "not_authentic_task" }
};
```



## Source code

```cpp
#include "broker.h"
#include "utils.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

/*
 */

using namespace std;

static const string me = "monitor";
Broker* broker;

/*
 * allowed communications list
 * "from", "to", "method"
 */
vector<tuple<string, string, string>> allowed = {
  { "communication", "fmac", "start" },                    // 2
  { "fmac", "eaic", "execute" },                             // 3
  { "fmac", "ccu", "execute" },                              // 4
  { "aggregation", "navigation", "get_coordinates" }, // 5, 16
  { "navigation", "aggregation", "coordinates" },     // 6, 17
  { "ccu", "aggregation", "get_coordinates" },                       // 9
  { "aggregation", "ccu", "coordinates" },                       // 10
  { "ccu", "movement", "move" },                          // 11
  { "movement", "ccu", "done" },                          // 13
  { "ccu", "extinguishing", "start_action" },                     // 14 start
  { "extinguishing", "eaic", "confirm_action" },                    // 15 start
  { "eaic", "aggregation", "get_coordinates" },                      // 18
  { "aggregation", "eaic", "coordinates" },                      // 19
  { "eaic", "extinguishing", "start_action" },                    // 21
  { "ccu", "situation", "is_action_running" },                         // 24
  { "situation", "ccu", "action_is_running" },                         // 26
  { "ccu", "extinguishing", "stop_action" },                     // 27 stop
  { "extinguishing", "eaic", "stop_action" },                    // 28 stop
  { "ccu", "communication", "started" },                     // 30 started
  { "fmac", "communication", "not_authentic_task" }
};

void
Broker::on_packet(packet pkt)
{
  if (is_allowed(pkt, allowed)) {
    packet out_pkt = { pkt.from, pkt.to,   pkt.method,
                       pkt.val1, pkt.val2, pkt.val3 };
    string message = out_pkt.str();
    broker->publish(nullptr,
                    pkt.to.c_str(),
                    static_cast<int>(message.size()),
                    message.c_str());
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
