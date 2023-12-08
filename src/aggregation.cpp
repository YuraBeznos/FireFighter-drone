#include "broker.h"
#include "utils.h"
#include <iostream>
#include <map>
#include <memory>
#include <mosquittopp.h>
#include <stdio.h>
#include <string>
#include <string_view>
#include <unistd.h>
#include <vector>

/*
 * Aggregation - Комплексирование
 */

using namespace std;

string me = "aggregation";
string coordinate = "0";

Broker* broker;
void
get_coordinates()
{
  packet out_pkt = { me.c_str(), "navigation", "get_coordinates" };
  broker->to_monitor(out_pkt);
}

void
set_coordinates(string new_coordinate)
{
  coordinate = new_coordinate;
}

bool
check_coordinates_validity(string gps, string ins)
{
  if (gps == ins) {
    set_coordinates(ins);
    return true;
  }
  return false;
}

void
Broker::on_packet(packet pkt)
{
  if (pkt.method == "get_coordinates") {
    packet out_pkt = { pkt.to, pkt.from, "coordinates", coordinate };
    broker->to_monitor(out_pkt);
  } else if (pkt.method == "coordinates") {
    check_coordinates_validity(pkt.val1, pkt.val2);
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
    get_coordinates();
    sleep(10);
  }
  mosqpp::lib_cleanup();
  return 0;
}
