#include <iostream>
#include<unistd.h>
#include<stdio.h>
#include "broker.h"
/*
 */

using namespace std;

void
Broker::on_message(const struct mosquitto_message* message)
{
}

int main(int argc, char** argv){
  cout << "start: " << argv[0] << endl;
  while(1) {
      cout << "working: " << argv[0] << endl;
      sleep(10);
  }
  return 0;
}
