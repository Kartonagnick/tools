
[![logo](../logo.png)](../home.md "for developers") 

[P1]: ../images/progress.png  "2021y-03m-05d"
[X1]: ../images/failed.png    "2021y-03m-05d"
[V1]: ../images/success.png   "2021y-03m-05d"
[E1]: ../images/nodata.png    "2021y-03m-05d"
[N1]: ../images/na.png        "2021y-03m-05d"

version 0.1.5

| **ID** | **компоненты**       |  used           |  
|:------:|:--------------------:|:---------------:|  
|  0000  | [dfor_lvalue][00]    | utf8.hpp        |  
|  0001  | [str_length][01]     | utf8_win.cpp    |  
|  0002  | [str_length][01]     | utf8_commin.cpp |  
|  0003  | [int_to_string_][03] | errno.cpp       |  
|  0004  | [tokenizePath][04]   | seh_path.hpp    |  
|  0005  | [shortPath][05]      | seh_path.hpp    |  

<br />
<br />


[00]: #dfor_lvalue         "метафункция: разрешает/запрещает использовать lvalue в аргументах шаблонов"  
[01]: #str_length          "грубый неоптимизированный способ получения длины строки"  
[03]: #int_to_string_      "преобразует int в строку. (старые компиляторы не поддерживают std::to_string)"  
[04]: #tokenizePath        "сплитит файловый путь на токены-каталоги. в перспективе может переехать в fsystem"  
[05]: #shortPath           "умеет укорачивать длинный файловый путь. в перспективе может переехать в fsystem"  

1) [История](../history.md)  


