
|     дата начала     |     дата конца      | длительность     | исполнитель  |
|:-------------------:|:-------------------:|:----------------:|:------------:|
| 2020y-03m-10d 04:15 | 2020y-03m-10d 23:30 | 19 hours, 15 min | Kartonagnick |

fixed
-----

Обертка для `cstdint`  

Предоставляет набор стандартных макросов:

```
#define INT8_MIN         (-127i8 - 1)
#define INT16_MIN        (-32767i16 - 1)
#define INT32_MIN        (-2147483647i32 - 1)
#define INT64_MIN        (-9223372036854775807i64 - 1)
#define INT8_MAX         127i8
#define INT16_MAX        32767i16
#define INT32_MAX        2147483647i32
#define INT64_MAX        9223372036854775807i64
#define UINT8_MAX        0xffui8
#define UINT16_MAX       0xffffui16
#define UINT32_MAX       0xffffffffui32
#define UINT64_MAX       0xffffffffffffffffui64
```

Предоставляет набор типов:  

```
tools::uint8_t ;
tools::uint16_t;
tools::uint32_t;
tools::uint64_t;

tools::int8_t  ; 
tools::int16_t ; 
tools::int32_t ; 
tools::int64_t ; 
```
Для новых компиляторов делегирует стандартному `cstdint`  

Для старых компиляторов, которые не поддерживают `cstdint`,
используется свой небольшой велосипед.  

Кроме алиасов, в поставке идут шаблоны для метапрограмминга:  
```
map_signed<Size>
map_unsigned<Size>
```

