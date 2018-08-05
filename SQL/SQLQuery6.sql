use test
--go

/*Хранение - int id, int x, double val; x - та степень икс, при кот. стотит данный коэф.*/
drop table pol

create table pol
	(
    id int,
    x int,
    val float
    primary key (id, x)
	)

Insert into pol values
(1, 1, 2),
(1, 0, 1),
(1, 2, 1),
(2, 2, 1),
(3, 3, 2),
(3, 2, 1),
(3, 4, 1)

declare @id int
declare @id1 int
declare @id2 int
declare @id3 int
declare @val float
declare @n int
declare @x float
set @id = 1
set @id1 = 1
set @id2 = 2
set @id3 = 3
set @val = 0.5
set @n = 2
set @x = 5

--
select x as X, val as VAL
from pol
where id = @id
order by x desc

--

select distinct pol.id
from pol, 
	(select id
	from pol
	where val <> 0
	group by id) as F
where pol.id <> F.id

--
select x as X, val * @val as VAL
from pol
where id = @id
order by x desc

--
select x = case when x = @n then 'yes' else 'no' end
from (
	select top 1 x 
	from pol
	where id = @id and val <> 0
	group by x
	order by x desc
	) t

--	
select x [x], SUM (val) [val]
from pol
where id = @id1 or id = @id2
group by x
order by 1 desc	

--
select x [x], SUM (val) as val
from (
	 select f1.x + f2.x as x, f1.val*f2.val as val
	 from pol f1, pol f2
	 where f1.id = @id1 and f2.id = @id2
	 ) as t
group by x
order by x desc

--
select SUM (POWER (val, x)) as RESULT
from pol
where id = @id

--9. Предположим, что многочлен степени 2 (для этого его можно было бы прогнать на 5ом запросе)
declare @a as float
declare @b as float
declare @c as float
declare @d as float
set @a = 0 set @b = 0 set @c = 0 set @d = 0


set @d =  (select val
		  from pol
		  where id = @id and x = 2) ;
if (@d IS NOT NULL) set @a = @d;
 

set @d =  (select val
		  from pol
		  where id = @id and x = 1)
if (@d IS NOT NULL) set @b = @d


set @d =  (select val
		  from pol
		  where id = @id and x = 0)
if (@d IS NOT NULL) set @c = @d

select case when @b*@b - 4*@a*@c = 0 then 'YES' else 'NO' end as RESULT

--10 +-0; 
;
with G as (select MAX (x) as maxx from pol where id = @id and x <> 0)
select a.res as [>0], b.res as [<0], c.res as [=0]
from 
	(
	 select COUNT (val) res
	 from pol, G
	 where id = @id and val > 0 and x <= maxx
	 ) as a,
	 (
	 select COUNT (val) res
	 from pol, G
	 where id = @id and val < 0 and x <= maxx
	 ) as b,
	 
	 (
	 select COUNT (val) res
	 from pol, G
	 where id = @id and val = 0 and x <= maxx
	 ) as c

--11
/*
declare @intx int

select case when res <> 0 then 'NO' else 'YES' end
(
select count (x) as res
from (
	 
	 )

) as G*/

--12
declare @x_1 float
declare @x_2 float

set @x_1 = (								
select case when x = 1 then val else NULL end								  
from (
	select top 1 x, val
	from pol
	where id = @id and val <> 0
	order by x desc
	) t )

set @x_2 = (								
	select top 1 val 
	from pol
	where id = @id and x = 0
	 )

if (@x_1 is NOT NULL)
	if (@x_2 is NULL or @x_2 = 0) select 0 as RESULT
	else select -@x_2/@x_1 as RESULT
else select NULL as RESULT

--13

declare @_x2 as float
declare @_x1 as float
declare @_x0 as float

set @_x2 = (								
select case when x = 2 then val else NULL end								  
from (
	select top 1 x, val
	from pol
	where id = @id and val <> 0
	order by x desc
	) t )
	

set @_x1 = (								
	select top 1 val 
	from pol
	where id = @id and x = 1
	 )

if (@_x1 is NULL) set @_x1 = 0

set @_x0 = (								
	select top 1 val 
	from pol
	where id = @id and x = 0
	 )

if (@_x1 is NULL) set @_x0 = 0

if (@_x2 IS  NULL or @_x1*@_x1 - 4*@_x0*@_x2 < 0) select NULL as RESULT
else if (@_x1*@_x1 - 4*@_x0*@_x2 = 0) select -@_x1/2 [x1], -@_x1/2 [x2]
else
SELECT (-@_x1 + POWER (@_x1*@_x1 - 4*@_x0*@_x2, 0.5))/2  [x1], 
	   (-@_x1 - POWER (@_x1*@_x1 - 4*@_x0*@_x2, 0.5))/2  [x2]
	   
--14

if (not exists(
select * 
	from 
	
	(select x , SUM (val) as val, count (distinct x) [c_x]
	from (
		 select f1.x + f2.x as x, f1.val*f2.val as val
		 from pol f1, pol f2
		 where f1.id = @id1 and f2.id = @id2
		 ) as t
	group by x
	) as table1,
	
	(select x, val, count (x) [c_x]
	from pol
	where id = @id3
	group by x, val
	) as table2
	
	where (table1.x = table2.x and table1.val <> table2.val or table1.c_x <> table2.c_x)
    )  
	) select 'true' else select 'false' 
	
--15 Такой же, как и предыдущий, но меняем местами @id1 и @id3