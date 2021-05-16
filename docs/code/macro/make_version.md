
[P]: ../../icons/progress.png
[V]: ../../icons/success.png
[X]: ../../icons/failed.png
[D]: ../../icons/danger.png
[E]: ../../icons/empty.png
[N]: ../../icons/na.png

version 1.0.0
---

| **ID**  | 2019      | 20017     | 2015      | 2013      | 2012      | 2010      | 2008      |  
|:-------:|:---------:|:---------:|:---------:|:---------:|:---------:|:---------:|:---------:|  
| msvc    | [![V]][M] | [![V]][M] | [![V]][M] | [![V]][M] | [![V]][M] | [![V]][M] | [![V]][M] |  

| **ID**  | 810       | 720       | 710       |  
|:-------:|:---------:|:---------:|:---------:|  
| mingw   | [![V]][M] | [![V]][M] | [![V]][M] |  

[T]: https://github.com/Kartonagnick/tools  "библиотека общего назначения tools"  
[M]: #make_version   "магия препроцессора"
[F]: #форматы-версий "допустимые форматы версий"

[0]: #Преобразование-версии-в-строку
[1]: #Преобразование-версии-в-число
[2]: #Сравнение-версий
[3]: #Формат-версий

make_version
---
Служит для манипуляций с `версией` продукта времени препроцессора:
  - [преобразовать версию в строку][0]  
  - [преобразовать версию в число][1]  
  - [сравнивать версии][2]  
  - [определить формат версий][3]  

Версия задаётся в виде дефайна препроцессора.  
Значения `мажор`, `минор`, и прочие токены разделяются запятой:  

```cpp
#define dMY_VERSION 1,22,3,44,555
  // 1   - major  (1 токен)
  // 22  - minor  (2 токен)
  // 3   - patch  (3 токен)
  // 44  - branch (4 токен)
  // 555 - extra  (5 токен)
```
Максимальное кол-во токенов - 5.  
Диапазоны допустимых значений отдельных токенов зависят от используемого [формата][F] версии.  

## Преобразование версии в строку
За преобразование в строку отвечают две макро-функции:  
  - `dMAKE_STR_VERSION`
  - `dVERSION_STR`

`dVERSION_STR` - принимает на входе имя дефайна версии,  
либо само значение версии:  
последовательность токенов, разделенных запятыми.  
Далее, версия преобразуется в текст в формате `COMPACT`.  

```cpp
#define dMY_VERSION 1,22,3,44,555
dMESSAGE("version: " dVERSION_STR(dMY_VERSION))
dMESSAGE("version: " dVERSION_STR(1,22,3,44,555))
```

`dMAKE_STR_VERSION` - ожидает, что имя дефайна заданно в формате: `имяВерсии_VERSION`  
А в качестве аргумента передаем только часть имени: `имяВерсии`  

Если `dMAKE_STR_VERSION` запущен с 1 аргументом, 
тогда предполагается, что аргумент - `имяВерсии`  

Если `dMAKE_STR_VERSION` запущен с 2 аргументами, 
тогда первый аргумент - желаемый формат, а второй - `имяВерсии`  

```cpp
#define dMY_VERSION 1,22,3,44,555

// --- по умолчанию: формат COMPACT
dMESSAGE("version: " dMAKE_STR_VERSION(dMY))           

// --- с явным указанием формата
dMESSAGE("version: " dMAKE_STR_VERSION(COMPACT, dMY))  
dMESSAGE("version: " dMAKE_STR_VERSION(CLASSIC, dMY))  
dMESSAGE("version: " dMAKE_STR_VERSION(PLUGIN , dMY))  
dMESSAGE("version: " dMAKE_STR_VERSION(TOOLS  , dMY))  
```

## Преобразование версии в число
За преобразование в число отвечают две макро-функции:  
  - `dMAKE_NUM_VERSION`
  - `dVERSION_NUM`

`dVERSION_NUM` - принимает на входе имя дефайна версии, 
либо само значение версии: последовательность токенов, разделенных запятыми.  
Далее, версия преобразуется в число в формате `COMPACT`.  

```cpp
#define dMY_VERSION 1,22,3,44,555
const size_t v1 = dVERSION_NUM(dMY_VERSION));
const size_t v2 = dVERSION_NUM(1,22,3,44,555));
```

`dMAKE_NUM_VERSION` - ожидает, что имя дефайна версии заданно в формате: `имяВерсии_VERSION`  
При этом в качестве аргумента нужно передовать только часть имени: `имяВерсии`  

Если `dMAKE_NUM_VERSION` запущен с 1 аргументом, 
тогда предполагается, что аргумент - `имяВерсии`  

Если `dMAKE_NUM_VERSION` запущен с 2 аргументами, 
тогда первый аргумент - желаемый формат, а второй - `имяВерсии`  

```cpp
#define dMY_VERSION 1,22,3,44,555

// --- по умолчанию: формат COMPACT
std::cout << dMAKE_NUM_VERSION(dMY)) << '\n';

// --- с явным указанием формата
std::cout << dMAKE_NUM_VERSION(COMPACT, dMY)) << '\n';  
std::cout << dMAKE_NUM_VERSION(CLASSIC, dMY)) << '\n'; 
std::cout << dMAKE_NUM_VERSION(PLUGIN , dMY)) << '\n'; 
std::cout << dMAKE_NUM_VERSION(TOOLS  , dMY)) << '\n'; 
```

## Сравнение версий
Сравнение можно исполнять времени препроцессора:

```cpp
#define dVERSION_ONE 1,99,9,99
#define dVERSION_TWO 2,22,3,44

#if dVERSION_NUM(dVERSION_ONE) < dVERSION_NUM(dVERSION_TWO)
    // actions...
#endif

#if dMAKE_NUM_VERSION(TOOLS, dVERSION_ONE) < dMAKE_NUM_VERSION(TOOLS, dVERSION_TWO)
    // actions...
#endif
```

## Форматы версий
Формат версии определяет смысловое значение каждого токена,  
и то, как этот токен должен быть преобразован в число или в текст.  

Из коробки доступны следующие форматы:  
| **ID** |     формат     | макс значение | major   | minor  | patch | branch | extra |  
|:------:|:--------------:|:-------------:|:-------:|:------:|:-----:|:------:|:-----:|  
|  0000  |  COMPACT       | 9.99.9.99.999 |  0-9    |  0-99  |  0-9  |  0-99  | 0-999 |  
|  0001  |  CLASSIC       | 99.99.99.999  |  0-99   |  0-99  |  0-99 |  0-999 |  n/a  |  
|  0002  |  PLUGIN        | 9999.99       |  0-9999 |  0-99  |  n/a  |  n/a   |  n/a  |  
|  0003  |  TOOLS         | 9999.9999     |  0-9999 | 0-9999 |  n/a  |  n/a   |  n/a  |  

## Кастомный формат
При желании, пользователь может изготовить свой собственный формат версии.  
Для этого нужно просто реализовать ещё один набор макро-функций по аналогии с уже существующими форматами.  
Например:  

```cpp
#define dVERSION_COMPACT_STR_0()                   error_0
#define dVERSION_COMPACT_STR_1(a1)                 dSSTRINGIZE(a1)
#define dVERSION_COMPACT_STR_2(a1, a2)             dSSTRINGIZE(a1.a2)
#define dVERSION_COMPACT_STR_3(a1, a2, a3)         dSSTRINGIZE(a1.a2.a3)
#define dVERSION_COMPACT_STR_4(a1, a2, a3, a4)     dSSTRINGIZE(a1.a2.a3.a4)
#define dVERSION_COMPACT_STR_5(a1, a2, a3, a4, a5) dSSTRINGIZE(a1.a2.a3.a4.a5)
#define dVERSION_COMPACT_STR(...) \
    dMACRO_CHOOSER_5(dVERSION_COMPACT_STR, __VA_ARGS__)(__VA_ARGS__)

// compact version format: 9.99.9.99.999
#define dVERSION_COMPACT_NUM_0()                   error_0
#define dVERSION_COMPACT_NUM_1(a1)                 a1 * 100000000
#define dVERSION_COMPACT_NUM_2(a1, a2)             a1 * 100000000 + a2 * 1000000
#define dVERSION_COMPACT_NUM_3(a1, a2, a3)         a1 * 100000000 + a2 * 1000000 + a3 * 100000
#define dVERSION_COMPACT_NUM_4(a1, a2, a3, a4)     a1 * 100000000 + a2 * 1000000 + a3 * 100000 + a4 * 1000
#define dVERSION_COMPACT_NUM_5(a1, a2, a3, a4, a5) a1 * 100000000 + a2 * 1000000 + a3 * 100000 + a4 * 1000 + a5
#define dVERSION_COMPACT_NUM(...) \
    dMACRO_CHOOSER_5(dVERSION_COMPACT_NUM, __VA_ARGS__)(__VA_ARGS__)
```
Обратите внимание: часть имени `COMPACT` определяет имя формата.  
Вместо этого фрагмента нужно будет подставить имя своего формата.  
Под разное кол-во токенов можно использовать различные алгоритмы преобразований.  



История изменений 
------

| **ID** |      tools      | версия |     дата      |  время   |   ветка   |  
|:------:|:---------------:|:------:|:-------------:|:--------:|:---------:|  
|  0000  | 0.2.7 [![P]][T] | 1.0.2  | 2021y-05m-08d | 23:44:00 | #9_update |  
