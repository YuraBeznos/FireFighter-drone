#include "broker.h"
#include "utils.h"
#include "gtest/gtest.h"
#include <string>

void
Broker::on_packet(packet pkt)
{
}

/*
 * allowed communications list
 * "from", "to", "method"
 */
vector<tuple<string, string, string>> allowed = {
  { "aggregation", "navigation", "get_coordinates" }, 
  { "navigation", "aggregation", "coordinates" } 
};

TEST(test_utils, monitor_pkt_is_allowed)
{
  packet pkt = { "navigation", "aggregation", "coordinates" };
  EXPECT_EQ(is_allowed(pkt, allowed), true);
}

TEST(test_utils, monitor_pkt_is_not_allowed)
{
  packet pkt = { "navigation", "ccu", "coordinates" };
  EXPECT_EQ(is_allowed(pkt, allowed), false);
}

int
main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
