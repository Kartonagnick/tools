
[![logo](../logo.png)](../home.md "for developers") 

[P1]: ../images/progress.png  "2021y-03m-11d"
[X1]: ../images/failed.png    "2021y-03m-11d"
[V1]: ../images/success.png   "2021y-03m-11d"
[E1]: ../images/nodata.png    "2021y-03m-11d"
[N1]: ../images/na.png        "2021y-03m-11d"

version 0.2.4

| **ID** | **компоненты**       |  used            |      include guard      |  
|:------:|:--------------------:|:----------------:|:-----------------------:|  
|  0000  | [dfor_lvalue][00]    | utf8.hpp         | dTOOLS_FOR_LVALUE_USED_ |  
|  0001  | [str_length][01]     | utf8_win.cpp     |                         |  
|  0002  | [str_length][01]     | utf8_commin.cpp  |                         |  
|  0003  | [int_to_string_][03] | errno.cpp        |                         |  
|  0004  | [tokenizePath][04]   | seh_path.hpp     |                         |  
|  0005  | [shortPath][05]      | seh_path.hpp     |                         |  
|  0006  | [remove_cv][06]      | types/fixed.hpp  | dTOOLS_REMOVE_CV_USED_  |  
|  0007  | [is_signed][07]      | types/fixed.hpp  | dTOOLS_IS_SIGNED_USED_  |  


| **ID** | **макрос**               |  used       |        описание         |  
|:------:|:------------------------:|:-----------:|:-----------------------:|  
|  0000  | [dDISABLE_SAFE_CAST][00] | numeric.hpp | отключает проверки      |  
|  0001  | [dFORBID_SAFE_CAST][01]  | numeric.hpp | запрещает использование |  

[00]: ../code/numeric.md/#safe_cast "отключает проверку правомерности каста в функциях safe_cast/assert_safe_cast" 
[01]: ../code/numeric.md/#safe_cast "запрещает использовать функции safe_cast/assert_safe_cast" 

<br />
<br />


dDISABLE_SAFE_CAST
---
Если активирован:  

```
#define dDISABLE_SAFE_CAST
```
Тогда отключает все проверки в функциях:  
  - assert_safe_cast  
  - safe_cast  

<br />
<br />


dFORBID_SAFE_CAST
---
Если активирован:  

```
#define dFORBID_SAFE_CAST
```
Тогда запрещает использовать функции:  
  - assert_safe_cast  
  - safe_cast  

<br />
<br />


[00]: #dfor_lvalue         "метафункция: разрешает/запрещает использовать lvalue в аргументах шаблонов"  
[01]: #str_length          "грубый неоптимизированный способ получения длины строки"  
[03]: #int_to_string_      "преобразует int в строку. (старые компиляторы не поддерживают std::to_string)"  
[04]: #tokenizePath        "сплитит файловый путь на токены-каталоги. в перспективе может переехать в fsystem"  
[05]: #shortPath           "умеет укорачивать длинный файловый путь. в перспективе может переехать в fsystem"  
[06]: #remove_cv           "служебная мета-функция: удаляет квалификаторы типов"  
[07]: #is_signed           "служебная мета-функция: определяет: является ли тип знаковым"  
[08]: #limit               "служебная мета-функция: определяет макс/мин значение типа"  


1) [История](../history.md)  


