#include "broker.h"
#include "utils.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <vector>

/*
 */

using namespace std;

string me = "fps";
vector<string> tasks = { "A", "B", "C", "D", "E", "F", "G" };
bool start_send = false;

Broker* broker;
void
Broker::on_message(const struct mosquitto_message* message)
{
  const std::string payload{ reinterpret_cast<char*>(message->payload),
                             static_cast<size_t>(message->payloadlen) };
  packet pkt = explode(payload);

  if (pkt.method == "started") {
    cout << pkt.method << " task at " << pkt.val1 << endl;
    start_send = false;
  } else if (pkt.method == "not_started") {
    cout << pkt.method << " task at " << pkt.val1 << endl;
    start_send = false;
  }
}

void start_task()
{
  if (!tasks.empty()) {
    string task = tasks.front();
    tasks.erase(tasks.begin());
    packet out_pkt = { me.c_str(), "communication", "start", task };
    broker->monitor(out_pkt);
    start_send = true;
  }
}


int
main(int argc, char** argv)
{
  cout << "start: " << me << endl;

  mosqpp::lib_init();
  broker = new Broker(me);
  broker->subscribe(NULL, me.c_str());
  broker->loop_start();


  while (1) {
    if (!start_send) {
      start_task();
    }
    cout << "working" << endl;
    sleep(10);
  }
  return 0;
}
