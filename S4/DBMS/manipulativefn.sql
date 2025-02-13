select LOWER('ASIET IS FOR TECH GEEKS ONLY') from dual;
LOWER('ASIETISFORTECHGEEKSON
----------------------------
asiet is for tech geeks only

select UPPER('siet is for tech geeks only') from dual;
UPPER('SIETISFORTECHGEEKSON
---------------------------
SIET IS FOR TECH GEEKS ONLY

SQL> @dbms.sql

select INITCAP('Ai is a sub branch of cse') from dual;
INITCAP('AIISASUBBRANCHOF
-------------------------
Ai Is A Sub Branch Of Cse
select CONCAT('CSE','-AI') from dual;

CONCAT
------
CSE-AI
select CONCAT(NULL,'AI') from dual;
CONCAT
------
AI
select LENGTH('Learning is always fun') from dual;

LENGTH('LEARNINGISALWAYSFUN')
-----------------------------
			   22
select substr('Database MAgement System', 9) from dual;
SUBSTR('DATABASEMA
------------------
 Management System


select substr('Database Management System', 9,7) from dual;
SUBSTR(
-------
 Manage

select INSTR('Google apps are great applications','app') from dual;
INSTR('GOOGLEAPPSAREGREATAPPLICATIONS','APP')
---------------------------------------------
					    8
select LPAD('100',5,'*') from dual;
LPAD(
-----
**100

select RPAD('100',5,'*') from dual;
RPAD(
-----
100**

select LPAD('hello',21,'asiet') from dual;
LPAD('HELLO',21,'ASIE
---------------------
asietasietasietahello

  select RPAD('earn',19,'respect') from dual;
RPAD('EARN',19,'RES
-------------------
earnrespectrespectr



select TRIM('A' from 'Android') from dual;
TRIM('
------
ndroid

select TRIM('   Android') from dual;

TRIM('A
-------
Android
  
select REPLACE('Data management','Data','Database') from dual;
REPLACE('DATAMANAGE
-------------------
Database management





create table sailors(sid int primary key,sname varchar(10),rating int,age int check(age>16 and age<100));
create table boat(bid int primary key,bname char(10),color char(10));
create table reserves(sid int,bid int, day date,foreign key(sid) references sailors(sid),foreign key(bid) references boat(bid));

insert into boat values(3,'AAA','red');
insert into boat values(5,'Rose','yellow');
insert into boat values(2,'Jacker','black');
insert into boat values(7,'Ship','green');
insert into boat values(8,'Junk','white');

	insert into reserves values(5,5,'12-Feb-2025');
select s.sname from sailors s,boat b,reserves r where s.sid = r.sid and b.bid = r.bid and(b.color = 'red' or b.color='yellow');

select s.sid from sailors s where s.rating = 5 UNION select r.sid from reserves r where r.bid = 5;
SQL> @dbms.sql

       SID
----------
	 1
	 5













