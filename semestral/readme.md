# LCS (Longest Common Subsequence)

The longest common subsequence (LCS) is defined as the longest subsequence that is common to all the given sequences, provided that the elements of the subsequence are not required to occupy consecutive positions within the original sequences (the definition os taken from https://www.programiz.com/dsa/longest-common-subsequence)

Examples:
LCS for input Sequences “ABCDGH” and “AEDFHR” is “ADH” of length 3.
LCS for input Sequences “AGGTAB” and “GXTXAYB” is “GTAB” of length 4.

## Options
My program has 3 options to choose. 

### 1st option 
-c [word 1][word 2] -- find the LCS of 2 words.

Input example: -c hello helicopter
Output example: LCS of the words -hello- and -helicopter- is 4.

### 2nd option
-c [word 1][word 2][word 3] -- find the LCS of 3 words.

Input example: -c hello helicopter header
Output example: LCS of the words -hello-, -helicopter- and -header- is 2.


### 3rd option
-f [file.txt][word] -- find the word from the file.txt which has the biggest LCS with the written word. The file words.txt in the repository contains 1000 words. It can be used for test purposes. 
*Note*: please, make sure that the working directory in configurations is correct.

Input example: -f words.txt alien
Output example: The word -listen- has the biggest LCS (4) with the given word -alien-.

I have done a screen how the configurations should look like: https://docs.google.com/document/d/1YsUI9d04uHJEb4nV1Ns-r30IgX9mg32llY9n5czMClU/edit?usp=sharing

Můj program splnuje nasledující požadavky:
✔Obsahuje implementaci s jedním vlaknem.
✔Bez problémů prochází kontrolou nástroji jako je Valgrind, Helgrind.
✔Program je přenositelný napříč architekturami a operačními systémy. 
✔Program poskytuje neinteraktivní rozhraní, tj. přebírá vstupy z příkazové řádky, vstupní data ze souboru či ze standardního vstupu
✔Program implementuje přepínač --help – vypíše použití a skončí
✔Program neakceptuje neznámé přepínače (vypíše chybu "Please, choose the defined option: --help, -c or -f!" )