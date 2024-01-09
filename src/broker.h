#ifndef _BROKER_H
#define _BROKER_H

#include "utils.h"
#include <exception>
#include <map>
#include <mosquittopp.h>
#include <string>

using namespace std;

class Broker : public mosqpp::mosquittopp
{
public:
  Broker(string id);
  ~Broker(){};
  void on_connect(int rc);
  void on_message(const struct mosquitto_message* message);
  void on_packet(packet pkt);
  void to_monitor(packet pkt);
  void on_subscribe(int mid, int qos_count, const int* granted_qos);
};

#endif // _BROKER_H
