---
title: http::Request

---

# http::Request






`#include <HTTPRequest.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[Request](Classes/classhttp_1_1Request.md#function-request)**(const std::string & uriString, const [InternetProtocol](Namespaces/namespacehttp.md#enum-internetprotocol) protocol =[InternetProtocol::v4](Namespaces/namespacehttp.md#enumvalue-v4)) |
| [Response](Classes/structhttp_1_1Response.md) | **[send](Classes/classhttp_1_1Request.md#function-send)**(const std::string & method ="GET", const std::string & body ="", const [HeaderFields](Namespaces/namespacehttp.md#using-headerfields) & headerFields ={}, const std::chrono::milliseconds timeout =std::chrono::milliseconds{-1}) |
| [Response](Classes/structhttp_1_1Response.md) | **[send](Classes/classhttp_1_1Request.md#function-send)**(const std::string & method, const std::vector< uint8_t > & body, const [HeaderFields](Namespaces/namespacehttp.md#using-headerfields) & headerFields ={}, const std::chrono::milliseconds timeout =std::chrono::milliseconds{-1}) |

## Public Functions Documentation

### function Request

```cpp
inline explicit Request(
    const std::string & uriString,
    const InternetProtocol protocol =InternetProtocol::v4
)
```


### function send

```cpp
inline Response send(
    const std::string & method ="GET",
    const std::string & body ="",
    const HeaderFields & headerFields ={},
    const std::chrono::milliseconds timeout =std::chrono::milliseconds{-1}
)
```


### function send

```cpp
inline Response send(
    const std::string & method,
    const std::vector< uint8_t > & body,
    const HeaderFields & headerFields ={},
    const std::chrono::milliseconds timeout =std::chrono::milliseconds{-1}
)
```


-------------------------------

Updated on 2023-12-13 at 13:54:01 +0300