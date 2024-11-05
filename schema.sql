-- Если база данных еще не создана, создайте ее вручную:
-- В командной строке или через клиент psql:
-- CREATE DATABASE autodealership;

-- Подключение к базе данных (в psql):
-- \c autodealership;

-- Создание таблицы должностей
CREATE TABLE Positions (
    position_id SERIAL PRIMARY KEY,
    position_name VARCHAR(100) NOT NULL
);

-- Создание таблицы сотрудников
CREATE TABLE Employees (
    employee_id SERIAL PRIMARY KEY,
    last_name VARCHAR(50) NOT NULL,
    first_name VARCHAR(50) NOT NULL,
    patronymic VARCHAR(50),
    address VARCHAR(200),
    date_of_birth DATE,
    position_id INT REFERENCES Positions(position_id),
    salary NUMERIC(10,2)
);

-- Создание таблицы сведений о перемещении сотрудников
CREATE TABLE EmployeeMovements (
    movement_id SERIAL PRIMARY KEY,
    employee_id INT REFERENCES Employees(employee_id),
    position_id INT REFERENCES Positions(position_id),
    reason VARCHAR(200),
    order_number VARCHAR(50),
    order_date DATE
);

-- Создание таблицы клиентов
CREATE TABLE Clients (
    client_id SERIAL PRIMARY KEY,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    patronymic VARCHAR(50),
    passport_data VARCHAR(100) NOT NULL
);

-- Создание таблицы документов
CREATE TABLE Documents (
    document_id SERIAL PRIMARY KEY,
    document_number VARCHAR(50),
    document_name VARCHAR(100),
    issue_date DATE,
    issued_by VARCHAR(100)
);


-- Создание таблицы автомобилей
CREATE TABLE Cars (
    car_id SERIAL PRIMARY KEY,
    make VARCHAR(50),
    model VARCHAR(50),
    color VARCHAR(30),
    engine_number VARCHAR(50),
    registration_number VARCHAR(20),
    body_number VARCHAR(50),
    chassis_number VARCHAR(50),
    manufacture_date DATE,
    mileage INT,
    manufacture_price NUMERIC(10,2),
    sale_price NUMERIC(10,2),
    purchase_price NUMERIC(10,2),
    technical_certificate_number VARCHAR(50),
    technical_certificate_date DATE,
    expert_id INT REFERENCES Employees(employee_id)
);

-- Создание таблицы продаж (покупатели)
CREATE TABLE Sales (
    sale_id SERIAL PRIMARY KEY,
    client_id INT REFERENCES Clients(client_id),
    car_id INT REFERENCES Cars(car_id),
    sale_date DATE,
    account_number VARCHAR(50),
    payment_method VARCHAR(50)
);

-- Создание таблицы покупок (продавцы)
CREATE TABLE Purchases (
    purchase_id SERIAL PRIMARY KEY,
    client_id INT REFERENCES Clients(client_id),
    car_id INT REFERENCES Cars(car_id),
    purchase_date DATE,
    document_id INT REFERENCES Documents(document_id)
);

-- Создание таблицы запчастей
CREATE TABLE SpareParts (
    spare_part_id SERIAL PRIMARY KEY,
    name VARCHAR(100),
    make VARCHAR(50),
    model VARCHAR(50),
    price NUMERIC(10,2),
    stock_quantity INT
);

-- Заполнение таблицы Positions
INSERT INTO Positions (position_name) VALUES
('Директор'),
('Менеджер по продажам'),
('Механик'),
('Бухгалтер'),
('Администратор'),
('Эксперт по техническому осмотру'),
('Секретарь'),
('Маркетолог');

-- Заполнение таблицы Employees
INSERT INTO Employees (last_name, first_name, patronymic, address, date_of_birth, position_id, salary) VALUES
('Иванов', 'Иван', 'Иванович', 'ул. Ленина, д.1', '1980-01-01', 1, 150000.00),
('Петров', 'Петр', 'Петрович', 'ул. Советская, д.2', '1982-02-02', 2, 80000.00),
('Сидоров', 'Алексей', 'Алексеевич', 'ул. Мира, д.3', '1985-03-03', 3, 60000.00),
('Кузнецова', 'Мария', 'Викторовна', 'ул. Гагарина, д.4', '1990-04-04', 4, 70000.00),
('Воробьева', 'Анна', 'Сергеевна', 'ул. Победы, д.5', '1988-05-05', 5, 50000.00),
('Морозов', 'Дмитрий', 'Павлович', 'ул. Кирова, д.6', '1992-06-06', 6, 65000.00),
('Смирнов', 'Андрей', 'Игоревич', 'ул. Пушкина, д.7', '1985-07-07', 6, 65000.00),
('Попова', 'Елена', 'Николаевна', 'ул. Чехова, д.8', '1993-08-08', 7, 40000.00),
('Лебедев', 'Сергей', 'Евгеньевич', 'ул. Толстого, д.9', '1989-09-09', 2, 80000.00),
('Новикова', 'Ольга', 'Владимировна', 'ул. Тургенева, д.10', '1991-10-10', 8, 75000.00);

-- Заполнение таблицы EmployeeMovements
INSERT INTO EmployeeMovements (employee_id, position_id, reason, order_number, order_date) VALUES
(2, 2, 'Повышение квалификации', '№101', '2020-01-15'),
(3, 3, 'Перевод в другой отдел', '№102', '2020-02-20'),
(5, 5, 'Назначение на должность', '№103', '2020-03-25'),
(6, 6, 'Повышение квалификации', '№104', '2020-04-30'),
(9, 2, 'Перевод в другой отдел', '№105', '2020-05-05');

-- Заполнение таблицы Clients
INSERT INTO Clients (first_name, last_name, patronymic, passport_data) VALUES
('Александр', 'Ковалев', 'Иванович', 'Паспорт №100200'),
('Максим', 'Ильин', 'Петрович', 'Паспорт №100201'),
('София', 'Кузьмина', 'Алексеевна', 'Паспорт №100202'),
('Даниил', 'Семенов', 'Максимович', 'Паспорт №100203'),
('Полина', 'Волкова', 'Андреевна', 'Паспорт №100204'),
('Михаил', 'Зайцев', 'Егорович', 'Паспорт №100205'),
('Алина', 'Соловьева', 'Романовна', 'Паспорт №100206'),
('Матвей', 'Лебедев', 'Денисович', 'Паспорт №100207'),
('Елизавета', 'Никитина', 'Владимировна', 'Паспорт №100208'),
('Илья', 'Сорокин', 'Сергеевич', 'Паспорт №100209');

-- Заполнение таблицы Documents
INSERT INTO Documents (document_number, document_name, issue_date, issued_by) VALUES
('DOC1001', 'Свидетельство о собственности', '2019-01-10', 'МРЭО №1'),
('DOC1002', 'Свидетельство о собственности', '2019-02-15', 'МРЭО №2'),
('DOC1003', 'Свидетельство о собственности', '2019-03-20', 'МРЭО №3');



-- Заполнение таблицы Cars
INSERT INTO Cars (make, model ,color, engine_number, registration_number, body_number, chassis_number, manufacture_date, mileage, manufacture_price, sale_price, purchase_price, technical_certificate_number, technical_certificate_date, expert_id) VALUES
('Toyota', 'Camry', 'Черный', 'EN1001', 'REG1001', 'BN1001', 'CH1001', '2018-01-10', 20000, 1500000.00, 1600000.00, 1400000.00, 'TCN1001', '2020-01-15', 6),
('Honda', 'Accord', 'Белый', 'EN1002', 'REG1002', 'BN1002', 'CH1002', '2017-02-15', 30000, 1400000.00, 1500000.00, 1300000.00, 'TCN1002', '2020-02-20', 6),
('BMW', 'X5', 'Серый', 'EN1003', 'REG1003', 'BN1003', 'CH1003', '2016-03-20', 40000, 1300000.00, 1400000.00, 1200000.00, 'TCN1003', '2020-03-25', 6),
('Mercedes-Benz', 'E-Class', 'Синий', 'EN1004', 'REG1004', 'BN1004', 'CH1004', '2019-04-25', 10000, 1600000.00, 1700000.00, 1500000.00, 'TCN1004', '2020-04-30', 6),
('Audi', 'A6', 'Красный', 'EN1005', 'REG1005', 'BN1005', 'CH1005', '2020-05-30', 5000, 1700000.00, 1800000.00, NULL, 'TCN1005', '2020-05-05', 6);

-- Заполнение таблицы Sales (покупатели)
INSERT INTO Sales (client_id, car_id, sale_date, account_number, payment_method) VALUES
(1, 1, '2020-01-20', 'ACC1001', 'Наличный расчет'),
(2, 2, '2020-02-25', 'ACC1002', 'Безналичный расчет'),
(3, 3, '2020-03-30', 'ACC1003', 'Кредит');

-- Заполнение таблицы Purchases (продавцы)
INSERT INTO Purchases (client_id, car_id, purchase_date, document_id) VALUES
(4, 4, '2020-04-05', 1),
(5, 5, '2020-05-10', 2);

-- Заполнение таблицы SpareParts
INSERT INTO SpareParts (name, make, model, price, stock_quantity) VALUES
('Фильтр масляный', 'Toyota', 'Camry', 500.00, 50),
('Тормозные колодки', 'Honda', 'Accord', 1500.00, 30),
('Свечи зажигания', 'BMW', 'X5', 800.00, 70),
('Воздушный фильтр', 'Mercedes-Benz', 'E-Class', 600.00, 40),
('Аккумулятор', 'Audi', 'A6', 5000.00, 20);