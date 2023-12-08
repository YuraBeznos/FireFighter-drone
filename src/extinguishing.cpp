#include "broker.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>

/*
 * Extinguishing - Процедура тушения
 */

using namespace std;

string me = "extinguishing";
bool action = false;

Broker* broker;

void
proceed_action()
{
  action = true;
  cout << "action (fire/extinguishing) has been started" << endl;
}

void
stop_action()
{
  action = false;
  cout << "action (fire/extinguishing) has been stopped" << endl;
}

void
Broker::on_packet(packet pkt)
{
  if (pkt.method == "action") {
    packet out_pkt = { me.c_str(), "eaic", "action" };
    broker->to_monitor(out_pkt);
  } else if (pkt.method == "start_action") {
    proceed_action();

  } else if (pkt.method == "stop_action") {
    stop_action();
    packet out_pkt = { me.c_str(), "eaic", "stop_action" };
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
