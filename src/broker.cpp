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
Broker::monitor(packet pkt)
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
