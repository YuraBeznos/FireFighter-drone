#include "CivetServer.h"
#include "HTTPRequest.h"
#include "broker.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>

/*
 * Communication - Связь
 */

using namespace std;

#define PORT "8081"

string me = "communication";

Broker* broker;
void
Broker::on_packet(packet pkt)
{
  if (pkt.method == "started") {
    try {
      http::Request request{ "http://fps:8081/api?command=started&task=" +
                             pkt.val1 };
      const auto response = request.send("GET");

    } catch (const exception& e) {
      cerr << "Request to fps failed, error: " << e.what() << '\n';
    }
  } else if (pkt.method == "not_authentic_task") {
    try {
      http::Request request{
        "http://fps:8081/api?command=not_authentic_task&task=" + pkt.val1
      };
      const auto response = request.send("GET");

    } catch (const exception& e) {
      cerr << "Request to fps failed, error: " << e.what() << '\n';
    }
  }
}

class APIHandler : public CivetHandler
{
private:
  bool handleAll(const char* method,
                 CivetServer* server,
                 struct mg_connection* conn)
  {
    string task_ = "";
    string command_ = "";

    mg_printf(conn,
              "HTTP/1.1 200 OK\r\nContent-Type: "
              "text/html\r\nConnection: close\r\n\r\n");
    if (CivetServer::getParam(conn, "command", command_)) {
      if (command_ == "start" && CivetServer::getParam(conn, "task", task_)) {
        if (task_.size() > 0) {
          packet out_pkt = { me, "fmac", "start", task_ };
          broker->to_monitor(out_pkt);
          mg_printf(conn, "<p>task set to %s</p>", task_.c_str());
        }
      }
    }
    mg_printf(conn, "</body></html>\n");
    return true;
  }

public:
  bool handleGet(CivetServer* server, struct mg_connection* conn)
  {
    return handleAll("GET", server, conn);
  }
  bool handlePost(CivetServer* server, struct mg_connection* conn)
  {
    return handleAll("POST", server, conn);
  }
};

int
main(int argc, char** argv)
{
  cout << "start: " << me << endl;
  // civet
  mg_init_library(0);
  vector<string> cpp_options = { "listening_ports", PORT };

  CivetServer server(cpp_options);

  APIHandler h_api;
  server.addHandler("/api", h_api);

  cout << "Communication at http://localhost:" << PORT << endl;
  // end of civet

  mosqpp::lib_init();
  broker = new Broker(me);
  broker->subscribe(NULL, me.c_str());
  broker->loop_start();
  mosqpp::lib_cleanup();

  while (1) {
    cout << "working" << endl;
    sleep(10);
  }
  mg_exit_library();

  return 0;
}
