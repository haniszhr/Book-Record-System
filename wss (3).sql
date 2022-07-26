-- phpMyAdmin SQL Dump
-- version 5.0.3
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 21, 2021 at 08:10 AM
-- Server version: 10.4.14-MariaDB
-- PHP Version: 7.4.11

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `wss`
--

-- --------------------------------------------------------

--
-- Table structure for table `admin`
--

CREATE TABLE `admin` (
  `AdminID` int(6) NOT NULL,
  `AdminName` varchar(255) DEFAULT NULL,
  `AdminEmail` varchar(250) NOT NULL,
  `AdminPassword` varchar(60) NOT NULL,
  `AdminPhone` varchar(20) DEFAULT NULL,
  `BorrowID` int(6) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `admin`
--

INSERT INTO `admin` (`AdminID`, `AdminName`, `AdminEmail`, `AdminPassword`, `AdminPhone`, `BorrowID`) VALUES
(1, 'Hanis Zahira', 'admin@gmail.com', 'admin', '01155013353', 1);

-- --------------------------------------------------------

--
-- Table structure for table `book`
--

CREATE TABLE `book` (
  `BookID` int(6) NOT NULL,
  `Title` varchar(255) DEFAULT NULL,
  `AdminID` int(6) NOT NULL,
  `Genre` varchar(300) DEFAULT NULL,
  `AuthorName` varchar(250) DEFAULT NULL,
  `Availability` varchar(250) DEFAULT 'Yes'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `book`
--

INSERT INTO `book` (`BookID`, `Title`, `AdminID`, `Genre`, `AuthorName`, `Availability`) VALUES
(1, 'Axel', 1, 'Romance', 'Bella Swan', 'Yes'),
(2, 'Twilight', 1, 'Romance Fantasy', 'Stephanie Knight', 'Yes'),
(3, 'All about Java', 1, 'Reference', 'Rubiah Samad', 'Yes'),
(4, 'Time to Bake', 1, 'Cooking', 'Roseanne Park', 'Yes'),
(5, 'Empire of Uthmaniyyah', 1, 'History', 'Norman Itzkowiz', 'Yes'),
(6, 'IT', 1, 'Horror', 'Stephen King', 'Yes'),
(7, 'Pet Sematary', 1, 'Horror Sci Fi', 'Stephen King', 'Yes'),
(8, 'Knowing about C++', 1, 'Reference', 'Kumaran Sekar', 'Yes'),
(9, 'The Sentinel', 1, 'Thriller', 'Lee Child', 'Yes'),
(10, 'In the woods', 1, 'Mystery', 'Tana French', 'Yes'),
(11, 'The Woman in White', 1, 'Mystery', 'Wilkie Collie', 'Yes'),
(12, 'Five Feet Apart', 1, 'Romance Fiction', 'Melanie Stephanie', 'Yes');

-- --------------------------------------------------------

--
-- Table structure for table `borrow`
--

CREATE TABLE `borrow` (
  `TransactionID` int(6) NOT NULL,
  `BookID` int(6) NOT NULL,
  `BorrowID` int(6) NOT NULL,
  `Borrow_Date` date NOT NULL,
  `Return_Date` date NOT NULL,
  `StatusReturn` varchar(250) DEFAULT 'Not Return',
  `StatusPayment` varchar(250) DEFAULT 'No fine',
  `ReturnBookDate` date NOT NULL,
  `Duration` varchar(25) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `borrow`
--

INSERT INTO `borrow` (`TransactionID`, `BookID`, `BorrowID`, `Borrow_Date`, `Return_Date`, `StatusReturn`, `StatusPayment`, `ReturnBookDate`, `Duration`) VALUES
(1, 1, 1, '2021-01-21', '2021-01-26', 'Return', 'No charge', '2021-01-25', NULL),
(2, 1, 2, '2021-01-21', '2021-01-26', 'Return', 'Paid', '2021-01-27', '1');

-- --------------------------------------------------------

--
-- Table structure for table `borrower`
--

CREATE TABLE `borrower` (
  `BorrowID` int(6) NOT NULL,
  `BorrowName` varchar(250) DEFAULT NULL,
  `BorrowEmail` varchar(250) NOT NULL,
  `BorrowPassword` varchar(60) NOT NULL,
  `BorrowPhone` varchar(60) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `borrower`
--

INSERT INTO `borrower` (`BorrowID`, `BorrowName`, `BorrowEmail`, `BorrowPassword`, `BorrowPhone`) VALUES
(1, 'Puteri Zulaikha Ismadi', 'put@gmail.com', 'put', '016366331661'),
(2, 'Syahmi Taib', 'syahmi@gmail.com', 'syahmi', '014424224242'),
(3, 'Nik Hasnida', 'Nik@gmail.com', 'niki7767', '0187673632');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`AdminID`),
  ADD KEY `Admin_Borrower_FK` (`BorrowID`);

--
-- Indexes for table `book`
--
ALTER TABLE `book`
  ADD PRIMARY KEY (`BookID`),
  ADD KEY `Book_Admin_FK` (`AdminID`);

--
-- Indexes for table `borrow`
--
ALTER TABLE `borrow`
  ADD PRIMARY KEY (`TransactionID`,`BorrowID`,`BookID`),
  ADD KEY `Borrow_Book_FK` (`BookID`),
  ADD KEY `Borrow_Borrower_FK` (`BorrowID`);

--
-- Indexes for table `borrower`
--
ALTER TABLE `borrower`
  ADD PRIMARY KEY (`BorrowID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `admin`
--
ALTER TABLE `admin`
  MODIFY `AdminID` int(6) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `book`
--
ALTER TABLE `book`
  MODIFY `BookID` int(6) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=13;

--
-- AUTO_INCREMENT for table `borrow`
--
ALTER TABLE `borrow`
  MODIFY `TransactionID` int(6) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `borrower`
--
ALTER TABLE `borrower`
  MODIFY `BorrowID` int(6) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `admin`
--
ALTER TABLE `admin`
  ADD CONSTRAINT `Admin_Borrower_FK` FOREIGN KEY (`BorrowID`) REFERENCES `borrower` (`BorrowID`);

--
-- Constraints for table `book`
--
ALTER TABLE `book`
  ADD CONSTRAINT `Book_Admin_FK` FOREIGN KEY (`AdminID`) REFERENCES `admin` (`AdminID`);

--
-- Constraints for table `borrow`
--
ALTER TABLE `borrow`
  ADD CONSTRAINT `Borrow_Book_FK` FOREIGN KEY (`BookID`) REFERENCES `book` (`BookID`),
  ADD CONSTRAINT `Borrow_Borrower_FK` FOREIGN KEY (`BorrowID`) REFERENCES `borrower` (`BorrowID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
