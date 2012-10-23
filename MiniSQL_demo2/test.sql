create table t1
( 
id int ,
name char(4) unique,
age int ,
salary float,
primary key(id)
);

insert into t1 values(1,'Jimm',20,2000.00);
insert into t1 values(2,'Kate',24,1800.00);
insert into t1 values(3,'John',34,4000.00);
insert into t1 values(4,'Mary',20,3000.00);
insert into t1 values(5,'Tomy',24,1850.00);
insert into t1 values(6,'Quen',28,24000.00);
insert into t1 values(7,'Pory',17,1000.00);
insert into t1 values(8,'Gren',24,8000.00);
insert into t1 values(8,'Jimy',20,4000.00);
insert into t1 values(9,'Gren',22,4000.00);

create index name on t1(name);

select * from t1;

delete from t1;

drop index name;
drop table t1;

help;
quit;
