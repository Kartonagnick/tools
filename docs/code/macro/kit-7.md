
[P]: ../../icons/progress.png
[V]: ../../icons/success.png
[X]: ../../icons/failed.png
[D]: ../../icons/danger.png
[E]: ../../icons/empty.png
[N]: ../../icons/na.png

version 1.0.0
---

| **ID**  | 2019      | 20017     | 2015      | 2013      | 2012      | 2010      | 2008      |  
|:-------:|:---------:|:---------:|:---------:|:---------:|:---------:|:---------:|:---------:|  
| msvc    | [![V]][M] | [![V]][M] | [![V]][M] | [![V]][M] | [![V]][M] | [![V]][M] | [![V]][M] |  

| **ID**  | 810       | 720       | 710       |  
|:-------:|:---------:|:---------:|:---------:|  
| mingw   | [![V]][M] | [![V]][M] | [![V]][M] |  

[M]: #macro  "магия препроцессора"

[0]: #args         "манипуляции с аргументами макро-функций"
[1]: #comb_tuples  "комбинирует все элементы первого кортёжа со всеми элементами второго кортёжа"
[2]: #comb_values  "комбинирует все переданные аргументы друг с дружкой"
[3]: #foreach      "перебирает все переданные в макрос аргументы"
[4]: #overload     "позволяет перегружать макрос под разное кол-во аргументов"
[5]: #repeat       "организует цикл для указанного кол-ва повторов"

kit-7
---
Состав комплекта:  
  - [args-7.hpp][0]  
  - [comb_tuples-7.hpp][1]  
  - [comb_values-7.hpp][2]  
  - [foreach-7.hpp][3]  
  - [overload-7.hpp][4]  
  - [repeat-7.hpp][5]  

## args
Манипуляции с аргументами макро-функций.  

Извлекает первый аргумент:  
```cpp
std::cout << dFIRST_ARG(1,2,3); // 1
```

Извлекает последний аргумент:  
```cpp
std::cout << dLAST_ARG_MAX_7(1,2,3); // 3
```

Извлекает аргумент по индексу:  
```cpp
std::cout << dLAST_ARG_MAX_7(1,  11,22,33,44,55); // 11
```
Извлекает первые N аргументов:  
```cpp
int etalon[3] = { dFIRST_ARGS(3, 1,2,3,4,5) }; // 1,2,3
```

Извлекает последние N аргументов:  
```cpp
int etalon[3] = { dLAST_ARGS_MAX_7(3, 1,2,3,4,5) }; // 3,4,5
```

Переворачивает весь список аргументов задом наперед:
```cpp
int etalon[3] = { dREVERT_ARGS_MAX_7(1,2,3) }; // 3,2,1
```

## comb_tuples
Комбинирует все элементы первого кортёжа 
со всеми элементами второго кортёжа.  

```cpp
#define pp_macro(index, a, b) \
    ss << "(" << index << ", " << #a << ":" << #b << ")";

#define pp_delim(index) \
    ss << ", ";

sstrem_t ss;
dCOMB_TUPLES_MAX_7(pp_macro, pp_delim, (1,2), (3,4,5) );
std::cout << ss.str() << '\n';

// output:
// (1, 1:3), (2, 1:4), (3, 1:5), (1, 2:3), (2, 2:4), (3, 2:5)
```
## comb_values
Комбинирует все переданные аргументы друг с дружкой.  

```cpp
#define pp_macro(index, a, b) \
    ss << "(" << index << ", " << #a << ":" << #b << ")";
     
#define pp_delim(index) \
    ss << ", ";

sstrem_t ss;
dCOMB_VALUES_MAX_7(pp_macro, pp_delim, 1,2,3);
std::cout << ss.str() << '\n';

// output
// (1, 1:1), (2, 1:2), (3, 1:3), (1, 2:1), (2, 2:2), (3, 2:3), (1, 3:1), (2, 3:2), (3, 3:3)
```

## foreach
Перебирает все переданные в макрос аргументы.  

```cpp
#define pp_beg(count) \
    ss << "beg{" << count << "}";

#define pp_macro(index, arg, element) \
    ss << "[" << index << ", " << #arg << " VS " << #element "]";

#define pp_delim(index) \
    ss << ",";

#define pp_end(count) \
    ss << '{' << count << "}end";

#define pp_enum(arg, ...)                                \
    pp_beg(dGET_ARGS_COUNT_MAX_7(__VA_ARGS__))           \
    dFOREACH_MAX_7(pp_macro, pp_delim, arg, __VA_ARGS__) \
    pp_end(dGET_ARGS_COUNT_MAX_7(__VA_ARGS__))

sstrem_t ss;
pp_enum(Arg, A,B,C);

std::cout << ss.str() << '\n';

// output
// beg{3}[1, Arg VS A],[2, Arg VS B],[3, Arg VS C]{3}end
```

## overload
Умеет определять кол-во аргументов, которое было переданно в макрос.  
И позволяет перегружать макрос под разное кол-во аргументов:  

```cpp
#include <tools/macro/overload-7.hpp>
    
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

#define dPRINT_6(a1, a2, a3, a4, a5, a6) \
    std::cout << a1 << ", " << a2 << ", "<< a3 << ", " << a4 << ", " << a5 << ", " << a6 << '\n'

#define dPRINT_7(a1, a2, a3, a4, a5, a6, a7) \
    std::cout << a1 << ", " << a2 << ", "<< a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7 << '\n'


#define dPRINT(...) \
    dMACRO_CHOOSER_7(dPRINT, __VA_ARGS__)(__VA_ARGS__)

#define dIF_ARG_COUNT_0(element, delim, ...) \
    dPRINT(element, delim)

#define dIF_ARG_COUNT_N(element, delim, ...) \
    dPRINT(element, delim, __VA_ARGS__)

#define dCALL_ONE_OR_MORE(element, delim, ...) \
    dNULL_OR_MORE_7(dIF_ARG_COUNT, __VA_ARGS__)(element, delim, __VA_ARGS__)

#include <iostream>
    
int main()
{
    dPRINT();
    dPRINT(1);
    dPRINT(1,2);
    dPRINT(1,2,3);
    dPRINT(1,2,3,4);
    dPRINT(1,2,3,4,5);
    dPRINT(1,2,3,4,5,6);
    dPRINT(1,2,3,4,5,6,7);
    std::cout << dGET_ARGS_COUNT_MAX_7(1, 2, 3, 4, 5) << '\n';

    dCALL_ONE_OR_MORE(1,2);
    dCALL_ONE_OR_MORE(1,2,3);
}
```

## repeat 
Организует цикл для указанного кол-ва повторов.  

```cpp
#define pp_macro(index) ss << index;
#define pp_delim(index) ss << ",";
    
#define pp_repeat(num) \
    dREPEAT(pp_macro, pp_delim, num);

sstrem_t ss;
pp_repeat(5);
std::cout << ss.str() << '\n';

// output:
// 1,2,3,4,5
```


История изменений 
------

| **ID** | tools | версия |     дата      |  время   |   ветка   |  
|:------:|:-----:|:------:|:-------------:|:--------:|:---------:|  
|  0000  | 0.1.7 | 1.0.0  | 2021y-02m-18d | 20:37:00 | #5_impl   |  
