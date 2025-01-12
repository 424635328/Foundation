use test;
create  table  player (
    id INT,
    name NVARCHAR(100),
    level int,
    exp int,
    gold decimal(10,2)

);

alter table player modify level int default 1;
alter table player modify exp int default 1;
alter table player modify gold decimal(10,2) default 1.00;

desc player;