
[P]: ../images/progress.png
[V]: ../images/success.png
[X]: ../images/failed.png
[D]: ../images/danger.png
[E]: ../images/empty.png
[N]: ../images/na.png

version 1.0.0
---

| **ID** | элементы               | tools | версия | mingw 830, 720 710 | msvc 2019, 2017, 2015 | msvc 2013, 2012, 2010, 2008             |  
|:------:|:----------------------:|:-----:|:------:|:------------------:|:---------------------:|:---------------------------------------:|  
|  0000  | [can_cast][00]         | 0.1.9 | 0.0.1  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![D]][0] [![D]][0] [![D]][1] [![D]][1] |  
|  0001  | [cast][01]             | 0.2.0 | 0.0.2  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![D]][0] [![D]][0] [![D]][1] [![D]][1] |  
|  0002  | [assert_cast][02]      | 0.2.0 | 0.0.2  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![D]][0] [![D]][0] [![D]][1] [![D]][1] |  
|  0003  | [safe_cast][03]        | 0.2.2 | 0.0.3  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![D]][0] [![D]][0] [![D]][1] [![D]][1] |  
|  0004  | [assert_safe_cast][04] | 0.2.2 | 0.0.3  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![D]][0] [![D]][0] [![D]][1] [![D]][1] |  

[M]:       #numeric  "можно ли выполнить каст без потерь данных"  
[MINGW]:   #mingw-new   "поддержка компиляторов mingw"  
[VS-NEW]:  #msvc-new    "поддержка новых компиляторов msvc"  
[VS-OLD]:  #msvc-old    "поддержка старых компиляторов msvc"  
[0]:  #-особенность     "не поддерживается constexpr"  
[1]:  #-особенность     "не поддерживается constexpr и enum"

[00]: #can_cast          "true, если каст можно выполнить без потерь"  
[01]: #cast              "exception-защита каста"  
[02]: #assert_cast       "assert-защита каста"  
[03]: #safe_cast         "выполняет безопасный каст"  
[04]: #assert_safe_cast  "выполняет безопасный каст под защитой assert"  

can_cast
----
Возвращает true, если каст можно осуществить без потерь данных.  

синопсис:  
```
// true, если каст можно осуществить без потерь данных
template<class ret, class from>
dCONSTEXPR_CPP11 dNODISCARD 
    bool can_cast(const from v) dNOEXCEPT;
```

пример:  
```
std::cout << tools::can_cast<char>(121);
```

cast
----
Бросит эксепшен, если каст приводит к потерям данных.  

синопсис:  
```
// каст из from в ret
// в случае угрозы потери данных будет брошенно исключение
template<class ret, class from>
dCONSTEXPR_CPP11 dNODISCARD 
    ret cast(const from val) 
```
пример:  
```
std::cout << tools::cast<char>(121);
```

assert_cast
---

синопсис:
```
// каст из from в ret
// в случае угрозы потери данных сработает assert
template<class ret, class from>
dCONSTEXPR_CPP11 dNODISCARD 
    ret assert_cast(const from val) 
```
пример:  
```
std::cout << tools::assert_cast<char>(121);
```

safe_cast
----

синопсис:

```
// если активирован макрос dDISABLE_SAFE_CAST
// то все проверки каста будут удалены

// если активирован макрос dFORBID_SAFE_CAST
// то использование данной функции будет запрещено

template<class ret, class from>
dCONSTEXPR_CPP11 dNODISCARD
    ret safe_cast(const from val);
```

пример:  
```
std::cout << tools::safe_cast<char>(121);
```

assert_safe_cast
----

синопсис:  

```
// если активирован макрос dDISABLE_SAFE_CAST
// то все проверки каста будут удалены

// если активирован макрос dFORBID_SAFE_CAST
// то использование данной функции будет запрещено

template<class ret, class from>
dCONSTEXPR_CPP11 dNODISCARD
    ret assert_safe_cast(const from val) dNOEXCEPT
```

пример:  
```
std::cout << tools::assert_safe_cast<char>(121);
```


[![D]][1] особенность  
---------------------

```
if dHAS_ENUM_CLASS
    поддержка enum
else
    enum не поддерживается
```

```
if dHAS_CPP11
    используются constexpr функции
else 
    используются inline функции
```

[![V]][M] особенности  

```
if dHAS_TYPE_TRAITS
    используется <type_traits>
else 
    используется <tools/types/traits.hpp>
```

