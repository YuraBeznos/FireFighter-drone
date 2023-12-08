#include "broker.h"
#include "utils.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

/*
 */

using namespace std;

static const string me = "monitor";
Broker* broker;

/*
 * allowed communications list
 * "from", "to", "method"
 */
vector<tuple<string, string, string>> allowed = {
  { "fps", "communication", "" },                     // 1
  { "communication", "fmac", "" },                    // 2
  { "fmac", "eaic", "" },                             // 3
  { "fmac", "ccu", "" },                              // 4
  { "aggregation", "navigation", "get_coordinates" }, // 5, 16
  { "navigation", "aggregation", "coordinates" },     // 6, 17
  { "ccu", "aggregation", "" },                       // 9
  { "aggregation", "ccu", "" },                       // 10
  { "ccu", "movement", "" },                          // 11
  { "movement", "ccu", "" },                          // 13
  { "ccu", "extinguishing", "" },                     // 14 start
  { "extinguishing", "eaic", "" },                    // 15 start
  { "eaic", "aggregation", "" },                      // 18
  { "aggregation", "eaic", "" },                      // 19
  { "eaic", "extinguishing", "" },                    // 21
  { "ccu", "situation", "" },                         // 24
  { "situation", "ccu", "" },                         // 26
  { "ccu", "extinguishing", "" },                     // 27 stop
  { "extinguishing", "eaic", "" },                    // 28 stop
  { "ccu", "communication", "" },                     // 30 started
  { "communication", "fps", "started" }               // 31 started
};

bool
is_allowed(packet pkt)
{
  tuple<string, string, string> suspect;
  suspect = make_tuple(pkt.from, pkt.to, pkt.method);
  if (find(allowed.begin(), allowed.end(), suspect) != allowed.end()) {
    cout << "allowed from=" << pkt.from << ", to=" << pkt.to
         << ", method=" << pkt.method << endl;
    return true;
  }
  cout << "not allowed from=" << pkt.from << ", to=" << pkt.to
       << ", method=" << pkt.method << endl;
  return false;
}

void
Broker::on_packet(packet pkt)
{
  if (is_allowed(pkt)) {
    packet out_pkt = { pkt.from, pkt.to,   pkt.method,
                       pkt.val1, pkt.val2, pkt.val3 };
    string message = out_pkt.str();
    broker->publish(nullptr,
                    pkt.to.c_str(),
                    static_cast<int>(message.size()),
                    message.c_str());
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
