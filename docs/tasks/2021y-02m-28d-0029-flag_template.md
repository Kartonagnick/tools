
|     дата начала     |     дата конца      | длительность  | исполнитель  |
|:-------------------:|:-------------------:|:-------------:|:------------:|
| 2020y-02m-28d 01:00 | 2020y-02m-28d 02:50 | 1 hour 50 min | Kartonagnick |


flag/template
-------------

Заголовок `tools/flag/template.hpp`  
Предоставляет возможность работать с флагами времени компиляции.  
Используется в метапрограммировании.  

Содержит набор свободных функций:  
  - [x] `tools::add_flag<flag, flags>::value`  
  - [x] `tools::del_flag<flag, flags>::value`  
  - [x] `tools::has_any_flag<flag, flags>::value`  
  - [x] `tools::has_flag<flag, flags>::value`  

План:  
  - [x] добавляем `tools/flag/template.hpp`  
  - [ ] добавляем тесты для `size_t`.  
  - [ ] добавляем тесты для `int`.  
  - [ ] проверяем сборку.  



