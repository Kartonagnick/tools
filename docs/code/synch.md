
[P]: ../images/progress.png
[V]: ../images/success.png
[X]: ../images/failed.png
[D]: ../images/danger.png
[E]: ../images/empty.png
[N]: ../images/na.png

version 1.0.2  [![P]][0]
---

| **ID** | 2019      | 20017     | 2015      | 2013      | 2012      | 2010      | 2008      |  
|:------:|:---------:|:---------:|:---------:|:---------:|:---------:|:---------:|:---------:|  
| msvc   | [![V]][0] | [![V]][0] | [![V]][0] | [![V]][0] | [![V]][0] | [![V]][0] | [![V]][0] |  

| **ID**  | 810       | 720       | 710       |  
|:-------:|:---------:|:---------:|:---------:|  
| mingw   | [![V]][0] | [![V]][0] | [![V]][0] |  


[0]: #synch  "класс мьютекс"  

synch
-----
особенность:  

```
if dHAS_ATOMIC
    используется std::recursive_mutex
else
    используется winapi CRITICAL_SECTION
```

synch_dummy
-----
Мьютекс-заглушка.  


synch_lock
-----
RAII-guard для synch  
