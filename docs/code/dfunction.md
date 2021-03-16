
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


[0]: #assert  "макрос dFUNCTION"  

dFUNCTION
------

Предназначение:  
Макрос раскрывается в объявление функции, внутри которой он был вызван.  

```
void example()
{
    std::cout << dFUNCTION << '\n';
}
```

Возможная реализация:  

```
#if defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW__)
    #define dFUNCTION __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
    #define dFUNCTION __FUNCSIG__
#else
    #define dFUNCTION __FUNCTION__
#endif
```

