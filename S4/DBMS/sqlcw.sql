create table players(player_id number(2) PRIMARY KEY,player_name  char(20),team char(20), highest_score number(3),player_dob date);


ALTER table Players add country varchar (20);
alter table Players rename column highest_score to best_score;
alter table Players modify team varchar(20);
alter table Players add column phone_no number(10);

alter table Players drop column phone_no;
