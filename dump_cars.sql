--
-- PostgreSQL database dump
--

-- Dumped from database version 17.0 (Debian 17.0-1.pgdg120+1)
-- Dumped by pg_dump version 17.0 (Debian 17.0-1.pgdg120+1)

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET transaction_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: cars; Type: TABLE; Schema: public; Owner: admin
--

CREATE TABLE public.cars (
    car_id integer NOT NULL,
    make character varying(50),
    model character varying(50),
    color character varying(30),
    engine_number character varying(50),
    registration_number character varying(20),
    body_number character varying(50),
    chassis_number character varying(50),
    manufacture_date date,
    mileage integer,
    manufacture_price numeric(10,2),
    sale_price numeric(10,2),
    purchase_price numeric(10,2),
    technical_certificate_number character varying(50),
    technical_certificate_date date,
    expert_id integer
);


ALTER TABLE public.cars OWNER TO admin;

--
-- Name: cars_car_id_seq; Type: SEQUENCE; Schema: public; Owner: admin
--

CREATE SEQUENCE public.cars_car_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.cars_car_id_seq OWNER TO admin;

--
-- Name: cars_car_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: admin
--

ALTER SEQUENCE public.cars_car_id_seq OWNED BY public.cars.car_id;


--
-- Name: clients; Type: TABLE; Schema: public; Owner: admin
--

CREATE TABLE public.clients (
    client_id integer NOT NULL,
    first_name character varying(50) NOT NULL,
    last_name character varying(50) NOT NULL,
    patronymic character varying(50),
    passport_data character varying(100) NOT NULL
);


ALTER TABLE public.clients OWNER TO admin;

--
-- Name: clients_client_id_seq; Type: SEQUENCE; Schema: public; Owner: admin
--

CREATE SEQUENCE public.clients_client_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.clients_client_id_seq OWNER TO admin;

--
-- Name: clients_client_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: admin
--

ALTER SEQUENCE public.clients_client_id_seq OWNED BY public.clients.client_id;


--
-- Name: documents; Type: TABLE; Schema: public; Owner: admin
--

CREATE TABLE public.documents (
    document_id integer NOT NULL,
    document_number character varying(50),
    document_name character varying(100),
    issue_date date,
    issued_by character varying(100)
);


ALTER TABLE public.documents OWNER TO admin;

--
-- Name: documents_document_id_seq; Type: SEQUENCE; Schema: public; Owner: admin
--

CREATE SEQUENCE public.documents_document_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.documents_document_id_seq OWNER TO admin;

--
-- Name: documents_document_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: admin
--

ALTER SEQUENCE public.documents_document_id_seq OWNED BY public.documents.document_id;


--
-- Name: employeemovements; Type: TABLE; Schema: public; Owner: admin
--

CREATE TABLE public.employeemovements (
    movement_id integer NOT NULL,
    employee_id integer,
    position_id integer,
    reason character varying(200),
    order_number character varying(50),
    order_date date
);


ALTER TABLE public.employeemovements OWNER TO admin;

--
-- Name: employeemovements_movement_id_seq; Type: SEQUENCE; Schema: public; Owner: admin
--

CREATE SEQUENCE public.employeemovements_movement_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.employeemovements_movement_id_seq OWNER TO admin;

--
-- Name: employeemovements_movement_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: admin
--

ALTER SEQUENCE public.employeemovements_movement_id_seq OWNED BY public.employeemovements.movement_id;


--
-- Name: employees; Type: TABLE; Schema: public; Owner: admin
--

CREATE TABLE public.employees (
    employee_id integer NOT NULL,
    last_name character varying(50) NOT NULL,
    first_name character varying(50) NOT NULL,
    patronymic character varying(50),
    address character varying(200),
    date_of_birth date,
    position_id integer,
    salary numeric(10,2)
);


ALTER TABLE public.employees OWNER TO admin;

--
-- Name: employees_employee_id_seq; Type: SEQUENCE; Schema: public; Owner: admin
--

CREATE SEQUENCE public.employees_employee_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.employees_employee_id_seq OWNER TO admin;

--
-- Name: employees_employee_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: admin
--

ALTER SEQUENCE public.employees_employee_id_seq OWNED BY public.employees.employee_id;


--
-- Name: positions; Type: TABLE; Schema: public; Owner: admin
--

CREATE TABLE public.positions (
    position_id integer NOT NULL,
    position_name character varying(100) NOT NULL
);


ALTER TABLE public.positions OWNER TO admin;

--
-- Name: positions_position_id_seq; Type: SEQUENCE; Schema: public; Owner: admin
--

CREATE SEQUENCE public.positions_position_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.positions_position_id_seq OWNER TO admin;

--
-- Name: positions_position_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: admin
--

ALTER SEQUENCE public.positions_position_id_seq OWNED BY public.positions.position_id;


--
-- Name: purchases; Type: TABLE; Schema: public; Owner: admin
--

CREATE TABLE public.purchases (
    purchase_id integer NOT NULL,
    client_id integer,
    car_id integer,
    purchase_date date,
    document_id integer
);


ALTER TABLE public.purchases OWNER TO admin;

--
-- Name: purchases_purchase_id_seq; Type: SEQUENCE; Schema: public; Owner: admin
--

CREATE SEQUENCE public.purchases_purchase_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.purchases_purchase_id_seq OWNER TO admin;

--
-- Name: purchases_purchase_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: admin
--

ALTER SEQUENCE public.purchases_purchase_id_seq OWNED BY public.purchases.purchase_id;


--
-- Name: sales; Type: TABLE; Schema: public; Owner: admin
--

CREATE TABLE public.sales (
    sale_id integer NOT NULL,
    client_id integer,
    car_id integer,
    sale_date date,
    account_number character varying(50),
    payment_method character varying(50)
);


ALTER TABLE public.sales OWNER TO admin;

--
-- Name: sales_sale_id_seq; Type: SEQUENCE; Schema: public; Owner: admin
--

CREATE SEQUENCE public.sales_sale_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.sales_sale_id_seq OWNER TO admin;

--
-- Name: sales_sale_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: admin
--

ALTER SEQUENCE public.sales_sale_id_seq OWNED BY public.sales.sale_id;


--
-- Name: spareparts; Type: TABLE; Schema: public; Owner: admin
--

CREATE TABLE public.spareparts (
    spare_part_id integer NOT NULL,
    name character varying(100),
    make character varying(50),
    model character varying(50),
    price numeric(10,2),
    stock_quantity integer
);


ALTER TABLE public.spareparts OWNER TO admin;

--
-- Name: spareparts_spare_part_id_seq; Type: SEQUENCE; Schema: public; Owner: admin
--

CREATE SEQUENCE public.spareparts_spare_part_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.spareparts_spare_part_id_seq OWNER TO admin;

--
-- Name: spareparts_spare_part_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: admin
--

ALTER SEQUENCE public.spareparts_spare_part_id_seq OWNED BY public.spareparts.spare_part_id;


--
-- Name: cars car_id; Type: DEFAULT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.cars ALTER COLUMN car_id SET DEFAULT nextval('public.cars_car_id_seq'::regclass);


--
-- Name: clients client_id; Type: DEFAULT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.clients ALTER COLUMN client_id SET DEFAULT nextval('public.clients_client_id_seq'::regclass);


--
-- Name: documents document_id; Type: DEFAULT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.documents ALTER COLUMN document_id SET DEFAULT nextval('public.documents_document_id_seq'::regclass);


--
-- Name: employeemovements movement_id; Type: DEFAULT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.employeemovements ALTER COLUMN movement_id SET DEFAULT nextval('public.employeemovements_movement_id_seq'::regclass);


--
-- Name: employees employee_id; Type: DEFAULT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.employees ALTER COLUMN employee_id SET DEFAULT nextval('public.employees_employee_id_seq'::regclass);


--
-- Name: positions position_id; Type: DEFAULT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.positions ALTER COLUMN position_id SET DEFAULT nextval('public.positions_position_id_seq'::regclass);


--
-- Name: purchases purchase_id; Type: DEFAULT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.purchases ALTER COLUMN purchase_id SET DEFAULT nextval('public.purchases_purchase_id_seq'::regclass);


--
-- Name: sales sale_id; Type: DEFAULT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.sales ALTER COLUMN sale_id SET DEFAULT nextval('public.sales_sale_id_seq'::regclass);


--
-- Name: spareparts spare_part_id; Type: DEFAULT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.spareparts ALTER COLUMN spare_part_id SET DEFAULT nextval('public.spareparts_spare_part_id_seq'::regclass);


--
-- Data for Name: cars; Type: TABLE DATA; Schema: public; Owner: admin
--

COPY public.cars (car_id, make, model, color, engine_number, registration_number, body_number, chassis_number, manufacture_date, mileage, manufacture_price, sale_price, purchase_price, technical_certificate_number, technical_certificate_date, expert_id) FROM stdin;
1	Toyota	Camry	Черный	EN1001	REG1001	BN1001	CH1001	2018-01-10	20000	1500000.00	1600000.00	1400000.00	TCN1001	2020-01-15	6
2	Honda	Accord	Белый	EN1002	REG1002	BN1002	CH1002	2017-02-15	30000	1400000.00	1500000.00	1300000.00	TCN1002	2020-02-20	6
3	BMW	X5	Серый	EN1003	REG1003	BN1003	CH1003	2016-03-20	40000	1300000.00	1400000.00	1200000.00	TCN1003	2020-03-25	6
4	Mercedes-Benz	E-Class	Синий	EN1004	REG1004	BN1004	CH1004	2019-04-25	10000	1600000.00	1700000.00	1500000.00	TCN1004	2020-04-30	6
5	Audi	A6	Красный	EN1005	REG1005	BN1005	CH1005	2020-05-30	5000	1700000.00	1800000.00	\N	TCN1005	2020-05-05	6
\.


--
-- Data for Name: clients; Type: TABLE DATA; Schema: public; Owner: admin
--

COPY public.clients (client_id, first_name, last_name, patronymic, passport_data) FROM stdin;
1	Александр	Ковалев	Иванович	Паспорт №100200
2	Максим	Ильин	Петрович	Паспорт №100201
3	София	Кузьмина	Алексеевна	Паспорт №100202
4	Даниил	Семенов	Максимович	Паспорт №100203
5	Полина	Волкова	Андреевна	Паспорт №100204
6	Михаил	Зайцев	Егорович	Паспорт №100205
7	Алина	Соловьева	Романовна	Паспорт №100206
8	Матвей	Лебедев	Денисович	Паспорт №100207
9	Елизавета	Никитина	Владимировна	Паспорт №100208
10	Илья	Сорокин	Сергеевич	Паспорт №100209
\.


--
-- Data for Name: documents; Type: TABLE DATA; Schema: public; Owner: admin
--

COPY public.documents (document_id, document_number, document_name, issue_date, issued_by) FROM stdin;
1	DOC1001	Свидетельство о собственности	2019-01-10	МРЭО №1
2	DOC1002	Свидетельство о собственности	2019-02-15	МРЭО №2
3	DOC1003	Свидетельство о собственности	2019-03-20	МРЭО №3
\.


--
-- Data for Name: employeemovements; Type: TABLE DATA; Schema: public; Owner: admin
--

COPY public.employeemovements (movement_id, employee_id, position_id, reason, order_number, order_date) FROM stdin;
1	2	2	Повышение квалификации	№101	2020-01-15
2	3	3	Перевод в другой отдел	№102	2020-02-20
3	5	5	Назначение на должность	№103	2020-03-25
4	6	6	Повышение квалификации	№104	2020-04-30
5	9	2	Перевод в другой отдел	№105	2020-05-05
\.


--
-- Data for Name: employees; Type: TABLE DATA; Schema: public; Owner: admin
--

COPY public.employees (employee_id, last_name, first_name, patronymic, address, date_of_birth, position_id, salary) FROM stdin;
1	Иванов	Иван	Иванович	ул. Ленина, д.1	1980-01-01	1	150000.00
2	Петров	Петр	Петрович	ул. Советская, д.2	1982-02-02	2	80000.00
3	Сидоров	Алексей	Алексеевич	ул. Мира, д.3	1985-03-03	3	60000.00
4	Кузнецова	Мария	Викторовна	ул. Гагарина, д.4	1990-04-04	4	70000.00
5	Воробьева	Анна	Сергеевна	ул. Победы, д.5	1988-05-05	5	50000.00
6	Морозов	Дмитрий	Павлович	ул. Кирова, д.6	1992-06-06	6	65000.00
7	Смирнов	Андрей	Игоревич	ул. Пушкина, д.7	1985-07-07	6	65000.00
8	Попова	Елена	Николаевна	ул. Чехова, д.8	1993-08-08	7	40000.00
9	Лебедев	Сергей	Евгеньевич	ул. Толстого, д.9	1989-09-09	2	80000.00
10	Новикова	Ольга	Владимировна	ул. Тургенева, д.10	1991-10-10	8	75000.00
\.


--
-- Data for Name: positions; Type: TABLE DATA; Schema: public; Owner: admin
--

COPY public.positions (position_id, position_name) FROM stdin;
1	Директор
2	Менеджер по продажам
3	Механик
4	Бухгалтер
5	Администратор
6	Эксперт по техническому осмотру
7	Секретарь
8	Маркетолог
\.


--
-- Data for Name: purchases; Type: TABLE DATA; Schema: public; Owner: admin
--

COPY public.purchases (purchase_id, client_id, car_id, purchase_date, document_id) FROM stdin;
1	4	4	2020-04-05	1
2	5	5	2020-05-10	2
\.


--
-- Data for Name: sales; Type: TABLE DATA; Schema: public; Owner: admin
--

COPY public.sales (sale_id, client_id, car_id, sale_date, account_number, payment_method) FROM stdin;
1	1	1	2020-01-20	ACC1001	Наличный расчет
2	2	2	2020-02-25	ACC1002	Безналичный расчет
3	3	3	2020-03-30	ACC1003	Кредит
\.


--
-- Data for Name: spareparts; Type: TABLE DATA; Schema: public; Owner: admin
--

COPY public.spareparts (spare_part_id, name, make, model, price, stock_quantity) FROM stdin;
1	Фильтр масляный	Toyota	Camry	500.00	50
2	Тормозные колодки	Honda	Accord	1500.00	30
3	Свечи зажигания	BMW	X5	800.00	70
4	Воздушный фильтр	Mercedes-Benz	E-Class	600.00	40
5	Аккумулятор	Audi	A6	5000.00	20
\.


--
-- Name: cars_car_id_seq; Type: SEQUENCE SET; Schema: public; Owner: admin
--

SELECT pg_catalog.setval('public.cars_car_id_seq', 5, true);


--
-- Name: clients_client_id_seq; Type: SEQUENCE SET; Schema: public; Owner: admin
--

SELECT pg_catalog.setval('public.clients_client_id_seq', 10, true);


--
-- Name: documents_document_id_seq; Type: SEQUENCE SET; Schema: public; Owner: admin
--

SELECT pg_catalog.setval('public.documents_document_id_seq', 3, true);


--
-- Name: employeemovements_movement_id_seq; Type: SEQUENCE SET; Schema: public; Owner: admin
--

SELECT pg_catalog.setval('public.employeemovements_movement_id_seq', 5, true);


--
-- Name: employees_employee_id_seq; Type: SEQUENCE SET; Schema: public; Owner: admin
--

SELECT pg_catalog.setval('public.employees_employee_id_seq', 10, true);


--
-- Name: positions_position_id_seq; Type: SEQUENCE SET; Schema: public; Owner: admin
--

SELECT pg_catalog.setval('public.positions_position_id_seq', 8, true);


--
-- Name: purchases_purchase_id_seq; Type: SEQUENCE SET; Schema: public; Owner: admin
--

SELECT pg_catalog.setval('public.purchases_purchase_id_seq', 2, true);


--
-- Name: sales_sale_id_seq; Type: SEQUENCE SET; Schema: public; Owner: admin
--

SELECT pg_catalog.setval('public.sales_sale_id_seq', 3, true);


--
-- Name: spareparts_spare_part_id_seq; Type: SEQUENCE SET; Schema: public; Owner: admin
--

SELECT pg_catalog.setval('public.spareparts_spare_part_id_seq', 5, true);


--
-- Name: cars cars_pkey; Type: CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.cars
    ADD CONSTRAINT cars_pkey PRIMARY KEY (car_id);


--
-- Name: clients clients_pkey; Type: CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.clients
    ADD CONSTRAINT clients_pkey PRIMARY KEY (client_id);


--
-- Name: documents documents_pkey; Type: CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.documents
    ADD CONSTRAINT documents_pkey PRIMARY KEY (document_id);


--
-- Name: employeemovements employeemovements_pkey; Type: CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.employeemovements
    ADD CONSTRAINT employeemovements_pkey PRIMARY KEY (movement_id);


--
-- Name: employees employees_pkey; Type: CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.employees
    ADD CONSTRAINT employees_pkey PRIMARY KEY (employee_id);


--
-- Name: positions positions_pkey; Type: CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.positions
    ADD CONSTRAINT positions_pkey PRIMARY KEY (position_id);


--
-- Name: purchases purchases_pkey; Type: CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.purchases
    ADD CONSTRAINT purchases_pkey PRIMARY KEY (purchase_id);


--
-- Name: sales sales_pkey; Type: CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.sales
    ADD CONSTRAINT sales_pkey PRIMARY KEY (sale_id);


--
-- Name: spareparts spareparts_pkey; Type: CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.spareparts
    ADD CONSTRAINT spareparts_pkey PRIMARY KEY (spare_part_id);


--
-- Name: cars cars_expert_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.cars
    ADD CONSTRAINT cars_expert_id_fkey FOREIGN KEY (expert_id) REFERENCES public.employees(employee_id);


--
-- Name: employeemovements employeemovements_employee_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.employeemovements
    ADD CONSTRAINT employeemovements_employee_id_fkey FOREIGN KEY (employee_id) REFERENCES public.employees(employee_id);


--
-- Name: employeemovements employeemovements_position_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.employeemovements
    ADD CONSTRAINT employeemovements_position_id_fkey FOREIGN KEY (position_id) REFERENCES public.positions(position_id);


--
-- Name: employees employees_position_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.employees
    ADD CONSTRAINT employees_position_id_fkey FOREIGN KEY (position_id) REFERENCES public.positions(position_id);


--
-- Name: purchases purchases_car_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.purchases
    ADD CONSTRAINT purchases_car_id_fkey FOREIGN KEY (car_id) REFERENCES public.cars(car_id);


--
-- Name: purchases purchases_client_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.purchases
    ADD CONSTRAINT purchases_client_id_fkey FOREIGN KEY (client_id) REFERENCES public.clients(client_id);


--
-- Name: purchases purchases_document_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.purchases
    ADD CONSTRAINT purchases_document_id_fkey FOREIGN KEY (document_id) REFERENCES public.documents(document_id);


--
-- Name: sales sales_car_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.sales
    ADD CONSTRAINT sales_car_id_fkey FOREIGN KEY (car_id) REFERENCES public.cars(car_id);


--
-- Name: sales sales_client_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY public.sales
    ADD CONSTRAINT sales_client_id_fkey FOREIGN KEY (client_id) REFERENCES public.clients(client_id);


--
-- PostgreSQL database dump complete
--

