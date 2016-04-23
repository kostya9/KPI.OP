CREATE TABLE "Designers" (
	`Id`	INTEGER,
	`Name`	TEXT NOT NULL,
	`Surname`	TEXT NOT NULL,
	`averageVertices`	REAL,
	`Experience`	INTEGER DEFAULT 0,
	`HireDate`	INTEGER DEFAULT 0,
	PRIMARY KEY(Id)
)