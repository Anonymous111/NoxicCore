ALTER TABLE `creature_proto` ADD COLUMN `power_type` TINYINT(1) UNSIGNED NOT NULL DEFAULT '0' AFTER `maxhealth`;
ALTER TABLE `creature_proto` CHANGE COLUMN `mana` `minpower` INT(30) UNSIGNED NOT NULL DEFAULT '0' AFTER `power_type`;
ALTER TABLE `creature_proto` ADD COLUMN `maxpower` INT(30) UNSIGNED NOT NULL DEFAULT '0' AFTER `minpower`;
UPDATE `world_db_version` SET `LastUpdate`='2013-10-28_16-16_creature_power_type' WHERE  `LastUpdate`='2012-08-14_21-25_worldmap_info';