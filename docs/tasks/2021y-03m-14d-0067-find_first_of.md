
|     дата начала     |     дата конца      | длительность    | исполнитель  |
|:-------------------:|:-------------------:|:---------------:|:------------:|
| 2020y-03m-14d 20:10 | 2020y-03m-14d 23:55 | 3 hours, 45 min | Kartonagnick |

find_first_of
----

Добавляем модуль: `algorithm`
 - tools\algorithm\find_first_of.hpp

синопсис:
```
template <class it1, class it2>
it1 find_first_of(const it1& b1, const it1& e1, const it2& b2, const it2& e2)
    noexcept ( noexcept(*b1 == *b2) )
```

Проверяем сборку:
 - [x] готово

