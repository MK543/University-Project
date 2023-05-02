--1 Ksiazki po terminie i kary
CREATE VIEW PO_TERMINIE AS
(SELECT wyp.id_wypozyczenia AS "ID wypożyczenia", os.imie AS "Imie", os.nazwisko AS "Nazwisko", round((sysdate- TO_DATE(wyp.data_oddania, 'YY/MM/DD')),0) AS "Dni po terminie",  ksk.nazwa_ksiazki AS "Nazwa książki", wyp.kara AS "Kara"
FROM pr_wypozyczenie wyp
JOIN pr_osoba os ON wyp.id_osoby = os.id_osoby
JOIN pr_egzemplarz egz ON wyp.id_egzemplarza = egz.id_egzemplarza
JOIN pr_ksiazka ksk ON egz.nazwa_ksiazki = ksk.nazwa_ksiazki
WHERE kara IS NOT NULL

union 

SELECT null, null, null, null, 'Razem', sum(nvl(kara,0)) FROM pr_wypozyczenie);

--2 Wypozyczenia ksiazek
CREATE VIEW ILOSC_WYPOZYCZEN AS
(SELECT COUNT(wyp.id_egzemplarza) AS "Ilość wypożyczeń", ksk.nazwa_ksiazki AS "Nazwa książki"
FROM pr_wypozyczenie wyp
JOIN pr_osoba os ON wyp.id_osoby = os.id_osoby
JOIN pr_egzemplarz egz ON wyp.id_egzemplarza = egz.id_egzemplarza
JOIN pr_ksiazka ksk ON egz.nazwa_ksiazki = ksk.nazwa_ksiazki
GROUP BY ksk.nazwa_ksiazki);

--3 Szczegolowy podzial
CREATE VIEW WYPOZYCZENIA_PODZIAL AS
(SELECT nsk.nazwa_nosnika AS "Nazwa nośnika", COUNT(egz.id_nosnika) AS "Ilość wypożyczeń", ksk.nazwa_ksiazki AS "Nazwa książki"
FROM pr_egzemplarz egz
JOIN pr_ksiazka ksk ON egz.nazwa_ksiazki = ksk.nazwa_ksiazki
JOIN pr_nosnik nsk ON egz.id_nosnika = nsk.id_nosnika
WHERE egz.status = 'BORROWED'
GROUP BY nsk.nazwa_nosnika, ksk.nazwa_ksiazki);


--4 Jakie ksiazki mozna polecic czesci klientom
CREATE VIEW POLECANIE_KSIAZEK AS 
(SELECT os.imie AS "Imie klienta", os.nazwisko AS "Nazwisko klienta", gat.nazwa_gatunku AS "Ulubione gatunki", aut.nazwisko AS "Ulubieni autorzy"
FROM pr_osoba os
JOIN pr_preferencje prf ON os.id_osoby = prf.id_osoby
LEFT OUTER JOIN pr_autor aut ON prf.id_autora = aut.id_autora
LEFT OUTER JOIN pr_gatunek gat ON prf.id_gatunku = gat.id_gatunku);

--5 Osoby ktore maja wiecej niz jedna kare za nieoddanie ksiazki
SELECT id_osoby, COUNT(kara)
FROM pr_wypozyczenie
GROUP BY id_osoby
HAVING COUNT(kara) > 1

--6 Rozpiska ile bylo wypozyczen na rok i na miesiac
SELECT EXTRACT(YEAR FROM data_wypozyczenia) AS "Rok", EXTRACT(MONTH FROM data_wypozyczenia) AS "Miesiąc", COUNT(id_wypozyczenia) AS "Ilość wypożyczeń"
FROM PR_WYPOZYCZENIE
GROUP BY EXTRACT(YEAR FROM data_wypozyczenia), EXTRACT(MONTH FROM data_wypozyczenia);

SELECT EXTRACT(YEAR FROM data_wypozyczenia) AS "Rok", to_char(to_date(data_wypozyczenia, 'YY/MM/DD'), 'Month') AS "Miesiąc", COUNT(id_wypozyczenia) AS "Ilość wypożyczeń"
FROM PR_WYPOZYCZENIE
GROUP BY EXTRACT(YEAR FROM data_wypozyczenia), to_char(to_date(data_wypozyczenia, 'YY/MM/DD'), 'Month');

--7 Rozpiska zyskow na miesiace i na lata
SELECT EXTRACT(YEAR FROM data_wypozyczenia) AS "Rok", EXTRACT(MONTH FROM data_wypozyczenia) AS "Miesiąc", SUM(koszt_wypozyczenia) AS "Zysk miesięczny", SUM(nvl(kara,0)) as "Kary"
FROM PR_WYPOZYCZENIE
GROUP BY EXTRACT(YEAR FROM data_wypozyczenia), EXTRACT(MONTH FROM data_wypozyczenia);

SELECT EXTRACT(YEAR FROM data_wypozyczenia) AS "Rok", to_char(to_date(data_wypozyczenia, 'YY/MM/DD'), 'Month') AS "Miesiąc", SUM(koszt_wypozyczenia) AS "Zysk miesięczny", SUM(nvl(kara,0)) as "Kary"
FROM PR_WYPOZYCZENIE
GROUP BY EXTRACT(YEAR FROM data_wypozyczenia), to_char(to_date(data_wypozyczenia, 'YY/MM/DD'), 'Month');

--8 Rozpiska zyskow na lata
SELECT EXTRACT(YEAR FROM data_wypozyczenia) AS "Rok", SUM(koszt_wypozyczenia) AS "Zysk roczny", SUM(nvl(kara,0)) as "Kary"
FROM PR_WYPOZYCZENIE
GROUP BY EXTRACT(YEAR FROM data_wypozyczenia);

--9 Chcemy sie dowiedziec jakie osoby wypozyczyly ksiazki gdzie autorem jest Warren
SELECT id_wypozyczenia, imie, nazwisko
FROM pr_wypozyczenie wyp
JOIN pr_osoba os ON wyp.id_osoby = os.id_osoby
WHERE id_egzemplarza IN (SELECT id_egzemplarza FROM pr_egzemplarz egz
JOIN pr_ksiazka ksk ON egz.nazwa_ksiazki = ksk.nazwa_ksiazki
JOIN pr_role rol ON ksk.nazwa_ksiazki = rol.nazwa_ksiazki
JOIN pr_autor aut ON rol.id_autora = aut.id_autora
WHERE aut.nazwisko = 'Warren' AND rol.rola = 'AUTHOR');

--10 TOP 5 wypozyczajac sie ksiazek ze wzgledu na ilosc
SELECT ROWNUM, nazwa_ksiazki
FROM (SELECT nazwa_ksiazki, COUNT(status)
FROM pr_egzemplarz egz
WHERE egz.status = 'BORROWED'
GROUP BY nazwa_ksiazki
ORDER BY COUNT(status))
WHERE ROWNUM < 6;