# Alfabetul românesc
ALFABET = "AĂÂBCDEFGHIÎJKLMNOPQRSȘTȚUVWXYZ"


# Transformă textul în litere mari și verifică dacă este valid
def curata_text(text):
    text = text.upper().replace(" ", "")

    for litera in text:
        if litera not in ALFABET:
            print("Eroare! Simbol invalid:", litera)
            return None

    return text


# Cezar simplu
def cezar_simplu():
    print("\n--- CIFRUL CEZAR SIMPLU ---")

    operatie = int(input("1. Criptare\n2. Decriptare\nAlege: "))

    if operatie != 1 and operatie != 2:
        print("Optiune invalida!")
        return

    k1 = int(input("Introdu cheia k1 (1-30): "))

    if k1 < 1 or k1 > 30:
        print("Cheia trebuie sa fie intre 1 si 30!")
        return

    text = input("Introdu textul: ")
    text = curata_text(text)

    if text is None:
        return

    rezultat = ""

    for litera in text:
        pozitie = ALFABET.index(litera)

        if operatie == 1:
            pozitie_noua = (pozitie + k1) % 31
        else:
            pozitie_noua = (pozitie - k1) % 31

        rezultat += ALFABET[pozitie_noua]

    print("\nText procesat:", text)
    print("Rezultat:", rezultat)


# Cezar cu permutare
def cezar_permutare():
    print("\n--- CIFRUL CEZAR CU PERMUTARE ---")

    operatie = int(input("1. Criptare\n2. Decriptare\nAlege: "))

    if operatie != 1 and operatie != 2:
        print("Optiune invalida!")
        return

    k1 = int(input("Introdu cheia k1 (1-30): "))

    if k1 < 1 or k1 > 30:
        print("Cheia trebuie sa fie intre 1 si 30!")
        return

    k2 = input("Introdu cheia k2 (minim 7 litere): ")
    k2 = curata_text(k2)

    if k2 is None:
        return

    if len(k2) < 7:
        print("Cheia k2 trebuie sa aiba cel putin 7 litere!")
        return

    # Construim alfabetul permutat
    alfabet_permutat = ""

    for litera in k2 + ALFABET:
        if litera not in alfabet_permutat:
            alfabet_permutat += litera

    print("Alfabetul permutat:", alfabet_permutat)

    text = input("Introdu textul: ")
    text = curata_text(text)

    if text is None:
        return

    rezultat = ""

    for litera in text:
        pozitie = alfabet_permutat.index(litera)

        if operatie == 1:
            pozitie_noua = (pozitie + k1) % 31
        else:
            pozitie_noua = (pozitie - k1) % 31

        rezultat += alfabet_permutat[pozitie_noua]

    print("\nText procesat:", text)
    print("Rezultat:", rezultat)


# Programul principal
while True:

    print("\n================ MENIU ================")
    print("1. Cezar simplu")
    print("2. Cezar cu permutare")
    print("3. Iesire")

    optiune = int(input("Alege optiunea: "))

    if optiune == 1:
        cezar_simplu()

    elif optiune == 2:
        cezar_permutare()

    elif optiune == 3:
        print("Programul s-a incheiat. La revedere!")
        break

    else:
        print("Optiune invalida!")


