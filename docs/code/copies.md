
[P]: ../images/progress.png
[V]: ../images/success.png
[X]: ../images/failed.png
[D]: ../images/danger.png
[E]: ../images/empty.png
[N]: ../images/na.png

version 1.0.0
---

| **ID** | 2019      | 20017     | 2015      | 2013      | 2012      | 2010      | 2008      |  
|:------:|:---------:|:---------:|:---------:|:---------:|:---------:|:---------:|:---------:|  
| msvc   | [![V]][0] | [![V]][0] | [![V]][0] | [![V]][0] | [![V]][0] | [![V]][0] | [![V]][0] |  

| **ID**  | 810       | 720       | 710       |  
|:-------:|:---------:|:---------:|:---------:|  
| mingw   | [![V]][0] | [![V]][0] | [![V]][0] |  


[0]: #copies  "класс copies"  

copies
-----

Предназначение: подсчитывает кол-во существующих экземпляров класса

методы:  

```
// конструктор
copies() dNOEXCEPT;

// конструктор копии
copies(const copies&) dNOEXCEPT

// вернёт количество объектов
static size_t instances() dNOEXCEPT;

```

[![V]][0] особенность  
---

```
if dHAS_ATOMIC
    используется std::atomic_size_t
else
    используется tools::counter
```