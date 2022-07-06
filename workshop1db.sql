-- phpMyAdmin SQL Dump
-- version 4.9.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 20, 2021 at 09:32 AM
-- Server version: 10.4.8-MariaDB
-- PHP Version: 7.3.11

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `workshop1db`
--
CREATE DATABASE IF NOT EXISTS `workshop1db` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
USE `workshop1db`;

-- --------------------------------------------------------

--
-- Table structure for table `feedback`
--

CREATE TABLE `feedback` (
  `feedback_id` int(11) NOT NULL,
  `user_id` int(11) DEFAULT NULL,
  `feedback_rating` int(11) NOT NULL,
  `feedback_desc` varchar(255) NOT NULL,
  `feedback_improve` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `feedback`
--

INSERT INTO `feedback` (`feedback_id`, `user_id`, `feedback_rating`, `feedback_desc`, `feedback_improve`) VALUES
(28, 2, 5, 'UI lari kalau data besar', 'fix this ASAP'),
(29, 2, 3, 'pre-test(14/1/2021) good enough so far', 'UI expand');

-- --------------------------------------------------------

--
-- Table structure for table `inventory`
--

CREATE TABLE `inventory` (
  `inv_id` int(11) NOT NULL,
  `user_id` int(11) DEFAULT NULL,
  `inv_name` varchar(255) DEFAULT NULL,
  `inv_adddate` date NOT NULL,
  `inv_quantity` int(11) NOT NULL,
  `inv_costPrice` double NOT NULL,
  `inv_sellPrice` double NOT NULL,
  `inv_expdate` date DEFAULT NULL,
  `inv_shelflife` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `inventory`
--

INSERT INTO `inventory` (`inv_id`, `user_id`, `inv_name`, `inv_adddate`, `inv_quantity`, `inv_costPrice`, `inv_sellPrice`, `inv_expdate`, `inv_shelflife`) VALUES
(1, 1, 'Adult 3-piece mask blue', '2020-10-31', 100, 15, 18, '2021-10-31', '365'),
(2, 1, 'Shieldtox Mosquito Spray', '2020-10-31', 100, 6, 10, '2021-10-31', '365'),
(3, 1, 'Kimball chilli sauce', '2020-10-31', 100, 1.5, 3, '2020-12-02', '32'),
(4, 1, 'Summer mineral water 2L', '2020-10-31', 100, 1, 2, '2020-12-03', '33'),
(5, 1, 'Imdex hand sanitizer', '2020-10-31', 100, 8, 10, '2020-12-04', '34'),
(38, 2, 'test', '2020-10-10', 2, 3, 3, '2021-10-10', '365');

-- --------------------------------------------------------

--
-- Table structure for table `revenue`
--

CREATE TABLE `revenue` (
  `revenue_id` int(11) NOT NULL,
  `user_id` int(11) DEFAULT NULL,
  `inv_id` int(11) DEFAULT NULL,
  `revenue_amount` double NOT NULL,
  `agg_revenue_amount` double NOT NULL,
  `revenue_state` varchar(255) NOT NULL,
  `revenue_percentage` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `revenue`
--

INSERT INTO `revenue` (`revenue_id`, `user_id`, `inv_id`, `revenue_amount`, `agg_revenue_amount`, `revenue_state`, `revenue_percentage`) VALUES
(777, 1, 1, 3, 300, 'PROFIT', 20),
(778, 1, 2, 4, 400, 'PROFIT', 66.6667),
(779, 1, 3, 1.5, 150, 'PROFIT', 100),
(780, 1, 4, 1, 100, 'PROFIT', 100),
(781, 1, 5, 2, 200, 'PROFIT', 25);

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE `user` (
  `user_id` int(11) NOT NULL,
  `user_name` varchar(255) NOT NULL,
  `user_email` varchar(255) DEFAULT NULL,
  `user_password` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`user_id`, `user_name`, `user_email`, `user_password`) VALUES
(1, 'ownergg', 'ownergg@gmail.com', 'ownergg'),
(2, 'test', 'test', 'test');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `feedback`
--
ALTER TABLE `feedback`
  ADD PRIMARY KEY (`feedback_id`),
  ADD KEY `feedbackFK1` (`user_id`);

--
-- Indexes for table `inventory`
--
ALTER TABLE `inventory`
  ADD PRIMARY KEY (`inv_id`),
  ADD UNIQUE KEY `inv_name` (`inv_name`),
  ADD KEY `inventoryFK1` (`user_id`);

--
-- Indexes for table `revenue`
--
ALTER TABLE `revenue`
  ADD PRIMARY KEY (`revenue_id`),
  ADD KEY `revenueFK1` (`user_id`),
  ADD KEY `revenueFK2` (`inv_id`);

--
-- Indexes for table `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`user_id`),
  ADD UNIQUE KEY `user_email` (`user_email`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `feedback`
--
ALTER TABLE `feedback`
  MODIFY `feedback_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=30;

--
-- AUTO_INCREMENT for table `inventory`
--
ALTER TABLE `inventory`
  MODIFY `inv_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=39;

--
-- AUTO_INCREMENT for table `revenue`
--
ALTER TABLE `revenue`
  MODIFY `revenue_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=782;

--
-- AUTO_INCREMENT for table `user`
--
ALTER TABLE `user`
  MODIFY `user_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `feedback`
--
ALTER TABLE `feedback`
  ADD CONSTRAINT `feedbackFK1` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`);

--
-- Constraints for table `inventory`
--
ALTER TABLE `inventory`
  ADD CONSTRAINT `inventoryFK1` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `revenue`
--
ALTER TABLE `revenue`
  ADD CONSTRAINT `revenueFK1` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `revenueFK2` FOREIGN KEY (`inv_id`) REFERENCES `inventory` (`inv_id`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
