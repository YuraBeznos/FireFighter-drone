#include "broker.h"
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>

/*
 * FMAC (Flight mission authenticity control) - Контроль аутентичности полётного задания
 */

using namespace std;

string me = "fmac";
vector<string> authentic_tasks = { "A", "C" };

Broker* broker;

bool
is_authentic_task(string task)
{
  if (find(authentic_tasks.begin(), authentic_tasks.end(), task) !=
      authentic_tasks.end()) {
    cout << "authentic task: " << task << endl;
    return true;
  }
  cout << "not authentic task: " << task << endl;
  return false;
}

void
Broker::on_packet(packet pkt)
{
  if (pkt.method == "start") {
    string task = pkt.val1;
    if (is_authentic_task(task)) {
      packet out_pkt = { me.c_str(), "eaic", "execute", task };
      broker->to_monitor(out_pkt);
      out_pkt = { me.c_str(), "ccu", "execute", task };
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
