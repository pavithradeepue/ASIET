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




















