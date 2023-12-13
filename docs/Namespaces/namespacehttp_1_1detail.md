---
title: http::detail

---

# http::detail



## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[http::Socket](Classes/classhttp_1_1detail_1_1Socket.md)**  |

## Functions

|                | Name           |
| -------------- | -------------- |
| constexpr int | **[getAddressFamily](Namespaces/namespacehttp_1_1detail.md#function-getaddressfamily)**(const [InternetProtocol](Namespaces/namespacehttp.md#enum-internetprotocol) internetProtocol) |
| char | **[toLower](Namespaces/namespacehttp_1_1detail.md#function-tolower)**(const char c) |
| template <class T \> <br>T | **[toLower](Namespaces/namespacehttp_1_1detail.md#function-tolower)**(const T & s) |
| template <typename C \> <br>constexpr bool | **[isWhiteSpaceChar](Namespaces/namespacehttp_1_1detail.md#function-iswhitespacechar)**(const C c) |
| template <typename C \> <br>constexpr bool | **[isDigitChar](Namespaces/namespacehttp_1_1detail.md#function-isdigitchar)**(const C c) |
| template <typename C \> <br>constexpr bool | **[isAlphaChar](Namespaces/namespacehttp_1_1detail.md#function-isalphachar)**(const C c) |
| template <typename C \> <br>constexpr bool | **[isTokenChar](Namespaces/namespacehttp_1_1detail.md#function-istokenchar)**(const C c) |
| template <typename C \> <br>constexpr bool | **[isVisibleChar](Namespaces/namespacehttp_1_1detail.md#function-isvisiblechar)**(const C c) |
| template <typename C \> <br>constexpr bool | **[isObsoleteTextChar](Namespaces/namespacehttp_1_1detail.md#function-isobsoletetextchar)**(const C c) |
| template <class Iterator \> <br>Iterator | **[skipWhiteSpaces](Namespaces/namespacehttp_1_1detail.md#function-skipwhitespaces)**(const Iterator begin, const Iterator end) |
| template <typename T ,typename C ,typename std::enable_if< std::is_unsigned< T >::value >::type *  =nullptr\> <br>constexpr T | **[digitToUint](Namespaces/namespacehttp_1_1detail.md#function-digittouint)**(const C c) |
| template <typename T ,typename C ,typename std::enable_if< std::is_unsigned< T >::value >::type *  =nullptr\> <br>constexpr T | **[hexDigitToUint](Namespaces/namespacehttp_1_1detail.md#function-hexdigittouint)**(const C c) |
| template <class Iterator \> <br>[Uri](Classes/structhttp_1_1Uri.md) | **[parseUri](Namespaces/namespacehttp_1_1detail.md#function-parseuri)**(const Iterator begin, const Iterator end) |
| template <class Iterator \> <br>std::pair< Iterator, [Version](Classes/structhttp_1_1Version.md) > | **[parseVersion](Namespaces/namespacehttp_1_1detail.md#function-parseversion)**(const Iterator begin, const Iterator end) |
| template <class Iterator \> <br>std::pair< Iterator, std::uint16_t > | **[parseStatusCode](Namespaces/namespacehttp_1_1detail.md#function-parsestatuscode)**(const Iterator begin, const Iterator end) |
| template <class Iterator \> <br>std::pair< Iterator, std::string > | **[parseReasonPhrase](Namespaces/namespacehttp_1_1detail.md#function-parsereasonphrase)**(const Iterator begin, const Iterator end) |
| template <class Iterator \> <br>std::pair< Iterator, std::string > | **[parseToken](Namespaces/namespacehttp_1_1detail.md#function-parsetoken)**(const Iterator begin, const Iterator end) |
| template <class Iterator \> <br>std::pair< Iterator, std::string > | **[parseFieldValue](Namespaces/namespacehttp_1_1detail.md#function-parsefieldvalue)**(const Iterator begin, const Iterator end) |
| template <class Iterator \> <br>std::pair< Iterator, std::string > | **[parseFieldContent](Namespaces/namespacehttp_1_1detail.md#function-parsefieldcontent)**(const Iterator begin, const Iterator end) |
| template <class Iterator \> <br>std::pair< Iterator, [HeaderField](Namespaces/namespacehttp.md#using-headerfield) > | **[parseHeaderField](Namespaces/namespacehttp_1_1detail.md#function-parseheaderfield)**(const Iterator begin, const Iterator end) |
| template <class Iterator \> <br>std::pair< Iterator, [Status](Classes/structhttp_1_1Status.md) > | **[parseStatusLine](Namespaces/namespacehttp_1_1detail.md#function-parsestatusline)**(const Iterator begin, const Iterator end) |
| template <typename T ,class Iterator ,typename std::enable_if< std::is_unsigned< T >::value >::type *  =nullptr\> <br>T | **[stringToUint](Namespaces/namespacehttp_1_1detail.md#function-stringtouint)**(const Iterator begin, const Iterator end) |
| template <typename T ,class Iterator ,typename std::enable_if< std::is_unsigned< T >::value >::type *  =nullptr\> <br>T | **[hexStringToUint](Namespaces/namespacehttp_1_1detail.md#function-hexstringtouint)**(const Iterator begin, const Iterator end) |
| std::string | **[encodeRequestLine](Namespaces/namespacehttp_1_1detail.md#function-encoderequestline)**(const std::string & method, const std::string & target) |
| std::string | **[encodeHeaderFields](Namespaces/namespacehttp_1_1detail.md#function-encodeheaderfields)**(const [HeaderFields](Namespaces/namespacehttp.md#using-headerfields) & headerFields) |
| template <class Iterator \> <br>std::string | **[encodeBase64](Namespaces/namespacehttp_1_1detail.md#function-encodebase64)**(const Iterator begin, const Iterator end) |
| std::vector< std::uint8_t > | **[encodeHtml](Namespaces/namespacehttp_1_1detail.md#function-encodehtml)**(const [Uri](Classes/structhttp_1_1Uri.md) & uri, const std::string & method, const std::vector< uint8_t > & body, [HeaderFields](Namespaces/namespacehttp.md#using-headerfields) headerFields) |


## Functions Documentation

### function getAddressFamily

```cpp
constexpr int getAddressFamily(
    const InternetProtocol internetProtocol
)
```


### function toLower

```cpp
inline char toLower(
    const char c
)
```


### function toLower

```cpp
template <class T >
T toLower(
    const T & s
)
```


### function isWhiteSpaceChar

```cpp
template <typename C >
constexpr bool isWhiteSpaceChar(
    const C c
)
```


### function isDigitChar

```cpp
template <typename C >
constexpr bool isDigitChar(
    const C c
)
```


### function isAlphaChar

```cpp
template <typename C >
constexpr bool isAlphaChar(
    const C c
)
```


### function isTokenChar

```cpp
template <typename C >
constexpr bool isTokenChar(
    const C c
)
```


### function isVisibleChar

```cpp
template <typename C >
constexpr bool isVisibleChar(
    const C c
)
```


### function isObsoleteTextChar

```cpp
template <typename C >
constexpr bool isObsoleteTextChar(
    const C c
)
```


### function skipWhiteSpaces

```cpp
template <class Iterator >
Iterator skipWhiteSpaces(
    const Iterator begin,
    const Iterator end
)
```


### function digitToUint

```cpp
template <typename T ,
typename C ,
typename std::enable_if< std::is_unsigned< T >::value >::type *  =nullptr>
constexpr T digitToUint(
    const C c
)
```


### function hexDigitToUint

```cpp
template <typename T ,
typename C ,
typename std::enable_if< std::is_unsigned< T >::value >::type *  =nullptr>
constexpr T hexDigitToUint(
    const C c
)
```


### function parseUri

```cpp
template <class Iterator >
Uri parseUri(
    const Iterator begin,
    const Iterator end
)
```


### function parseVersion

```cpp
template <class Iterator >
std::pair< Iterator, Version > parseVersion(
    const Iterator begin,
    const Iterator end
)
```


### function parseStatusCode

```cpp
template <class Iterator >
std::pair< Iterator, std::uint16_t > parseStatusCode(
    const Iterator begin,
    const Iterator end
)
```


### function parseReasonPhrase

```cpp
template <class Iterator >
std::pair< Iterator, std::string > parseReasonPhrase(
    const Iterator begin,
    const Iterator end
)
```


### function parseToken

```cpp
template <class Iterator >
std::pair< Iterator, std::string > parseToken(
    const Iterator begin,
    const Iterator end
)
```


### function parseFieldValue

```cpp
template <class Iterator >
std::pair< Iterator, std::string > parseFieldValue(
    const Iterator begin,
    const Iterator end
)
```


### function parseFieldContent

```cpp
template <class Iterator >
std::pair< Iterator, std::string > parseFieldContent(
    const Iterator begin,
    const Iterator end
)
```


### function parseHeaderField

```cpp
template <class Iterator >
std::pair< Iterator, HeaderField > parseHeaderField(
    const Iterator begin,
    const Iterator end
)
```


### function parseStatusLine

```cpp
template <class Iterator >
std::pair< Iterator, Status > parseStatusLine(
    const Iterator begin,
    const Iterator end
)
```


### function stringToUint

```cpp
template <typename T ,
class Iterator ,
typename std::enable_if< std::is_unsigned< T >::value >::type *  =nullptr>
T stringToUint(
    const Iterator begin,
    const Iterator end
)
```


### function hexStringToUint

```cpp
template <typename T ,
class Iterator ,
typename std::enable_if< std::is_unsigned< T >::value >::type *  =nullptr>
T hexStringToUint(
    const Iterator begin,
    const Iterator end
)
```


### function encodeRequestLine

```cpp
inline std::string encodeRequestLine(
    const std::string & method,
    const std::string & target
)
```


### function encodeHeaderFields

```cpp
inline std::string encodeHeaderFields(
    const HeaderFields & headerFields
)
```


### function encodeBase64

```cpp
template <class Iterator >
std::string encodeBase64(
    const Iterator begin,
    const Iterator end
)
```


### function encodeHtml

```cpp
inline std::vector< std::uint8_t > encodeHtml(
    const Uri & uri,
    const std::string & method,
    const std::vector< uint8_t > & body,
    HeaderFields headerFields
)
```






-------------------------------

Updated on 2023-12-13 at 13:54:01 +0300