#include "broker.h"
#include "utils.h"
#include "policies.h"
#include <iostream>
#include <string>

/*
 * Monitor - контроль взаимодействия осуществляет компонент под названием "монитор безопасности"
 */

using namespace std;

static const string me = "monitor";
Broker* broker;

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
