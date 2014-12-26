DROP TABLE `image_master_table` IF EXISTS
CREATE TABLE `image_master_table` (
  `image_id` int(11) NOT NULL,
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
