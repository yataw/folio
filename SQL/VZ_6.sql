DECLARE @Polynoms AS TABLE(
	P_ID INT NOT NULL,
	Degr INT,
	Coef FLOAT
)

INSERT INTO @Polynoms VALUES (1, 0, 1)
INSERT INTO @Polynoms VALUES (1, 1, 4)
INSERT INTO @Polynoms VALUES (1, 2, 1)
INSERT INTO @Polynoms VALUES (2, 0, 4)
INSERT INTO @Polynoms VALUES (2, 1, 2)
INSERT INTO @Polynoms VALUES (2, 2, 1)
INSERT INTO @Polynoms VALUES (3, 1, 1)
INSERT INTO @Polynoms VALUES (3, 2, 2.4)
INSERT INTO @Polynoms VALUES (3, 3, 1)
INSERT INTO @Polynoms VALUES (4, 0, -2)
INSERT INTO @Polynoms VALUES (4, 1, 1)
INSERT INTO @Polynoms VALUES (4, 3, -1)
INSERT INTO @Polynoms VALUES (4, 5, 0.5)
INSERT INTO @Polynoms VALUES (5, 0, 2)
INSERT INTO @Polynoms VALUES (5, 1, 1)
INSERT INTO @Polynoms VALUES (5, 2, 0)


DECLARE @ID AS INT
SET @ID = 4

SELECT Polynoms.Degr AS Degr, Polynoms.Coef AS Coef
FROM @Polynoms AS Polynoms
WHERE Polynoms.P_ID = @ID
ORDER BY Degr DESC

SELECT Polynoms.P_ID AS ID
FROM @Polynoms AS Polynoms
WHERE Polynoms.Coef = 0
GROUP BY Polynoms.P_ID

SET @ID = 1
DECLARE @K INT
SET @K = 3

SELECT Polynoms.Degr AS Degr, Polynoms.Coef*@K AS Coef
FROM @Polynoms AS Polynoms
WHERE Polynoms.P_ID = @ID
ORDER BY Degr DESC

DECLARE @N INT
SET @N = 2
SET @ID = 1

IF( 
	SELECT MAX(Polynoms.Degr)
	FROM @Polynoms AS Polynoms
	WHERE Polynoms.P_ID = @ID AND Polynoms.Coef <> 0
	) = @N
SELECT 'YES' AS Polynom_is_n_degr
ELSE
SELECT 'NO' AS Polynom_is_n_degr

DECLARE @ID1 INT
DECLARE @ID2 INT
SET @ID1 = 1
SET @ID2 = 2

SELECT Polynoms1.Degr AS Degr, (Polynoms1.Coef + Polynoms2.Coef) AS Coef
FROM @Polynoms AS Polynoms1,  @Polynoms AS Polynoms2
WHERE Polynoms1.P_ID = @ID1 AND Polynoms2.P_ID = @ID2 AND Polynoms1.Degr = Polynoms2.Degr
ORDER BY Degr DESC


SET @ID1 = 1
SET @ID2 = 2
SELECT T.Degr, SUM(T.Coef) AS Coef
	FROM
		(
			SELECT T1.Degr + T2.Degr AS Degr,
				T1.Coef * T2.Coef AS Coef
			FROM @Polynoms AS T1,
				@Polynoms AS T2
			WHERE T1.P_ID = @ID1
				AND T2.P_ID = @ID2
		) AS T
GROUP BY T.Degr
ORDER BY T.Degr DESC



DECLARE @X INT
SET @X = 3

SELECT SUM(Polynoms.Coef*@X) AS P_ot_x
FROM @Polynoms AS Polynoms
WHERE Polynoms.P_ID = @ID

SET @ID = 1
DECLARE @A INT
DECLARE @B INT
DECLARE @C INT

SET @B = ( 
		SELECT Polynoms.Coef
		FROM @Polynoms AS Polynoms
		WHERE Polynoms.P_ID = @ID AND Polynoms.Degr = 1
	)


IF( 
	SELECT MAX(Polynoms.Degr)
	FROM @Polynoms AS Polynoms
	WHERE Polynoms.P_ID = @ID AND Polynoms.Coef <> 0
	) = 2
	AND @B*@B - $*@A*@C = 0
SELECT 'YES' AS Polynom_is_square
ELSE
SELECT 'NO' AS Polynom_is_square


SET @ID = 4

SET @N =(SELECT MAX(Polynoms.Degr)
		FROM @Polynoms AS Polynoms
		WHERE Polynoms.P_ID = @ID AND Polynoms.Coef <> 0)


SET @A =(SELECT COUNT(*)
		FROM @Polynoms AS Polynoms
		WHERE Polynoms.P_ID = @ID AND Polynoms.Degr <= @N AND Polynoms.Coef > 0)

SET @B =(SELECT COUNT(*)
		FROM @Polynoms AS Polynoms
		WHERE Polynoms.P_ID = @ID AND Polynoms.Degr <= @N AND Polynoms.Coef = 0)

SET @C =(SELECT COUNT(*)
		FROM @Polynoms AS Polynoms
		WHERE Polynoms.P_ID = @ID AND Polynoms.Degr <= @N AND Polynoms.Coef < 0)

SELECT @A AS 'more than 0', @B AS 'ecual 0', @C AS 'less than 0'


SET @ID = 3
IF( 
	SELECT SUM(ABS(Polynoms.Coef - FLOOR(Polynoms.Coef)))
	FROM @Polynoms AS Polynoms
	WHERE Polynoms.P_ID = @ID 
	) != 0
SELECT 'NO' AS Polynoms_coefs_is_int
ELSE
SELECT 'YES' AS Polynoms_coefs_is_int



SET @ID = 5
IF(SELECT MAX(Polynoms.Degr)
		FROM @Polynoms AS Polynoms
		WHERE Polynoms.P_ID = @ID AND Polynoms.Coef <> 0) != 1
SELECT 'NO' AS Polynom_has_first_degr
ELSE
BEGIN
	SET @A = ( SELECT Polynoms.Coef
				FROM @Polynoms AS Polynoms
				WHERE Polynoms.P_ID = @ID AND Polynoms.Degr = 0)
	SELECT Polynoms.Coef / @A AS Solution
	FROM @Polynoms AS Polynoms
	WHERE Polynoms.P_ID = @ID AND Polynoms.Degr = 1
END



SET @ID = 1
IF(SELECT MAX(Polynoms.Degr)
		FROM @Polynoms AS Polynoms
		WHERE Polynoms.P_ID = @ID AND Polynoms.Coef <> 0) != 2
SELECT 'NO' AS Polynom_has_second_degr
ELSE
BEGIN
		SET @A =(SELECT Polynoms.Coef
				FROM @Polynoms AS Polynoms
				WHERE Polynoms.P_ID = @id AND Degr = 2)  
		SET @B =(SELECT Polynoms.Coef
				FROM @Polynoms AS Polynoms
				WHERE Polynoms.P_ID = @id AND Degr = 1)  
		SET @C=(SELECT Polynoms.Coef
				FROM @Polynoms AS Polynoms
				WHERE Polynoms.P_ID = @id AND Degr = 0) 
		IF @B * @B >= 4 * @A * @C
			IF @B * @B = 4 * @A * @C
				SELECT -@B / 2 / @A AS X1
			ELSE SELECT (-@B + SQRT(@B * @B - 4 * @A * @C)) / 2 / @A AS X1,
					(-@B - SQRT(@B * @B - 4 * @A * @C)) / 2 / @A AS X2
		ELSE SELECT 'NO'
END





DECLARE @id_1 INT, @id_2 INT, @id_3 INT
SET @ID1 = 1
SET @ID2 = 2
SET @ID = 3


DECLARE @R FLOAT
SET @R = (SELECT SUM(ABS(T3.Coef - T4.Coef))
			 FROM (SELECT P_ID, Degr, Coef
				   FROM @Polynoms AS Polynoms
				   WHERE Polynoms.P_ID = @ID) AS T3,
				  (SELECT P_ID = @ID + 1, T.Degr, SUM(T.Coef) AS Coef
				   FROM
					   (SELECT  T1.Degr + T2.Degr AS Degr,
					 	T1.Coef * T2.Coef AS Coef
					 	FROM @Polynoms AS T1,
					   	@polynoms AS T2
						WHERE T1.P_ID = @ID1
						AND T2.P_ID = @ID2
						) AS T
			       GROUP BY T.Degr) AS T4
			 WHERE T3.Degr = T4.Degr AND T3.P_ID = @ID)

IF @R = 0
	SELECT 'YES' AS Result
ELSE
	SELECT 'NO' AS Result


SET @ID1 = 1
SET @ID2 = 2
SET @ID = 3

SET @R = (SELECT SUM(ABS(T3.Coef - T4.Coef))
			 FROM (SELECT P_ID, Degr, Coef
				   FROM @Polynoms
				   WHERE P_ID = @ID1) AS T3,
				  (SELECT ID = @ID + 1, T.Degr, SUM(T
				  .Coef) AS Coef
				   FROM
					   (SELECT  T1.Degr + T2.Degr AS Degr,
					 	T1.Coef * T2.Coef AS Coef
					 	FROM @Polynoms AS T1,
					   	@Polynoms AS T2
						WHERE T1.P_ID = @ID
						AND T2.P_ID = @ID2
						) AS T
			       GROUP BY T.Degr) AS T4
			 WHERE T3.Degr = T4.Degr AND T3.P_ID = @ID1)

IF @R = 0
	SELECT 'YES' AS Result
ELSE
	SELECT 'NO' AS Result
