
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


[0]: #raise  "макросы dRAISE и dVERIFY"  

raise
-----

Предназначение:  
В дебаге используется assert, в релизе бросаются исключения.  

```
dRAISE("ERROR_MESSAGE");
dVERIFY(!name.empty());
```

Возможная реализация:  
```
#ifdef NDEBUG
    //release
    #include <stdexcept>

    #define dRAISE(...) \
        throw ::std::runtime_error(__VA_ARGS__);

    #define dVERIFY(...)                         \
        if(!(__VA_ARGS__))                       \
            throw ::std::runtime_error("verify(failed): " # __VA_ARGS__)
#else
    //debug
    #include <cassert>

    #define dRAISE(...) \
        assert(0  &&  __VA_ARGS__ )

    #define dVERIFY(...) \
        assert("verify(failed):" && __VA_ARGS__)

#endif
```

