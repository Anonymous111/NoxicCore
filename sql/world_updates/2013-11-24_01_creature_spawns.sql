ALTER TABLE `creature_spawns`
	COMMENT='Creature Spawn System',
	CHANGE COLUMN `id` `id` INT(11) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'Global Unique Identifier' FIRST,
	CHANGE COLUMN `entry` `entry` MEDIUMINT(10) UNSIGNED NOT NULL COMMENT 'Creature Identifier' AFTER `id`,
	CHANGE COLUMN `map` `map` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Map Identifier' AFTER `entry`,
	CHANGE COLUMN `position_x` `position_x` FLOAT(8,2) NOT NULL DEFAULT '0' AFTER `map`,
	CHANGE COLUMN `position_y` `position_y` FLOAT(8,2) NOT NULL DEFAULT '0' AFTER `position_x`,
	CHANGE COLUMN `position_z` `position_z` FLOAT(8,2) NOT NULL DEFAULT '0' AFTER `position_y`,
	CHANGE COLUMN `orientation` `orientation` FLOAT(5,2) NOT NULL DEFAULT '0' AFTER `position_z`;
UPDATE `world_db_version` SET `LastUpdate` = '2013-11-24_01_creature_spawns' WHERE `LastUpdate` = '2012-08-14_21-25_worldmap_info';