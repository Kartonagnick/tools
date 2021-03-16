
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
| msvc   | [![V]][0] | [![V]][0] | [![V]][0] | [![D]][1] | [![D]][1] | [![D]][1] | [![D]][1] |  

| **ID**  | 810       | 720       | 710       |  
|:-------:|:---------:|:---------:|:---------:|  
| mingw   | [![V]][0] | [![V]][0] | [![V]][0] |  


[0]: #utf8  "преобразование utf16 <--> utf8"  
[1]: #utf8  "функция convert_to недоступна: требуется с++11"  

utf8
----

Предназначение: преобразования между char <--> wchar_t

методы:  

```
// Convert a wide Unicode string to an UTF8 string
::std::string convert(const ::std::wstring& text);
::std::string convert(const wchar_t* text, const size_t len);
::std::string convert(const wchar_t* text);

// Convert an UTF8 string to a wide Unicode String
std::wstring convert(const ::std::string& text);
std::wstring convert(const char* text, const size_t len);
std::wstring convert(const char* text);
```

```
#ifdef dHAS_CPP11
// char ------------> std::string
// wchar_t ---------> std::wstring
template<class s> auto convert(const s& src);

// return std::basic_string<ch>
// if 'ch' == 's' -> return reference
template<class ch, class s>
decltype(auto) convert_to(s&& src);
#endif // dHAS_CPP11

```

[![D]][1] особенность:  

```
if dHAS_CPP11
    становится доступной функция convert_to
```