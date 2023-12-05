#include "broker.h"
#include "utils.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
/*
 */

using namespace std;

static const string me = "navigation";
string coordinate = "0";

Broker* broker;

void
Broker::on_message(const struct mosquitto_message* message)
{
  const std::string payload{ reinterpret_cast<char*>(message->payload),
                             static_cast<size_t>(message->payloadlen) };
  packet pkt = explode(payload);
  if (pkt.method == "get_coordinates") {
    packet out_pkt = { pkt.to, pkt.from, "coordinates", coordinate };
    broker->monitor(out_pkt);
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
