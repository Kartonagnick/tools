
[P]: ../images/progress.png
[V]: ../images/success.png
[X]: ../images/failed.png
[D]: ../images/danger.png
[E]: ../images/empty.png
[N]: ../images/na.png

version 1.0.0
---

| **ID** | элементы         | версия | mingw 830, 720 710 | msvc 2019, 2017, 2015 | msvc 2013, 2012, 2010, 2008 |  
|:------:|:----------------:|:------:|:------------------:|:---------------------:|:---------------------------:|  
|  0000  | для 5 аргументов | 1.0.0  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![V]][VS-OLD]              |  
|  0001  | для 7 аргументов | 1.0.0  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![V]][VS-OLD]              |  

[M]: #macro
[MINGW]:   #mingw-new        "поддержка компиляторов mingw"  
[VS-NEW]:  #msvc-new         "поддержка новых компиляторов msvc"  
[VS-OLD]:  #msvc-old         "поддержка старых компиляторов msvc"  

#macro
---

| **ID** | элемент                                | tools | версия |  
|:------:|:--------------------------------------:|:-----:|:------:|  
|  0000  | [dTOOLS_MACRO_ARGS_5_USED_][00]        | 0.1.7 | 1.0.0  |  
|  0001  | [dTOOLS_MACRO_COMB_TUPLES_5_USED_][01] | 0.1.7 | 1.0.0  |  
|  0002  | [dTOOLS_MACRO_COMB_VALUES_5_USED_][02] | 0.1.7 | 1.0.0  |  
|  0003  | [dTOOLS_MACRO_FOREACH_5_USED_][03]     | 0.1.7 | 1.0.0  |  
|  0004  | [dTOOLS_MACRO_OVERLOAD_5_USED_][04]    | 0.1.7 | 1.0.0  |  
|  0005  | [dTOOLS_MACRO_REPEAT_5_USED_][05]      | 0.1.7 | 1.0.0  |  
|  0006  | [dTOOLS_MACRO_ARGS_7_USED_][06]        | 0.1.7 | 1.0.0  |  
|  0007  | [dTOOLS_MACRO_COMB_TUPLES_7_USED_][07] | 0.1.7 | 1.0.0  |  
|  0008  | [dTOOLS_MACRO_COMB_VALUES_7_USED_][08] | 0.1.7 | 1.0.0  |  
|  0009  | [dTOOLS_MACRO_FOREACH_7_USED_][09]     | 0.1.7 | 1.0.0  |  
|  0010  | [dTOOLS_MACRO_OVERLOAD_7_USED_][10]    | 0.1.7 | 1.0.0  |  
|  0011  | [dTOOLS_MACRO_REPEAT_7_USED_][11]      | 0.1.7 | 1.0.0  |  

[00]: #ARGS_5         "обработка аргументов макроса"  
[01]: #COMB_TUPLES_5  "комбинирует элементы двух кортежей"  
[02]: #COMB_VALUES_5  "комбинирует аргументы друг с другом"  
[03]: #FOREACH_5      "выполняет действие над каждым аргументов макроса"  
[04]: #OVERLOAD_5     "перегрузка макросов под различное количество аргументов"  
[05]: #REPEAT_5       "цикл repeat на макросах"  

[06]: #ARGS_7         "обработка аргументов макроса"  
[07]: #COMB_TUPLES_7  "комбинирует элементы двух кортежей"  
[08]: #COMB_VALUES_7  "комбинирует аргументы друг с другом"  
[09]: #FOREACH_7      "выполняет действие над каждым аргументов макроса"  
[10]: #OVERLOAD_7     "перегрузка макросов под различное количество аргументов"  
[11]: #REPEAT_7       "цикл repeat на макросах"  

ARGS_5
----
манипуляции с аргументами макроса.  

```
// получение первого аргумента макроса
dFIRST_ARG(arg, ...)

// получение n-го аргумента макроса
dGET_ARG(num, ...)

// получение первых n аргументов
dFIRST_ARGS(num, ...)

// переставляет аргументы задом наперед
dREVERT_ARGS_MAX_5(...)

// получение последних n аргументов
dLAST_ARGS_MAX_5(n, ...)
```

COMB_TUPLES_5
----
Комбинирует аргументы двух кортёжей друг с другом.  

```
#include <iostream>

int main()
{
    #define pp_macro(index, a, b) \
        ss << "(" << index << ", " << #a << " vs " << #b << ")";

    #define pp_delim(index) \
        ss << ", ";
    
    dCOMB_TUPLES_MAX_5(pp_macro, pp_delim, (1,2), (3,4));
}
```
<br />
<br />

COMB_VALUES_5
----
Комбинирует аргументы друг с другом.  

```
#include <iostream>

int main()
{
    #define pp_macro(index, a, b) \
        ss << "(" << index << ", " << #a << ":" << #b << ")";
        
    #define pp_delim(index) \
        ss << ", ";
    
    dCOMB_VALUES_MAX_5(pp_macro, pp_delim, 1,2,3,4);
}
```

<br />
<br />

FOREACH_5
----
Выполняет действие над каждым аргументов макроса:  

```
    // usage: 

    #define pp_beg(count) \
        std::cout << "begin(" << count << ")\n";

    #define pp_element(index, name) \
        std::cout << "[" << index << "]" << name;

    #define pp_delim(index) \
        std::cout << "[" << index << "]\n";

    #define pp_end(count) \
        std::cout << "\n" << "end(" << count << ")\n";

    #define pp_enum(...)                                  \
        pp_beg(dGET_ARGS_COUNT_MAX_5(__VA_ARGS__))        \
        dFOREACH_MAX_5(pp_element, pp_delim, __VA_ARGS__) \
        pp_end(dGET_ARGS_COUNT_MAX_5(__VA_ARGS__))

    #include <iostream>
    
    int main()
    {
        //pp_enum();    std::cout << "==========\n";
        pp_enum(1);     std::cout << "==========\n";
        pp_enum(1,2);   std::cout << "==========\n";
        pp_enum(1,2,3); std::cout << "==========\n";
    }
```

<br />
<br />


OVERLOAD_5
----
Перегрузка макросов:  

```
    // usage: 
    #define dPRINT_0() \
        std::cout <<"empty\n"
    
    #define dPRINT_1(a1) \
        std::cout << a1 << '\n'
    
    #define dPRINT_2(a1, a2) \
        std::cout << a1 << ", " << a2 << '\n'
    
    #define dPRINT_3(a1, a2, a3) \
        std::cout << a1 << ", " << a2 << ", " << a3 << '\n'
    
    #define dPRINT_4(a1, a2, a3, a4) \
        std::cout << a1 << ", " << a2 << ", " << a3 << ", " << a4 << '\n'
    
    #define dPRINT_5(a1, a2, a3, a4, a5) \
        std::cout << a1 << ", " << a2 << ", "<< a3 << ", " << a4 << ", " << a5 << '\n'
    
    #define dPRINT(...) \
        dMACRO_CHOOSER_5(dPRINT, __VA_ARGS__)(__VA_ARGS__)

    #define dIF_ARG_COUNT_0(element, delim, ...) \
        dPRINT(element, delim)

    #define dIF_ARG_COUNT_N(element, delim, ...) \
        dPRINT(element, delim, __VA_ARGS__)

    #define dCALL_ONE_OR_MORE(element, delim, ...) \
        dNULL_OR_MORE_5(dIF_ARG_COUNT, __VA_ARGS__)(element, delim, __VA_ARGS__)
    
    #include <iostream>
    
    int main()
    {
        dPRINT();
        dPRINT(1);
        dPRINT(1,2);
        dPRINT(1,2,3);
        dPRINT(1,2,3,4);
        dPRINT(1,2,3,4,5);
        std::cout << dGET_ARGS_COUNT_MAX_5(1, 2, 3, 4, 5) << '\n';

        dCALL_ONE_OR_MORE(1,2);
        dCALL_ONE_OR_MORE(1,2,3);
    }
```

<br />
<br />


REPEAT_5
----
Простейший цикл на макросах:  

```
    // usage: 
    #define pp_macro(index) ss << index;

    #define pp_delim(index) ss << ",";
    
    #define pp_repeat(num) \
        dREPEAT(pp_macro, pp_delim, num);

    sstrem_t ss;
    pp_repeat(2);
    std::cout << ss.str() << '\n';
```

<br />
<br />
