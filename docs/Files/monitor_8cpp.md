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
  { "fps", "communication", "" },                     
  { "communication", "fmac", "" },                    
  { "fmac", "eaic", "" },                             
  { "fmac", "ccu", "" },                              
  { "aggregation", "navigation", "get_coordinates" }, 
  { "navigation", "aggregation", "coordinates" },     
  { "ccu", "aggregation", "" },                       
  { "aggregation", "ccu", "" },                       
  { "ccu", "movement", "" },                          
  { "movement", "ccu", "" },                          
  { "ccu", "extinguishing", "" },                     
  { "extinguishing", "eaic", "" },                    
  { "eaic", "aggregation", "" },                      
  { "aggregation", "eaic", "" },                      
  { "eaic", "extinguishing", "" },                    
  { "ccu", "situation", "" },                         
  { "situation", "ccu", "" },                         
  { "ccu", "extinguishing", "" },                     
  { "extinguishing", "eaic", "" },                    
  { "ccu", "communication", "" },                     
  { "communication", "fps", "started" }               
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
  { "fps", "communication", "" },                     // 1
  { "communication", "fmac", "" },                    // 2
  { "fmac", "eaic", "" },                             // 3
  { "fmac", "ccu", "" },                              // 4
  { "aggregation", "navigation", "get_coordinates" }, // 5, 16
  { "navigation", "aggregation", "coordinates" },     // 6, 17
  { "ccu", "aggregation", "" },                       // 9
  { "aggregation", "ccu", "" },                       // 10
  { "ccu", "movement", "" },                          // 11
  { "movement", "ccu", "" },                          // 13
  { "ccu", "extinguishing", "" },                     // 14 start
  { "extinguishing", "eaic", "" },                    // 15 start
  { "eaic", "aggregation", "" },                      // 18
  { "aggregation", "eaic", "" },                      // 19
  { "eaic", "extinguishing", "" },                    // 21
  { "ccu", "situation", "" },                         // 24
  { "situation", "ccu", "" },                         // 26
  { "ccu", "extinguishing", "" },                     // 27 stop
  { "extinguishing", "eaic", "" },                    // 28 stop
  { "ccu", "communication", "" },                     // 30 started
  { "communication", "fps", "started" }               // 31 started
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

Updated on 2023-12-10 at 12:51:12 +0300
