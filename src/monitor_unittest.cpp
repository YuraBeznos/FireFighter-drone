#include "broker.h"
#include "utils.h"
#include "gtest/gtest.h"

void
Broker::on_packet(packet pkt)
{
}

TEST(test_utils, monitor_pkt_is_allowed)
{
  packet pkt = { "navigation", "aggregation", "coordinates" };
  EXPECT_EQ(is_allowed(pkt), true);
}

TEST(test_utils, monitor_pkt_is_not_allowed)
{
  packet pkt = { "navigation", "ccu", "coordinates" };
  EXPECT_EQ(is_allowed(pkt), false);
}

int
main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
