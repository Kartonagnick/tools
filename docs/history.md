
Основан
-------
20 февраля 2021 18:41:19 Картонажником.  

[2021y-02m-20d][18:41:19] Idrisov Denis R.  
[2021y-02m-20d][18:41:19] birthday of the project  


**История изменений**  

**Версия 0.2.6 (предварительная)**  
----------------------------------
[2021y-03m-17d][23:44:05]  

1) add: tools/pragma                   100  
    - add: pragma.hpp                 100  
    - add: magic                      001  
    - add: warning                    (без версии)  

2) add: types/common.hpp                 100  
     - types/common/common-msvc2015.hpp 100  
        - degradate                    100  
        - dfor_lvalue                  100  
        - for_rvalue                   100  
     - types/common/common-msvc2013.hpp 100  
        - degradate                    100  
        - dfor_lvalue                  100  


**Версия 0.2.5 (предварительная)**  
----------------------------------
[2021y-03m-16d][18:58:45]  
1) Реорганизация проектной документации.  
2) аудит кода.  
    - add: types/types.hpp                100  
    - add: algorithm/algorithm.hpp        001  
    - upd: tools/flag/template-cpp98.hpp  100  
    - upd: tools/flag/template-cpp11.hpp  100  
    - upd: tools/flag/template.hpp        100  


**Версия 0.2.4 (предварительная)**  
----------------------------------
[2021y-03m-15d][21:35:16]  
1) add: algorithm/tokenizer.hpp    001  

2) upd: features:                  109  
    - `dHAS_AGGREGATE_INITIALIZE`             поддерживается ли агрегатная инициализация вида: `type obj { params};`  


**Версия 0.2.3 (предварительная)**  
----------------------------------
[2021y-03m-14d][23:55:31]  
1) upd: traits                           002  
    - add: remove_reference            001  
    - add: decay                       001  

2) add:  
    - tools/algorithm/find_first_of.hpp  001  
    - tools/valid.hpp                    001  


**Версия 0.2.2 (предварительная)**  
----------------------------------
[2021y-03m-13d][23:47:05]  
1) upd:  tools/numeric.hpp  003 (не изменился)  
  - assert_safe_cast  
  - safe_cast  


**Версия 0.2.1 (предварительная)**  
----------------------------------
[2021y-03m-13d][22:24:07]  
1) rename:  
     - from: tools/numeric_cast.hpp   002  
     - to:   tools/numeric.hpp        003  
[2021y-03m-13d][23:12:07]
2) дополнительные тесты assert  


**Версия 0.2.0 (предварительная)**  
----------------------------------
[2021y-03m-12d][23:30:12]  
1) bug: assert.hpp                    100 (почему не изменился?)  

2) upd: tools/numeric_cast.hpp  002  
     - assert_numeric_cast  
     - can_numeric_cast  
     - numeric_cast  


**Версия 0.1.9 (предварительная)**  
----------------------------------
[2021y-03m-11d][23:18:42]  
1) upd: tools/types/fixed.hpp       100 (почему не изменился?)  
     - fixed-cpp98                100  
     - fixed-cpp11                100  

2) add: tools/types/traits.hpp      001  
     - is_same                    001  
     - remove_cv                  001  
     - is_signed                  001  
     - is_floating_point          001  
     - is_integral                001  
     - conditional                001  
     - enable_if                  001  
     - type_of_enum (msvc2012)    001  

3) add: tools/cast.hpp                  001  
     - can_numeric_cast               001  

4) rename: 
     - from: tools/cast.hpp             001  
     - to:   tools/numeric_cast.hpp     001  


**Версия 0.1.8 (предварительная)**  
----------------------------------
[2021y-03m-11d][00:30:56]  
1) upd: tools/features.hpp     108  
    - `dHAS_CSTDINT`                          поддерживается ли `#include <cstdint>`
    - `dCONSTANT`                             если поддерживается `с++11`, тогда `constexpr`, иначе - `const`
2) add: tools/types/fixed.hpp  100  

3) add: test-200-types  

**Версия 0.1.7 (предварительная)**  
----------------------------------
[2021y-03m-09d][21:01:42]  
1) add: tools/macro  100  
    - [link](https://github.com/Kartonagnick/tools-macro/blob/master/docs/history.md#%D0%B2%D0%B5%D1%80%D1%81%D0%B8%D1%8F-101-%D0%B1%D0%BE%D0%B5%D0%B2%D0%B0%D1%8F)
    - версия компонентов 001  
    - после интеграции в tools, 
      версия модуля в исходном проекте стала равной 101  


**Версия 0.1.6 (предварительная)**  
----------------------------------
[2021y-03m-09d][01:44:12]  
аудит кода:  

1) bug: `conv.cpp`  
    - `multibyte::convert`  

2) bug: `utf8_win.cpp`  
    - incorrect assert  

3) upd: random         101  
    - add: thread-safe  

4) upd: `errno.cpp`  
    - add: thread-safe  

5) upd: `secure_msvc.cpp`  
    - add: thread-safe  

6) upd: seh            100 (почему не изменился?)  
   - chk: compilers errors  
   - upd: `seh.hpp`  
   - upd: `seh_win.cpp`  


**Версия 0.1.5 (предварительная)**  
----------------------------------
[2021y-03m-08d][05:36:27]  
1) add: tools/url.hpp   100  


**Версия 0.1.4 (предварительная)**  
----------------------------------
[2021y-03m-08d][03:31:39]  

1) upd: tools/features      107  
     - `dHAS_EMPLACE`                          поддерживают ли стандартные контейнеры метод `emplace`  

2) add: tools/marker.hpp    001  


**Версия 0.1.3 (предварительная)**  
----------------------------------
[2021y-03m-07d][10:33:15]  
1) add: tools/secure.hpp  100  
2) add: tools/seh.hpp     001  


**Версия 0.1.2 (предварительная)**  
----------------------------------
[2021y-03m-06d][04:07:27]  
1) chg: tools/utf8.hpp  100 (почему версия не изменилась?)  
2) add: tools/conv.hpp  100  


**Версия 0.1.1 (предварительная)**  
----------------------------------
[2021y-03m-05d][23:20:22]  
1) add: docs/images/limit  
2) add: tools/utf8.hpp      100  


**Версия 0.1.0 (предварительная)**  
----------------------------------
[2021y-03m-04d][20:32:05]  
1) add: random 100  

2) upd: feature  106  
    - add: `dHAS_TYPE_TRAITS`                  поддерживает ли компилятор `#include <type_traits>`  
    - add: `dHAS_NULLPTR`                      поддерживает ли компилятор `nullptr`  
    - add: `dHAS_CHRONO`                       поддерживает ли компилятор `#include <chrono>`  
    - add: `dTHREAD_LOCAL_EXTENSION`           расширение от компилятора `__declspec(thread)/__thread`  
    - add: `dHAS_THREAD_LOCAL`                 поддерживает ли компилятор `thread_local`  


**Версия 0.0.9 (предварительная)**  
----------------------------------
[2021y-03m-03d][23:47:23]  

1) очистка проекта  

2) add: tools/hash              100  
    - add: tools/hash/hash.hpp    100  
    - add: tools/hash/accum.hpp   100  
    - add: tools/hash/combine.hpp 100  

7) add: errno     100  
8) upd: features  105  
    - `dSTATIC_ASSERT`                         ассерт времени компиляции (для поддержки старых компиляторов)  
    - `dHAS_HASH`                              доступно ли `#include <hash>`  


**Версия 0.0.8 (предварительная)**  
----------------------------------
[2021y-02m-28d][07:09:00]  

1) обновлен: tools/flag            101  
   - теперь thread-safe  
2) добавлен: tools/flag/function   100  
3) добавлен: tools/flag/template   100  

4) обновлен: synch                 102  
    - добавлен: synch_guard  

5) обновлен: festures              104  
     - `dHAS_STATIC_ASSERT`                    поддерживает ли комппилятор `static_assert`  


**Версия 0.0.7 (предварительная)**  
----------------------------------
[2021y-02m-26d][06:30:00]  
1) добавлен: tools/flag          100  
2) обновлен: festures            103  
     - `dHAS_ENUM_CLASS`                       поддерживает ли комппилятор `enum class`  

**Версия 0.0.6 (предварительная)**  
----------------------------------
[2021y-02m-26d][05:20:00]  
1) добавлен: dFUNCTION           100  
2) покрытие тестами assert  


**Версия 0.0.5 (предварительная)**  
----------------------------------
[2021y-02m-25d][04:10:00]  
1) обновлен: festures            102  
    - косметические улучшения  
    - покрытие тестами  


**Версия 0.0.4 (предварительная)**  
----------------------------------
[2021y-02m-23d][20:30:00]  
1) обновлен: synch               101  
    - стал кросс-платформеным:  
      - platform/windows/sync -> tools/synch  

**Версия 0.0.3 (предварительная)**  
----------------------------------
[2021y-02m-22d][04:15:00]  
1) добавлен: tools/counter.hpp                 100  
2) добавлен: tools/platform/windows/sync.hpp   100  
3) добавлен: tools/copies.hpp                  100  
4) добавлен: tools/windows.hpp                 100  


**Версия 0.0.2 (предварительная)**  
----------------------------------
[2021y-02m-21d][00:00:00]  
1) добавлен: raise   100  


**Версия 0.0.1 (предварительная)**  
----------------------------------
[2021y-02m-20d][18:41:19]  
1) добавлен: каркас проекта  
2) добавлен: assert          100 (содержит баг)  
3) добавлен: festures        101  
     - `dMESSAGE`                              вывод сообщений в лог компиляции  
     - `dHAS_RVALUE_REFERENCES`                поддерживает ли компилятор `rvalue-ссылки`  
     - `dHAS_CPP11`                            поддерживает ли компилятор `с++11`  
     - `dHAS_CONSTEXPR_CPP11`                  поддерживает ли компилятор `constexpr (с++11)`  
     - `dCONSTEXPR_CPP11`                      если `с++11` поддерживается, тогда: `constexpr`, иначе: `const`  
     - `dHAS_TEMPLATE_FUNCTION_DEFAULT_PARAM`  поддерживаются ли параметры по умолчанию для шаблонов функций  
     - `dHAS_DELETING_FUNCTIONS`               поддерживается ли синтаксис `delete` для функций  
     - `dHAS_USING_ALIAS`                      поддерживается ли синтаксис `using type`  
     - `dNOCOPYABLE`                           макрос делает класс некопируемым  
     - `dHAS_NOEXCEPT`                         поддерживается ли ключевое слово `noexcept`  
     - `dNOEXCEPT`                             если `noexcept` не поддерживается, то макрос сворачивается в пустоту  
     - `dHAS_CPP14`                            поддерживает ли компилятор `с++14`  
     - `dHAS_CONSTEXPR_CPP14`                  поддерживает ли компилятор `constexpr (с++14)`  
     - `dCONSTEXPR_CPP14`                      если `с++14` поддерживается, тогда: `constexpr`, иначе: `const`  
     - `dHAS_RVALUE_ARRAY`                     поддерживает ли компилятор `rvalue-ссылки-на-массивы`  
     - `dHAS_CPP17`                            поддерживает ли компилятор `с++17`  
     - `dNODISCARD`                            поддерживается ли ключевое атрибут `[[nodiscard]]`  

