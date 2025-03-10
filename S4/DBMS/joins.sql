CREATE TABLE departments(dept_id INT PRIMARY KEY,dept_name VARCHAR(100));
CREATE TABLE employees(emp_id INT PRIMARY KEY,name VARCHAR(100),dept_id INT);
CREATE TABLE employees(emp_id INT PRIMARY KEY,name VARCHAR(100),dept_id INT,foreign key(dept_id) references departments(dept_id));
 select * from departments;
+---------+-----------+
| dept_id | dept_name |
+---------+-----------+
|     101 | Pavithra  |
|     102 | Prithvi   |
|     103 | Roshan    |
|     104 | Sidharth  |
|     105 | Nima      |
+---------+-----------+
5 rows in set (0.00 sec)
select * from employees;
+--------+----------+---------+
| emp_id | name     | dept_id |
+--------+----------+---------+
|      1 | Nima     |     105 |
|      2 | Pavithra |     101 |
|      3 | Prithvi  |     102 |
|      4 | Roshan   |     103 |
|      5 | Sidharth |     104 |
+--------+----------+---------+
5 rows in set (0.00 sec)
//COMPANY ACCEPTED FORMAT\\
 SELECT e.name,d.dept_name FROM employees e INNER JOIN departments d ON e.dept_id = d.dept_id;
+----------+-----------+
| name     | dept_name |
+----------+-----------+
| Pavithra | Pavithra  |
| Prithvi  | Prithvi   |
| Roshan   | Roshan    |
| Sidharth | Sidharth  |
| Nima     | Nima      |
+----------+-----------+
5 rows in set (0.00 sec)
//OTHER FORMATS\\
SELECT name,dept_name FROM employees e INNER JOIN departments d ON e.dept_id = d.dept_id;
Select employees.name,departments.dept_name FROM employees INNER JOIN departments ON employees.dept_id = departments.dept_id;
select name,dept_name FROM employees INNER JOIN departments ON employees.dept_id = departments.dept_id;
SELECT name,dept_name FROM employees e INNER JOIN departments d ON e.dept_id = d.dept_id;

///////In mysql full join wont work so we use left and right and union cheyyum but in oracle it'll work\\\\\\\\\
SELECT employees.name,departments.dept_name from employees LEFT JOIN departments ON employees.dept_id = departments.dept_id UNION SELECT employees.name,departments.dept_name FROM employees RIGHT JOIN departments ON employees.dept_id = departments.dept_id;

//left outer and right outer\\
SELECT e.name,d.dept_name FROM employees e LEFT OUTER JOIN departments d ON e.dept_id = d.dept_id;
SELECT e.name,d.dept_name FROM employees e RIGHT OUTER JOIN departments d ON e.dept_id = d.dept_id;

 











