CREATE TABLE CHAT_USERS(
id INT AUTO_INCREMENT PRIMARY KEY,
username VARCHAR(50) NOT NULL UNIQUE
);

CREATE TABLE CHAT_GROUPS (
id INT AUTO_INCREMENT PRIMARY KEY,
name VARCHAR(50) NOT NULL UNIQUE
);

CREATE TABLE chat_messages(
id INT AUTO_INCREMENT PRIMARY KEY,
content VARCHAR(255) NOT NULL,
createdDate DATE;
user_id INT NOT NULL, 
group_id INT NOT NULL
);


ALTER  TABLE chat_messages ADD CONSTRAINT FK_USER_ID FOREIGN KEY(user_id) REFERENCES CHAT_USERS(id);
ALTER  TABLE chat_messages ADD CONSTRAINT FK_GROUP_ID FOREIGN KEY(group_id) REFERENCES CHAT_GROUPS(id)



INSERT INTO chat_users(username) VALUE("hoanglinh");
INSERT INTO chat_users(username) VALUE("thanhnguyen");
INSERT INTO chat_users(username) VALUE("phucnguyen");



INSERT INTO chat_groups(name) VALUE("Work");
INSERT INTO chat_groups(name) VALUE("Student");
INSERT INTO chat_groups(name) VALUE("C++ Class");