/*
 Navicat Premium Data Transfer

 Source Server         : May
 Source Server Type    : Oracle
 Source Server Version : 180000
 Source Host           : localhost:1521
 Source Schema         : C##DOG

 Target Server Type    : Oracle
 Target Server Version : 180000
 File Encoding         : 65001

 Date: 15/05/2019 18:16:49
*/


-- ----------------------------
-- Table structure for INFO
-- ----------------------------
DROP TABLE "C##DOG"."INFO";
CREATE TABLE "C##DOG"."INFO" (
  "ID" NUMBER VISIBLE NOT NULL ,
  "NAME" VARCHAR2(20 BYTE) VISIBLE ,
  "ADDRESS" VARCHAR2(20 BYTE) VISIBLE 
)
TABLESPACE "USERS"
LOGGING
NOCOMPRESS
PCTFREE 10
INITRANS 1
STORAGE (
  INITIAL 65536 
  NEXT 1048576 
  MINEXTENTS 1
  MAXEXTENTS 2147483645
  BUFFER_POOL DEFAULT
)
PARALLEL 1
NOCACHE
DISABLE ROW MOVEMENT
;

-- ----------------------------
-- Records of "INFO"
-- ----------------------------
INSERT INTO "C##DOG"."INFO" VALUES ('2017', 'Tian', 'Henan');
INSERT INTO "C##DOG"."INFO" VALUES ('2018', 'Wang', 'Shandong');
INSERT INTO "C##DOG"."INFO" VALUES ('2019', 'Li', 'Beijing');
INSERT INTO "C##DOG"."INFO" VALUES ('2020', 'Sun', 'Shanghai');

-- ----------------------------
-- Checks structure for table INFO
-- ----------------------------
ALTER TABLE "C##DOG"."INFO" ADD CONSTRAINT "SYS_C007430" CHECK ("ID" IS NOT NULL) NOT DEFERRABLE INITIALLY IMMEDIATE NORELY VALIDATE;
