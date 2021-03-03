
unit tests
----------

Зарезервированные имена юнит-тестов.  

test-000-platform    тесты свойств платформы.  
  - [x] макросы версии 103  
    - [x] dMESSAGE  
    - [x] dHAS_NULLPTR  
    - [x] dHAS_RVALUE_REFERENCES  
    - [x] dHAS_ENUM_CLASS  
    - [x] dHAS_ATOMIC  
    - [x] dHAS_CPP11  
    - [x] dHAS_CONSTEXPR_CPP11  
    - [x] dCONSTEXPR_CPP11  
    - [x] dHAS_TEMPLATE_FUNCTION_DEFAULT_PARAM  
    - [x] dHAS_DELETING_FUNCTIONS  
    - [x] dHAS_USING_ALIAS  
    - [x] dNOCOPYABLE  
    - [x] dHAS_NOEXCEPT  
    - [x] dNOEXCEPT  
    - [x] dCONSTEXPR_CPP14  
    - [x] dHAS_CONSTEXPR_CPP14  
    - [x] dHAS_CPP14  
    - [x] dHAS_RVALUE_ARRAY  
    - [x] dHAS_CPP17  
    - [x] dNODISCARD  
  - [x] макросы версии 104  
    - [x] dHAS_STATIC_ASSERT  
    - [x] dSTATIC_ASSERT  
  - [x] макросы версии 105  
    - [x] dHAS_VARIADIC_TEMPLATE  
    - [x] dHAS_HASH  


test-100-macro       тесты модуля препроцессорной магии.  
test-200-types       тесты модуля анализа типов.  
test-300-staff       тесты служебной библиотеки staff.  
test-400-strlen      тесты функции вычисления длины строки.  
test-500-stringed    тесты модуля операций со строками.  

test-600-others      тесты мелких инструментов:  
  - [x] assert  
  - [x] raise  
  - [x] counter  
  - [x] copies  
  - [x] synch  
  - [x] flag  
    - [x] flag\flag_synch  
    - [x] flag\flag_void  
    - [x] flag\function  
    - [x] flag\template  
  - [x] errno  
  - [x] hash  
    - [x] hash\combine  
    - [x] hash\accum  
    - [x] hash\hash  

test-700-thread      тесты модуля работы с потоками.  
test-800-time        тесты модуля для работы со временем.  
test-modern          тесты classic/modern.  
