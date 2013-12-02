/* Added full loot for `Dark Runed Chest` - Shadow */
DELETE FROM `loot_gameobjects` WHERE `entryid`=190663;
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal25percentchance`,`mincount`,`maxcount`) VALUES (190663,43102,66.3488,1,1); -- Frozen Orb
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal25percentchance`,`mincount`,`maxcount`) VALUES (190663,37689,18.448,1,1); -- Pendant of the Nathrezim
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal25percentchance`,`mincount`,`maxcount`) VALUES (190663,37692,18.3591,1,1); -- Pierce's Pistol
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal25percentchance`,`mincount`,`maxcount`) VALUES (190663,37691,18.0961,1,1); -- Mantle of Deceit
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal25percentchance`,`mincount`,`maxcount`) VALUES (190663,37690,18.0943,1,1); -- Pauldrons of Destiny
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal25percentchance`,`mincount`,`maxcount`) VALUES (190663,37693,14.841,1,1); -- Greed
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal10percentchance`,`normal25percentchance`,`mincount`,`maxcount`) VALUES (190663,43228,24.3147,12.2625,3,4); -- Stone Keeper's Shard
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal25percentchance`,`mincount`,`maxcount`) VALUES (190663,43085,14.4554,1,1); -- Royal Crest of Lordaeron
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal25percentchance`,`mincount`,`maxcount`) VALUES (190663,37694,14.329,1,1); -- Band of Guile
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal25percentchance`,`mincount`,`maxcount`) VALUES (190663,37695,14.1484,1,1); -- Legguards of Nature's Power
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal25percentchance`,`mincount`,`maxcount`) VALUES (190663,37696,13.6159,1,1); -- Plague-Infected Bracers
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal25percentchance`,`mincount`,`maxcount`) VALUES (190663,33470,4.8762,2,7); -- Frostweave Cloth
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal25percentchance`,`mincount`,`maxcount`) VALUES (190663,43852,2.5073,1,1); -- Thick Fur Clothing Scraps
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal10percentchance`,`mincount`,`maxcount`) VALUES (190663,37114,23.6104,1,1); -- Gloves of Northern Lordaeron
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal10percentchance`,`mincount`,`maxcount`) VALUES (190663,37107,21.2049,1,1); -- Leeka's Shield
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal10percentchance`,`mincount`,`maxcount`) VALUES (190663,37110,21.1182,1,1); -- Gauntlets of Dark Conversion
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal10percentchance`,`mincount`,`maxcount`) VALUES (190663,37108,19.883,1,1); -- Dreadlord's Blade
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal10percentchance`,`mincount`,`maxcount`) VALUES (190663,37113,19.6121,1,1); -- Demonic Fabric Bands
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal10percentchance`,`mincount`,`maxcount`) VALUES (190663,37112,19.3629,1,1); -- Beguiling Scepter
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal10percentchance`,`mincount`,`maxcount`) VALUES (190663,37109,19.092,1,1); -- Discarded Silver Hand Spaulders
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal10percentchance`,`mincount`,`maxcount`) VALUES (190663,37111,17.2716,1,1); -- Soul Preserver
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal25percentchance`,`mincount`,`maxcount`) VALUES (190663,35947,1.1718,1,1); -- Sparkling Frostcap
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal25percentchance`,`mincount`,`maxcount`) VALUES (190663,33445,0.5934,1,1); -- Honeymint Tea
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal25percentchance`,`mincount`,`maxcount`) VALUES (190663,33447,0.3847,1,1); -- Runic Healing Potion
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal10percentchance`,`mincount`,`maxcount`) VALUES (190663,36062,0.726,1,1); -- Coldwraith Handwraps
INSERT INTO `loot_gameobjects` (`entryid`,`itemid`,`normal10percentchance`,`mincount`,`maxcount`) VALUES (190663,36325,0.2492,1,1); -- Halgrind Carapace

DELETE FROM `db_version` WHERE  `db_name`='ArcPro 4.3.4';
DELETE FROM `db_version` WHERE  `db_name`='ArcPro 3.3.5a';
DELETE FROM `db_version` WHERE  `db_name`='ArcPro';
INSERT INTO `db_version` (`db_name`, `revision`, `changeset`, `game_version`, `last_included_arcemu_update`, `last_db_update_by`) VALUES 
('ArcPro 3.3.5a', 1, 1, '3.3.5a', '2013-12-01_01_loot_gameobject', 'zdroid9770');
UPDATE `world_db_version` SET `LastUpdate`='2013-12-01_01_loot_gameobject' WHERE `LastUpdate` = '2013-11-28_01_isle_of_conquest';