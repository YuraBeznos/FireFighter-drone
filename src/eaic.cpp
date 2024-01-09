#include "broker.h"
#include <iostream>
#include <unistd.h>

/*
 * EAIC (extinguishing and ignition circuits controller) - Контроль активации
 * цепей тушения и поджига
 */

using namespace std;
string me = "eaic";

string task;

bool
action_is_allowed(string coordinates)
{
  return true;
}

void
position_control()
{
}

Broker* broker;
void
Broker::on_packet(packet pkt)
{
  if (pkt.method == "execute") { // step 4
    task = pkt.val1;
  } else if (pkt.method == "confirm_action") {                 // step 15
    packet out_pkt = { me, "aggregation", "get_coordinates" }; // step 18
    broker->to_monitor(out_pkt);
  } else if (pkt.method == "coordinates") {
    if (action_is_allowed(pkt.val1)) {
      packet out_pkt = { me, "extinguishing", "start_action" }; // step 21
      broker->to_monitor(out_pkt);
      position_control(); // 23
    }
  } else if (pkt.method == "stop_action") { // 28
    task = "";                              // 29
  }
}

int
main(int argc, char** argv)
{
  cout << "start: " << argv[0] << endl;
  while (1) {
    cout << "working: " << argv[0] << endl;
    sleep(10);
  }
  return 0;
}
