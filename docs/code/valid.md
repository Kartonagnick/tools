
[P]: ../images/progress.png
[V]: ../images/success.png
[X]: ../images/failed.png
[D]: ../images/danger.png
[E]: ../images/empty.png
[N]: ../images/na.png

version 0.0.1  [![P]][M]
---

| **ID** | 2019      | 20017     | 2015      | 2013      | 2012      | 2010      | 2008      |  
|:------:|:---------:|:---------:|:---------:|:---------:|:---------:|:---------:|:---------:|  
| msvc   | [![V]][M] | [![V]][M] | [![V]][M] | [![D]][1] | [![D]][1] | [![D]][1] | [![D]][1] |  

| **ID**  | 810       | 720       | 710       |  
|:-------:|:---------:|:---------:|:---------:|  
| mingw   | [![V]][M] | [![V]][M] | [![V]][M] |  


[M]: #valid  "проверяет валидность указателя"  
[1]: #valid  "constexpr требует с++11"  

valid
----

Вернет true, если аргумент не является указателем, 
либо указатель валидный.  

синопсис:
```
dTEMPLATE bool valid(const t& p) dNOEXCEPT 
{ 
    return ::tools::detail::valid(p);
}
```

[![D]][1] особенность:  

```
if dHAS_CPP11
    функция является constexpr
```