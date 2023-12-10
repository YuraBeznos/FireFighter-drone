---
title: src/monitor_unittest.cpp

---

# src/monitor_unittest.cpp



## Functions

|                | Name           |
| -------------- | -------------- |
| | **[TEST](Files/monitor__unittest_8cpp.md#function-test)**(test_utils , monitor_pkt_is_allowed ) |
| | **[TEST](Files/monitor__unittest_8cpp.md#function-test)**(test_utils , monitor_pkt_is_not_allowed ) |
| int | **[main](Files/monitor__unittest_8cpp.md#function-main)**(int argc, char ** argv) |

## Attributes

|                | Name           |
| -------------- | -------------- |
| vector< tuple< string, string, string > > | **[allowed](Files/monitor__unittest_8cpp.md#variable-allowed)**  |


## Functions Documentation

### function TEST

```cpp
TEST(
    test_utils ,
    monitor_pkt_is_allowed 
)
```


### function TEST

```cpp
TEST(
    test_utils ,
    monitor_pkt_is_not_allowed 
)
```


### function main

```cpp
int main(
    int argc,
    char ** argv
)
```



## Attributes Documentation

### variable allowed

```cpp
vector< tuple< string, string, string > > allowed = {
  { "aggregation", "navigation", "get_coordinates" }, 
  { "navigation", "aggregation", "coordinates" } 
};
```



## Source code

```cpp
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
```


-------------------------------

Updated on 2023-12-10 at 12:51:12 +0300
