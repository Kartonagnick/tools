
[P]: ../images/progress.png
[V]: ../images/success.png
[X]: ../images/failed.png
[D]: ../images/danger.png
[E]: ../images/empty.png
[N]: ../images/na.png

version 1.0.1
---

| **ID** | элементы     | версия | mingw 830, 720 710 | msvc 2019, 2017, 2015 | msvc 2013, 2012, 2010, 2008             |  
|:------:|:------------:|:------:|:------------------:|:---------------------:|:---------------------------------------:|  
|  0000  | [random][00] | 1.0.1  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![V]][2] [![V]][3] [![N]][3] [![N]][3] |  

[M]: #random                 "получение псевдорандомных чисел"  
[MINGW]:   #mingw-new        "поддержка компиляторов mingw"  
[VS-NEW]:  #msvc-new         "поддержка новых компиляторов msvc"  
[VS-OLD]:  #msvc-old         "поддержка старых компиляторов msvc"  
[2]:       #msvc-old         "поддержка старых компиляторов msvc"  
[3]:       #-особенности     "минимальное требование: msvc2012"  

[00]: #random                "функция рандомайзер"  

random  
----

синопсис:
```
template<class T> 
T random(const T& a, const T& b) dNOEXCEPT
```

[![D]][M] особенности  
---------------------

```
if !dHAS_CHRONO (msvc2012)
    ошибка: не поддерживается

if dHAS_THREAD_LOCAL
    используется thread_local
else
    используется synch
```









