
[P]: ../images/progress.png
[V]: ../images/success.png
[X]: ../images/failed.png
[D]: ../images/danger.png
[E]: ../images/empty.png
[N]: ../images/na.png

version 1.0.0
---

| **ID** | элементы | версия | mingw 830, 720 710 | msvc 2019, 2017, 2015 | msvc 2013, 2012, 2010, 2008 |  
|:------:|:--------:|:------:|:------------------:|:---------------------:|:---------------------------:|  
|  0000  | marker   | 1.0.0  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![V]][VS-OLD]              |  

[M]: #marker                 "получение псевдорандомных чисел"  
[MINGW]:   #mingw-new        "поддержка компиляторов mingw"  
[VS-NEW]:  #msvc-new         "поддержка новых компиляторов msvc"  
[VS-OLD]:  #msvc-old         "поддержка старых компиляторов msvc"  

marker
---

методы:

```
// конструктор 
marker() dNOEXCEPT;

// if success ---> true
// if exists ----> false
// add event mark
bool add(const Key&, const Value&);

// if exists -------> true 
// if not exists ---> false
// remove event mark
bool del(const Key&, const Value&);

// if exists ---> true 
// else --------> false
bool exists(const Key&, const Value&) const;
```

[![V]][M] особенности
---------------------

```
if dHAS_TYPE_TRAITS
    используется unordered_map
else 
    используется map
```

```
if dHAS_EMPLACE
    используется emplace
else 
    используется insert
```