#include "broker.h"
#include "utils.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>

/*
 */

using namespace std;

string me = "movement";

Broker* broker;

bool
to_position(string task)
{
  cout << "going to position of: " << task;
  sleep(5); // TODO: logic of movement to coordinates
  return true;
}

void
Broker::on_packet(packet pkt)
{
  if (pkt.method == "move") {
    string task = pkt.val1;
    if (to_position(task)) {
      packet out_pkt = { me.c_str(), pkt.from, "done", task };
      broker->to_monitor(out_pkt);
    }
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
