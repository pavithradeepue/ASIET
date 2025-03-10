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
desc employees;
+---------+--------------+------+-----+---------+-------+
| Field   | Type         | Null | Key | Default | Extra |
+---------+--------------+------+-----+---------+-------+
| emp_id  | int          | NO   | PRI | NULL    |       |
| name    | varchar(100) | YES  |     | NULL    |       |
| dept_id | int          | YES  | MUL | NULL    |       |
+---------+--------------+------+-----+---------+-------+
3 rows in set (0.01 sec)

