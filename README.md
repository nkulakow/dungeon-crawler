# *Dungeon Crawler*

Jest to aplikacja robiona przez mój zespół w ramach przedmiotu Programowanie Obiektowe na Politechnice Warszawskiej.

### **OPIS PROGRAMU**
Inspirację do projektu stanowi klasyczny typ gry Dungeon Crawler, polegającej na poruszaniu się drużyną postaci po mapie, wykonywaniu misji i pokonywaniu przeciwników.

### **STRUKTURA PROGRAMU**
1. 4 główne katalogi (w katalogu *src*) z plikami zarządzającymi 4 głównymi obszarami
     - **Logic** - pliki organizujące działanie gry, w tym:
        - *constants.h* - plik zawierający zdefiniowane stałe (jeden plik ze względu na niewielką ilość). Najważniejsze stałę w pliku to 4 typy wyliczeniowe: *GAMESTATES*, *PARTYSTATES*, *BATTLESTATES* i *CHARACTERSTATES*, które umożliwiają wygodne i czytelne zarządzanie stanem rozgrywki
        - *globals.h* - plik zawierające definicje statycznej instancji klasy Game używanej przez cały czas działania programu
    - **Map** - hierarchia klas potrzebna do wygenerowania i zarządzania mapą
    - **Menu** - pliki zawierające klasy poszczególnych menu
    - **Characters** - hierarchia klas postaci
2. Plik _**main.cpp**_ uruchomiający program i dodający bohaterów
3. 3 podkatalogi z potrzebnymi materiałami innymi niż kod
      - **fonts** zawierający czcionki
      - **Soundtrack** zawierający utwory muzyczne i efekty dźwiękowe
      - **Textures** zawierający tekstury postaci, tła itd.
4. Katalog **tests** z testami

### **HIERARCHIA KLAS**

- ### *POSTACI*

    - #### **CHARACTER**
        Klasa abstrakcyjna, stanowiąca bazę dla każdego występującego w grze typu postaci, dziedziczą po niej klasy **Hero** i **Enemy**   
        
        - #### **HERO**
            Klasa dziedzicząca po **Character**, rozszerzająca ją o funkcjonalność cechującą postać gracza.   

            - **WARRIOR**  
            Klasa dziedzicząca po **Hero**, reprezentująca charakterystyki postaci gracza typu Wojownik.   

            - **WIZARD**  
            Klasa dziedzicząca po **Hero**, reprezentująca charakterystyki postaci gracza typu Mag.   

        - #### **ENEMY**
            Klasa dziedzicząca po **Character**, rozszerzająca ją o funkcjonalność cechującą postać przeciwnika w grze.   

            - **SKELETON**  
            Klasa dziedzicząca po **Enemy**, reprezentująca charakterystyki postaci przeciwnika typu Skeleton.   

            - **SKULL_BOSS**   
            Klasa dziedzicząca po **Enemy**, reprezentująca charakterystyki postaci przeciwnika typu Boss.   
            
- ### *GENEROWANIE MAPY*

    - #### **MAP**
        Klasa reprezentująca samą mapę, aktualnie mapa to 4 komnaty i 3 korytarze położone na przemian.   

    - #### **ROOM**
        Wirtualna klasa reprezentująca pojedyncze pomieszczenie na mapie.   

        - **CHAMBER**  
        Klasa dziedzicząca po **Room**, reprezentująca komnatę na mapie, w instancjach tej klasy odbywają się walki.   

        - **CORRIDOR**  
        Klasa dziedzicząca po **Room**, reprezentująca korytarz na mapie, łączą one komnaty.


- ### *PRZECHODZENIE POMIĘDZY MENU A GRĄ*

    - #### **MENU**
        Klasa reprezentująca menu główne gry. Zawiera funckje odpowiadające za wybieranie opcji w głównym menu.

    - #### **GAME_OVER**
        Klasa reprezentująca menu wyjściowe gry po przegranej walce, czyli potyczce w której żadna z postaci gracza nie pozostała przy życiu.   

    - #### **VICTORY**
        Klasa reprezentująca menu wyjściowe gry po zwycięstwie, czyli przejściu z sukcesem przez całą mapę i pokonaniu wszystkich napotkanych przeciwników.   


- ### *MECHANIKA GRY*
    - #### **GAME**
        Klasa organizująca całą rozgrywkę, core całego kodu, zajmująca się inicjalizacją, update'owaniem i rysowaniem większości parametrów tworzących grę.   

    - #### **FIGHT**
        Klasa reprezentująca pojedynczą bitwę między dwiema drużynami (klasa Party), organizuje kolejność tur i przebieg walki.   

    - #### **PARTY**
        Klasa reprezentująca drużynę bohaterów i drużyny przeciwników, potrzebna do zarządzania m.in. poruszaniem się i walką.
  

### **SPOSÓB TESTOWANIA**
Do testowania aspektów programu, niezwiązanych z wykorzystywanymi bibliotekami, stworzone zostały testy jednostkowe z użyciem Catch2, znajdujące się w folderze */tests*. Aby je skompilować należy wykonać polecenie _make tests_ i uruchomić _./test_.

### **SPOSÓB INSTALACJI I OBSŁUGI**
W celu uruchomienia gry, po sklonowaniu repozytorium, należy znajdując się w folderze głównym wykonać w terminalu komendę *make*, a następnie po zakończeniu procesu kompilacji otworzyć plik *./app*.

#### **Obsługa i przebieg gry**
- Poruszanie się po Menu: za pomocą strzałek góra-dół należy wybrać opcję i potwierdzić klawiszem Enter
- Poruszanie się postaciami: następuje za pomocą klawiszy A (lewo), D (prawo), W (przejście do następnego pomieszczenia)
- Ruch podczas walki: prawą strzałką należy wybrać przeciwnika i potwierdzić Enterem
- Wyświetlanie parametrów postaci: należy najechać myszką na bohatera/przeciwnika aby wyświetlić jego atrybuty
- Przebieg walki:
    - rozgrywka jest turowa
    - w odpowiednich turach gracz jest informowany, kiedy jest jego kolej
    - gracz atakuje kolejno swoimi postaciami (od lewej do prawej), jedną naraz
    - gracz wygrywa rozgrywkę po pokonaniu wszystkich przeciwników
    - po wygranej rozgrywce każda z postaci otrzymuje bonusowe punkty do DMG i HP 
- W kolejnych komnatach przeciwnicy stają się coraz silniejsi
- Gra kończy się, gdy gracz przejdzie przez wszystkie komnaty i wygra wszystkie bitwy, lub cała jego drużyna zostanie pokonana

### **WYKORZYSTANE NARZĘDZIA**
- Głównym narzędziem z pomocą którego powstał projekt jest biblioteka SFML, służąca do tworzenia prostych gier komputerowych. Użyta została do zaprojektowania i implementacji strony graficznej projektu.
- Bardzo użyteczne były sprytne skaźniki umożliwiające implementację polimorficznych klas.
- Niezwykle użyteczne okazały się typy wyliczeniowe, które pomogły zorganizować rozgrywkę.
- Dziedziczenie i wirtualne klasy/metody umożliwiły łatwą implementację walki i rozszerzalność aplikacji.


### **TEKSTURY I UTWORY MUZYCZNE**
Tekstury tła (oprócz *menu_background*), tekstura strzałki oraz wszystkie tekstury postaci zostały stworzone przez członków grupy w ramach tego projektu. Pliki muzyczne zostały pobrane ze strony [Uppbeat](uppbeat.io), natomiast efektów dźwiękowych użyczył portal [Freesound](https://freesound.org/).
  
### **CIEKAWE ROZWIĄZANIA PROGRAMISTYCZNE**
Wykorzystanie dużej ilości wyliczeń enum, służących do określenia stanu gry, które zdecydowanie ułatwiają klasie Game ocenić sytuację i pomagają napisać schludniejszy, czytelniejszy kod.
Zadeklarowanie większości stałych, takich jak ścieżki do plików graficznych, czy też offsety pixelowe przesunięć, razem z klasami enum, w pliku *src/Logic/constants.h*, znacząco wpływające na czytelnośc kodu i łatwość wprowadzania zmian oraz ulepszeń.

### **UWAGI**
W jednym miejscu został użyty zwykły, "surowy" wskaźnik * - przy atrybucie klasy Game window, ponieważ próba użycia sprytnego wskaźnika kończyła się błędami kompilacji lub tym, że program się nie uruchamiał.
Występują również przypadki "surowych" ścieżek do plików, min. z czcionkami, czy też muzyką. W wielu przypadkach jest to spowodowane nieoczekiwanym działaniem programu w efekcie na próbę zapisu ścieżek w pomocniczym pliku ze stałymi *src/Logic/constants.h*, co jest prawdopodobnie spowodowane zastosowanie obiektu klasy Game jako zmiennej statycznej.


