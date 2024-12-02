# Taxi_Backend  

**Taxi_Backend** — це додаток для управління системою таксі, розроблений з урахуванням сучасних архітектурних підходів та використанням надійних технологій. Проєкт надає функціонал для реєстрації користувачів, бронювання поїздок, управління балансом, створення звітів і ведення логування.  

---

## Основний функціонал  
- **Аутентифікація та авторизація**: Безпечна реєстрація та вхід для водіїв і пасажирів.  
- **Бронювання поїздок**: Розрахунок відстані, вартості та часу в дорозі з використанням API-запитів.  
- **Управління балансом**: Поповнення, списання коштів і облік транзакцій для користувачів.  
- **Статистика та звіти**: Генерація статистики по поїздках, перегляд заробітків і експорт даних у форматі CSV.  
- **Логування та моніторинг**: Інтеграція з ElasticSearch для централізованого збору логів та їх візуалізації.  
- **Сесії**: Реалізація сесій за допомогою **патерну проєктування Singleton**.  

---

## Використані технології  
- **База даних**: SQLite із гарантіями ACID для забезпечення надійності даних.  
- **Логування**: ElasticSearch для збору, збереження та аналізу логів.  
- **API-запити**: Використання зовнішніх API для обчислення відстані, часу в дорозі та інших сервісів.  
- **Архітектурний підхід**:  
  - **Clean Architecture**: Чітке розділення на рівні для спрощення підтримки:  
  - **Backend for Frontend (BFF)**: Проєкт реалізовано на C++ із урахуванням архітектурного підходу BFF, наприклад (Flutter, FastAPI ...) 
  - **SOLID**: Дотримання принципів об'єктно-орієнтованого проєктування для підвищення зрозумілості й масштабованості коду.  

---

## Архітектура бази даних  
База даних побудована на основі SQLite і включає наступні таблиці:  
1. **Users**: Загальна інформація про користувачів.  
2. **Driver**: Атрибути для водіїв із зовнішнім ключем (Foreign Key) до таблиці Users.  
3. **Passenger**: Атрибути для пасажирів із зовнішнім ключем (Foreign Key) до таблиці Users.  
4. **Orders**: Відстеження замовлень, включаючи пункти відправлення і призначення, вартість і статус.  

*Схема бази даних:*  
![image](https://github.com/user-attachments/assets/07420c1f-b580-4aeb-8e70-997ec660a566)

---

## Установка і запуск  
1. Клонуйте репозиторій:  
   ```bash
   git clone https://github.com/Davidkovel/Taxi_Backend.git
   cd Taxi_Backend
