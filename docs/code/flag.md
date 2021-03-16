
[P]: ../images/progress.png
[V]: ../images/success.png
[X]: ../images/failed.png
[D]: ../images/danger.png
[E]: ../images/empty.png
[N]: ../images/na.png

version 1.0.1
---

| **ID** | элементы            | tools | версия | mingw 830, 720 710 | msvc 2019, 2017, 2015 | msvc 2013, 2012, 2010, 2008 |  
|:------:|:-------------------:|:-----:|:------:|:------------------:|:---------------------:|:---------------------------:|  
|  0000  | [flag-synch][00]    | 0.0.8 | 1.0.1  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![D]][VS-OLD]              |  
|  0001  | [flag-void][01]     | 0.0.8 | 1.0.1  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![D]][VS-OLD]              |  
|  0002  | [flag-function][02] | 0.0.8 | 1.0.0  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![D]][VS-OLD]              |  
|  0001  | [flag-template][03] | 0.0.8 | 1.0.0  |   [![V]][MINGW]    |  [![V]][VS-NEW]       | [![D]][VS-OLD]              |  
                               
[M]: #flag                   "работа с флагами"  
[0]: #mingw-new              "поддержка компиляторов mingw"  
[1]: #msvc-new               "поддержка новых компиляторов msvc"  
[2]: #msvc-old               "поддержка старых компиляторов msvc"  

[MINGW]:   #mingw-new.md     "поддержка компиляторов mingw"  
[VS-NEW]:  #msvc-new.md      "поддержка новых компиляторов msvc"  
[VS-OLD]:  #flag-function    "старые компиляторы не поддерживают constexpr"  

[00]: #flag-synch            "потокобезопасный flag"  
[01]: #flag-void             "не обладает thred-safe"  
[02]: #flag-function         "набор свободных функций для работы с флагами"  
[03]: #flag-template         "набор мета-функций для работы с флагами"  



flag  
----
Шаблон класса:  

```
template<class Enum, class Mutex = synch> 
    class flag;
```

`Enum` - тип флага.  
`Mutex` - тип мютекса.  

Мьютекс используется для обеспечения синхронизации.  
По умолчанию в качестве `Mutex` используется [tools::synch][00]  
Можно указать `void`, тогда инстанцируется версия [single-thread][01].  

синопсис:

```
// конструкторы
template<class intT>
flag(const intT& fl) dNOEXCEPT;

flag(const Enum& fl) dNOEXCEPT;
flag(const flag& fl) dNOEXCEPT;
flag() dNOEXCEPT;
```

```
// оператор= присвоения
template<class intT>
flag& operator=(const intT& fl) dNOEXCEPT;

flag& operator=(const Enum& fl) dNOEXCEPT;
flag& operator=(const flag& fl) dNOEXCEPT;
```

```
// оператор сравнения

template<class intT>
bool operator==(const intT& fl) const dNOEXCEPT;

bool operator==(const Enum& fl) const dNOEXCEPT;
bool operator==(const flag& fl) const dNOEXCEPT;
```

```
// оператор сравнения

template<class intT>
bool operator!=(const intT& fl) const dNOEXCEPT;

bool operator!=(const Enum& fl) const dNOEXCEPT;
bool operator!=(const flag& fl) const dNOEXCEPT;
```

```
// true, если все флаги выкл.
bool is_empty() const dNOEXCEPT;

// true, если все флаги вкл.
bool is_full()  const dNOEXCEPT;
```

```
// true, если задано значение 1
// true, если включены все указанные флаги
template<class intT>
bool has(const intT& fl) const dNOEXCEPT;

bool has(const Enum& fl) const dNOEXCEPT;
bool has(const flag& fl) const dNOEXCEPT;
```

```
// true, если задано значение 1, 
// true, если включен хотя бы 1 из указанных флагов
template<class intT>
bool has_any(const intT& fl) const dNOEXCEPT;

bool has_any(const Enum& fl) const dNOEXCEPT;
bool has_any(const flag& fl) const dNOEXCEPT;
```

```
// выключает все флаги
void clear() dNOEXCEPT; 

// включает все флаги
void full()  dNOEXCEPT; 
```

```
// добавляет флаги к уже включенным
template<class intT>
void add(const intT& fl) dNOEXCEPT; 

void add(const Enum& fl) dNOEXCEPT; 
void add(const flag& fl) dNOEXCEPT; 
```

```
// выключает указанные флаги
template<class intT>
void del(const intT& fl) dNOEXCEPT; 

void del(const Enum& fl) dNOEXCEPT; 
void del(const flag& fl) dNOEXCEPT; 
```

```
// оставляет включенным только указанные флаги
template<class intT>
void valid_only(const intT& fl) dNOEXCEPT; 
void valid_only(const Enum& fl) dNOEXCEPT;
void valid_only(const flag& fl) dNOEXCEPT; 
```

```
// выключает Old флаги, 
// и включает New флаги
template<class Old, class New>
void change(const Old& oldFlag, const New& newFlag) dNOEXCEPT;
```

```
// преобразование к указанному типу
template<class intT>
intT as() const dNOEXCEPT
```

<br />
<br />

flag-synch  
----
Специализация по умолчанию.  
В качестве мутекса используется `tools::synch`  
<br />
<br />

flag-void  
----
Специализация для `single-thread`.  
- работает быстрее, чем thread-safe аналоги.  
- не использует синхронизацию.  
- не обеспечивает thread-safe.  
<br />
<br />

flag-function  
----
Набор свободных функций, для работы с флагами.  

[![D]][VS-OLD] начиная с `с++11` функции являются `constexpr`,  
И могут быть быть использованы в метапрограммировании.  

синопсис:  

```
dCONSTEXPR_CPP11 
int add_flags(const int flag, const int flags) dNOEXCEPT;

dCONSTEXPR_CPP11 
int del_flags(const int flag, const int flags) dNOEXCEPT;

dCONSTEXPR_CPP11 
bool has_flags(const int flag, const int flags) dNOEXCEPT;

dCONSTEXPR_CPP11
bool has_any_flags(const int flag, const int flags) dNOEXCEPT;
```

```
dCONSTEXPR_CPP11 
unsigned add_flags(const unsigned flag, const unsigned flags) dNOEXCEPT;

dCONSTEXPR_CPP11 
unsigned del_flags(const unsigned flag, const unsigned flags) dNOEXCEPT;

dCONSTEXPR_CPP11 
bool has_any_flags(const unsigned flag, const unsigned flags) dNOEXCEPT;

dCONSTEXPR_CPP11 
bool has_flags(const unsigned flag, const unsigned flags) dNOEXCEPT;
```
<br />
<br />


flag-template  
----
Набор мета-функций, для работы с флагами.  

Модуль реализован в двух версиях: для старых и новых компиляторов.  

```
if dHAS_CONSTEXPR_CPP11
    используются constexpr константы
else
    используются enum константы
```

синопсис:  

```
template<unsigned flag, unsigned flags> struct add_flag;
template<unsigned flag, unsigned flags> struct del_flag;
template<unsigned flag, unsigned flags> struct has_flag;
template<unsigned flag, unsigned flags> struct has_any_flag;
```
<br />
<br />








