--1
DECLARE @Polynoms AS TABLE (
	ID INT,
	Degr INT,
	Coeff FLOAT
)

INSERT INTO @Polynoms VALUES (1, 0, 1)
INSERT INTO @Polynoms VALUES (1, 1, 2)
INSERT INTO @Polynoms VALUES (1, 2, 1)
INSERT INTO @Polynoms VALUES (2, 0, 4)
INSERT INTO @Polynoms VALUES (2, 1, 2)
INSERT INTO @Polynoms VALUES (2, 2, 1)
INSERT INTO @Polynoms VALUES (3, 1, 1)
INSERT INTO @Polynoms VALUES (3, 2, 2)
INSERT INTO @Polynoms VALUES (3, 3, 1)
INSERT INTO @Polynoms VALUES (4, 0, -2)
INSERT INTO @Polynoms VALUES (4, 1, 0.5)
INSERT INTO @Polynoms VALUES (4, 3, -1)
INSERT INTO @Polynoms VALUES (4, 5, 0)
INSERT INTO @Polynoms VALUES (5, 0, 2)
INSERT INTO @Polynoms VALUES (5, 1, 1)
INSERT INTO @Polynoms VALUES (5, 2, 0)

--2
DECLARE @ID1 AS INT
SET @ID1 = 2

SELECT Coeff, Degr
FROM @Polynoms
WHERE ID = @ID1
ORDER BY Degr DESC

--3
SELECT DISTINCT ID
FROM @Polynoms
WHERE Coeff = 0

--4
SET @ID1 = 4
DECLARE @Factor AS FLOAT
SET @Factor = 1.5

SELECT Coeff * @Factor AS Coeff, Degr
FROM @Polynoms
WHERE ID = @ID1
ORDER BY Degr DESC

--5
SET @ID1 = 4
DECLARE @N AS INT
SET @N = 3
	
IF (
	SELECT MAX(Degr)
	FROM (
		SELECT Degr AS Degr
		FROM @Polynoms
		WHERE ID = @ID1 AND Coeff != 0
	) AS T
) = @N
SELECT '��' AS [��������?]
ELSE
SELECT '���' AS [��������?]

--6 �������, ��� �������� � 4 ������, �� � �� ��������, ���. �������� ����, �� � ������� ������ �����������, �� ������� ���, �� ������� �������� ���.
--����� �������� � ���������� ����� �������� ������ �������
SET @ID1 = 1
DECLARE @ID2 AS INT
SET @ID2 = 2

DECLARE @SUM AS TABLE (
	Degr INT,
	Coeff FLOAT
)

DECLARE @Degr AS INT
IF (
	SELECT MAX(Degr)
	FROM @Polynoms
	WHERE ID = @ID1
) > (
	SELECT MAX(Degr)
	FROM @Polynoms
	WHERE ID = @ID2
)
SET @Degr = (
	SELECT MAX(Degr)
	FROM @Polynoms
	WHERE ID = @ID1
)
ELSE
SET @Degr = (
	SELECT MAX(Degr)
	FROM @Polynoms
	WHERE ID = @ID2
)

WHILE (@Degr > -1)
BEGIN
	IF (
		SELECT Coeff
		FROM @Polynoms
		WHERE ID = @ID1 AND Degr = @Degr
	) != 0
		IF (
			SELECT Coeff
			FROM @Polynoms
			WHERE ID = @ID2 AND Degr = @Degr
		) != 0
			INSERT INTO @SUM VALUES(@Degr, (
				SELECT T1.Coeff + T2.Coeff
				FROM @Polynoms AS T1, @Polynoms AS T2
				WHERE T1.ID = @ID1 AND T2.ID = @ID2 AND T1.Degr = @Degr AND T2.Degr = @Degr
			))
		ELSE
			INSERT INTO @SUM VALUES(@Degr, (
				SELECT T.Coeff
				FROM @Polynoms AS T
				WHERE T.ID = @ID1 AND T.Degr = @Degr
			))
	ELSE
		IF (
			SELECT Coeff
			FROM @Polynoms
			WHERE ID = @ID2 AND Degr = @Degr
		) != 0
			INSERT INTO @SUM VALUES(@Degr, (
				SELECT T.Coeff
				FROM @Polynoms AS T
				WHERE T.ID = @ID2 AND T.Degr = @Degr
			))
	SET @Degr = @Degr - 1
END

SELECT *
FROM @SUM
ORDER BY Degr DESC

--6 � ������ �������� ���� �����, ����� ������� - ������������� � "�������������" ����
DECLARE @MAXDEGR AS INT
DECLARE @First AS TABLE (
	Degr INT,
	Coeff FLOAT
)
SET @Degr = (
	SELECT MAX(Degr)
	FROM @Polynoms
	WHERE ID = @ID1
)
SET @MAXDEGR = @Degr
WHILE(@Degr > -1)
BEGIN
	IF (
		SELECT Coeff
		FROM @Polynoms
		WHERE ID = @ID1 AND Degr = @Degr
	) != 0
		INSERT INTO @First VALUES (@Degr, (
			SELECT Coeff
			FROM @Polynoms
			WHERE ID = @ID1 AND Degr = @Degr
		))
	ELSE
	BEGIN
		IF @Degr = @MAXDEGR
			SET @MAXDEGR = @MAXDEGR - 1
		ELSE
			INSERT INTO @First VALUES (@Degr, 0)
	END
	SET @Degr = @Degr - 1
END

DECLARE @Second AS TABLE (
	Degr INT,
	Coeff FLOAT
)
SET @Degr = (
	SELECT MAX(Degr)
	FROM @Polynoms
	WHERE ID = @ID2
)
SET @MAXDEGR = @Degr
WHILE(@Degr > -1)
BEGIN
	IF (
		SELECT Coeff
		FROM @Polynoms
		WHERE ID = @ID2 AND Degr = @Degr
	) != 0
		INSERT INTO @Second VALUES (@Degr, (
			SELECT Coeff
			FROM @Polynoms
			WHERE ID = @ID2 AND Degr = @Degr
		))
	ELSE
	BEGIN
		IF @Degr = @MAXDEGR
			SET @MAXDEGR = @MAXDEGR - 1
		ELSE
			INSERT INTO @Second VALUES (@Degr, 0)
	END
	SET @Degr = @Degr - 1
END

--��� ������ ���������� ���

SELECT T1.Degr, T1.Coeff + T2.Coeff AS Coeff
FROM @First AS T1, @Second AS T2
WHERE T1.Degr = T2.Degr

--7 ������������� ��������������� �� ��������, ����� �� ��������� ��� ������.
SELECT T1.Degr + T2.Degr AS Degr, SUM(T1.Coeff * T2.Coeff) AS Coeff
FROM @First AS T1, @Second AS T2
GROUP BY T1.Degr + T2.Degr

--8
SET @ID1 = 4
SET @N = 2

SELECT SUM(Coeff * POWER(@N, Degr)) AS ��������
FROM @Polynoms
WHERE ID = @ID1

--9
SET @ID1 = 1
IF (
	SELECT MAX(Degr)
	FROM @Polynoms
	WHERE ID = @ID1
) != 2
	SELECT '���' AS [��������?]
ELSE
	IF (
		SELECT Coeff
		FROM @Polynoms
		WHERE ID = @ID1 AND Degr = 1
	) * (
		SELECT Coeff
		FROM @Polynoms
		WHERE ID = @ID1 AND Degr = 1
	) = 4 * (
		SELECT Coeff
		FROM @Polynoms
		WHERE ID = @ID1 AND Degr = 2
	) * (
		SELECT Coeff
		FROM @Polynoms
		WHERE ID = @ID1 AND Degr = 0
	)
		SELECT '��' AS [��������?]
	ELSE
		SELECT '���' AS [��������?]

--10 ������������� ��������������� �� ��������, ����� �� ��������� ��� ������.
SELECT (
	SELECT COUNT(Coeff)
	FROM @Second
	WHERE Coeff < 0
) AS [< 0], (
	SELECT COUNT(Coeff)
	FROM @Second
	WHERE Coeff = 0
) AS [= 0], (
	SELECT COUNT(Coeff)
	FROM @Second
	WHERE Coeff > 0
) AS [> 0]

--11
SET @ID1 = 4
IF (
	SELECT COUNT(Coeff)
	FROM @Polynoms
	WHERE ID = @ID1 AND FLOOR(Coeff) != Coeff
) = 0
	SELECT '��' AS [�����?]
ELSE
	SELECT '���' AS [�����?]

--12 ������� � "�������������" ���� �������
SET @ID1 = 5
DECLARE @Third AS TABLE (
	Degr INT,
	Coeff FLOAT
)
SET @Degr = (
	SELECT MAX(Degr)
	FROM @Polynoms
	WHERE ID = @ID1
)
SET @MAXDEGR = @Degr
WHILE(@Degr > -1)
BEGIN
	IF (
		SELECT Coeff
		FROM @Polynoms
		WHERE ID = @ID1 AND Degr = @Degr
	) != 0
		INSERT INTO @Third VALUES (@Degr, (
			SELECT Coeff
			FROM @Polynoms
			WHERE ID = @ID1 AND Degr = @Degr
		))
	ELSE
	BEGIN
		IF @Degr = @MAXDEGR
			SET @MAXDEGR = @MAXDEGR - 1
		ELSE
			INSERT INTO @Third VALUES (@Degr, 0)
	END
	SET @Degr = @Degr - 1
END
-- � �������� ������ �������� ������, �� ��������� ������� ����� �������������� ���������� @MAXDEGR
IF (
	SELECT MAX(Degr)
	FROM @Third
) = 1
	SELECT (
		SELECT Coeff
		FROM @Third
		WHERE Degr = 0
	) / (
		SELECT Coeff
		FROM @Third
		WHERE Degr = 1
	) AS ������

--13 ������������� ��������������� �� ��������, ����� �� ��������� ��� ������.
IF (
	SELECT MAX(Degr)
	FROM @Second
) = 2
	IF (
		SELECT Coeff
		FROM @Second
		WHERE Degr = 1
	) = 0
		SELECT SQRT((
			SELECT Coeff
			FROM @Second
			WHERE Degr = 0
		) / (
			SELECT Coeff
			FROM @Second
			WHERE Degr = 2
		)) AS [������ ������], -SQRT((
			SELECT Coeff
			FROM @Second
			WHERE Degr = 0
		) / (
			SELECT Coeff
			FROM @Second
			WHERE Degr = 2
		)) AS [������ ������]
		
	ELSE
	IF (
		SELECT Coeff
		FROM @Second
		WHERE Degr = 1
	) * (
		SELECT Coeff
		FROM @Second
		WHERE Degr = 1
	) < 4 * (
		SELECT Coeff
		FROM @Second
		WHERE Degr = 0
	) * (
		SELECT Coeff
		FROM @Second
		WHERE Degr = 2
	)
		SELECT NULL AS [��� ������]
	ELSE
		IF (
			SELECT Coeff
			FROM @Second
			WHERE Degr = 1
		) * (
			SELECT Coeff
			FROM @Second
			WHERE Degr = 1
		) = 4 * (
			SELECT Coeff
			FROM @Second
			WHERE Degr = 0
		) * (
			SELECT Coeff
			FROM @Second
			WHERE Degr = 2
		)
			SELECT (
				SELECT SQRT(Coeff)
				FROM @Second
				WHERE Degr = 0
			) / (
				SELECT SQRT(Coeff)
				FROM @Second
				WHERE Degr = 2
			) AS ������
		ELSE
			SELECT (0 - (
				SELECT Coeff
				FROM @Second
				WHERE Degr = 1
			) - SQRT((
				SELECT Coeff
				FROM @Second
				WHERE Degr = 1
			) * (
				SELECT Coeff
				FROM @Second
				WHERE Degr = 1
			) - 4 * (
				SELECT Coeff
				FROM @Second
				WHERE Degr = 0
			) * (
				SELECT Coeff
				FROM @Second
				WHERE Degr = 2
			))) / 2 / (
				SELECT Coeff
				FROM @Second
				WHERE Degr = 2
			) AS [������ ������], (0 - (
				SELECT Coeff
				FROM @Second
				WHERE Degr = 1
			) + SQRT((
				SELECT Coeff
				FROM @Second
				WHERE Degr = 1
			) * (
				SELECT Coeff
				FROM @Second
				WHERE Degr = 1
			) - 4 * (
				SELECT Coeff
				FROM @Second
				WHERE Degr = 0
			) * (
				SELECT Coeff
				FROM @Second
				WHERE Degr = 2
			))) / 2 / (
				SELECT Coeff
				FROM @Second
				WHERE Degr = 2
			) AS [������ ������]

--14 ������������� ��� 3-�� ���������������� ����������
IF ((
	SELECT MAX(T.Degr)
	FROM (
		SELECT T1.Degr + T2.Degr AS Degr, SUM(T1.Coeff * T2.Coeff) AS Coeff
		FROM @First AS T1, @Second AS T2
		GROUP BY T1.Degr + T2.Degr
	) AS T) = (
		SELECT MAX(Degr)
		FROM @Third
))
	IF (
		SELECT SUM(ABS(T.Coeffs))
		FROM (
			SELECT T1.Coeff - T2.Coeff AS Coeffs
			FROM (
				SELECT T1.Degr + T2.Degr AS Degr, SUM(T1.Coeff * T2.Coeff) AS Coeff
				FROM @First AS T1, @Second AS T2
				GROUP BY T1.Degr + T2.Degr
			) AS T1, @Third AS T2
			WHERE T1.Degr = T2.Degr
		) AS T
	) > 0
	SELECT '1' AS ������������

--15 �� ��, �� �������� �������. ������ ������ ������� @Third, � ����� @First � @Second
IF ((
	SELECT MAX(T.Degr)
	FROM (
		SELECT T1.Degr + T2.Degr AS Degr, SUM(T1.Coeff * T2.Coeff) AS Coeff
		FROM @First AS T1, @Second AS T2
		GROUP BY T1.Degr + T2.Degr
	) AS T) = (
		SELECT MAX(Degr)
		FROM @Third
))
	IF (
		SELECT SUM(ABS(T.Coeffs))
		FROM (
			SELECT T1.Coeff - T2.Coeff AS Coeffs
			FROM (
				SELECT T1.Degr + T2.Degr AS Degr, SUM(T1.Coeff * T2.Coeff) AS Coeff
				FROM @First AS T1, @Second AS T2
				GROUP BY T1.Degr + T2.Degr
			) AS T1, @Third AS T2
			WHERE T1.Degr = T2.Degr
		) AS T
	) > 0
	SELECT '1' AS ������������