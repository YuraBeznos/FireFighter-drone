---
title: Broker

---

# Broker






`#include <broker.h>`

Inherits from mosqpp::mosquittopp

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[Broker](Classes/classBroker.md#function-broker)**(string id) |
| | **[~Broker](Classes/classBroker.md#function-~broker)**() |
| void | **[on_connect](Classes/classBroker.md#function-on-connect)**(int rc) |
| void | **[on_message](Classes/classBroker.md#function-on-message)**(const struct mosquitto_message * message) |
| void | **[on_packet](Classes/classBroker.md#function-on-packet)**([packet](Classes/structpacket.md) pkt) |
| void | **[to_monitor](Classes/classBroker.md#function-to-monitor)**([packet](Classes/structpacket.md) pkt) |
| void | **[on_subscribe](Classes/classBroker.md#function-on-subscribe)**(int mid, int qos_count, const int * granted_qos) |

## Public Functions Documentation

### function Broker

```cpp
Broker(
    string id
)
```


### function ~Broker

```cpp
inline ~Broker()
```


### function on_connect

```cpp
void on_connect(
    int rc
)
```


### function on_message

```cpp
void on_message(
    const struct mosquitto_message * message
)
```


### function on_packet

```cpp
void on_packet(
    packet pkt
)
```


### function to_monitor

```cpp
void to_monitor(
    packet pkt
)
```


### function on_subscribe

```cpp
void on_subscribe(
    int mid,
    int qos_count,
    const int * granted_qos
)
```


-------------------------------

Updated on 2023-12-10 at 12:45:08 +0300