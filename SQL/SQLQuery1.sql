declare @mytable as table(
	���� int NOT NULL,
	���� datetime NOT NULL,
	����� nvarchar(100) NOT NULL,
	���������� nvarchar(100) NOT NULL,
	����� int,
	���� float
	primary key (����)
	)
	
insert into @mytable VALUES
(1, '18.4.2006', '������', '����������', 18, 4.1),
(2, '21.10.2000', '����', '���������', 4, 72.4),
(3, '22.3.2013', '���', '�����', 21, 70.5),
(4, '5.3.2000', '�������', '�����', 21, 49.1),
(5, '13.9.2010', '��������', '�����', 5, 39.1),
(6, '16.2.2012', '���', '����', 22, 38.2),
(7, '22.6.2001', '�������', '������', 2, 44.7),
(8, '11.7.2007', '����', '�����������', 18, 91.2),
(9, '6.9.2004', '�������', '�����������2', 12, 70.3),
(10, '9.5.2011', '���', '����������', 17, 66.4),
(11, '18.9.2000', '�������', '�������', 20, 54.7),
(12, '23.1.2011', '�������', '�����_�������', 24, 85.9),
(13, '9.6.2000', '�����', '�������_��_����������', 11, 31.6),
(14, '25.4.2010', '������', '����������', 16, 10.6),
(15, '17.03.2014', '�����_���', '������_��������', 6, 44.6)

---	
SELECT distinct ����
from @mytable
--
SELECT distinct ����������
from @mytable
where (DATEPART (wk, GETDATE ()) - DATEPART (wk, ����) = 1) and 
	  (DATEPART (yy, GETDATE ()) - DATEPART (yy, ����) = 0) 
--
SELECT distinct ����������
from @mytable
order by ���������� ASC
--
SELECT ����*����� as ���������
from @mytable
--
SELECT *
from @mytable
where (���������� like 'A*' and DATEPART (mm, ����) = 1 and DATEPART (yy, ����) = 2013 or
		����� > 5 and ���� < 10.0)
--
SELECT TOP 5 ���������� 
from @mytable
order by ���������� ASC
--
DECLARE @tov NVARCHAR(50)
SET @tov = '������'
SELECT ���������� 
from @mytable
where ����� = @tov
--
SELECT top 1 ����
from @mytable
order by ����*����� desc
--
SELECT top 1 �����
from @mytable
order by ����
