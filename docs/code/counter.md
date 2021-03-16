
[P]: ../images/progress.png
[V]: ../images/success.png
[X]: ../images/failed.png
[D]: ../images/danger.png
[E]: ../images/empty.png
[N]: ../images/na.png

version 1.0.0  [![P]][0]
---

| **ID** | 2019      | 20017     | 2015      | 2013      | 2012      | 2010      | 2008      |  
|:------:|:---------:|:---------:|:---------:|:---------:|:---------:|:---------:|:---------:|  
| msvc   | [![V]][0] | [![V]][0] | [![V]][0] | [![V]][0] | [![V]][0] | [![V]][0] | [![V]][0] |  

| **ID**  | 810       | 720       | 710       |  
|:-------:|:---------:|:---------:|:---------:|  
| mingw   | [![V]][0] | [![V]][0] | [![V]][0] |  


[0]: #counter  "класс counter"  

counter
-----

Предназначение: атомарный счетчик.  

методы:  

```
// prefix ++it
counter& operator++() dNOEXCEPT

// prefix --it
counter& operator--() dNOEXCEPT

// возвращает текущее значение счетчика
operator size_t() const dNOEXCEPT

```

[![V]][0] особенность  
---------------------

```
if dHAS_ATOMIC
    используется std::atomic_size_t
else
    используется winapi interlocked api
```