
[P]: ../images/progress.png
[V]: ../images/success.png
[X]: ../images/failed.png
[D]: ../images/danger.png
[E]: ../images/empty.png
[N]: ../images/na.png

version 1.0.9
---

| **ID** | элемент                                    | tools | версия |  статус   |  
|:------:|:------------------------------------------:|:-----:|:------:|:---------:|  
|  0000  | [dMESSAGE][00]                             | 0.0.1 | 1.0.1  | [![V]][M] |  
|  0001  | [dHAS_RVALUE_REFERENCES][01]               | 0.0.1 | 1.0.1  | [![V]][M] |  
|  0002  | [dHAS_CPP11][02]                           | 0.0.1 | 1.0.1  | [![V]][M] |  
|  0003  | [dHAS_CONSTEXPR_CPP11][03]                 | 0.0.1 | 1.0.1  | [![V]][M] |  
|  0004  | [dCONSTEXPR_CPP11][04]                     | 0.0.1 | 1.0.1  | [![V]][M] |  
|  0005  | [dHAS_TEMPLATE_FUNCTION_DEFAULT_PARAM][05] | 0.0.1 | 1.0.1  | [![V]][M] |  
|  0006  | [dHAS_DELETING_FUNCTIONS][06]              | 0.0.1 | 1.0.1  | [![V]][M] |  
|  0007  | [dHAS_USING_ALIAS][07]                     | 0.0.1 | 1.0.1  | [![V]][M] |  
|  0008  | [dNOCOPYABLE][08]                          | 0.0.1 | 1.0.1  | [![V]][M] |  
|  0009  | [dHAS_NOEXCEPT][09]                        | 0.0.1 | 1.0.1  | [![V]][M] |  
|  0010  | [dNOEXCEPT][10]                            | 0.0.1 | 1.0.1  | [![V]][M] |  
|  0011  | [dHAS_CPP14][11]                           | 0.0.1 | 1.0.1  | [![V]][M] |  
|  0012  | [dHAS_CONSTEXPR_CPP14][12]                 | 0.0.1 | 1.0.1  | [![V]][M] |  
|  0013  | [dCONSTEXPR_CPP14][13]                     | 0.0.1 | 1.0.1  | [![V]][M] |  
|  0014  | [dHAS_RVALUE_ARRAY][14]                    | 0.0.1 | 1.0.1  | [![V]][M] |  
|  0015  | [dHAS_CPP17][15]                           | 0.0.1 | 1.0.1  | [![V]][M] |  
|  0016  | [dNODISCARD][16]                           | 0.0.1 | 1.0.1  | [![V]][M] |  
|  0017  | [dHAS_ATOMIC][17]                          | 0.0.3 | 1.0.2  | [![V]][M] |  
|  0018  | [dHAS_NULLPTR][18]                         | 0.0.3 | 1.0.2  | [![V]][M] |  
|  0019  | [dHAS_ENUM_CLASS][19]                      | 0.0.7 | 1.0.3  | [![V]][M] |  
|  0020  | [dHAS_STATIC_ASSERT][20]                   | 0.0.8 | 1.0.4  | [![V]][M] |  
|  0021  | [dHAS_VARIADIC_TEMPLATE][21]               | 0.0.9 | 1.0.5  | [![V]][M] |  
|  0022  | [dHAS_HASH][22]                            | 0.0.9 | 1.0.5  | [![V]][M] |  
|  0023  | [dHAS_TYPE_TRAITS][23]                     | 0.1.0 | 1.0.6  | [![V]][M] |  
|  0024  | [dHAS_CHRONO][24]                          | 0.1.0 | 1.0.6  | [![V]][M] |  
|  0025  | [dTHREAD_LOCAL_EXTENSION][25]              | 0.1.0 | 1.0.6  | [![V]][M] |  
|  0026  | [dHAS_THREAD_LOCAL][26]                    | 0.1.0 | 1.0.6  | [![V]][M] |  
|  0027  | [dHAS_EMPLACE][27]                         | 0.1.4 | 1.0.7  | [![V]][M] |  
|  0028  | [dHAS_CSTDINT][28]                         | 0.1.8 | 1.0.8  | [![V]][M] |  
|  0029  | [dCONSTANT][29]                            | 0.1.8 | 1.0.8  | [![V]][M] |  
|  0030  | [dHAS_AGGREGATE_INITIALIZE][30]            | 0.2.4 | 1.0.9  | [![V]][M] |  

[M]:  #features  "возможности компиляторов"  
[00]: #features  "вывод сообщений времени сборки"  
[01]: #features  "поддерживает ли компилятор rvalue reference"  
[02]: #features  "поддерживает ли компилятор c++11"  
[03]: #features  "поддерживает ли компилятор constexpr c++11"  
[04]: #features  "constexpr/inline"  
[05]: #features  "поддерживают ли компилятор параметры по умолчанию для шаблонов функций"  
[06]: #features  "поддерживают ли компилятор синтаксис удаленных функций"  
[07]: #features  "поддерживают ли компилятор шаблонный typedef (template using)"  
[08]: #features  "макрос dNOCOPYABLE"  
[09]: #features  "поддерживает ли компилятор noexcept"  
[10]: #features  "макрос dNOEXCEPT"  
[11]: #features  "поддерживают ли компилятор c++14"  
[12]: #features  "поддерживают ли компилятор constexpr c++14"  
[13]: #features  "constexpr/inline"  
[14]: #features  "поддерживает ли компилятор rvalue reference для массивов"  
[15]: #features  "поддерживает ли компилятор c++17"  
[16]: #features  "атрибут [[nodiscard]]"  
[17]: #features  "поддерживает ли компилятор <atomic>"  

[18]: #features  "поддерживает ли компилятор nullptr"  
[19]: #features  "поддерживает ли компилятор enum class"  
[20]: #features  "поддерживает ли компилятор static_assert"  
[21]: #features  "поддерживает ли компилятор variadic template"  
[22]: #features  "поддерживает ли компилятор std::hash"  
[23]: #features  "поддерживает ли компилятор <type_traits>"  
[24]: #features  "поддерживает ли компилятор <chrono>"  
[25]: #features  "расширение от компилятора: thread_local"  
[26]: #features  "поддерживает ли компилятор thread_local"  
[27]: #features  "поддерживаются ли методы emplace для стандартных контейнеров"
[28]: #features  "поддерживает ли компилятор <cstdint>"
[29]: #features  "constexpr/const"
[30]: #features  "поддерживает ли компилятор агрегатную инициализацию"
