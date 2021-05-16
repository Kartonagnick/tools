
[P]: ../icons/progress.png
[V]: ../icons/success.png
[X]: ../icons/failed.png
[D]: ../icons/danger.png
[E]: ../icons/empty.png
[N]: ../icons/na.png

version 1.0.1
---

| **ID**  | 2019      | 20017     | 2015      | 2013      | 2012      | 2010      | 2008      |  
|:-------:|:---------:|:---------:|:---------:|:---------:|:---------:|:---------:|:---------:|  
| msvc    | [![V]][M] | [![V]][M] | [![V]][M] | [![V]][M] | [![V]][M] | [![V]][M] | [![V]][M] |  

| **ID**  | 810       | 720       | 710       |  
|:-------:|:---------:|:---------:|:---------:|  
| mingw   | [![V]][M] | [![V]][M] | [![V]][M] |  


[T]: https://github.com/Kartonagnick/tools  "библиотека общего назначения tools"  
[M]: #assert  "макрос dASSERT"  

assert
------
- Заголовок `<cassert>` подключается только в дебааге.  
- В дебаге макрос `dASSERT` вызывает `assert`  
- В релизе макрос `dASSERT` сворачивается в пустоту.  

Стандартный макрос имеет дефект: **the argument comma separator problem**  
Макрос `dASSERT` исправляет этот дефект:  

```cpp
bool val = false;
if (!val)
    dASSERT(some<int, int>().compare(1, 1) && "trololo");
```

Возможная реализация:  

```cpp
#ifdef NDEBUG
    #define dASSERT(...) void()
#else
    #include <cassert>
    #define dASSERT(...) assert((__VA_ARGS__))
#endif
```

История изменений 
---

| **ID** |      tools      | версия |     дата      |  время   |  
|:------:|:---------------:|:------:|:-------------:|:--------:|  
|  0001  | 0.2.7 [![P]][T] | 1.0.1  | 2021y-03m-31d | 11:54:37 |  
|  0000  | 0.0.1           | 1.0.0  | 2021y-02m-20d | 18:41:19 |  
