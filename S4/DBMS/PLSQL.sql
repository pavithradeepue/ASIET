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
