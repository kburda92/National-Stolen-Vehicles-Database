CREATE TABLE IF NOT EXISTS `Vehicles` (
	`ID`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`Registration`	TEXT NOT NULL UNIQUE,
	`Make`	TEXT NOT NULL,
	`Model`	TEXT NOT NULL,
	`Owner`	TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS `Vehicles_Log` (
	`ID`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`Date`	TEXT,
	`Registration`	TEXT,
	`Make`	TEXT,
	`Model`	TEXT,
	`Owner`	TEXT
);

INSERT INTO `Vehicles`(`Registration`,`Make`,`Model`,`Owner`) VALUES ('SB122256','Honda','CR-V','Jan Kowalski');
INSERT INTO `Vehicles`(`Registration`,`Make`,`Model`,`Owner`) VALUES ('ABC3434245','Volkswagen','Jetta','John Doe');