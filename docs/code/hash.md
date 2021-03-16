
[P]: ../images/progress.png
[V]: ../images/success.png
[X]: ../images/failed.png
[D]: ../images/danger.png
[E]: ../images/empty.png
[N]: ../images/na.png

version 1.0.0
---

| **ID** | элементы            | версия | mingw 830, 720 710 | msvc 2019, 2017, 2015 | msvc 2013, 2012, 2010, 2008              |  
|:------:|:-------------------:|:------:|:------------------:|:---------------------:|:----------------------------------------:|  
|  0000  | [hash][00]          | 1.0.0  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![V]][00] [![N]][1] [![N]][1] [![N]][0] |  
|  0001  | [hash-combine][01]  | 1.0.0  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![V]][01] [![N]][1] [![N]][1] [![N]][0] |  
|  0002  | [hash-accum][02]    | 1.0.0  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![V]][VS-OLD]                           |  


[M]: #hash                   "получение хэшей произвольных объектов"  
[MINGW]:   #mingw-new        "поддержка компиляторов mingw"  
[VS-NEW]:  #msvc-new         "поддержка новых компиляторов msvc"  
[VS-OLD]:  #msvc-old         "поддержка старых компиляторов msvc"  

[0]: #-особенности           "std::hash: требует c++0x, msvc2010 (or newer)"  
[1]: #-особенности           "variadic template: требует c++11, msvc2013 (or newer)"  

[00]: #hash                  "шаблон класса hash"  
[01]: #hash-combine          "шаблон hash_combine"  
[02]: #hash-accum            "класс hash_accum"  

hash  
----
Шаблон класса:

```
tools::hash<args...>
```

Есть возможность легко создавать специализацию:  

```
struct some { int a, b; };
dMAKE_TOOLS_HASHABLE(some, v.a, v.b);
```

<br />
<br />



hash-combine  
----
Предоставляет шаблон функции вычисления хэша произвольного объекта:

```
template <class T>
::std::size_t
    hash_combine(seed_t seed, const T& v) dNOEXCEPT
```

Есть возможность легко изготовить специализацию для `std::hash`  

```
struct some { int a, b; };
dMAKE_HASHABLE(some, v.a, v.b);
```

<br />
<br />



test-accum
---
Класс hash_accum  
Поддерживается всеми компиляторами, даже самыми старыми.  
Аккумулирует 32х битный хэш произвольного объекта  

Методы:  

```
hash_accum() dNOEXCEPT; 

u32 get() const dNOEXCEPT;
operator u32() const dNOEXCEPT;

template<class t> 
void add(const t& v) dNOEXCEPT;
```

<br />
<br />


[![D]][M] особенности  
---------------------

```
if !dHAS_HASH (msvc2010)
    ошибка: функциональность не поддерживается

if !dHAS_VARIADIC_TEMPLATE (msvc2013)
    ошибка: функциональность не поддерживается
```







