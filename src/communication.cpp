#include "broker.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>

/*
 * Communication - Связь
 */

using namespace std;
string me = "communication";

Broker* broker;
void
Broker::on_packet(packet pkt)
{
  if (pkt.method == "start" && pkt.from == "fps") {
    packet out_pkt = { me, "fmac", pkt.method, pkt.val1 };
    broker->to_monitor(out_pkt);
  } else if (pkt.method == "started" && pkt.from == "ccu") {
    packet out_pkt = { me, "fps", pkt.method, pkt.val1 };
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
