use test
go

create table #t (
	sotr nvarchar(max), podch nvarchar(max) )
	
	
declare @n as int
declare @i as int
set @i = 1

create table #buffer1 (
	sotr nvarchar(max) )
	
create table #buffer2 (
	sotr nvarchar(max) )


insert into #buffer1
select podch
from #t
where sotr = @n 

	
while (@i <= 3 - 1)
begin

insert into  #buffer2 
select a.podch
from #t a inner join #buffer1 b on a.podch = b.sotr

truncate table #buffer1

insert into #buffer1
select * from #buffer2

truncate table #buffer2

set @i = @i + 1
end


select * from #buffer1