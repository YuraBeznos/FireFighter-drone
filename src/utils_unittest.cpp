#include "broker.h"
#include "utils.h"
#include "gtest/gtest.h"
#include <string>

void
Broker::on_packet(packet pkt)
{
}

TEST(test_utils, packet_three_values)
{
  packet pkt = { "from", "to", "method", "val1", "val2", "val3" };
  string csv = "from,to,method,val1,val2,val3";
  EXPECT_EQ(pkt.str(), csv);
}

TEST(test_utils, packet_two_values)
{
  packet pkt = { "from", "to", "method", "val1", "val2" };
  string csv = "from,to,method,val1,val2,";
  EXPECT_EQ(pkt.str(), csv);
}

TEST(test_utils, packet_one_value)
{
  packet pkt = { "from", "to", "method", "val1" };
  string csv = "from,to,method,val1,,";
  EXPECT_EQ(pkt.str(), csv);
}

TEST(test_utils, packet_no_values)
{
  packet pkt = { "from", "to", "method" };
  string csv = "from,to,method,,,";
  EXPECT_EQ(pkt.str(), csv);
}

TEST(test_utils, count)
{
  string csv = "from,to,method,val1,,";
  EXPECT_EQ(count(csv, ','), 5);
}

TEST(test_utils, explode)
{
  packet pkt = { "from", "to", "method", "val1" };
  string csv = "from,to,method,val1,,";
  EXPECT_EQ(explode(csv).str(), pkt.str());
}

int
main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
