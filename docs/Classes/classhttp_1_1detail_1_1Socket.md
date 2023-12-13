---
title: http::Socket

---

# http::Socket






`#include <HTTPRequest.h>`

## Public Types

|                | Name           |
| -------------- | -------------- |
| using int | **[Type](Classes/classhttp_1_1detail_1_1Socket.md#using-type)**  |

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[Socket](Classes/classhttp_1_1detail_1_1Socket.md#function-socket)**(const [InternetProtocol](Namespaces/namespacehttp.md#enum-internetprotocol) internetProtocol) |
| | **[~Socket](Classes/classhttp_1_1detail_1_1Socket.md#function-~socket)**() |
| | **[Socket](Classes/classhttp_1_1detail_1_1Socket.md#function-socket)**([Socket](Classes/classhttp_1_1detail_1_1Socket.md) && other) |
| [Socket](Classes/classhttp_1_1detail_1_1Socket.md) & | **[operator=](Classes/classhttp_1_1detail_1_1Socket.md#function-operator=)**([Socket](Classes/classhttp_1_1detail_1_1Socket.md) && other) |
| void | **[connect](Classes/classhttp_1_1detail_1_1Socket.md#function-connect)**(const struct sockaddr * address, const socklen_t addressSize, const std::int64_t timeout) |
| std::size_t | **[send](Classes/classhttp_1_1detail_1_1Socket.md#function-send)**(const void * buffer, const std::size_t length, const std::int64_t timeout) |
| std::size_t | **[recv](Classes/classhttp_1_1detail_1_1Socket.md#function-recv)**(void * buffer, const std::size_t length, const std::int64_t timeout) |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| constexpr Type | **[invalid](Classes/classhttp_1_1detail_1_1Socket.md#variable-invalid)**  |

## Public Types Documentation

### using Type

```cpp
using http::detail::Socket::Type =  int;
```


## Public Functions Documentation

### function Socket

```cpp
inline explicit Socket(
    const InternetProtocol internetProtocol
)
```


### function ~Socket

```cpp
inline ~Socket()
```


### function Socket

```cpp
inline Socket(
    Socket && other
)
```


### function operator=

```cpp
inline Socket & operator=(
    Socket && other
)
```


### function connect

```cpp
inline void connect(
    const struct sockaddr * address,
    const socklen_t addressSize,
    const std::int64_t timeout
)
```


### function send

```cpp
inline std::size_t send(
    const void * buffer,
    const std::size_t length,
    const std::int64_t timeout
)
```


### function recv

```cpp
inline std::size_t recv(
    void * buffer,
    const std::size_t length,
    const std::int64_t timeout
)
```


## Public Attributes Documentation

### variable invalid

```cpp
static constexpr Type invalid = -1;
```


-------------------------------

Updated on 2023-12-13 at 13:54:01 +0300