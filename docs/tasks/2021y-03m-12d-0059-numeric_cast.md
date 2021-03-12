
|     дата начала     |     дата конца      | длительность    | исполнитель  |
|:-------------------:|:-------------------:|:---------------:|:------------:|
| 2020y-03m-12d 20:00 | 2020y-03m-11d 23:25 | 3 hours, 25 min | Kartonagnick |

numeric_cast
-----

Модуль состоит из трех функций:

Возвращает true, если можно выполнить каст без потерь
```
template<class ret, class from>
bool can_numeric_cast(const from) noexcept;
```

assert-защита каста 
```
template<class ret, class from>
ret assert_numeric_cast(const from val) noexcept;
```

exception-защита каста
```
template<class ret, class from>
ret numeric_cast(const from val);
```

Если компилятор поддерживает constexpr, 
функции то функции могут отработать времени компиляции.  

План:  
 - [x] добавляем тесты рантайма  
 - [x] добавляем тесты времени компиляции  
 - [x] проверяем старые компиляторы  
 - [x] проверяем новые компиляторы  
