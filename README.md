# Laboratorium 6 i 7 - Zarządzanie procesami

## Opis projektu
Repozytorium zawiera rozwiązania zadań z laboratorium 6 i 7 z Programowania Systemowego, których głównym celem była nauka zarządzania procesami w języku C.

## Jak używać plików w języku C

1. **Kompilacja plików C**
   Aby skompilować plik w języku C, użyj polecenia `gcc`:
   ```bash
   gcc -o <nazwa_wyjściowego_pliku> <nazwa_pliku.c>
   ```
   Przykład:
   ```bash
   gcc -o 2.out 2.c
   ```

2. **Uruchamianie programu**
   Po skompilowaniu pliku uruchom program za pomocą:
   ```bash
   ./<nazwa_wyjściowego_pliku>
   ```
   Przykład:
   ```bash
   ./2.out
   ```

## Lista zadań

### Zadanie 1 (`1.c`)
Program rozwidlający się na dwa procesy – bez podmiany kodu, z oczekiwaniem na zakończenie potomka. W obu procesach wyświetlane są identyfikatory PID i PPID.

```bash
# Kompilacja
gcc -o 1.out 1.c

# Uruchomienie
./1.out
```

Program pokazuje podstawy tworzenia procesów za pomocą funkcji `fork()` oraz oczekiwania na zakończenie procesu potomnego za pomocą `wait()`.

### Zadanie 2 (`2.c`)
Program rozwidlający się na dwa procesy – z podmianą kodu potomka na program z poprzednich zajęć. Dodatkowo program oczekuje na zakończenie potomka. W obu procesach wyświetlane są identyfikatory PID i PPID.

```bash
# Kompilacja
gcc -o 2.out 2.c

# Uruchomienie
./2.out
```

Program demonstruje użycie funkcji `execl()` do podmiany kodu procesu potomnego na inny program. W tym przypadku używany jest program `SIGTERM.out`, który powinien znajdować się w tym samym katalogu.

### Zadanie 3 (`3.c`)
Program rozwidlający się na trzy procesy – z podmianą kodu na program z poprzednich zajęć oraz oczekiwaniem na zakończenie potomków. We wszystkich procesach wyświetlane są identyfikatory PID i PPID.

```bash
# Kompilacja
gcc -o 3.out 3.c

# Uruchomienie
./3.out
```

Program pokazuje, jak tworzyć wiele procesów potomnych i jak zarządzać ich cyklem życia. Podobnie jak w zadaniu 2, do podmiany kodu używany jest program `SIGTERM.out`.

### Zadanie 4 (`4.c`)
Program demonstrujący przypisanie procesu do wybranego rdzenia procesora za pomocą funkcji `sched_setaffinity()`. Program tworzy proces potomny, przypisuje go do określonego rdzenia CPU i wyświetla informacje o przypisaniu procesów do rdzeni.

```bash
# Kompilacja
gcc -o 4.out 4.c

# Uruchomienie
./4.out
```

Program wykorzystuje funkcje z biblioteki `<sched.h>` do zarządzania przydziałem procesora.

## Struktura programów

Każdy program składa się z dwóch głównych części:
1. **Kod procesu rodzica** - zarządza cyklem życia procesu potomnego i wyświetla informacje o procesie rodzica
2. **Kod procesu potomnego** - wykonuje określone zadania i wyświetla informacje o procesie potomnym

Programy wykorzystują następujące funkcje systemowe:
- `fork()` - tworzy nowy proces (potomny)
- `execl()` - podmienia kod wykonywanego procesu
- `wait()` - oczekuje na zakończenie procesu potomnego
- `getpid()` - pobiera identyfikator bieżącego procesu
- `getppid()` - pobiera identyfikator procesu rodzica
- `sched_setaffinity()` - przypisuje proces do określonego rdzenia procesora
- `sched_getcpu()` - pobiera informację o bieżącym rdzeniu procesora

## Powiązane pliki

W poprzednich laboratoriach powstał program `SIGTERM.out`, który jest używany w zadaniach 2 i 3 jako program wykonywany przez procesy potomne.