use test
go

DROP TABLE T

CREATE TABLE T
	( 
	id INT, 
	x INT, 
	y INT, 
	value FLOAT
	PRIMARY KEY (id, x, y) 
	);
 
INSERT INTO T VALUES (1,1,1,1) 
INSERT INTO T VALUES (1,2,1,0) 
INSERT INTO T VALUES (1,1,2,0) 
INSERT INTO T VALUES (1,2,2,1) 
INSERT INTO T VALUES (2,1,1,1) 
INSERT INTO T VALUES (2,2,1,2) 
INSERT INTO T VALUES (2,1,2,3) 
INSERT INTO T VALUES (2,2,2,0) 
INSERT INTO T VALUES (3,1,1,2) 
INSERT INTO T VALUES (3,2,1,4) 
INSERT INTO T VALUES (4,1,1,2) 
INSERT INTO T VALUES (4,1,2,1) 
INSERT INTO T VALUES (5,1,1,2) 
INSERT INTO T VALUES (5,1,2,1) 
INSERT INTO T VALUES (5,1,3,1) 
INSERT INTO T VALUES (6,1,1,2)

IF OBJECT_ID (N'dbo.f_kvadrat', N'FN') is not null
DROP FUNCTION dbo.f_kvadrat; 
GO 

CREATE FUNCTION dbo.f_kvadrat (@id as INT) 
RETURNS int 
AS 
BEGIN 
DECLARE @max_x INT 
DECLARE @max_y INT 
DECLARE @res int 
SET @max_x = (SELECT MAX(x) FROM T WHERE id=@id) 
SET @max_y = (SELECT MAX(y) FROM T WHERE id=@id) 
IF (@max_x = @max_y) SET @res = @max_x
ELSE SET @res = 0 
RETURN @res 
END 
GO

IF OBJECT_ID (N'dbo.f_simm', N'FN') is not null
DROP FUNCTION dbo.f_simm; 
GO 

CREATE FUNCTION dbo.f_simm (@id as INT)
returns bit 
as begin
declare @size int
declare @num int 
SET @size = dbo.f_kvadrat (@id)
if (@size = 0) return 0

SET @num = (select COUNT (*)
	   from T first
	   where @id = id and value = (select value 
								   from T second 
								   where second.id = first.id and second.x = first.y and 
								   second.y = first.x)																	
	   )
if (@num <> @size) return 0

return 1
end
go
-----------------------------------------!можно ли проверить, дойдя только до первого несовпадения
IF OBJECT_ID (N'dbo.f_ed', N'FN') is not null
DROP FUNCTION dbo.f_ed; 
GO 

CREATE FUNCTION dbo.f_ed (@id as INT)
returns bit 
as begin
declare @num_nulls int 
declare @num_one int
declare @num int
Set @num = dbo.f_kvadrat (@id)
if (@num = 0) return 0

Set @num_nulls = (Select count (*)
				  from T
				  where id = @id and value = 0
				  )
Set @num_one= (Select count (*)
				  from T
				  where id = @id and value = 1
				  )
if (@num_one + @num_nulls = @num*@num) return 1

return 0
end
go

IF OBJECT_ID (N'dbo.f_summ_or_not', N'FN') is not null
DROP FUNCTION dbo.f_summ_or_not; 
GO 

CREATE FUNCTION dbo.f_summ_or_not (@id1 as INT, @id2 as INT)
returns bit 
as begin
declare @result as int
Set @result = (select ABS (MAX (f.x) - MAX (s.x)) + ABS (MAX (f.y) - MAX (s.y))
				from T f, T s
				where f.id = @id1 and s.id = @id2
			  )
if (@result <> 0) return 0
return 1
end
go 

--
-----------------------------------------------------Что возвращать, если суммирование невозможно?
IF OBJECT_ID (N'dbo.f_sum', N'IF') IS NOT NULL 
DROP FUNCTION dbo.f_sum; 
GO 
--создание функции 
CREATE FUNCTION dbo.f_sum (@id1 as INT, @id2 as INT) 
RETURNS TABLE 
AS 
RETURN 
( 
SELECT f.x as 'x' , f.y as 'y', f.value +  s.value as 'value'
FROM T f, T s
WHERE f.id = @id1 and s.id = @id2 and f.x = s.x and f.y = s.y 
); 


go

IF OBJECT_ID (N'dbo.mult_or_not', N'FN') IS NOT NULL 
DROP FUNCTION dbo.mult_or_not; 
GO

create function dbo.mult_or_not (@id1 as int, @id2 as int)
returns bit
as begin
declare @result as int
Set @result = (select ABS (MAX (f.y) - MAX (s.x))
				from T f, T s
				where f.id = @id1 and s.id = @id2
			  )
if (@result <> 0) return 0
return 1
end
go


---------------------------------------------------------Если нельзя перемножить, что возвращать?		
if OBJECT_ID (N'dbo.multi', N'IF') is not null
drop function dbo.multi;
go

create function dbo.multi (@id1 as int, @id2 as int)
returns table
as return 
	(
	select f.x as 'x', s.y as 'y', SUM (f.value*s.value) as 'value'
	from T f, T s
	where f.id = @id1 and s.id = @id2 and f.x = s.y
	group by f.x, s.y
	);
go
	
--select * from dbo.multi (1, 2)

--///////////////////////////////////////////////////////////////////////////////////////////////
drop table Состав_банды
create table Состав_банды
	(
	БандитID int,
	Уровень int,
	Специализация nvarchar(50),
	Статус nvarchar(50),
	Кличка nvarchar(50),
	Контакты nvarchar(50),
	Дата datetime
	primary key (БандитID)
	)

drop table Ограбление	
create table Ограбление --считаю, что может быть только 1огр в день одного и того же банка
	(
	БанкID int,
	БандитID int,
	Исход_для_бандита nvarchar(max),
	Дата datetime,
	Оценка_действий nvarchar(max),
	Доля int
	);

drop table Банки
create table Банки
	(
	БанкID int,
	Привлекательность nvarchar (max),
	Ежедневная_выручка int,
	Адрес nvarchar (max),
	Название nvarchar (max),
	Уровень_охраны int
	primary key (БанкID)
	)
	
insert into Состав_банды values
(1, 4, 'вор', 'мертв', 'KILLA', 80559114444, '13.02.2011'),
(2, 80, 'потрошитель', 'готов', 'SnapDragon', 89998887766, '10.02.2004'),
(3, 1, 'слесарь', 'готов', 'лох', 84953141003, '15.04.2014'),
(4, 5, 'спец по взрывчатке', 'готов', 'alphaterror', 89492121215, '11.09.1999'),
(5, 4, 'водитель', 'завязал', 'Стэтхэм', 83141592653, '29.08.2013')

insert into Ограбление values
(1, 2, 'неуд', '26.04.2001', 'уд', 20000),
(1, 2, 'уд', '26.04.2001', 'неуд', 10000),
(2, 1, 'уд', '20.07.2008', 'неуд', 2000),
(2, 3, 'уд', '20.07.2008', 'неуд', 1000000),
(2, 1, 'неуд', '21.11.2003', 'неуд', 50000),
(2, 2, 'неуд', '21.11.2003', 'неуд', 5),
(4, 1, 'уд', '12.01.2012', 'уд', 10000) 

insert into Банки values
(1, 'выс', 20000, 'Измайлово 37', 'Сберыч', '2'),
(2, 'низк', 10000, 'Измайлово 36', 'Madison', '0'),
(3, 'средн', -500, 'Измайлово 35', 'газпромнафтотехнотранссибуралмосковиябанк', '4')

--Оптимальным считаю просто Мах по сумме, затем Мин потерь (т.е. 100 4 может быть лучше, чем 99 0)

select Банки.Название, F.Дата, F.выручка, F.Потерянно
from (
select top 1 Ограбление.БанкID, Ограбление.Дата as Дата, SUM (Ограбление.Доля) as Выручка,
						COUNT (case when Ограбление.Исход_для_бандита = 'уд' then 1 else 0 end) as Потерянно
from Ограбление left join Банки on Ограбление.БанкID = Банки.БанкID
group by Ограбление.БанкID, Ограбление.Дата
order by Выручка desc, Потерянно
) as F
left join Банки on Банки.БанкID = F.БанкID


--////
select Кличка, Число_ограблений
from Состав_банды right join
	 (select БандитID, COUNT (*) as Число_ограблений
	from Ограбление
	where Дата > '21.11.2003' and БандитID IN (select БандитID
											   from Ограбление
											   where БанкID = (select БанкID from Банки
														  where Название = 'Madison') 
													 and Дата = '21.11.2003')
							  and Дата > '21.11.2003'
	group by БандитID) as F on Состав_банды.БандитID = F.БандитID
	
--////

select distinct top 10 Специализация, MAX (Уровень)
from Состав_банды
group by Специализация

--////
Select COUNT (*) /12 as res
from Ограбление
where DATEPART (yy, Дата) = 2005 and Исход_для_бандита = 'уд'
group by Дата

--////
select Кличка, Специализация, Уровень, Статус, Количество_удачных_дел, общий_доход
from Состав_банды left join
	(select БандитID, SUM (Доля) as общий_доход, 
		COUNT (case when Исход_для_бандита = 'уд' then 1 else 0 end) as Количество_удачных_дел
	from Ограбление
	group by БандитID) as F on F.БандитID = Состав_банды.БандитID
	
--////Ср_колво_огр_за_год считаю только по тем годам, когда было хотя бы 1 ограбление

;
with f as (select distinct БанкID, Дата, Исход_для_бандита from Ограбление)
select Название, Привлекательность, КОЛВООГР /КОЛВОЛЕТ as ср_колво_огр, кол_уд_огр
from (select БанкID, COUNT (distinct Дата) as КОЛВООГР
	  from f
	  group by БанкID
	  ) as sec inner join
	  (select  БанкID, COUNT (distinct DATEPART (yy, Дата)) as КОЛВОЛЕТ
	  from f
	  group by БанкID  
	  ) as th on sec.БанкID = th.БанкID inner join 
	  (select БанкID, COUNT (*) as кол_уд_огр
	  from f
	  where Исход_для_бандита = 'уд'
	  group by БанкID 
	  ) as fi on fi.БанкID = th.БанкID inner join
	  Банки on fi.БанкID = Банки.БанкID
	  
--//////? Год рассматривается, если он присутствует в Дата, если не присутст, то не рассм
;
with f as (select DATEPART (YY, Дата) as год from Состав_банды group by DATEPART (YY, Дата))
select год, Статус, COUNT (*) as колво
from f, Состав_банды
where not (datepart (yy, Дата) < год and Статус in ('мертв', 'завязал'))
group by год, Статус
order by 1, 2

--
IF OBJECT_ID (N'dbo.veroyatnost', N'FN') IS NOT NULL 
DROP FUNCTION dbo.veroyatnost; 
GO

create function dbo.veroyatnost (@БандитID as int)
returns nvarchar(max)
as begin
declare @luck as int
declare @all as int
declare @res as nvarchar(50)
set @luck = (select COUNT (*)
		from Ограбление
		where БандитID = @БандитID and Исход_для_бандита = 'уд'
		)

set @all = (select COUNT (*)
		from Ограбление
		where БандитID = @БандитID
		)
if (@all = 0)
	return NULL
set @res =  cast(  cast (@luck as float) / @all*100 as nvarchar (max) ) + '%'
return @res 
end

go
select Кличка, Уровень, dbo.veroyatnost (БандитID) as res
from Состав_банды