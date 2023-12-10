---
title: src/broker.cpp

---

# src/broker.cpp






## Source code

```cpp
#include "broker.h"
#include <iostream>

using namespace std;

Broker::Broker(string clientId)
  : mosquittopp(clientId.c_str())
{
  const int keepalive = 60;
  const int port = 1883;
  string host = "broker";
  cout << "Connecting to broker: " << host << ":" << port << endl;
  connect(host.c_str(), port, keepalive);
}

void
Broker::on_connect(int rc)
{
  if (rc == 0) {
    cout << "Connected to broker" << endl;
  } else {
    cerr << "Connection to broker failed" << endl;
  }
}

void
Broker::on_message(const struct mosquitto_message* message)
{
  const std::string payload{ reinterpret_cast<char*>(message->payload),
                             static_cast<size_t>(message->payloadlen) };
  packet pkt = explode(payload);
  on_packet(pkt);
}

void
Broker::to_monitor(packet pkt)
{
  string message = pkt.str();
  publish(
    nullptr, "monitor", static_cast<int>(message.size()), message.c_str());
}

void
Broker::on_subscribe(int mid, int qos_count, const int* granted_qos)
{
  cout << "Subscribed!" << endl;
}
```


-------------------------------

Updated on 2023-12-10 at 12:51:12 +0300
