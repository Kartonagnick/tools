
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
| msvc   | [![V]][0] | [![V]][0] | [![V]][0] | [![D]][1] | [![D]][1] | [![D]][1] | [![D]][1] |  

| **ID**  | 810       | 720       | 710       |  
|:-------:|:---------:|:---------:|:---------:|  
| mingw   | [![V]][0] | [![V]][0] | [![V]][0] |  


[0]: #conv  "преобразование utf16 <--> utf8"  
[1]: #-особенность "функция convert_to недоступна: требуется с++11"  

conv
----

Предназначение: преобразования между char <--> wchar_t

методы:  

```
namespace multibyte 
{
    ::std::string convert(const wchar_t* s, const size_t length);
    ::std::string convert(const wchar_t* s);
    ::std::string convert(const std::wstring& s);

    ::std::wstring convert(const char* s, const size_t length);
    ::std::wstring convert(const char* s);
    ::std::wstring convert(const std::string& s);
}
```

```
namespace multibyte 
{
    #ifdef dHAS_CPP11
        // 'char' or 'wchar_t' only
        // char ------> std::wstring
        // wchar_t ---> std::string
        template<class s> auto convert(const s& src);

        // 'char' or 'wchar_t' only
        // ch == deduce_symbol_t<s> ? 
        //     string& -----> string&      (from reference returned reference)
        //     string&& ----> string       (from rvalue returned by value)
        //     stringed ----> stringed&    (from stringed returned string by value)
        // else
        //     convert(src)
        template<class ch, class s> 
        decltype(auto) convert_to(s&& src);
    #endif
}
```

```
namespace stdlocal 
{
    ::std::string convert(const wchar_t* s, const size_t len, const ::std::locale& loc);
    ::std::string convert(const wchar_t* s, const ::std::locale& loc);

    ::std::string convert(const wchar_t* s, const size_t len);
    ::std::string convert(const wchar_t* s);

    ::std::string convert(const std::wstring& s, const ::std::locale& loc);
    ::std::string convert(const std::wstring& s);

    ::std::wstring convert(const char* s, const size_t len, const ::std::locale& loc);
    ::std::wstring convert(const char* s, const ::std::locale& loc);

    ::std::wstring convert(const char* s, const size_t len);
    ::std::wstring convert(const char* s);

    ::std::wstring convert(const std::string& s, const ::std::locale& loc);
    ::std::wstring convert(const std::string& s);
}
```

```
namespace stdlocal 
{
    #ifdef dHAS_CPP11
        // char ------> std::wstring
        // wchar_t ---> std::string
        template<class s> auto convert(const s& src);

        template<class str> auto convert(
            const str& s, 
            const ::std::locale& loc
        );

        // 'char' or 'wchar_t' only
        // ch == deduce_symbol_t<s> ? 
        //     string& -----> string&               (from reference returned reference)
        //     string&& ----> string                (from rvalue returned by value)
        //     stringed ----> basic_string<char>    (from stringed returned string by value)
        // else
        //     convert(src)
        template<class ch, class s> 
        decltype(auto) convert_to(s&& src);

        template<class ch, class s> 
        decltype(auto) convert_to(
            s&& src, 
            const ::std::locale& loc
        );
    #endif
}
```

[![D]][1] особенность  
---------------------

```
if dHAS_CPP11
    становится доступной доп. функция convert_to
    становится доступной доп. функция convert
```