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
  { "aggregation", "navigation", "get_coordinates" },
  { "navigation", "aggregation", "coordinates" }
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
