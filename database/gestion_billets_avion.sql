-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Hôte : 127.0.0.1
-- Généré le : mer. 07 oct. 2026 à 20:05
-- Version du serveur : 10.4.32-MariaDB
-- Version de PHP : 8.0.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données : `gestion_billets_avion`
--

CREATE DATABASE `gestion_billets_avion`;
USE `gestion_billets_avion`;

-- --------------------------------------------------------

--
-- Structure de la table `avion`
--

CREATE TABLE `avion` (
  `immatriculation` varchar(20) NOT NULL,
  `modele` varchar(50) NOT NULL,
  `nombre_places` int(11) NOT NULL,
  `compagnie_id` varchar(3) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Déchargement des données de la table `avion`
--

INSERT INTO `avion` (`immatriculation`, `modele`, `nombre_places`, `compagnie_id`) VALUES
('2-REJA', 'ATR 72‑600 ', 72, 'ML'),
('5R-EJB', 'ATR 72-600', 80, 'TD'),
('5R-EJC', 'ATR 72-500', 72, 'ML'),
('5R-MJF', 'ATR 72-500', 68, 'ML'),
('5R‑EJA', 'ATR 72‑600', 72, 'TD'),
('5R‑EJC', 'ATR 72‑500', 72, 'TD'),
('5R‑EJD', 'ATR 72‑500', 72, 'TD'),
('5R‑EJF', 'ATR 72‑500', 68, 'TD'),
('5R‑MJC', 'ATR 72‑500', 72, 'ML'),
('5R‑MJD ', 'ATR 72-500', 72, 'ML'),
('5R‑MJE', 'ATR 72‑600 ', 68, 'ML'),
('A6-EBB', 'Boeing 777-300ER', 354, 'EK'),
('A6‑EEC', 'Airbus A380‑800', 517, 'EK'),
('A6‑EHP', 'Boeing 777‑300ER', 427, 'EK'),
('A6‑EXG', 'Airbus A350‑941', 327, 'EK'),
('A6‑EXH', 'Airbus A350‑941', 327, 'EK'),
('A6‑EXI', 'Airbus A350‑941', 327, 'EK'),
('A7‑ADQ', 'Airbus A321neo', 197, 'QR'),
('A7‑AEE', 'Airbus A350‑900', 283, 'QR'),
('A7‑AFC', 'Airbus A380‑800', 517, 'QR'),
('A7‑BAA', 'Boeing 777‑300ER', 360, 'QR'),
('A7‑BEBN', 'Boeing 787-9', 312, 'QR'),
('ET-ANN', 'Boeing 777-200LR', 321, 'ET'),
('ET‑ABP', 'Bombardier Q400 ', 78, 'ET'),
('ET‑ANB', '	Airbus A350‑900', 319, 'ET'),
('ET‑AOO', 'Boeing 737‑800', 156, 'ET'),
('ET‑AOV', 'Boeing 787‑9', 315, 'ET'),
('ET‑ARB', 'Boeing 777‑300ER', 365, 'ET'),
('F-HPJE', 'Airbus A380-800', 516, 'AF'),
('F‑GKXQ', 'Airbus A320‑214', 174, 'AF'),
('F‑GKXR', 'Airbus A320‑214', 174, 'AF'),
('F‑GKXS', 'Airbus A320‑214', 174, 'AF'),
('F‑GKXT', 'Airbus A320‑214', 174, 'AF'),
('F‑HTYJ', 'Airbus A350‑900', 324, 'AF'),
('HL7754 ', 'Airbus A330‑300', 280, 'KE'),
('HL8001 ', 'Boeing 747‑8I ', 314, 'KE'),
('HL8065', 'Boeing 787‑9', 300, 'KE'),
('HL8082 ', 'Boeing 737‑900', 180, 'KE'),
('HL8251 ', 'Airbus A220‑300', 140, 'KE'),
('HL8348', 'Boeing 737-8', 273, 'KE'),
('M275AY', 'Airbus A330-300', 280, 'AA'),
('N227NN', 'Boeing 737-823', 160, 'AA'),
('N303AN', 'Boeing 787-8', 234, 'AA'),
('N818NN', 'Boeing 737-823', 160, 'AA'),
('N912AN', 'Airbus A321-231', 190, 'AA'),
('N923AN', 'Airbus A321neo', 195, 'AA'),
('Q-GKXA', 'Airbus A350-1000', 327, 'QR');

-- --------------------------------------------------------

--
-- Structure de la table `compagnie_aerienne`
--

CREATE TABLE `compagnie_aerienne` (
  `identifiant` varchar(3) NOT NULL,
  `nom` varchar(100) NOT NULL,
  `pays` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Déchargement des données de la table `compagnie_aerienne`
--

INSERT INTO `compagnie_aerienne` (`identifiant`, `nom`, `pays`) VALUES
('AA', 'American Airlens', 'États-Unis'),
('AF', 'Air France', 'France'),
('EK', 'Emirates', 'Émirats Arabes Unis'),
('ET', 'Éthiopian Airlens', 'Éthiopie'),
('JML', 'lsmjdq', 'LKSDJSQM'),
('KE', 'Korean Air', 'Corée du Sud'),
('ML', 'Madagascar Airlines', 'Madagascar'),
('QR', 'Qatar Airways', 'Qatar'),
('TD', 'Tsaradia', 'Madagascar');

-- --------------------------------------------------------

--
-- Structure de la table `compte`
--

CREATE TABLE `compte` (
  `nom` varchar(20) NOT NULL,
  `prenoms` varchar(20) NOT NULL,
  `nom_utilisateur` varchar(20) NOT NULL,
  `date_naissance` date NOT NULL,
  `numero_cin` varchar(12) NOT NULL,
  `mdp` varchar(12) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Déchargement des données de la table `compte`
--

INSERT INTO `compte` (`nom`, `prenoms`, `nom_utilisateur`, `date_naissance`, `numero_cin`, `mdp`) VALUES
('ADMINISTRATEUR', 'Principal', 'Admin', '2000-01-01', '145147556654', 'motdepasse');

-- --------------------------------------------------------

--
-- Structure de la table `historique`
--

CREATE TABLE `historique` (
  `numero` int(11) NOT NULL,
  `nom_utilisateur` varchar(20) NOT NULL,
  `date` datetime DEFAULT current_timestamp(),
  `operation` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Structure de la table `passager`
--

CREATE TABLE `passager` (
  `identifiant` varchar(10) NOT NULL,
  `nom` varchar(50) NOT NULL,
  `prenoms` varchar(100) NOT NULL,
  `date_naissance` date NOT NULL,
  `numero_passeport` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Déchargement des données de la table `passager`
--

INSERT INTO `passager` (`identifiant`, `nom`, `prenoms`, `date_naissance`, `numero_passeport`) VALUES
('PASS0001', 'AKIM', 'Abdalah', '2007-10-10', 'PA013471'),
('PASS0002', 'MARIE', 'Françoise', '2007-09-15', 'PB791457'),
('PASS0003', 'JEAN', 'Paul', '2005-03-01', 'PB631478'),
('PASS0004', 'RAKOTOARINIRINA', 'Fanomezantsoa Joshy', '2007-01-01', 'PA245678'),
('PASS0005', 'MARIE', 'Louise', '1998-12-01', 'FA5698652'),
('PASS0006', 'JASON', 'Smith', '2000-05-10', '847561478'),
('PASS0007', 'KIM', 'Chan', '1981-11-01', 'G25478965'),
('PASS0008', 'MOHAMED', 'Ali', '1985-04-05', 'D8965890'),
('PASS0009', 'ALVIN', 'Smith', '2000-01-12', '54789524');

--
-- Déclencheurs `passager`
--
DELIMITER $$
CREATE TRIGGER `before_passager_insert1` BEFORE INSERT ON `passager` FOR EACH ROW BEGIN
    DECLARE next_num INT;
    SELECT IFNULL(MAX(CAST(SUBSTRING(identifiant, 5) AS UNSIGNED)), 0) + 1
    INTO next_num FROM passager;  -- CORRIGÉ
    SET NEW.identifiant = CONCAT('PASS', LPAD(next_num, 4, '0'));
END
$$
DELIMITER ;

-- --------------------------------------------------------

--
-- Structure de la table `reservation`
--

CREATE TABLE `reservation` (
  `numero_reservation` varchar(20) NOT NULL,
  `passager_id` varchar(10) DEFAULT NULL,
  `numero_vol` varchar(10) DEFAULT NULL,
  `classe` enum('Première','Économique','Business') NOT NULL,
  `date_reservation` datetime DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Déchargement des données de la table `reservation`
--

INSERT INTO `reservation` (`numero_reservation`, `passager_id`, `numero_vol`, `classe`, `date_reservation`) VALUES
('RES25001', 'PASS0002', 'VOL002', 'Première', '2025-09-05 08:45:05'),
('RES25002', 'PASS0005', 'VOL005', 'Économique', '2025-09-17 09:53:13'),
('RES25003', 'PASS0004', 'VOL008', 'Première', '2025-09-17 15:15:11'),
('RES25004', 'PASS0001', 'VOL001', 'Première', '2025-09-29 10:05:12'),
('RES25005', 'PASS0007', 'VOL003', 'Business', '2025-10-01 14:32:04'),
('RES25006', 'PASS0006', 'VOL007', 'Économique', '2025-10-05 07:58:01'),
('RES25007', 'PASS0008', 'VOL006', 'Business', '2025-10-16 11:07:56'),
('RES25008', 'PASS0003', 'VOL004', 'Première', '2025-10-20 15:49:55'),
('RES25009', 'PASS0009', 'VOL010', 'Première', '2025-11-03 22:38:06');

--
-- Déclencheurs `reservation`
--
DELIMITER $$
CREATE TRIGGER `before_reservation_insert1` BEFORE INSERT ON `reservation` FOR EACH ROW BEGIN
    DECLARE next_num INT;
    DECLARE current_year VARCHAR(2);
    SET current_year = DATE_FORMAT(NOW(), '%y');
    
    SELECT IFNULL(MAX(CAST(SUBSTRING(numero_reservation, 8) AS UNSIGNED)), 0) + 1
    INTO next_num 
    FROM reservation  -- CORRIGÉ
    WHERE numero_reservation LIKE CONCAT('RES', current_year, '%');
    
    SET NEW.numero_reservation = CONCAT('RES', current_year, LPAD(next_num, 3, '0'));
END
$$
DELIMITER ;

-- --------------------------------------------------------

--
-- Structure de la table `vol`
--

CREATE TABLE `vol` (
  `numero_vol` varchar(10) NOT NULL,
  `aeroport_depart` varchar(100) NOT NULL,
  `aeroport_arrive` varchar(100) NOT NULL,
  `date_depart` date NOT NULL,
  `heure_depart` time NOT NULL,
  `duree` time NOT NULL,
  `avion_id` varchar(20) DEFAULT NULL,
  `compagnie_id` varchar(3) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Déchargement des données de la table `vol`
--

INSERT INTO `vol` (`numero_vol`, `aeroport_depart`, `aeroport_arrive`, `date_depart`, `heure_depart`, `duree`, `avion_id`, `compagnie_id`) VALUES
('VOL001', 'Ivato', 'Mahajanga', '2025-11-06', '06:45:00', '02:45:00', '5R-EJB', 'TD'),
('VOL002', 'Ivato', 'Antsiranana', '2025-11-06', '20:00:00', '04:15:00', '5R-EJC', 'ML'),
('VOL003', 'Ivato', 'Éthiopie', '2025-11-08', '10:30:00', '06:30:00', 'ET-ANN', 'ET'),
('VOL004', 'Ivato', 'Qatar', '2025-11-09', '15:00:00', '24:05:00', 'Q-GKXA', 'QR'),
('VOL005', 'Ivato', 'Paris', '2025-11-11', '09:15:00', '12:00:00', 'F-HPJE', 'AF'),
('VOL006', 'Ivato', 'Dubai', '2025-11-15', '10:00:00', '28:15:00', 'A6-EBB', 'EK'),
('VOL007', 'Ivato', 'Los Angeles', '2025-11-15', '21:30:00', '32:45:00', 'M275AY', 'AA'),
('VOL008', 'Ivato', 'Corée du Sud', '2025-11-29', '18:15:00', '24:35:00', 'HL8348', 'KE'),
('VOL010', 'Ivato', 'Brésil', '2025-11-15', '09:15:00', '32:00:00', 'N818NN', 'AA');

--
-- Déclencheurs `vol`
--
DELIMITER $$
CREATE TRIGGER `before_vol_insert1` BEFORE INSERT ON `vol` FOR EACH ROW BEGIN
    DECLARE aeroport VARCHAR(5);
    SET aeroport = 'Ivato';
    SET NEW.aeroport_depart = aeroport;
END
$$
DELIMITER ;

--
-- Index pour les tables déchargées
--

--
-- Index pour la table `avion`
--
ALTER TABLE `avion`
  ADD PRIMARY KEY (`immatriculation`),
  ADD KEY `avion_ibfk_1` (`compagnie_id`);

--
-- Index pour la table `compagnie_aerienne`
--
ALTER TABLE `compagnie_aerienne`
  ADD PRIMARY KEY (`identifiant`);

--
-- Index pour la table `compte`
--
ALTER TABLE `compte`
  ADD PRIMARY KEY (`nom_utilisateur`);

--
-- Index pour la table `historique`
--
ALTER TABLE `historique`
  ADD PRIMARY KEY (`numero`),
  ADD KEY `historique_ibfk_1` (`nom_utilisateur`);

--
-- Index pour la table `passager`
--
ALTER TABLE `passager`
  ADD PRIMARY KEY (`identifiant`),
  ADD UNIQUE KEY `numero_passeport` (`numero_passeport`),
  ADD KEY `idx_passager_nom1` (`nom`,`prenoms`);

--
-- Index pour la table `reservation`
--
ALTER TABLE `reservation`
  ADD PRIMARY KEY (`numero_reservation`),
  ADD KEY `idx_reservation_passager` (`passager_id`),
  ADD KEY `idx_reservation_vol` (`numero_vol`),
  ADD KEY `idx_reservation_dates1` (`date_reservation`);

--
-- Index pour la table `vol`
--
ALTER TABLE `vol`
  ADD PRIMARY KEY (`numero_vol`),
  ADD KEY `avion_id` (`avion_id`),
  ADD KEY `compagnie_id` (`compagnie_id`),
  ADD KEY `idx_vol_dates1` (`date_depart`,`heure_depart`),
  ADD KEY `idx_vol_aeroports1` (`aeroport_depart`,`aeroport_arrive`);

--
-- AUTO_INCREMENT pour les tables déchargées
--

--
-- AUTO_INCREMENT pour la table `historique`
--
ALTER TABLE `historique`
  MODIFY `numero` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- Contraintes pour les tables déchargées
--

--
-- Contraintes pour la table `avion`
--
ALTER TABLE `avion`
  ADD CONSTRAINT `avion_ibfk_1` FOREIGN KEY (`compagnie_id`) REFERENCES `compagnie_aerienne` (`identifiant`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Contraintes pour la table `historique`
--
ALTER TABLE `historique`
  ADD CONSTRAINT `historique_ibfk_1` FOREIGN KEY (`nom_utilisateur`) REFERENCES `compte` (`nom_utilisateur`);

--
-- Contraintes pour la table `reservation`
--
ALTER TABLE `reservation`
  ADD CONSTRAINT `reservation_ibfk_1` FOREIGN KEY (`passager_id`) REFERENCES `passager` (`identifiant`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `reservation_ibfk_2` FOREIGN KEY (`numero_vol`) REFERENCES `vol` (`numero_vol`) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- Contraintes pour la table `vol`
--
ALTER TABLE `vol`
  ADD CONSTRAINT `vol_ibfk_1` FOREIGN KEY (`avion_id`) REFERENCES `avion` (`immatriculation`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `vol_ibfk_2` FOREIGN KEY (`compagnie_id`) REFERENCES `compagnie_aerienne` (`identifiant`) ON DELETE SET NULL ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
