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

insert into nobel_win1 values(&year,'&subject','&winner','&country', '&cat');
select year,subject,winner from nobel_win1 where year=1990;

