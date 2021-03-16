
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
|  0000  | secure   | 1.0.0  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![V]][VS-OLD]              |  

[M]: #secure                 "получение псевдорандомных чисел"  
[MINGW]:   #mingw-new        "поддержка компиляторов mingw"  
[VS-NEW]:  #msvc-new         "поддержка новых компиляторов msvc"  
[VS-OLD]:  #msvc-old         "поддержка старых компиляторов msvc"  

secure  
----

синопсис:

```
// --- hide
str_t encrypt(const str_t& src, const str_t& access);

// --- show
str_t decrypt(const str_t& src, const str_t& access);
```

[![D]][M] особенности
---------------------
Поддерживается только Windows

