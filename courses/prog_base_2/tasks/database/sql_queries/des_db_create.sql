CREATE TABLE "Designers" (
	`Id`	INTEGER,
	`Name`	TEXT NOT NULL,
	`Surname`	TEXT NOT NULL,
	`AverageVertices`	REAL,
	`Experience`	INTEGER DEFAULT 0,
	`Salary`	REAL,
	`ProjectCount`	INTEGER,
	`HireDate`	TEXT DEFAULT 0,
	PRIMARY KEY(Id)
)