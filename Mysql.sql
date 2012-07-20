-- MySQL dump 10.13  Distrib 5.5.9, for Win32 (x86)
--
-- Host: localhost    Database: Elixir
-- ------------------------------------------------------
-- Server version	5.5.15

/*!40101 SET @OLD_CHARACTER_SET_Client=@@CHARACTER_SET_Client */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Current Database: `Elixir`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `Elixir` /*!40100 DEFAULT CHARACTER SET utf8 */;

USE `Elixir`;

--
-- Table structure for table `Acompte`
--

DROP TABLE IF EXISTS `Acompte`;
/*!40101 SET @saved_cs_Client     = @@character_set_Client */;
/*!40101 SET character_set_Client = utf8 */;
CREATE TABLE `Acompte` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `client` int(11) DEFAULT '0',
  `valeur` float DEFAULT '0',
  `dateintro` date DEFAULT '0000-00-00',
  `tickintro` int(11) DEFAULT '0',
  `datededuit` date DEFAULT '0000-00-00',
  `tickdeduit` int(11) DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_Client = @saved_cs_Client */;

--
-- Table structure for table `Caisse`
--

DROP TABLE IF EXISTS `Caisse`;
/*!40101 SET @saved_cs_Client     = @@character_set_Client */;
/*!40101 SET character_set_Client = utf8 */;
CREATE TABLE `Caisse` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `date` date DEFAULT '0000-00-00',
  `montant` float DEFAULT '0',
  `nom` varchar(45) DEFAULT '',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_Client = @saved_cs_Client */;


--
-- Table structure for table `Client`
--

DROP TABLE IF EXISTS `Client`;
/*!40101 SET @saved_cs_Client     = @@character_set_Client */;
/*!40101 SET character_set_Client = utf8 */;
CREATE TABLE `Client` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nom` varchar(255) DEFAULT '',
  `prenom` varchar(255) DEFAULT '',
  `civilite` int(1) DEFAULT '0',
  `adresse` varchar(255) DEFAULT '',
  `codepostal` varchar(255) DEFAULT '',
  `localite` varchar(255) DEFAULT '',
  `tel` varchar(255) DEFAULT '',
  `remarques` varchar(255) DEFAULT '',
  `tva` varchar(255) DEFAULT '',
  `courriel` varchar(255) DEFAULT '',
  `pays` varchar(255) DEFAULT 'Belgique',
  `fax` varchar(255) DEFAULT '',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_Client = @saved_cs_Client */;


--
-- Table structure for table `Facture`
--

DROP TABLE IF EXISTS `Facture`;
/*!40101 SET @saved_cs_Client     = @@character_set_Client */;
/*!40101 SET character_set_Client = utf8 */;
CREATE TABLE `Facture` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nbdoc` varchar(45) DEFAULT NULL,
  `date` date DEFAULT '0000-00-00',
  `datedoc` date DEFAULT '0000-00-00',
  `fournisseur` int(11) DEFAULT '0',
  `dateech` varchar(45) DEFAULT '0000-00-00',
  `montanttva` float DEFAULT '0',
  `datepai` date DEFAULT '0000-00-00',
  `statut` int(1) DEFAULT NULL,
  `remarques` text,
  `refdoc` varchar(45) DEFAULT NULL,
  `montant` float DEFAULT NULL,
  `supprime` tinyint(1) DEFAULT '0',
  `communication` varchar(255) DEFAULT '',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_Client = @saved_cs_Client */;


--
-- Table structure for table `Fournisseur`
--

DROP TABLE IF EXISTS `Fournisseur`;
/*!40101 SET @saved_cs_Client     = @@character_set_Client */;
/*!40101 SET character_set_Client = utf8 */;
CREATE TABLE `Fournisseur` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nom` varchar(255) DEFAULT NULL,
  `tva` varchar(255) DEFAULT '',
  `adresse` varchar(255) DEFAULT '',
  `codepostal` varchar(15) DEFAULT '',
  `localite` varchar(255) DEFAULT '',
  `pays` varchar(45) DEFAULT '',
  `tel` varchar(255) DEFAULT '',
  `fax` varchar(15) DEFAULT '',
  `courriel` varchar(255) DEFAULT '',
  `iban` varchar(255) DEFAULT '',
  `bic` varchar(255) DEFAULT '',
  `banque` varchar(255) DEFAULT '',
  `remarques` varchar(255) DEFAULT '',
  `supprime` tinyint(1) DEFAULT '0',
  `coefficient` float DEFAULT '2.8',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_Client = @saved_cs_Client */;

--
-- Table structure for table `Inventaire`
--

DROP TABLE IF EXISTS `Inventaire`;
/*!40101 SET @saved_cs_Client     = @@character_set_Client */;
/*!40101 SET character_set_Client = utf8 */;
CREATE TABLE `Inventaire` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `fournisseur` int(11) DEFAULT '0',
  `facture` int(11) DEFAULT '0',
  `modele` varchar(45) DEFAULT '',
  `narticle` varchar(45) DEFAULT '',
  `taille` varchar(10) DEFAULT '',
  `pa` float DEFAULT '0',
  `pv` float DEFAULT '0',
  `coloris` varchar(45) DEFAULT '',
  `qt` int(11) DEFAULT '0',
  `qtv` int(11) DEFAULT '0',
  `imprime` tinyint(1) DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_Client = @saved_cs_Client */;


--
-- Table structure for table `Reprise`
--

DROP TABLE IF EXISTS `Reprise`;
/*!40101 SET @saved_cs_Client     = @@character_set_Client */;
/*!40101 SET character_set_Client = utf8 */;
CREATE TABLE `Reprise` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `code` int(11) DEFAULT '0',
  `ticket` int(11) DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_Client = @saved_cs_Client */;


--
-- Table structure for table `Solde`
--

DROP TABLE IF EXISTS `Solde`;
/*!40101 SET @saved_cs_Client     = @@character_set_Client */;
/*!40101 SET character_set_Client = utf8 */;
CREATE TABLE `Solde` (
  `id` int(11) NOT NULL,
  `valeur` float DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_Client = @saved_cs_Client */;

--
-- Dumping data for table `Solde`
--

LOCK TABLES `Solde` WRITE;
/*!40000 ALTER TABLE `Solde` DISABLE KEYS */;
INSERT INTO `Solde` VALUES (1,200);
/*!40000 ALTER TABLE `Solde` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Ticket`
--

DROP TABLE IF EXISTS `Ticket`;
/*!40101 SET @saved_cs_Client     = @@character_set_Client */;
/*!40101 SET character_set_Client = utf8 */;
CREATE TABLE `Ticket` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `prixc` decimal(12,2) DEFAULT '0.00',
  `prixb` decimal(12,2) DEFAULT '0.00',
  `Prixd` decimal(12,2) DEFAULT '0.00',
  `client` int(11) DEFAULT '0',
  `date` datetime DEFAULT '0000-00-00 00:00:00',
  `num` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_Client = @saved_cs_Client */;


--
-- Table structure for table `Vente`
--

DROP TABLE IF EXISTS `Vente`;
/*!40101 SET @saved_cs_Client     = @@character_set_Client */;
/*!40101 SET character_set_Client = utf8 */;
CREATE TABLE `Vente` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `inventaire` int(11) DEFAULT '0',
  `ticket` int(11) DEFAULT '0',
  `prix` float DEFAULT '0',
  `qt` int(11) DEFAULT '1',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_Client = @saved_cs_Client */;


--
-- Table structure for table `Ventenonreconnue`
--

DROP TABLE IF EXISTS `Ventenonreconnue`;
/*!40101 SET @saved_cs_Client     = @@character_set_Client */;
/*!40101 SET character_set_Client = utf8 */;
CREATE TABLE `Ventenonreconnue` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `modele` varchar(45) DEFAULT '',
  `narticle` varchar(45) DEFAULT '',
  `coloris` varchar(45) DEFAULT '',
  `taille` varchar(45) DEFAULT '',
  `prix` float DEFAULT '0',
  `qt` int(11) DEFAULT '1',
  `ticket` int(11) DEFAULT '0',
  `retrouve` tinyint(1) DEFAULT '1',
  `pv` float DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_Client = @saved_cs_Client */;

--
-- Dumping routines for database 'Elixir'
--
/*!50003 DROP PROCEDURE IF EXISTS `alter_Solde` */;
/*!50003 SET @saved_cs_Client      = @@character_set_Client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_Client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `alter_solde`(IN variation FLOAT)
BEGIN
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_Client  = @saved_cs_Client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `CalculSolde` */;
/*!50003 SET @saved_cs_Client      = @@character_set_Client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_Client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `calculsolde`(IN datelim DATE)
BEGIN
DECLARE somme FLOAT DEFAULT 0.0;
DECLARE terme FLOAT DEFAULT 0.0;
SELECT SUM(montant) INTO terme FROM Facture WHERE statut=2 AND supprime=FALSE AND datepai>='2012-01-01' AND datepai<=datelim;
IF ISNULL(terme)
THEN SELECT 0 INTO terme;
END IF;
SELECT somme-terme INTO somme;
SELECT SUM(prixc) INTO terme FROM Ticket WHERE DATE(date)>='2012-01-01'AND DATE(date)<=datelim;
IF ISNULL(terme)
THEN SELECT 0 INTO terme;
END IF;
SELECT somme+terme INTO somme;
SELECT SUM(montant) INTO terme FROM Caisse WHERE date>='2012-01-01'AND date<=datelim;
IF ISNULL(terme)
THEN SELECT 0 INTO terme;
END IF;
SELECT somme+terme INTO somme;
SELECT valeur INTO terme FROM Solde WHERE id=1;
IF ISNULL(terme)
THEN SELECT 0 INTO terme;
END IF;
SELECT terme+somme AS Solde;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_Client  = @saved_cs_Client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `TicNum` */;
/*!50003 SET @saved_cs_Client      = @@character_set_Client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_Client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `ticnum`(in datedem date)
BEGIN
DECLARE numtick INT;
SELECT Max(num) INTO numtick FROM Ticket WHERE Date(date)=datedem;
if isnull(numtick)
THEN SELECT 1 INTO numtick;
ELSE SELECT numtick+1 INTO numtick;
END IF;
SELECT numTick;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_Client  = @saved_cs_Client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `vendre` */;
/*!50003 SET @saved_cs_Client      = @@character_set_Client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_Client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `vendre`(IN iTicket INT,IN icode INT,IN Qti INT,IN iPrix FLOAT)
BEGIN
INSERT INTO Vente (inventaire,ticket,prix,qt) VALUES (icode,iTicket,iPrix/Qti,Qti);
SELECT qtv INTO iTicket FROM Inventaire WHERE id=icode;
UPDATE Inventaire SET Qtv=iTicket+Qti where id=idcode;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_Client  = @saved_cs_Client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_Client=@OLD_CHARACTER_SET_Client */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2012-07-19 17:08:55

GRANT ALL PRIVILEGES ON Elixir.* TO Elixir_user@localhost IDENTIFIED BY '';
INSERT INTO Client (Nom) VALUES ('Divers');
