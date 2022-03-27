/*
 Navicat Premium Data Transfer

 Source Server         : localhost_3306
 Source Server Type    : MySQL
 Source Server Version : 80028
 Source Host           : localhost:3306
 Source Schema         : managerdb

 Target Server Type    : MySQL
 Target Server Version : 80028
 File Encoding         : 65001

 Date: 27/03/2022 19:17:05
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for department
-- ----------------------------
DROP TABLE IF EXISTS `department`;
CREATE TABLE `department`  (
  `Id` int NOT NULL AUTO_INCREMENT,
  `Name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL,
  `Desc` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL,
  `Create_time` datetime NOT NULL,
  `User_id` int NOT NULL,
  PRIMARY KEY (`Id`) USING BTREE,
  INDEX `User_id`(`User_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 34 CHARACTER SET = utf8 COLLATE = utf8_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of department
-- ----------------------------
INSERT INTO `department` VALUES (1, '密码事业部', '密码事业部', '2022-03-26 18:35:22', 1);
INSERT INTO `department` VALUES (2, '机要事业部1', '机要事业部', '2022-03-26 18:35:22', 2);
INSERT INTO `department` VALUES (3, '机要事业2', '机要事业部', '2022-03-26 18:35:22', 3);
INSERT INTO `department` VALUES (4, '宣传部', '宣传部', '2022-07-26 19:07:12', 4);
INSERT INTO `department` VALUES (5, '宣传部1', '宣传1', '2022-07-26 19:07:12', 5);
INSERT INTO `department` VALUES (6, '宣传部', '123', '2022-07-26 19:07:12', 6);
INSERT INTO `department` VALUES (7, '全职', '全职', '2022-02-11 11:20:00', 7);
INSERT INTO `department` VALUES (8, '党支部', 'A党支部', '2022-03-26 21:14:58', 8);

-- ----------------------------
-- Table structure for role
-- ----------------------------
DROP TABLE IF EXISTS `role`;
CREATE TABLE `role`  (
  `Id` int NOT NULL AUTO_INCREMENT,
  `Name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL,
  `Create_time` datetime NOT NULL,
  `Update_time` datetime NOT NULL,
  PRIMARY KEY (`Id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 6 CHARACTER SET = utf8 COLLATE = utf8_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of role
-- ----------------------------
INSERT INTO `role` VALUES (1, '职工', '2022-03-25 21:36:44', '2022-03-25 21:36:48');
INSERT INTO `role` VALUES (2, '组长', '2022-03-25 21:37:11', '2022-03-25 21:37:14');
INSERT INTO `role` VALUES (3, '主任', '2022-03-25 21:37:38', '2022-03-25 21:37:41');
INSERT INTO `role` VALUES (4, '经理', '2022-03-25 21:37:59', '2022-03-25 21:38:01');
INSERT INTO `role` VALUES (5, '董事长', '2022-03-25 21:38:21', '2022-03-25 21:38:26');

-- ----------------------------
-- Table structure for schedule
-- ----------------------------
DROP TABLE IF EXISTS `schedule`;
CREATE TABLE `schedule`  (
  `Id` int NOT NULL AUTO_INCREMENT,
  `Reason` varchar(200) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL,
  `Start` datetime NOT NULL,
  `End` date NOT NULL,
  `Type` int NOT NULL,
  `Create_time` datetime NOT NULL,
  `User_id` int NOT NULL,
  `Status` bit(1) NOT NULL,
  PRIMARY KEY (`Id`) USING BTREE,
  INDEX `User_id`(`User_id`) USING BTREE,
  CONSTRAINT `schedule_ibfk_1` FOREIGN KEY (`User_id`) REFERENCES `user` (`Id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 32 CHARACTER SET = utf8 COLLATE = utf8_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of schedule
-- ----------------------------
INSERT INTO `schedule` VALUES (32, '出差', '2022-03-27 14:20:39', '2022-03-28', 2, '2022-03-27 14:20:59', 1, b'1');
INSERT INTO `schedule` VALUES (33, '出差', '2022-03-27 14:20:39', '2022-03-28', 2, '2022-03-27 14:20:59', 2, b'1');
INSERT INTO `schedule` VALUES (37, '请假', '2022-03-27 14:20:39', '2022-03-28', 1, '2022-03-27 14:20:59', 4, b'1');
INSERT INTO `schedule` VALUES (38, '请假', '2022-03-27 14:20:39', '2022-03-28', 1, '2022-03-27 14:20:59', 4, b'1');
INSERT INTO `schedule` VALUES (39, '请假', '2022-03-27 14:20:39', '2022-03-28', 1, '2022-03-27 14:20:59', 4, b'1');
INSERT INTO `schedule` VALUES (40, '请假', '2022-03-27 14:20:39', '2022-03-28', 1, '2022-03-27 14:20:59', 4, b'1');
INSERT INTO `schedule` VALUES (41, '请假', '2022-03-27 14:20:39', '2022-03-28', 1, '2022-03-27 14:20:59', 4, b'0');
INSERT INTO `schedule` VALUES (42, '出差', '2022-03-27 14:20:39', '2022-03-28', 2, '2022-03-27 14:20:59', 4, b'1');
INSERT INTO `schedule` VALUES (43, '请假', '2022-03-27 14:20:39', '2022-03-28', 1, '2022-03-27 14:20:59', 4, b'1');
INSERT INTO `schedule` VALUES (44, '请假', '2022-03-27 14:20:39', '2022-03-28', 1, '2022-03-27 14:20:59', 4, b'1');
INSERT INTO `schedule` VALUES (45, '请假', '2022-03-27 14:20:39', '2022-03-28', 1, '2022-03-27 14:20:59', 7, b'1');
INSERT INTO `schedule` VALUES (46, '请假', '2022-03-27 14:20:39', '2022-03-28', 1, '2022-03-27 14:20:59', 7, b'1');
INSERT INTO `schedule` VALUES (47, '请假', '2022-03-27 14:20:39', '2022-03-28', 1, '2022-03-27 14:20:59', 7, b'1');
INSERT INTO `schedule` VALUES (48, '请假', '2022-03-27 14:20:39', '2022-03-28', 1, '2022-03-27 14:20:59', 7, b'1');
INSERT INTO `schedule` VALUES (49, '请假', '2022-03-27 14:20:39', '2022-03-28', 1, '2022-03-27 14:20:59', 7, b'1');

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `Id` int NOT NULL AUTO_INCREMENT,
  `Name` varchar(50) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NOT NULL,
  `Email` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NOT NULL,
  `Password` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL,
  `Role_id` int NOT NULL,
  `Department_id` int NOT NULL,
  `Create_time` datetime NOT NULL,
  `Phone` bigint NOT NULL,
  PRIMARY KEY (`Id`) USING BTREE,
  INDEX `fk_010`(`Department_id`) USING BTREE,
  INDEX `Role_id`(`Role_id`) USING BTREE,
  CONSTRAINT `fk_010` FOREIGN KEY (`Department_id`) REFERENCES `department` (`Id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `user_ibfk_1` FOREIGN KEY (`Role_id`) REFERENCES `role` (`Id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 741 CHARACTER SET = utf8 COLLATE = utf8_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES (1, 'admin', 'admin', 'admin', 1, 1, '2022-03-26 18:38:49', 12312321);
INSERT INTO `user` VALUES (2, '1234', '1234@qq.com', '123', 1, 2, '2022-03-26 19:04:06', 123123);
INSERT INTO `user` VALUES (4, '周东平', '12123213@qqmcom', '123', 1, 1, '2022-03-27 11:33:43', 1999999999);
INSERT INTO `user` VALUES (5, '小董', '12123213@qqmcom', '123', 1, 4, '2022-03-27 11:33:43', 1999999999);
INSERT INTO `user` VALUES (6, '小马', '12123213@qqmcom', '123', 1, 1, '2022-03-27 11:33:43', 1999999999);
INSERT INTO `user` VALUES (7, '小王', '12123213@qqmcom', '123', 1, 3, '2022-03-27 11:33:43', 1999999999);
INSERT INTO `user` VALUES (741, '小王1', '12123213@qqmcom', '123', 1, 6, '2022-03-27 11:33:43', 1999999999);
INSERT INTO `user` VALUES (742, '小王2', '12123213@qqmcom', '123', 1, 4, '2022-03-27 11:33:43', 1999999999);
INSERT INTO `user` VALUES (743, '小王3', '12123213@qqmcom', '123', 1, 1, '2022-03-27 11:33:43', 1999999999);
INSERT INTO `user` VALUES (744, '小王4', '12123213@qqmcom', '123', 1, 4, '2022-03-27 11:33:43', 1999999999);
INSERT INTO `user` VALUES (745, '小王5', '12123213@qqmcom', '123', 1, 1, '2022-03-27 11:33:43', 1999999999);
INSERT INTO `user` VALUES (746, '小王6', '12123213@qqmcom', '123', 1, 4, '2022-03-27 11:33:43', 1999999999);
INSERT INTO `user` VALUES (747, '小王7', '12123213@qqmcom', '123', 1, 1, '2022-03-27 11:33:43', 1999999999);
INSERT INTO `user` VALUES (748, '小王8', '12123213@qqmcom', '123', 1, 5, '2022-03-27 11:33:43', 1999999999);
INSERT INTO `user` VALUES (749, '马化腾', '11111@qq.com', '123', 1, 1, '2022-03-27 17:19:46', 123123213123);

-- ----------------------------
-- Table structure for vacation
-- ----------------------------
DROP TABLE IF EXISTS `vacation`;
CREATE TABLE `vacation`  (
  `Id` int NOT NULL AUTO_INCREMENT,
  `Time` datetime NOT NULL,
  `Remark` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL,
  `Create_time` datetime NOT NULL,
  `Updata_time` datetime NOT NULL,
  PRIMARY KEY (`Id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 8 CHARACTER SET = utf8 COLLATE = utf8_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of vacation
-- ----------------------------
INSERT INTO `vacation` VALUES (1, '2022-03-25 21:39:34', '参加冬奥会', '2022-03-25 21:39:56', '2022-03-25 21:40:02');
INSERT INTO `vacation` VALUES (2, '2022-11-10 00:00:00', '生病', '2022-11-10 22:33:00', '2022-11-22 00:00:00');
INSERT INTO `vacation` VALUES (3, '2022-11-10 00:00:00', '生病', '2022-11-10 22:33:00', '2022-11-22 00:00:00');
INSERT INTO `vacation` VALUES (4, '2022-11-10 00:00:00', '生病', '2022-11-10 22:33:00', '2022-11-22 00:00:00');
INSERT INTO `vacation` VALUES (5, '2022-11-10 00:00:00', '生病', '2022-11-10 22:33:00', '2022-11-22 00:00:00');
INSERT INTO `vacation` VALUES (6, '2022-11-10 00:00:00', '生病', '2022-11-10 22:33:00', '2022-11-22 00:00:00');
INSERT INTO `vacation` VALUES (7, '2022-11-10 00:00:00', '生病', '2022-11-10 22:33:00', '2022-11-22 00:00:00');
INSERT INTO `vacation` VALUES (8, '2022-11-10 00:00:00', '生病', '2022-11-10 22:33:00', '2022-11-22 00:00:00');

-- ----------------------------
-- Table structure for work_check
-- ----------------------------
DROP TABLE IF EXISTS `work_check`;
CREATE TABLE `work_check`  (
  `Id` int NOT NULL AUTO_INCREMENT COMMENT '员工编号',
  `Time` date NOT NULL COMMENT '日期',
  `Start` datetime NOT NULL COMMENT '最晚开始时间',
  `End` datetime NOT NULL COMMENT '最早开始时间',
  `Start_check` datetime NOT NULL COMMENT '员工上班打卡时间',
  `End_check` datetime NOT NULL COMMENT '员工下班打卡时间',
  `Work_time` decimal(10, 0) NULL DEFAULT NULL COMMENT '工作时间',
  `User_id` int NOT NULL COMMENT '用户编号',
  PRIMARY KEY (`Id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 34 CHARACTER SET = utf8 COLLATE = utf8_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of work_check
-- ----------------------------
INSERT INTO `work_check` VALUES (4, '2022-03-26', '2022-03-26 18:44:56', '2022-03-26 18:44:59', '2022-03-26 18:45:01', '2022-03-26 18:45:05', NULL, 1);
INSERT INTO `work_check` VALUES (5, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 2);
INSERT INTO `work_check` VALUES (6, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 2);
INSERT INTO `work_check` VALUES (7, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 3);
INSERT INTO `work_check` VALUES (8, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 2);
INSERT INTO `work_check` VALUES (9, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 1);
INSERT INTO `work_check` VALUES (10, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 2);
INSERT INTO `work_check` VALUES (11, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 3);
INSERT INTO `work_check` VALUES (12, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 4);
INSERT INTO `work_check` VALUES (13, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 5);
INSERT INTO `work_check` VALUES (14, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 6);
INSERT INTO `work_check` VALUES (15, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 7);
INSERT INTO `work_check` VALUES (16, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 1);
INSERT INTO `work_check` VALUES (17, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 2);
INSERT INTO `work_check` VALUES (18, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 2);
INSERT INTO `work_check` VALUES (19, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 2);
INSERT INTO `work_check` VALUES (20, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 2);
INSERT INTO `work_check` VALUES (21, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 1);
INSERT INTO `work_check` VALUES (22, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 2);
INSERT INTO `work_check` VALUES (23, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 2);
INSERT INTO `work_check` VALUES (24, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 2);
INSERT INTO `work_check` VALUES (25, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 2);
INSERT INTO `work_check` VALUES (26, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 2);
INSERT INTO `work_check` VALUES (27, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 3);
INSERT INTO `work_check` VALUES (28, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 3);
INSERT INTO `work_check` VALUES (29, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 3);
INSERT INTO `work_check` VALUES (30, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 5);
INSERT INTO `work_check` VALUES (31, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 5);
INSERT INTO `work_check` VALUES (32, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 1);
INSERT INTO `work_check` VALUES (33, '2022-03-26', '2022-03-26 18:43:10', '2022-03-26 18:43:12', '2022-03-26 18:43:14', '2022-03-26 18:43:18', NULL, 1);

SET FOREIGN_KEY_CHECKS = 1;
