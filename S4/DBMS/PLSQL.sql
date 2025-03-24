/*PROCEDURE*/
DECLARE 
a number;
b number;
c number;
PROCEDURE finndMin(x IN number,y IN number,z OUT number) IS
BEGIN 
 if x < y THEN
  z:= x;
 ELSE
  z:= y;
 END IF;
END;

BEGIN
a:=23;
b:=45;
findMin(a,b,c);
dbms_output.put_line('Minimum of (23,45): '||c);
END;
/

/*OUTPUT*/
SQL> @PLsql.sql    
Minimum of (23,45): 23

PL/SQL procedure successfully completed.

/*FUNCTION*/
create table customer10(id number(5) primary key, name char(15),salary number(10));

/*CURSOR*/
CREATE table electricity(cons_id char(4) primARY KEY,name char(15),rent number(2) check (rent=20),unit number(6));
insert into electricity values(&cons_id,'&name',&rent,&unit);
alter table electricity add(total number(6,2));

DECLARE 
 v_toal electricity.total%TYPE;
 CURSOR c IS SELECT * FROM electricity;
BEGIN
 FOR i IN c LOOP
  BEGIN -- Start inner block for exception handling(if needed)
   IF i.unit <= 40 THEN
    v_total := i.rent;
   ELSE IF i.unit <= 80 THEN
    v_total := i.rent + (i.unit - 40) * 0.40;
   ELSE
    v_total := i.rent + (40*0.40) + (i.unit - 80) * 1.40;
   END IF;
