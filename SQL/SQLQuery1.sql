declare @mytable as table(
	НДок int NOT NULL,
	Дата datetime NOT NULL,
	Товар nvarchar(100) NOT NULL,
	Покупатель nvarchar(100) NOT NULL,
	Колво int,
	Цена float
	primary key (нДок)
	)
	
insert into @mytable VALUES
(1, '18.4.2006', 'молоко', 'Зивертлайн', 18, 4.1),
(2, '21.10.2000', 'яйца', 'Эдельвейс', 4, 72.4),
(3, '22.3.2013', 'сыр', 'Холмы', 21, 70.5),
(4, '5.3.2000', 'пастила', 'Речка', 21, 49.1),
(5, '13.9.2010', 'мармелад', 'Барни', 5, 39.1),
(6, '16.2.2012', 'мед', 'Клуб', 22, 38.2),
(7, '22.6.2001', 'плесень', 'Гепард', 2, 44.7),
(8, '11.7.2007', 'мясо', 'Продуктовый', 18, 91.2),
(9, '6.9.2004', 'селедка', 'Продуктовый2', 12, 70.3),
(10, '9.5.2011', 'рис', 'Бесплатный', 17, 66.4),
(11, '18.9.2000', 'морковь', 'Платный', 20, 54.7),
(12, '23.1.2011', 'тушенка', 'Очень_платный', 24, 85.9),
(13, '9.6.2000', 'просо', 'Платный_но_бесплатный', 11, 31.6),
(14, '25.4.2010', 'ячмень', 'Неназвание', 16, 10.6),
(15, '17.03.2014', 'рыбий_жир', 'Ничего_хорошего', 6, 44.6)

---	
SELECT distinct Дата
from @mytable
--
SELECT distinct Покупатель
from @mytable
where (DATEPART (wk, GETDATE ()) - DATEPART (wk, Дата) = 1) and 
	  (DATEPART (yy, GETDATE ()) - DATEPART (yy, Дата) = 0) 
--
SELECT distinct Покупатель
from @mytable
order by Покупатель ASC
--
SELECT Цена*Колво as Стоимость
from @mytable
--
SELECT *
from @mytable
where (Покупатель like 'A*' and DATEPART (mm, Дата) = 1 and DATEPART (yy, Дата) = 2013 or
		Колво > 5 and Цена < 10.0)
--
SELECT TOP 5 Покупатель 
from @mytable
order by Покупатель ASC
--
DECLARE @tov NVARCHAR(50)
SET @tov = 'Молоко'
SELECT Покупатель 
from @mytable
where Товар = @tov
--
SELECT top 1 нДок
from @mytable
order by Цена*Колво desc
--
SELECT top 1 Товар
from @mytable
order by Цена
