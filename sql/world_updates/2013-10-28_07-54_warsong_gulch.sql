DELETE FROM `worldstate_templates` WHERE `map`='489' AND `zone`='3277' AND `field`='4247';
DELETE FROM `worldstate_templates` WHERE `map`='489' AND `zone`='3277' AND `field`='4248';
INSERT INTO `worldstate_templates` (`map`, `zone`, `field`, `value`) VALUES 
('489', '3277', '4247', '1'),
('489', '3277', '4248', '25'); 
UPDATE `world_db_version` SET `LastUpdate`='2013-10-28_07_54_warsong_gulch' WHERE `LastUpdate` = '2013-10-28_16_16_creature_power_type';