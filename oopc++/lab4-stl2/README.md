# C++  STL 2

 
**Zadatak**. U ovom zadatku treba napisati četiri funkcije koje služe čitanju tekstualne datoteke 
i računanju određene statistike pojavljivanja riječi u datoteci. U zadatku se koriste spremnici map, multimap i set.

Signature funkcija i njihov opis dani su u datoteci zaglavlja src/zadatak.h.
Funkcija **procitaj_datoteku** čita datoteku zadanog imena i sprema sve riječi u mapu u
kojoj je ključ riječ, a vrijednost je broj pojavljivanja te riječi u tekstu. Za čitanje riječi
koristi se funkcija **procitaj_rijec**.

Funkcija **naj** treba vratiti listu riječi koje se najčešće ponavljaju u tekstu i broj ponavljanja. 

Funkcija **broj_iz_grupe** treba vratiti broj ponavljanja grupe riječi u tekstu. Funkcija uzima 
multimap varijablu koja predstavlja grupe riječi. Ključ u multimapu je ime grupe, a vrijednosti su riječi
koje pripadaju grupi. Funkcija vraća vektor cijelih brojeva koji predstavljaju kumulativni broj ponavljanja riječi iz 
svake pojedine grupe u tekstu. (Prva vrijednost u povratnom vektoru odgovara prvoj grupi u multimap-u itd.)

Napisati vlastitu main funkciju u kojoj se testiraju sve četiri funkcija.

Svi testovi moraju proći. Testove izvršavati u build/test/ direktoriju jer inače test_zad program neće 
naći tražene datoteke.

 Ako nemate odgovarajuće datoteke u odgovarajućem direktoriju (1.txt i text.txt u build/src
i 1.txt, 2.txt, 3.txt, 4.txt u build/test direktoriju) izvedite još jednom cmake koji treba kopirati  datoteke.   
