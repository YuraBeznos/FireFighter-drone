#include "CivetServer.h"
#include "HTTPRequest.h"
#include "broker.h"
#include "utils.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <vector>

/*
 * FPS (Flight Plan Server) - Источник полётного задания
 */

using namespace std;

#define PORT "8081"

string me = "fps";
vector<vector<string>> tasks;
bool start_send = false;
string task = "";

Broker* broker;
void
Broker::on_packet(packet pkt)
{
}

class MainHandler : public CivetHandler
{
public:
  bool handleGet(CivetServer* server, struct mg_connection* conn)
  {
    mg_printf(conn,
              "HTTP/1.1 200 OK\r\nContent-Type: "
              "text/html\r\nConnection: close\r\n\r\n");
    mg_printf(
      conn,
      "<html><head><meta http-equiv=\"refresh\" content=\"5\"><body>\r\n");
    if (tasks.size() > 0) {
      mg_printf(conn, "<h2>Tasks status:</h2><pre>\r\n");
      for (auto i : tasks) {
        mg_printf(conn, "Task %s: %s\r\n", i[0].c_str(), i[1].c_str());
      }
      mg_printf(conn, "</pre>\r\n");
    }
    mg_printf(conn, "<h2>FPS interface</h2>\r\n");
    mg_printf(conn,
              "<form action=\"api\" method=\"get\">"
              "To start the task A (allowed)"
              "<input name=\"task\" value=\"A\"\\>"
              "<input type=\"submit\" value=\"start\" "
              "name=\"command\" \\>click here</form>\r\n");
    mg_printf(conn,
              "<form action=\"api\" method=\"get\">"
              "To start the task B (not allowed)"
              "<input name=\"task\" value=\"B\" \\>"
              "<input type=\"submit\" value=\"start\" "
              "name=\"command\" \\>click here</form>\r\n");
    mg_printf(conn, "</body></html>\r\n");
    return true;
  }
};

class APIHandler : public CivetHandler
{
private:
  bool handleAll(const char* method,
                 CivetServer* server,
                 struct mg_connection* conn)
  {
    string task_ = "";
    string command_ = "";
    if (CivetServer::getParam(conn, "tasks_log", command_)) {
      mg_printf(conn,
                "HTTP/1.1 200 OK\r\nContent-Type: "
                "text/plain\r\nConnection: close\r\n\r\n");

      if (tasks.size() > 0) {
        for (auto i : tasks) {
          mg_printf(conn, "Task %s: %s\r\n", i[0].c_str(), i[1].c_str());
        }
        return true;
      } else {
        mg_printf(conn, "Tasks log is empty");
        return true;
      }
    }

    mg_printf(conn,
              "HTTP/1.1 200 OK\r\nContent-Type: "
              "text/html\r\nConnection: close\r\n\r\n");

    mg_printf(conn, "<html>");
    mg_printf(conn, "<meta http-equiv=\"refresh\" content=\"2; URL=/\" />");
    mg_printf(conn, "<body>");
    if (CivetServer::getParam(conn, "command", command_)) {
      if (!start_send && command_ == "start" &&
          CivetServer::getParam(conn, "task", task_)) {
        if (task_.size() > 0) {
          try {
            http::Request request{
              "http://communication:8081/api?command=start&task=" + task_
            };
            const auto response = request.send("GET");
          } catch (const exception& e) {
            cerr << "Request failed, error: " << e.what() << '\n';
            mg_printf(conn, "<p>An issue with accessing communication</p>\r\n");
            mg_printf(conn, "</body></html>\n");
            return true;
          }

          start_send = true;
          task = task_;
          tasks.push_back({ task, "in progress" });
          mg_printf(conn, "<p>task set to %s</p>", task.c_str());
        }
      } else if (start_send && command_ == "started" &&
                 CivetServer::getParam(conn, "task", task_)) {
        if (task_.size() > 0) {
          tasks.push_back({ task, "started" });
          mg_printf(conn, "<p>task %s has been started</p>", task.c_str());
          start_send = false;
          task = "";
        }
      } else if (start_send && command_ == "not_authentic_task" &&
                 CivetServer::getParam(conn, "task", task_)) {
        if (task_.size() > 0) {
          tasks.push_back({ task, "not authentic, not able to start" });
          start_send = false;
          task = "";
        }
      } else {
        mg_printf(conn, "<p>task already in progress:  %s</p>", task.c_str());
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

  MainHandler h_main;
  server.addHandler("/", h_main);

  APIHandler h_api;
  server.addHandler("/api", h_api);

  cout << "FPS at http://localhost:" << PORT << endl;
  // end of civet

  while (1) {
    cout << "working" << endl;
    sleep(10);
  }

  mg_exit_library();

  return 0;
}
