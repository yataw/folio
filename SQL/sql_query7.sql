use test 
go

drop table #names
drop table #names_norm
drop table #names_temp

create table #names (Имена nvarchar(max))
create table #names_norm (Имя nvarchar(max))
create table #names_temp (Имя1 nvarchar(max), Имя2 nvarchar(max))

insert into #names values
('Вася, Петя, Игорь, Максим'),
('Маша, Вера, Лена, Игорь, Степа'), 
('Антон, Владимир, Григорий'), 
('Слава, Леонид, Ирина')


----------------
while (
		(select top 1 * from #names) is not null
	  )

begin

TRUNCATE table #names_temp

insert into #names_temp
select case when PATINDEX ('%,%', #names.Имена) > 0
		then SUBSTRING (#names.Имена, 0,  PATINDEX ('%,%', #names.Имена))
		else #names.Имена end,
 case when PATINDEX ('%,%', #names.Имена) > 0
 then
 SUBSTRING (#names.Имена, 2 + PATINDEX ('%,%', #names.Имена), LEN (#names.Имена))
 else '' end
 
from #names

truncate table #names

insert into #names
select #names_temp.Имя2
from #names_temp

delete from #names
where Имена = ''

insert into #names_norm
select Имя1
from #names_temp

end
 
select * from #names_norm