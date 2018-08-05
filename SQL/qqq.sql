use test
go


create table tab
(
id int,
x int,
y int,
re float,
im float
primary key (id, x, y)
);

declare @id1 int
declare @id2 int
set @id1 = 1
set @id2 = 2

insert into tab values
(1, 1, 1, 1, 1),
(1, 1, 2, 0, 0),
(1, 2, 1, 0, 2),
(1, 2, 2, 1, 1),
(2, 1, 1, 1, 1),
(2, 1, 2, 3, -1),
(2, 2, 1, 2, 2),
(2, 2, 2, 0, 0)


IF OBJECT_ID (N'dbo.f_sum', N'IF') IS NOT NULL 
DROP FUNCTION dbo.f_sum; 
GO 
 
CREATE FUNCTION dbo.f_sum (@id1 as INT, @id2 as INT) 
RETURNS TABLE 
as
return 
(
SELECT f.x as 'x' , f.y as 'y', f.re +  s.re as 're', f.im + s.im as 'im'
FROM tab f,  tab s
WHERE f.id = @id1 and s.id = @id2 and f.x = s.x and f.y = s.y 
)
------------
IF OBJECT_ID (N'dbo.f_mult', N'IF') IS NOT NULL 
DROP FUNCTION dbo.f_mult; 
GO 
 
CREATE FUNCTION dbo.f_mult (@id1 as INT, @id2 as INT) 
returns table
as return 
	(
	select f.x as 'x', s.y as 'y', SUM (f.re*s.re - f.im*s.im) as re, SUM (f.re*s.im + f.im*s.re) as im
	from tab f, tab s
	where f.id = @id1 and s.id = @id2 and f.y = s.x
	group by f.x, s.y
	)
;

go
select *
from dbo.f_mult (1, 2)

--
create table tab2
	(
	sotr int,
	nach int
	);



insert into tab values
(1, null),
(2, 1),
(3, 1),
(4, 1),
(5, 2),
(6, 2),
(7, 2),
(8, 2),
(9, 3),
(10, 3),
(11, 10),
(12, 11),
(13, 6),
(14, 12)
	
select sotr
from (
	select top 1 nach, count (sotr) as kolvo
	from tab2
	group by nach
	order by 2 desc
	) as t, tab2
	
where t.nach = tab2.nach