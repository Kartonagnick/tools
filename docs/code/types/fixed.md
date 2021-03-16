
[P]: ../../images/progress.png
[V]: ../../images/success.png
[X]: ../../images/failed.png
[D]: ../../images/danger.png
[E]: ../../images/empty.png
[N]: ../../images/na.png

version 1.0.0
---

| **ID** | элементы           | версия | mingw 830, 720 710 | msvc 2019, 2017, 2015 | msvc 2013, 2012, 2010, 2008 |  
|:------:|:------------------:|:------:|:------------------:|:---------------------:|:---------------------------:|  
|  0000  | [fixed][00]        | 1.0.0  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![V]][VS-OLD]              |  
|  0001  | [defines][01]      | 1.0.0  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![V]][VS-OLD]              |  
|  0002  | [map_signed][02]   | 1.0.0  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![V]][VS-OLD]              |  
|  0003  | [map_unsigned][03] | 1.0.0  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![V]][VS-OLD]              |  
|  0004  | [limit][04]        | 1.0.0  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![V]][VS-OLD]              |  


[M]:       #fixed       "типы фиксированных размеров"  
[MINGW]:   #mingw-new   "поддержка компиляторов mingw"  
[VS-NEW]:  #msvc-new    "поддержка новых компиляторов msvc"  
[VS-OLD]:  #msvc-old    "поддержка старых компиляторов msvc"  

[00]: #fixed            "типы фиксированных размеров"  
[01]: #defines          "макросы-константы"  
[02]: #map_signed       "связь между знаковым типом и его размером"  
[03]: #map_unsigned     "связь между беззнаковым типом и его размером"  
[04]: #limit            "метафункция получения мак/мин значения интегральных целочисленных типов"  


корреляции:
| **ID** | **элементы**    |      include guard      | оригинальное расположение |  
|:------:|:---------------:|:-----------------------:|:-------------------------:|  
|  0006  | [remove_cv][98] | dTOOLS_REMOVE_CV_USED_  | tools/types/traits.hpp    |  
|  0007  | [is_signed][99] | dTOOLS_REMOVE_CV_USED_  | tools/types/traits.hpp    |  

[98]: #remove_cv    "мета-функция: удаляет квалификаторы типов"  
[99]: #is_signed    "мета-функция: определяет: является ли тип знаковым"  


fixed
-----
Данный модуль предоставляет типы с фиксированным размером.  
Если заголовок доступен, то используется `<cstdint>`.  

```
namespace tools
{
    using ::std::uint8_t ;
    using ::std::uint16_t;
    using ::std::uint32_t;
    using ::std::uint64_t;
        
    using ::std::int8_t  ; 
    using ::std::int16_t ; 
    using ::std::int32_t ; 
    using ::std::int64_t ; 
}
```

В противном случае используются собственные реализации типов:  

```
namespace tools
{
    typedef unsigned char    uint8_t ;
    typedef unsigned __int16 uint16_t;
    typedef unsigned __int32 uint32_t;
    typedef unsigned __int64 uint64_t;

    typedef signed char      int8_t  ;
    typedef __int16          int16_t ;
    typedef __int32          int32_t ;
    typedef __int64          int64_t ;
}

```


defines
-------

Макросы-константы.  
Если доступен `<cstdint>`, то используются стандартные макросы.  
Иначе используются самодельные аналогичные макросы:  

```
#define INT8_MIN         (-127 - 1)
#define INT16_MIN        (-32767 - 1)
#define INT32_MIN        (-2147483647 - 1)
#define INT64_MIN        (-9223372036854775807 - 1)

#define INT8_MAX         127
#define INT16_MAX        32767
#define INT32_MAX        2147483647
#define INT64_MAX        9223372036854775807

#define UINT8_MAX        0xff
#define UINT16_MAX       0xffff
#define UINT32_MAX       0xffffffff
#define UINT64_MAX       0xffffffffffffffff
```

map_signed
----------
Связь между типом и его размером:  

```
namespace tools
{
    template<size_t Size> struct map_signed;
    template<> struct map_signed<1>;
    template<> struct map_signed<2>;
    template<> struct map_signed<4>;
    template<> struct map_signed<8>;
}
```

map_unsigned
----------
Для беззнаковых:  

```
namespace tools
{
    template<size_t Size> struct map_unsigned;
    template<> struct map_unsigned<1>;
    template<> struct map_unsigned<2>;
    template<> struct map_unsigned<4>;
    template<> struct map_unsigned<8>;
}
```

Map позволяет получить лимит:  
  - максимальное/минимальное значение для данного типа.  

```
std::cout << map_signed<4>::max_value << '\n';
std::cout << map_signed<4>::min_value << '\n';
```

limit
-----
Метафункция получения лимитов для целочисленных интегральных типа:  

```
template <class t> struct limit;
```

Использование:
```
std::cout << limit<int>::max_value << '\n';
std::cout << limit<int>::min_value << '\n';
```

[![V]][M] особенности
---------------------

```
if dHAS_CPP11
    используются constexpr константы 
else 
    используются enum константы
```

```
if dHAS_CSTDINT
    используется <cstdint>
else 
    используется самодельная реализация
```

