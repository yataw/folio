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
-----------------------------------------!����� �� ���������, ����� ������ �� ������� ������������
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
-----------------------------------------------------��� ����������, ���� ������������ ����������?
IF OBJECT_ID (N'dbo.f_sum', N'IF') IS NOT NULL 
DROP FUNCTION dbo.f_sum; 
GO 
--�������� ������� 
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


---------------------------------------------------------���� ������ �����������, ��� ����������?		
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
drop table ������_�����
create table ������_�����
	(
	������ID int,
	������� int,
	������������� nvarchar(50),
	������ nvarchar(50),
	������ nvarchar(50),
	�������� nvarchar(50),
	���� datetime
	primary key (������ID)
	)

drop table ����������	
create table ���������� --������, ��� ����� ���� ������ 1��� � ���� ������ � ���� �� �����
	(
	����ID int,
	������ID int,
	�����_���_������� nvarchar(max),
	���� datetime,
	������_�������� nvarchar(max),
	���� int
	);

drop table �����
create table �����
	(
	����ID int,
	����������������� nvarchar (max),
	����������_������� int,
	����� nvarchar (max),
	�������� nvarchar (max),
	�������_������ int
	primary key (����ID)
	)
	
insert into ������_����� values
(1, 4, '���', '�����', 'KILLA', 80559114444, '13.02.2011'),
(2, 80, '�����������', '�����', 'SnapDragon', 89998887766, '10.02.2004'),
(3, 1, '�������', '�����', '���', 84953141003, '15.04.2014'),
(4, 5, '���� �� ����������', '�����', 'alphaterror', 89492121215, '11.09.1999'),
(5, 4, '��������', '�������', '�������', 83141592653, '29.08.2013')

insert into ���������� values
(1, 2, '����', '26.04.2001', '��', 20000),
(1, 2, '��', '26.04.2001', '����', 10000),
(2, 1, '��', '20.07.2008', '����', 2000),
(2, 3, '��', '20.07.2008', '����', 1000000),
(2, 1, '����', '21.11.2003', '����', 50000),
(2, 2, '����', '21.11.2003', '����', 5),
(4, 1, '��', '12.01.2012', '��', 10000) 

insert into ����� values
(1, '���', 20000, '��������� 37', '������', '2'),
(2, '����', 10000, '��������� 36', 'Madison', '0'),
(3, '�����', -500, '��������� 35', '�����������������������������������������', '4')

--����������� ������ ������ ��� �� �����, ����� ��� ������ (�.�. 100 4 ����� ���� �����, ��� 99 0)

select �����.��������, F.����, F.�������, F.���������
from (
select top 1 ����������.����ID, ����������.���� as ����, SUM (����������.����) as �������,
						COUNT (case when ����������.�����_���_������� = '��' then 1 else 0 end) as ���������
from ���������� left join ����� on ����������.����ID = �����.����ID
group by ����������.����ID, ����������.����
order by ������� desc, ���������
) as F
left join ����� on �����.����ID = F.����ID


--////
select ������, �����_����������
from ������_����� right join
	 (select ������ID, COUNT (*) as �����_����������
	from ����������
	where ���� > '21.11.2003' and ������ID IN (select ������ID
											   from ����������
											   where ����ID = (select ����ID from �����
														  where �������� = 'Madison') 
													 and ���� = '21.11.2003')
							  and ���� > '21.11.2003'
	group by ������ID) as F on ������_�����.������ID = F.������ID
	
--////

select distinct top 10 �������������, MAX (�������)
from ������_�����
group by �������������

--////
Select COUNT (*) /12 as res
from ����������
where DATEPART (yy, ����) = 2005 and �����_���_������� = '��'
group by ����

--////
select ������, �������������, �������, ������, ����������_�������_���, �����_�����
from ������_����� left join
	(select ������ID, SUM (����) as �����_�����, 
		COUNT (case when �����_���_������� = '��' then 1 else 0 end) as ����������_�������_���
	from ����������
	group by ������ID) as F on F.������ID = ������_�����.������ID
	
--////��_�����_���_��_��� ������ ������ �� ��� �����, ����� ���� ���� �� 1 ����������

;
with f as (select distinct ����ID, ����, �����_���_������� from ����������)
select ��������, �����������������, �������� /�������� as ��_�����_���, ���_��_���
from (select ����ID, COUNT (distinct ����) as ��������
	  from f
	  group by ����ID
	  ) as sec inner join
	  (select  ����ID, COUNT (distinct DATEPART (yy, ����)) as ��������
	  from f
	  group by ����ID  
	  ) as th on sec.����ID = th.����ID inner join 
	  (select ����ID, COUNT (*) as ���_��_���
	  from f
	  where �����_���_������� = '��'
	  group by ����ID 
	  ) as fi on fi.����ID = th.����ID inner join
	  ����� on fi.����ID = �����.����ID
	  
--//////? ��� ���������������, ���� �� ������������ � ����, ���� �� ��������, �� �� �����
;
with f as (select DATEPART (YY, ����) as ��� from ������_����� group by DATEPART (YY, ����))
select ���, ������, COUNT (*) as �����
from f, ������_�����
where not (datepart (yy, ����) < ��� and ������ in ('�����', '�������'))
group by ���, ������
order by 1, 2

--
IF OBJECT_ID (N'dbo.veroyatnost', N'FN') IS NOT NULL 
DROP FUNCTION dbo.veroyatnost; 
GO

create function dbo.veroyatnost (@������ID as int)
returns nvarchar(max)
as begin
declare @luck as int
declare @all as int
declare @res as nvarchar(50)
set @luck = (select COUNT (*)
		from ����������
		where ������ID = @������ID and �����_���_������� = '��'
		)

set @all = (select COUNT (*)
		from ����������
		where ������ID = @������ID
		)
if (@all = 0)
	return NULL
set @res =  cast(  cast (@luck as float) / @all*100 as nvarchar (max) ) + '%'
return @res 
end

go
select ������, �������, dbo.veroyatnost (������ID) as res
from ������_�����