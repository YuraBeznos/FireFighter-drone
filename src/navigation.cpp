#include "broker.h"
#include "utils.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>

/*
 * Navigation system - Навигация GNSS + ИНС
 */

using namespace std;

static const string me = "navigation";
string coordinate = "0";

Broker* broker;

void
Broker::on_packet(packet pkt)
{
  if (pkt.method == "get_coordinates") {
    packet out_pkt = { pkt.to, pkt.from, "coordinates", coordinate };
    broker->to_monitor(out_pkt);
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
