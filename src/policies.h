#include <string>
#include <tuple>
#include <vector>

/*
 * Policies - политики безопасности
 */

using namespace std;

/*
 * allowed communications list
 * "from", "to", "method"
 */
static vector<tuple<string, string, string>> allowed = {
  { "communication", "fmac", "start" },               // 2
  { "fmac", "eaic", "execute" },                      // 3
  { "fmac", "ccu", "execute" },                       // 4
  { "aggregation", "navigation", "get_coordinates" }, // 5, 16
  { "navigation", "aggregation", "coordinates" },     // 6, 17
  { "ccu", "aggregation", "get_coordinates" },        // 9
  { "aggregation", "ccu", "coordinates" },            // 10
  { "ccu", "movement", "move" },                      // 11
  { "movement", "ccu", "done" },                      // 13
  { "ccu", "extinguishing", "start_action" },         // 14 start
  { "extinguishing", "eaic", "confirm_action" },      // 15 start
  { "eaic", "aggregation", "get_coordinates" },       // 18
  { "aggregation", "eaic", "coordinates" },           // 19
  { "eaic", "extinguishing", "start_action" },        // 21
  { "ccu", "situation", "is_action_running" },        // 24
  { "situation", "ccu", "action_is_running" },        // 26
  { "ccu", "extinguishing", "stop_action" },          // 27 stop
  { "extinguishing", "eaic", "stop_action" },         // 28 stop
  { "ccu", "communication", "started" },              // 30 started
  { "fmac", "communication", "not_authentic_task" }
};
