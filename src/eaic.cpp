#include "broker.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>

/*
 * EAIC (extinguishing and ignition circuits controller) - Контроль активации цепей тушения и поджига
 */

using namespace std;

void
Broker::on_packet(packet pkt)
{
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
