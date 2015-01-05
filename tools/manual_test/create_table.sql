CREATE TABLE `image_master_table` (
  `image_id` int(11) NOT NULL auto_increment,
  `path` varchar(255) NOT NULL,
  `latitude` double NOT NULL,
  `longitude` double NOT NULL,
  `height` double NOT NULL,
  `row` double NOT NULL,
  `pitch` double NOT NULL,
  `yaw` double NOT NULL,
  `image_size_height` int(11) NOT NULL,
  `image_size_width` int(11) NOT NULL,
  `created_date` timestamp NULL DEFAULT NULL,
  `converted` tinyint(1) DEFAULT '0',
  PRIMARY KEY (`image_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `image_processed_tables` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `path` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `x` int(11) DEFAULT NULL,
  `y` int(11) DEFAULT NULL,
  `z` int(11) DEFAULT NULL,
  `create_date` datetime DEFAULT NULL,
  `taken_date` datetime DEFAULT NULL,
  `theta` int(11) DEFAULT NULL,
  `height` int(11) DEFAULT NULL,
  `width` int(11) DEFAULT NULL,
  `source_image_ids` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `position_index` (`x`,`y`,`z`,`theta`,`height`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
