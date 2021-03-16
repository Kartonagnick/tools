
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


[0]: #assert  "макрос dASSERT"  

assert
------

Предназначение:  
Заголовок `<cassert>` подключается только в дебааге.  
В дебаге макрос `dASSERT` вызывает `assert`  
В релизе макрос `dASSERT` сворачивается в пустоту.  

```
dASSERT(expression);
```

Возможная реализация:  
```
#ifdef NDEBUG
    #define dASSERT(...)
#else
    #include <cassert>
    #define dASSERT(...) assert((__VA_ARGS__))
#endif
```

