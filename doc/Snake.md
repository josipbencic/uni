# Snake game


Igra Snake je kreirana 1976 godine (pod imenom Blockade) i od tada je
doživjela nebrojeno mnogo verzija i klonova. Igra se bazira na ovim
pravilama:

* Zmija se može kretati u četiri smjera (lijevo, desno, gore, dolje);
* Produžuje se kada pojede jabuku;
* Ne smije ući u zidove, inače je igra gotova.
* Ako dotakne sebe gubi dio repa od mjesta gdje se je dotakla i
  gubi jedan život.
* Igra je gotova kad zmija izgubi sva tri života koja dobiva na početku
  igre.


Igra počinje u stanju miraovanja. Smjer zmije određujemo tipkama
_Up_, _Down_, _Left_ i _Right_. Kad stisnemo jednu od strelica zmija se
počinje kretati i nadalje kontroliramo samo njezin smjer.

Koliko objekata na treba za implementaciju igre? Jedan objekt će predstavljati zmiju. Za jabuku nam ne treba poseban objekt jer je
ona pasivan element u igri. Jedan će nam objekt trebati za prezentaciju
svijeta unutar kojeg se zmija kreće. Svijet će imati zidove i jabuku.
Konačno jedan objekt će implementirati igru i time dolazimo do zaključka
da nam trebaju tri klase za implementaciju igre. Te ćemo klase nazvati
_Game_, _Snake_ i _World_.

Čitav program je interakcija triju klasa: _Game_, _Snake_ i _World_
koje modeliraju osnovne koncepte u simulaciji. _Game_ je klasa koja
implementira čitavu igru i stoga se postavlja pitanje njenog odnosa prema
druge dvije klase. Kako igra kontrolira životni vijek svih svojih
komponenti ovdje se nameće _kompozicija_ kao pravi način konstrukcije igre.
Klasa  _Game_ će sadržavati objekte tipa  _Snake_ i  _World_ kao svoje
varijable članice.

## _Game_ klasa

Ova klasa predstavlja igru. Ona ima run() metodu u kojoj se unutar
petlje igre poziva trojka: procesiraj događaje -- odredi novo stanje
igre (_update_) -- iscrtaj novo stanje.  Klase _Snake_
i _World_ ne moraju biti svjesne kalse _Game_ te stoga i ne drže
referencu na nju.

Kod procesiranja događaja klasa će prosljediti događaje zmiji. To
znači da klasa _Snake_ mora nuditi metodu _setDirection()_ koja
određuje smjer zmije i koja će se pozivati u _Game_ klasi.

U metodi _update()_ klasa će pozvati metode _update()_  zmije i svijeta.
I zmija i svijet trebaju znati odrediti svoje novo stanje.

Konačno, u kod iscrtavanja klasa _Game_ će jedostavno iscrtati svijet
i zmiju.


## _Snake_ klasa

Zmija se sastoji od niza pravokutnih blokova. Glava ima jednu boju, a
tijelo drugu. Za položaj zmije uzimamo položaj njene glave. Kako je cijela
domena igre podijeljena u blokove (veličine `msize`x`msize`) ti se
blokovi mogu indeksirati cjelobrojnim indeksima. I zmija i svijet modeliraju
imati istu veličinu bloka.  

Zmija je implementirana kao vektor blokova. `std::vector` nam dozvoljava
lako produžavanje i skraćivanje zmije. Blok drži samo svoje koordinate.
Kod iscrtavanja zmije iscrtava se jedan `sf::RectangleShape` više puta
i pri tome mu se mijenja pozicija i boja.

Kao atribute zmija ima i brzinu, broj preostalih života,
postignute bodove i zastavicu kraja igre.

Zmija nije svjesna jabuke (nema referencu na nju) i stoga ne može
sama odrediti kada je "pojela" jabuku. Jabuka je dio svijeta i svijet
će u svijoj `update()` metodi uzeti referencu na zmiju i utvrditi
je li zmija "pojela" jabuku. Zatim će na referenci na zmiju pozvati
metode `extend()` i `increaseScore()`.


**Napomena** - Dodavanje bloka zmiji. Blok se dodaje na kraj zmije. Ako zmija ima samo jedan blok, onda je kraj određen smjerom kretanja zmije.


## _World_ klasa

Ova klasa sadrži jabuku i zidove te utvrđuje je li zmija pojela jabuku.
Ona treba utvrditi je li zmija prošla kroz zid i tada pozvati zmijinu
 `lose()` metodu. U metodu `update()` klase `Game` može se ispitivati
 je li igra izgubljena i tada izvršiti `reset` zmije. Klasa
 _World_ u svojoj metodi `respawnApple()` postavlja položaj jabuke
slučajnim generiranjem novih koordinata jabuke. To se dešava kada je
jabuka pojedena (pa se generira nova) i kada je igra gotova pa se ide na
novi početak.

## Iscrtavanje

_Snake_ i _World_ su klase čiji se objekti iscrtavaju na ekranu. Za iscrtavanje
se koristi metoda `draw` klase `sf::RenderWindow` kojoj se predaje objekt
koji želimo iscrtati. Tako iscrtavamo objekte iz SFML biblioteke (`sf::Sprite`,
  `sf::RectangleShape`, `sf::CircleShape` itd.). Naše klase želimo
iscrtavati na isti način što postižemo deriviranjem naše klase iz
baze `sf::Drawable`. To je apstraktna bazna klasa koja nudi samo čistu virtualnu
metodu `draw` koju u našoj klasi moramo reimplementirati. Ta implementacija ide u
privatni dio naše klase. Na taj način postižemo da se metoda može pozvati samo kroz
pokazivač ili referencu na klasu  `sf::Drawable` (a ne i direktno na instanci
naše klase). Kao primjer dana je implementacija metode `World::draw` u datoteci
`world.cpp`.


## Linkovi

* [sf::Drawable](https://www.sfml-dev.org/documentation/2.5.0/classsf_1_1Drawable.php)

* [sf::CircleShape](https://www.sfml-dev.org/documentation/2.5.0/classsf_1_1CircleShape.php)
* [sf::RectangleShape](https://www.sfml-dev.org/documentation/2.5.0/classsf_1_1RectangleShape.php)

* [Shapes](https://www.sfml-dev.org/tutorials/2.5/graphics-shape.php)
* [Generiranje slučajnih brojeva](http://en.cppreference.com/w/cpp/numeric/random)
