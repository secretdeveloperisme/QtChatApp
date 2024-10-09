-- --------------------------------------------------------
-- Host:                         chat_app.db
-- Server version:               3.44.0
-- Server OS:                    
-- HeidiSQL Version:             12.6.0.6765
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES  */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;


-- Dumping database structure for chat_app
CREATE DATABASE IF NOT EXISTS "chat_app";
;

-- Dumping structure for table chat_app.CHAT_GROUPS
CREATE TABLE IF NOT EXISTS CHAT_GROUPS (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL UNIQUE);

-- Dumping data for table chat_app.CHAT_GROUPS: 3 rows
/*!40000 ALTER TABLE "CHAT_GROUPS" DISABLE KEYS */;
INSERT INTO "CHAT_GROUPS" ("id", "name") VALUES
	(1, 'Work'),
	(2, 'Student'),
	(3, 'C++ Class');
/*!40000 ALTER TABLE "CHAT_GROUPS" ENABLE KEYS */;

-- Dumping structure for table chat_app.CHAT_MESSAGES
CREATE TABLE IF NOT EXISTS CHAT_MESSAGES (id INTEGER PRIMARY KEY AUTOINCREMENT, content TEXT NOT NULL, createdDate TEXT, user_id INTEGER NOT NULL, group_id INTEGER NOT NULL, FOREIGN KEY (user_id) REFERENCES CHAT_USERS(id), FOREIGN KEY (group_id) REFERENCES CHAT_GROUPS(id));

-- Dumping data for table chat_app.CHAT_MESSAGES: 10 rows
/*!40000 ALTER TABLE "CHAT_MESSAGES" DISABLE KEYS */;
INSERT INTO "CHAT_MESSAGES" ("id", "content", "createdDate", "user_id", "group_id") VALUES
	(1, 'hello this is message', '2024-10-09T09:25:16.000Z', 1, 1),
	(2, 'ohknow', '2024-10-09T09:25:21.000Z', 1, 1),
	(3, 'really great', '2024-10-09T09:25:42.000Z', 3, 1),
	(4, 'this is owe some', '2024-10-09T09:25:48.000Z', 3, 1),
	(5, 'know', '2024-10-09T09:25:51.000Z', 3, 1),
	(6, 'that really great to debug', '2024-10-09T12:56:56.000Z', 1, 1),
	(7, 'happy coding!', '2024-10-09T12:57:06.000Z', 1, 1),
	(8, '🎆 wow', '2024-10-09T12:57:19.000Z', 1, 1),
	(9, 'that is so cool', '2024-10-09T13:00:57.000Z', 3, 1),
	(10, 'happy  codding tooo🎀', '2024-10-09T13:01:11.000Z', 3, 1);
/*!40000 ALTER TABLE "CHAT_MESSAGES" ENABLE KEYS */;

-- Dumping structure for table chat_app.CHAT_USERS
CREATE TABLE IF NOT EXISTS CHAT_USERS (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT NOT NULL UNIQUE);

-- Dumping data for table chat_app.CHAT_USERS: 3 rows
/*!40000 ALTER TABLE "CHAT_USERS" DISABLE KEYS */;
INSERT INTO "CHAT_USERS" ("id", "username") VALUES
	(1, 'hoanglinh'),
	(2, 'thanhnguyen'),
	(3, 'phucnguyen');
/*!40000 ALTER TABLE "CHAT_USERS" ENABLE KEYS */;

/*!40103 SET TIME_ZONE=IFNULL(@OLD_TIME_ZONE, 'system') */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
