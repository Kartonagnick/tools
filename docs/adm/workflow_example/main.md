﻿
Синопсис:
---------

1. Имя задачи: `example`  
2. #ID задачи: `#33`  
3. Имя бранча: `#33_example`  
4. Последний коммит: `fix #33, example`  
5. Имя пулл-реквеста: `fix #33, example`  

Пример полного рабочего цикла с использованием github
-----------------------------------------------------

1. Для нашего примера пусть будет:  
     - Дата создания задачи: `2021y-01m-09d`  
     - Дата начала работы над задачей: `2021y-01m-10d`  
     - Дата завершения работы над задачей: `2021y-01m-11d`  
     - #ID issue в github: `#33`  
     - Исполнитель задачи: `Kartonagnick`  

2. В github создаём новый issue:  
     - Название: example  
     - Описание: "Пример задачи"  
     - Нажимаем на кнопку: "submit new issue"  
     - Дата создания в нашем примере: `2021y-01m-09d`  

3. github создает новый issue:  
     - Новому issue присваивается уникальный #ID (#33)  
     - Новое issue появляется в списке issues.  
     - Новое issuse появляется на доске проекта:  
       - Для больших досок в столбце `Backlog`  
       - Для маленьких досок в столбце `To do`  

4. Перемещаем карточку задачи в столбик "In Progress".  
     - Это означает, что работа над задачей уже началась.  
     - Дата начала работы: `2021y-01m-10d`  

5. Заходим в ветку `master`, и ищем последний версионный коммит:  
     - имеет формат: `version: major.minor.patch`  

6. От ветки master, от версионного коммита, делаем бранч: `#33_example`.  
     Где:  
       - `#33` - #ID issue в github.  
       - `example` - имя issue в github.  
 
7. Переключившись на новый бранч, заходим в каталог: `docs/tasks`  
8. Создаём файл задачи по имени: `2021y-01m-09d-00033-example.md`  
     Где:  
       - `2021y-01m-09d` - дата создания issue в github.  
       - `00033` - #ID issue в github.  
       - `example` - имя issue в github.  

9. Записываем в файл шапку и текст задачи:  
     ```
     [2021y-01m-10d] Kartonagnick
     ---

     example
     -------

     Пример задачи
     ```

10. Обратите внимание: работа над назадачей ещё не закончилась,
    поэтому, дата окончания задачи ещё не указана.  


11. Разработчик спокойно закончил работу над задачей:  
      - выполнил цели задачи.  
      - подготовил бранч к code-review.  
      - последний коммит в бранче имеет формат: `fix #ID, task-name`  
      - в файле задачи указана дата завершения, и время, 
        которое было затраченно на выполнение данной задачи:  

       ```
       [2021y-01m-10d][2021y-01m-11d] (24h) Kartonagnick
       ---

       example
       -------

       Пример задачи
       ```

12. Создаётся пул-реквест по имени: `fix #33, example`  
13. В github связываем пул-реквест с issue.  
     - в столбике 'Review' появляется карточка пулл-реквеста.  

14. Выполняем code-review:  
     - если обнаружили проблемы:  
       - разработчик вносит исправления в своём бранче.  
       - дата окончания работы смещается право.  
       - время затраченное на задачу смещается вправо.  

15. Когда code-review успешно пройден, нажимаем на кнопку: "принять пулл-реквест".  
      - `#33_example` будет слит с `master`  
      - карточки issue и пулреквеста переместятся с толбик `Done`  

16. Теперь руководитель проекта может увеличить версию продукта, 
    либо подкопить ещё подкопить пулл-реквесты.  




