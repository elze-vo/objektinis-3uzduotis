# **Objektinis programavimas (2-oji užduotis)**

## **Programos versijų aprašymas**

* ### **v2.0**

  - Sukurta projekto dokumentacija naudojant **Doxygen**. Ji įkelta į repozitoriją kaip atskiras *doxygen* HTML katalogas.
  - Dokumentacijos *.pdf* failas, naudojantis **Latex**: [v2_0.pdf](https://github.com/user-attachments/files/18099887/v2_0.pdf)

  - Realizuoti **Unit Testai** su klase Studentas naudojant Google Test *framework*'ą.

* ### **v1.5**

  - Sukurta **abstrakti** klasė *Zmogus*, kurios objektų sukurti negalima;
  - Klasė Studentas tapo šios klasės **išvestine (derived)** klase.

* ### **v1.2**

  - Rezultatai.h ir Studentas.h sujungti į vieną failą, tad class projekto versijose liko vienintelė klasė Studentas.
  - Studentas klasei realizuota **"Rule of Three"** ir visi reikiami **įvesties/išvesties operatoriai**.
    - Įvesties operatorius:
      - nuskaito naudotojo *ranka įvestus* duomenis;
      - nuskaito duomenis iš *.txt* failo.
    - Išvesties operatorius:
      - išveda rezultatus (studentų vardai, pavardės, vieta atmintyje ir galutiniai balai) *į ekraną* arba naudojamas funkcijoje, išvedančioje rezultatus į failą.
  - Atlikta greičio analizė klasei su realizuota "Rule of Three" ir klasei be realizuotos "Rule of Three" pagal kompiliatoriaus -02 optimizavimo lygį, naudojant fiksuotą konteinerį (vektorių) ir greičiausią rūšiavimo strategiją (trečia).
  - Pridėta galimybė demonstruoti visus metodus, atitinkančius trijų metodų taisyklę. Kitaip nei su kitais pradiniais pasirinkimas 1-5, trijų metodų demonstravimas (6) reikalauja *ENTER* paspausti du kartus.
 
<img width="700" alt="lalala" src="https://github.com/user-attachments/assets/1e0e201f-10e5-4dcc-83a7-ed8e7cc0460a">

#

* ### **v1.1**

  - Ankstesnės atliktos užduoties pagrindu sukurta nauja repozitorija **objektinis-2uzduotis**, kurioje išliko *commit*'ų ir *tag*'ų istorija.
  - Ankstesnės programos versijoms su std::vector ir std::list pridėtas testavimas su -O1, -O2, -Ox kompiliatoriaus optimizacijos lygiais.
    Šios programos versijos dabar talpinamos **struct_versija** direktorijoje.
  - Ankstesnės programos versijos Struct Studentas ir Struct Rezultatai pakeistos į Class Studentas ir Class Rezultatai.
    Šioms versijoms (naudojančioms std::vector arba std::list) taip pat pridėtas testavimas su -O1, -O2, -Ox kompiliatoriaus optimizacijos lygiais.
    Šios programos versijos dabar talpinamos **class_versija** direktorijoje.
  - Atlikta eksperimentinė realizacijos spartos analizė pagal kompiliatoriaus optimizavimo lygį, naudojant fiksuotą konteinerį - vektorių.

<img width="900" alt="Screenshot 2024-11-20 190020" src="https://github.com/user-attachments/assets/fb6223dd-8ef1-4285-9929-05d6c47de9af">

# **Objektinis programavimas (1-oji užduotis)**

## **Programos versijų aprašymas**

* ### **v.pradinė**
  
  - Programa priima naudotojo įvestus studentų:
    - vardus;
    - pavardes;
    - namų darbų rezultatus (kiekvienam studentui gali būti skirtingas kiekis);
    - egzamino rezultatą.
  - Programa taip pat gali atsitiktinai generuoti viršuje išdėstytus duomenis.
  - Programa leidžia pasirinkti galutinio balo skaičiavimui naudoti vidurkį arba medianą.
  - Programa suskaičiuoja galutinį balą pagal formulę:
    - galutinis = 0,4 * namų darbų vidurkis arba mediana + 0,6 * egzaminas.
  - Programa studentų vardus ir pavardes bei jų galutinį balą atspausdina ekrane.

#

* ### **v0.1**
  
  - Pridėta galimybė duomenis apie studentus nuskaityti iš ***.txt** failo.
  - Pridėtas studentų abėcėlinis rūšiavimas pagal pavardes.
  - Projektas išskirstytas į atskirus ***.cpp** ir ***.h** failus.
  - Pridėta daugiau išimčių valdymo (angl. *exception handling*).
    
 #
 
* ### **v0.2**

    - Pridėta galimybė rezultatus išsaugoti dviejuose skirtinguose ***.txt** failuose (**islaike.txt**, kai galutinis studento balas daugiau arba lygus 5, kitu atveju **neislaike.txt**).
    - Pašalintas studentų rikiavimas pagal pavardę.
    - Pridėtas studentų rikiavimas pagal galutinį balą (galima pasirinkti didėjimo arba mažėjimo tvarka).
    - Pridėta galimybė kurti failus programos testavimui (galima pasirinkti studentų ir namų darbų kiekį). Šie failai neturi apdoroto galutinio balo.
    - Pridėtas testinių failų kūrimo trukmės skaičiavimas.
    - Pridėta galimybė paleisti programos veikimo spartos testą (programa parašo, kiek laiko ji užtruko perskaityti testinį failą, surūšiuoti duomenis, ir įrašyti rezultatus į du atskirus failus pagal studentų galutinį pažymį (**islaike.txt** ir **neislaike.txt**).
    - Atliktas programos veikimo spartos testavimas.
      
<img width="500" alt="v0,2sparta" src="https://github.com/user-attachments/assets/00d70886-ad6d-4995-ad66-c561c7655ea0">
<img width="500" alt="v0,2kurimas" src="https://github.com/user-attachments/assets/14671c43-cbcb-43b4-b3ca-b340835df84c">

#

* ### **v0.3**

    - Parašyta alternatyvi programos versija, kurioje vietoje **std::vector** studentų duomenims saugoti naudojamas **std::list**.
    - Pridėta galimybė matyti vector ir list **adresą kompiuterio atmintyje**, kai duomenys apie studentus yra įrašomi ranka.
    - Atlikta programos spartos analizė, lyginant std::vector ir std::list programos versijų spartą:
      - Pastebėta, kad std::vector versija su visais studentų kiekiais yra spartesnė.
      - Rezultatai std::vector versijai, lyginant su praeita programos versija v0.2, **drastiškai** pakito, nes analizė buvo atliekama **"Release"**, o ne "Debug" režimu.
     
<img width="500" alt="VECTOR" src="https://github.com/user-attachments/assets/b12ad602-b788-4739-8c65-194d8d328865">
<img width="500" alt="LIST" src="https://github.com/user-attachments/assets/eee0b52b-53f0-43df-b0cc-934ea511adcf">
     
#

* ### **v1.0**

    - Pridėtos dar dvi skirtingos strategijos (originali strategija sutapo su siūloma 1-ąja) bendro **studentai** konteinerio rūšiavimui į dvi kategorijas (strategijos pritaikytos tiek **vector**, tiek **list** konteinerius naudojančioms programos versijoms iš v0.3). Trijų naudojamų strategijų aprašymas:
      - **1 strategija**: Bendro studentų konteinerio rūšiavimas į du naujus konteinerius **"neislaike"** ir **"islaike"**. Tokiu būdu tas pats studentas yra dviejuose konteineriuose: bendrame **studentai** ir viename iš jam tinkančių pagal galutinį balą.
      - **2 strategija**: Bendro studentų konteinerio rūšiavimas mažesnį už 5 galutinį balą turinčių studentų iškėlimu į "**neislaike"**, kai kiti studentai lieka bendrame konteineryje **"studentai"**.
      - **3 strategija**: Bendro studentų konteinerio rūšiavimas panaudojant **antros strategijos logiką** ir efektyvius darbo su konteineriais metodus:
        - **Vector** atveju naudojama **std::stable_partition**, **std::move**;
        - **List** atveju naudojama **std::list::splice**
    - Prie programos spartos analizės pasirinkimo pridėtas pasirinkimas testuoti individualios strategijos spartą arba palyginti visų strategijų spartą.
    - Pašalinta galimybė atlikti išsamią programos veikimo spartos analizę (skaičiuojant laiką, kurį programa užtrunka failą nuskaitydama, duomenis surūšiuodama ir kurdama du išvesties failus).
    - Atlikta programos duomenų rūšiavimo spartos analizė (pagal **vector** arba **list** ir trijų skirtingų rūšiavimo strategijų naudojimą).
    - Pridėta galimybė stebėti, kiek vietos (bytes) užima **vector** arba **list** konteineriai, reikalingi kiekvienos strategijos vykdymui.
    - Abiejoms programos versijoms (naudojant **vector** arba **list**) sukurti **CMakeLists.txt** ir **run.bat** failai.
 
<img width="500" alt="v1,0VECTOR" src="https://github.com/user-attachments/assets/5cdb0400-1c76-46e6-964c-bcb5b0b1f413">
<img width="500" alt="v1,0LIST" src="https://github.com/user-attachments/assets/41c20bee-4217-413a-9a43-70a3d0067400">

#

## **Programos įdiegimo instrukcija**

  1.  Reikia turėti CMake programos 3.10 versiją (arba naujesnę). CMake galima parsisiųsti internetu.
  2.  Reikia parsisiųsti **std::list** arba **std::vector** (arba abi) direktoriją (-as).
  3.  Direktorijoje reikia surasti failą **run.bat** ir jį paleisti.
  4.  Po run.bat paleidimo direktorijoje atsirado nauja direktorija **Release**. Joje yra failas **studentuAppsas.exe** (vector atveju) arba **studentuAppsasList.exe** (list atveju). ***.exe** failą paleidus atsidarys programa.
  5.  Pakartotiniam programos paleidimui tereikia paleisti minėtąjį ***.exe** failą.

#

## **UnitTest paleidimo instrukcija**

  1. Reikia turėti Microsoft Visual Studio 2022 versiją.
  2. Reikia sukurti naują repozitoriją C++ kalbai, pasirenkant Google Test.
  3. Failo viduje turi būti test.cpp failo kodas.
  4. Įprastai paleisti programą.
     
#

## **Programos naudojimo instrukcija**

Paleidus programą reikia pasirinkti iš 5-ių veiksmų. Veiksmą pasirinkti galima įvedus tinkamą skaičių ir paspaudus **ENTER**:

- Pridėti studentus iš failo:
  
  Šis pasirinkimas leidžia apdoroti studentų duomenis, nuskaitytus iš ***.txt** failo.
  
  - Reikia įvesti tinkamą failo pavadinimą. Pavyzdiniai failai (stud1000.txt, stud10000.txt ir stud100000.txt) yra pridėti **std::list** ir **std::vector** direktorijų **src** direktorijoje.
  - Reikia pasirinkti, kaip norime skaičiuoti galutinį balą (pagal vidurkį ar medianą).
  - Reikia pasirinkti, kaip apdorotus studentų duomenis norime rikiuoti pagal galutinį balą (didėjimo ar mažėjimo tvarka).
  - Reikia pasirinkti išvedimo būdą. Pasirinkus *spausdinti į ekraną* arba *spausdinti į ekraną ir išsaugoti į failus*, rezultatai bus parodomi ekrane. Pasirinkus *išsaugoti į failus* arba *spausdinti į ekraną ir išsaugoti į failus*, duomenys bus įrašomi į du ***.txt** failus **islaike.txt** ir **neislaike.txt**. Šiuos failus galima rasti ten pat, kur yra ***.exe** programos failas.
  - Norint programą uždaryti, paspauskite bet kurį klaviatūros klavišą.
 
- Pridėti studentus ranka:

  Šis pasirinkimas leidžia apdoroti studentų duomenis, įvestus ranka.
  
  - Reikia įvesti, kiek studentų norime įvesti.
  - 1-ajam studentui įvedame vardą ir pavardę.
  - 1-ajam studentui įvedame namų darbų rezultatus. Po kiekvieno rezultato reikia paspausti **ENTER**. Norint užbaigti namų darbų rezultatų įvedimą 1-ajam studentui, reikia du kartus paspausti **ENTER**.
  - 1-ajam studentui įvedame egzamino rezultatą.
  - Vėlesniems studentams procesas kartojasi.
  - Reikia pasirinkti, kaip norime skaičiuoti galutinį balą (pagal vidurkį ar medianą).
  - Reikia pasirinkti, kaip apdorotus studentų duomenis norime rikiuoti pagal galutinį balą (didėjimo ar mažėjimo tvarka).
  - Reikia pasirinkti išvedimo būdą. Pasirinkus *spausdinti į ekraną* arba *spausdinti į ekraną ir išsaugoti į failus*, rezultatai bus parodomi ekrane. Pasirinkus *išsaugoti į failus* arba *spausdinti į ekraną ir išsaugoti į failus*, duomenys bus įrašomi į du ***.txt** failus **islaike.txt** ir **neislaike.txt**. Šiuos failus galima rasti ten pat, kur yra ***.exe** programos failas.
  - Norint programą uždaryti, paspauskite bet kurį klaviatūros klavišą.
 
- Generuoti studentus atsitiktinai:
    
  Šis pasirinkimas leidžia apdoroti studentų duomenis, programos sugeneruotus atsitiktinai.

  - Reikia įvesti, keliems studentams norime sugeneruoti duomenis.
  - Reikia pasirinkti, kaip norime skaičiuoti galutinį balą (pagal vidurkį ar medianą).
  - Reikia pasirinkti, kaip apdorotus studentų duomenis norime rikiuoti pagal galutinį balą (didėjimo ar mažėjimo tvarka).
  - Reikia pasirinkti išvedimo būdą. Pasirinkus *spausdinti į ekraną* arba *spausdinti į ekraną ir išsaugoti į failus*, rezultatai bus parodomi ekrane. Pasirinkus *išsaugoti į failus* arba *spausdinti į ekraną ir išsaugoti į failus*, duomenys bus įrašomi į du ***.txt** failus **islaike.txt** ir **neislaike.txt**. Šiuos failus galima rasti ten pat, kur yra ***.exe** programos failas.
  - Norint programą uždaryti, paspauskite bet kurį klaviatūros klavišą.
 
- Sukurti studentų failą:

  Šis pasirinkimas leidžia sukurti testinį studentų ***.txt** failą, kuriame duomenys bus neapdoroti (t.y. faile bus studentų vardai ir pavardės, namų darbų ir egzamino rezultatai).

  - Reikia įvesti, keliems studentams norime sugeneruoti duomenis.
  - Reikia įvesti, kiek namų darbų pažymių turės studentai.
  - Reikia įvesti, kaip turės būti pavadintas sukurtas testinis failas.
  - Sukurtą failą galima rasti ten pat, kur yra ***.exe** programos failas.
  - Norint programą uždaryti, paspauskite bet kurį klaviatūros klavišą.
 
- Testuoti programos greitį:

  Šis pasirinkimas leidžia testuoti studentų rūšiavimo strategijų į dvi grupes pagal galutinį balą spartą ir strategijų naudojamų konteinerių užimamą vietą kompiuterio atmintyje.

  - Reikia įvesti failo, kurio apdorojimo spartą norime testuoti, pavadinimą.
  - Reikia pasirinkti, kaip norime skaičiuoti galutinį balą (pagal vidurkį ar medianą).
  - Reikia pasirinkti, kurios duomenų rūšiavimo strategijos spartą norime testuoti:
    - Pasirinkus 1-3 variantą:
      - Reikia pasirinkti, kaip apdorotus studentų duomenis norime rikiuoti pagal galutinį balą (didėjimo ar mažėjimo tvarka).
      - Informacija apie rūšiavimo spartą ir pasirinktos strategijos naudojamų konteinerių užimamą kompiuterio atmintį bus spausdinama ekrane, o išvestis talpinama į **islaike.txt** ir **neislaike.txt** failus.
      - Reikia pasirinkti, ar norime kartoti programos greičio testavimą nuo pradžių (įvesti **y** ir spausti **ENTER**), ar uždaryti programą (įvesti **n** ir spausti **ENTER**).
    - Pasirinkus 4-a variantą:
      - Reikia pasirinkti, kaip apdorotus studentų duomenis norime rikiuoti pagal galutinį balą (didėjimo ar mažėjimo tvarka).
      - Informacija apie rūšiavimo spartą ir strategijų naudojamų konteinerių užimamą kompiuterio atmintį bus spausdinama ekrane.
      - Reikia pasirinkti, ar norime kartoti programos greičio testavimą nuo pradžių (įvesti **y** ir spausti **ENTER**), ar uždaryti programą (įvesti **n** ir spausti **ENTER**).
     
- Demonstruoti tris metodus:

  Šis pasirinkimas leidžia pademonstruoti "Rule of Three" metodų veikimą.

  - Įvedus pasirinkimą **6** ir paspaudus **ENTER**, atsiras tuščia eilutė. Reikia vėl paspausti **ENTER**.
  - Reikia įvesti studento vardą.
  - Reikia įvesti studento pavardę.
  - Reikia įvesti namų darbų rezultatus, tačiau jie nebus naudojami. Po kiekvieno rezultato reikia paspausti **ENTER**. Norint užbaigti namų darbų rezultatų įvedimą 1-ajam studentui, reikia du kartus paspausti **ENTER**.
  - Reikia įvesti egzamino rezultatą, tačiau jis nebus naudojamas.

- Demonstruoti Zmogus klasės objektų kūrimą:

  Šis pasirinkimas parodo Zmogus klasės objektų kūrimą.

  
#

## **Kompiuteris (testavimo sistemos parametrai):**
  
  - CPU - **AMD RYZEN 5 4600H**
  - RAM - **8GB**
  - SSD - **477GB**
