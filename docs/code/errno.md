
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


[0]: #errno  "функции преобразования кодов ошибок в текст"  

errno
-----

функции:  

```
// --- возвращает текст ошибки 
str_t get_errno(const int error_id = errno);

// --- возвращает текст GetLasError
str_t get_last_error();
str_t get_last_error(const int code);

// --- возвращает текст ошибки 
// --- в формате: from: error-description 
str_t get_last_error(const char*  from_description);
str_t get_last_error(const str_t& from_description);

// --- бросает исключение с текстом ошибки
void throw_error(const char*  from_description);
void throw_error(const str_t& from_description);

```

особенность:  

[![D]][0] `get_last_error` поддерживается только в `Windows`
