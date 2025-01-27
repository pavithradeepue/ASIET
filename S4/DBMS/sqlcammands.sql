create table salesman1(salesman_id number(5) primary key, name char(15), city char(5), commission decimal(5,2));

create table orders1(ord_no number(5), purch_amt number(4),ord_date date, cust_id number(5),salesman_id number(5), foreign key(salesman_id) references salesman1(salesman_id));

create table customer1(cust_id number(5), cust_name char(15), city char(5), grade char(1),salesman_id number(5), foreign key(salesman_id) references salesman1(salesman_id));

insert into salesman1 values(&salesman_id,'&name','&city',&commission);

insert into orders1 values(&ord_no,&purch_amt,'&ord_date',&cust_id,&salesman_id);

select salesman_id,name,commission from salesman1;
select ord_date,salesman_id,ord_no,purch_amt from orders1;
select distinct salesman_id from orders1;
select name from salesman1 WHERE city = 'aluva';
select * from customer1 where Grade ='A';
select ord_no,ord_date,purch_amt from orders1 where salesman_id =101;

create table nobel_win1(year number(4), subject char(5), winner char(10), country char(3), cat char(5))
insert into nobel_win1 values(&year,'&subject','&winner','&country', '&cat');
select year,subject,winner from nobel_win1 where year=1990;
select winner from nobel_win1 where year=1990 AND subject='Eng';
select year,subject from nobel_win1 where winner='Nelson';
select winner from nobel_win1 where subject='Phy' AND year > 1950;
select year,winner,country from nobel_win1 where subject='CHEM' AND year>=1965 AND year<=2025;
select * from nobel_win1 where (subject='Eng' AND year=1990) UNION (select * from nobel_win1 where (subject='Phy' AND year=2022));
select * from nobel_win1 where year = 1990 and subject not in('Phy','Chem');
select * from nobel_win1 where subject NOT LIKE 'P%' order by year DESC; #or  asc


create table products1(p_id number(1),p_price number(4),p_name char(5));
insert into products1 values(&p_id,&p_price,'&p_name');
select min(p_price) AS Minimum_price from products1;
select max(p_price) AS Maximum_price from products1;
select count(p_id) AS Total_number_of_products from products1;
select sum(p_price) AS Total_price from products1;
select avg(p_price) AS Average_price from products1;
