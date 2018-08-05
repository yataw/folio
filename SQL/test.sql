use test
go
declare @t as table(
	x1 int,
	x2 int,
	x3 int,
	x4 int,
	x5 int,
	x6 int
	--primary key (x1)
	);

declare @names as table(
	id int,
	x2 int
	--primary key (id)
	);

	



	
	
insert into @t values
(1, 1, 7, 14, 0, 9),
(1, 5, 7, 14, 0, 9),
(2, 4, 18, 18, 2, 4),
(2, 4, 18, 18, 2, 4),
(2, 4, 18, 18, 2, 4),
(3, 5, 5, 1, 7, 1),
(3, 9, 5, 1, 7, 1),
(4, 11, 15, 2, 7, 16),
(5, 11, 4, 2, 13, 12),
(6, 2, 1, 16, 18, 15),
(7, 7, 6, 11, 18, 9),
(8, 12, 7, 19, 15, 14),
(9, 3, 11, 2, 13, 13),
(10, 4, 1, 11, 13, 8),
(11, 7, 4, 2, 17, 17),
(12, 19, 3, 1, 9, 18),
(13, 16, 15, 10, 2, 8),
(14, 6, 0, 2, 4, 8),
(15, 6, 5, 10, 9, 10),
(16, 10, 6, 1, 13, 8),
(17, 9, 3, 4, 14, 16),
(18, 0, 6, 16, 11, 8),
(19, 4, 19, 6, 3, 17),
(20, 18, 18, 2, 9, 1),
(21, 13, 15, 19, 18, 4),
(22, 10, 17, 6, 13, 6),
(23, 1, 5, 4, 12, 10),
(24, 9, 17, 13, 17, 12),
(25, 6, 10, 1, 16, 15),
(26, 7, 15, 14, 11, 12),
(27, 10, 10, 1, 4, 6),
(28, 10, 7, 11, 7, 17),
(29, 17, 7, 13, 3, 5),
(30, 9, 9, 18, 1, 8)

insert into @names values
(1, 2),
(2, 3),
(3, 4),
(1, 2)

declare @a as table
	(
	id  int,
	data  datetime
	)

---
--select a.id /b.id as sss
--from @names a, @names b 
--;


if OBJECT_ID (N'dbo.sdssft', N'FN') is not null
drop function dbo.sdssft;

go	
create function dbo.sdssft (@x as int)
returns nvarchar(max)
as begin
declare @y as int
declare @u as int
set @u = cast (cast (@y as float) /2 as float)
return 'f'
end
go

		

--exists v A. V podzapr agr fun


drop table tab

create table tab
(
x int,
y int
);

insert into tab values
(1, 2),
(2, 3),
(3, 4),
(4, 5)

select *
from tab a left join tab b on a.x = b.y


select *
from tab a left join tab b on a.x = b.y
where b.x > 1

------------
declare @tab as table
(x int, y int primary key (x))

select MAX (x), MAX (y)
from @tab 