#include "broker.h"
#include "utils.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>

/*
 * Situation control - Контроль обстановки
 */

using namespace std;

string me = "situation";
bool running = true;

Broker* broker;
void
Broker::on_packet(packet pkt)
{
  if (pkt.method == "is_action_running") {
    if (running) {
      packet out_pkt = { me.c_str(), pkt.from, "action_is_running" };
      broker->to_monitor(out_pkt);
    }
  }
}

int
main(int argc, char** argv)
{
  mosqpp::lib_init();
  broker = new Broker(me);
  broker->subscribe(NULL, me.c_str());
  broker->loop_start();

  cout << "start: " << argv[0] << endl;
  while (1) {
    cout << "working: " << argv[0] << endl;
    sleep(10);
  }
  return 0;
}
