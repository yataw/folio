use test 
go

drop table #names
drop table #names_norm
drop table #names_temp

create table #names (����� nvarchar(max))
create table #names_norm (��� nvarchar(max))
create table #names_temp (���1 nvarchar(max), ���2 nvarchar(max))

insert into #names values
('����, ����, �����, ������'),
('����, ����, ����, �����, �����'), 
('�����, ��������, ��������'), 
('�����, ������, �����')


----------------
while (
		(select top 1 * from #names) is not null
	  )

begin

TRUNCATE table #names_temp

insert into #names_temp
select case when PATINDEX ('%,%', #names.�����) > 0
		then SUBSTRING (#names.�����, 0,  PATINDEX ('%,%', #names.�����))
		else #names.����� end,
 case when PATINDEX ('%,%', #names.�����) > 0
 then
 SUBSTRING (#names.�����, 2 + PATINDEX ('%,%', #names.�����), LEN (#names.�����))
 else '' end
 
from #names

truncate table #names

insert into #names
select #names_temp.���2
from #names_temp

delete from #names
where ����� = ''

insert into #names_norm
select ���1
from #names_temp

end
 
select * from #names_norm