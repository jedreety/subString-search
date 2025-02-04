/*
    Projet de Recherche de sous-chaînes
    Auteur : Mehdi Mazouz
    Date : 2024

    Ce projet a pour but de réaliser une recherche optimisée de sous-chaînes sans doublons de lettres dans une chaîne de caractères donnée.

    L'objectif de ce projet est de développer un programme en langage C capable de parcourir une chaîne de caractères très longue et de trouver,
    de la manière la plus optimisée possible, toutes les sous-chaînes de longueur 14 qui ne contiennent aucun doublon de lettres.
    Autrement dit, chaque lettre dans la sous-chaîne doit être unique.

    Petite conclusion, un projet assez fun mais qui a demandé beaucoup de réflexion mais qui s'implemente rapidement.
    Il se peut qu'il existe des méthodes plus optimisées

    Ce projet m'a permis d'approfondir mes connaissances sur les bits et les opérations bit à bit et les structures de données.
	Et de prendre en main la programmation ceci étant mon premier projet.
    Fun : 7/10
    Difficulté : 5/10 (en programmation sans prendre en compte la reflexion)
    Utilité : 9/10
*/

#include <stdio.h>
#include <string.h>
#include <time.h>

enum { SOUS_CHAINE_LEN = 14, NB_METHOD = 3, ITERATIONS = 100000 };

typedef enum { false, true } bool;

// Méthode 1 que j'ai implémentée à chaud une sorte de fonction de reference
void method1(const char* chaine, size_t longueur);

// Méthode 2 avec une reflexion plus poussée
void method2(const char* chaine, size_t longueur);

// Méthode 3 est une amélioration de la méthode 2 un approfondissement de celle-ci
void method3(const char* chaine, size_t longueur);

int main() {

    printf("\n");

    const char chaine[] = "qvllndllhzhfzhhdzhddhjdjggvnvhvccmffwllqgqmmfjfqfhhtrrzczjczzlplddfpptqqfbqffmnmjnnqppfjfccgnnmqqsvvdbbgppjvpjvpjjctjjttwtrrdldlcddrvddqndqnqwqwzwfwwzczggcppgzpzhpzhppprfffbhhwmhhtftstrsrvsrvsrvvshvssnwwpllhfhnnfflcltlblzlqlvqlvlcldcccpptggtdgdjdbbrggmbmnncscbssqrrjddvcvgvfflpppgpvphvphhpcpzpzvvctvctvthtwtfwwbrrhhlplmlwwlqlnlhhtmhmmqlqplllrvrgvrvrffzfgfjfjtjmjvmjmwmvvjffmpfphfhvfvmfvmmhpphhltthgttgccqggpzpfpqpcpvcpvcvvqtqvqbbrlrtllmrmllhmhvmhhvzhvzvrrrzjzbbtvvbgvbbfnnqndqnnpnbnbnlnggwqggmgmqmgmbbmccgqcqbccpvcvnnhvvrvlrrcwrcwrcwrwbrwwzbwbdbfddpttntzzjszsnznbndnzngzgccjrcjchcffmlmqqlrqqzsqzzsbsnsttzpztpzpggzrrttbqqplpqlqjjqcqvccdzdccthccvfcvvqvhqhfhhzwzpzwppgpttntssflfjjrwrqrjrppptlltptpvttpfpwpswpppzzsrzssqllbnlljpllrjllsrlrhrdrmdrmrrpsrprnrffgrffdqdhdqhhrhggwqqlddsbsqbqtqdtdhdvhhbdhdzhdhhtrrppzddgfgzgpzpvpfpnpptggltggbnbppqffzfrzzzsbsrrdgrddwsdsqddhpdpbpvpfvppfsfgfngffzmzbzlblclsccvqvqmmjtjqtjjlcjllsddjqddhldlvlrrbgbrgbrrdzzpfpggqnqbqrrqbbgjgppqgpgwgqqndncndnpdnnbvbnvnwnjjgppzlplqqdgqghqgqzggjssqmmwwcfcpptrpprggrppgbplmzwmdtnpqwzcrthqbppwbgcvgqrpfpnbscnhvrllpvpqwnsslcjrqtvdccprvqfrpswtpvzdzlgtmmvppdmhgdbbsmrbqpqspdhpqgfjznqzphrnggcbzhdqrgvzcfzrhtrlssgmjjghqsjtghhnwjffqrrfslfnsvvdvfjqbfpffrrstdhggvbfwtfpfgswqlfdrnjpjmwzptlbmwgghgwqrphcrvfmhrplllgbnjlprllmjwccphsflntgpnbmdbfqcdsbgvrnfznfrlcfvswqfrqvdnbjsflnsmlcrdstzppmcvbgdtcvgztbdzqbwhmwcfvbwjjcdgbnwjwzrrdqhpgscwtnztjsfstzfwftcldjgvdvwbzrlbdslwttbqpnlwbjcjwqgtrgcglsgtdqbqbnqznptzzbwffwlwzvvtdpcjbvhnswzptclpbndcdvsfmcrmwwgzdfsszqjjdztmtsqgfqzjpctfdpwnzbpnzzwngqnghntblndfrnjzdrmgbqmzbdqfzctrgshwqgfgqssqjltrqlzjswjhmpgwwjdwcjpnsvgrvbfpmlmmwzmbdjwsrjthppfrccjgnmwlvqlprgslbwtbbzlqbznczmsmhsfdcqnwblprcpbzzwfllbnldvpjcwsdhglrzjsptmsjdjqzsmgvhjfjrrtvvbjlmzjsntnrggwbpjlrjggfgqzvswtggthzfmfjnmrzrttbzqpwpsnmdtnbfblpfgslgcmjlbdpshnnrbhvwsbrnvdmjqhvhdjhbfzjmqrmqmdthhzvnrmqcnbtwcdjdqfvdgvmfbhrfqnmdncrddggtcppjlznbsnntppjtnsqsrjwvfrzpnzqcrzhhdflfmmtmwcvtpzbqhdwsczffcqhtdbdjblmgnrmhlqcsvcpgghhvwqhdtzpzlpfllchzltqgcwgfqnbzhgzmdwqdlwnvhqmpqjqnjbhjctslghdqvctdmjfwdfpdjnhdndzwsfjzlmsbmfmzvnvpqgqhtngvgqmlrrzsfmwlcwsscvghjvrzjjqbnplnjzqswpblwzwczhwbhhnjmctnmwlbqqfmnlwdcrptlmfjpjrnpcvmhffjhwhmntdzpdjzwzhrrsdvmjlwdtcpvjfmfzfsrgjghhlvmjjjczgmhvrfpgqbnhldwbrjgzmnszzbssfzcggrwmdfvddwsdmnwtwfwlfnwlvzlctfblbtrjvcwjjdljplcrjhwqslppwwtvfqwsjlfmdznmcdzdmgvmmsrfcclcvhtrhlsjzrbjwrjlfnvqhqvmpzmdttnbhfcvnqlrqbcsvtvwfccjstjpmhqgwlnrzjjmfdszflmglrdbpqhqhqsdfzrcljbdvvnlcqfllmnqcjfzjppdsjwshfschzqbnwfqnpwhqnmwsjbtcgvrljsrtzvcvghcjjlqsngglcggqpntrrhbjpbfhmvpltmnfmfdtwnczwfbvjcqnhvppjftwvwsrlhvvcjtsfptpqgrmrqwwddnqmnmfgrlnphbpqhhhvglqgtwvnwvnbssftmwttmfrffwtzhrpqspclvgchwqwcsgwqwwvpgcwngrcfmhbhflwfbfchlphdzdcrflfmfclsngtlwrqcrsgrdzcpdsvvcdbhgtljmbntbbcqgjqfsbfwzlfsnljpjdcnmjlqrwpmlvwgdlrrdgfhdqhzgltmclzgzzhmrbggsmgtpqdrgmjtlzwstrwbpvhppvsmdqvvwwglzjgdswjszqmrdbmshbhhcstpcsjdbvgjnvcmvhbtclrlmlgnvppgvncsrfchdbqjrclwwlnchmcgvshfsbsvvcvjrsgjlnsfqtqmgntffwnqjtldcqbcqhsgztllstswwqnfrswpchqhnfzzzszqjztzfrgrbjdbjlpvqfqrlrmmpbfbbcclrgmnlzwqrjhqrstswjpgsrtnlwsbqthzpvdzllzqmdmbvvtcztftvlwphhjzbfnrvccfmhmvmzlbrzlnppfzcsffjvjmbgpvlwgwszpztjpsrbnftqtdrbnljtbrjzzbwlsvtwtlwptdtnmtncvcblcmdngjzmctlqtzchncccnwjzrrmmmnllbhrnhwtqjsnvcslrqjfbfndqvdlrjshdzmlprtzbtnhthdqhplwzdbnjmgzlzrbzrvrqnflwfmsmbssqnbcddnvdpltpmplpdzvtjrslcdcnrdplwtjtvctwfzhlvwwqqtbqcjjwhhnpmvgzhqmqfgthwbphrmrtdghchsmwghdqjgjgmpddbrtngtvhqgjfrplrdgpbnhqvswrmqhcmsqvsqmqsgwjndwjrbrhvrctmmrmfwpsgfgdlrzpslpflgvwrgcthgcrnhgrzsmqdgdssjgspfhmqfmjfpmwqhnfjdvqzhpndvnbmqglbrjmdrwgmgctrgzpsdvfbmcstcslblmvnprphntgslmlrqwthrndrhtbccgzzfsglhgqztcsnqjwfzbzlvrpbvswbhrwdsrhrrpnrmsbvbvjccbdsdcfrrzpgwjtnnnvjwlcppwzdqsbdzpfjplrlfgvjpsmbzwpwlghnvqgddfjvrsztrpzlfgmqqzrfcgglghndbhgbmldglclhldljjdslvhzshshtqwhqnbzhvqrcmwdmcmhjcrmdmhrwnwcbhvbbrwrbtfdnztwnbpdfjfhgrmcpngftsvbsmsptnwcvvllnmbnsntbzmwnhfdptbtzswtjzdqwjdhprnjwvhzpscjvlsgrhdrmmrmhzhwwtslzdjqmzfncnmgplhnmwrvqhslvchtjcmpzpjpnpfbjptvvwcsmhgdjtsqrjlfpnfdncpqqmpgpvtlvwljlsqbnhtsqgfwlsmdjpgtvgjvjcrnnzmbllqzlrfdnlffgmtphhhgbcjgdlpzqpwmjwtcmdrsmtnmddftwczbsddtppsptbwfvpnfnsqmsgcfqfmnzffzqgcdvwzrgdwhmnzmrlhcdpdsltnsmjzdqwmmpwvjqbbwsrfgzh";
    const size_t chaine_len = strlen(chaine);
    clock_t times[NB_METHOD];

    // Méthode 1
    times[0] = clock();
    for (int i = 0; i < ITERATIONS; ++i) {
        method1(chaine, chaine_len);
    }
    times[0] = clock() - times[0];

    printf("Temps d'execution pour la methode 1 : %f secondes\n", (double)times[0] / CLOCKS_PER_SEC);

    // Méthode 2
    times[1] = clock();
    for (int i = 0; i < ITERATIONS; ++i) {
        method2(chaine, chaine_len);
    }
    times[1] = clock() - times[1];

    printf("Temps d'execution pour la methode 2 : %f secondes\n", (double)times[1] / CLOCKS_PER_SEC);

    // Méthode 3
    times[2] = clock();
    for (int i = 0; i < ITERATIONS; ++i) {
        method3(chaine, chaine_len);
    }
    times[2] = clock() - times[2];

    printf("Temps d'execution pour la methode 3 : %f secondes\n", (double)times[2] / CLOCKS_PER_SEC);

    return 0;
}

void method1(const char* chaine, size_t longueur) {
    /*
    Méthode 1 - Approche naïve avec triple boucle

    Ma pensée initiale :
    L'idée est simple : pour chaque position dans la chaîne, on vérifie les 14 caractères suivants.
    Pour chaque sous-chaîne, on compare chaque caractère avec tous les précédents dans la fenêtre.

    La complexité est O(n*m²) où m=14, donc O(n*196) ce qui est acceptable pour de petites chaînes
    mais devient problématique sur de très longues chaînes (comme le montre le temps d'exécution).

    Points faibles :
    - Triple boucle imbriquée (i, j, h)
    - Recopie inutile de la sous-chaîne
    - Vérification exhaustive même après avoir trouvé un doublon
    */
    bool chaine_correct = false;
    char sous_chaine[SOUS_CHAINE_LEN + 1];
    const size_t max_i = longueur - SOUS_CHAINE_LEN;

    for (size_t i = 0; i <= max_i; ++i) {
        bool doublons = false;
        size_t index = 0;

        // Construction de la sous-chaîne et vérification des doublons
        for (size_t j = i; j < i + SOUS_CHAINE_LEN; ++j) {
            sous_chaine[index] = chaine[j];

            // Comparaison avec tous les caractères précédents
            for (size_t h = 0; h < index; ++h) {
                if (sous_chaine[h] == sous_chaine[index]) {
                    doublons = true;
                    break; // On sort dès qu'un doublon est trouvé
                }
            }

            if (doublons) break;
            ++index;
        }

        if (!doublons) {
            chaine_correct = true;
            break; // Sortie anticipée si sous-chaîne valide trouvée
        }
    }

    if (!chaine_correct) {
        printf("Aucune chaîne trouvée\n");
    }
}

void method2(const char* chaine, size_t longueur) {
    /*
    Méthode 2 - Optimisation avec masque binaire

    Révolution par rapport à la méthode 1 :
    Au lieu de comparer physiquement les caractères, on utilise un entier comme tableau de bits
    où chaque bit représente la présence d'une lettre (a=bit0, z=bit25).

    Avantages :
    - Suppression de la troisième boucle (h)
    - Vérification des doublons en O(1) via opérations bit à bit
    - Complexité réduite à O(n*m) soit O(n*14)

    Nouveautés ajoutées :
    - Vérification des caractères hors [a-z] (shift < 0 || shift >= 26)
    - Variable 'found' pour sortir rapidement en cas de doublon
    */
    const size_t max_i = longueur - SOUS_CHAINE_LEN;

    for (size_t i = 0; i <= max_i; ++i) {
        unsigned int sous_chaine = 0; // Masque de 32 bits (suffisant pour 26 lettres)
        bool found = true;

        for (size_t j = i; j < i + SOUS_CHAINE_LEN; ++j) {
            const char c = chaine[j];
            const int shift = c - 'a'; // Conversion caractère -> index bit (0-25)

            // Protection contre les caractères non minuscules
            if (shift < 0 || shift >= 26 || (sous_chaine & (1 << shift))) {
                found = false;
                break; // Caractère invalide ou déjà vu
            }
            sous_chaine |= (1 << shift); // Marque le bit correspondant au caractère
        }

        if (found) {
            return; // Sous-chaîne valide trouvée, sortie immédiate
        }
    }
    printf("Aucune chaîne trouvée\n");
}

void method3(const char* chaine, size_t longueur) {
    /*
    Méthode 3 - Fenêtre glissante optimisée

    Approche radicalement différente :
    Au lieu de réinitialiser la recherche à chaque position, on maintient une fenêtre dynamique.

    Principe clé :
    Quand on trouve un doublon, on déplace le début de la fenêtre juste après la première occurrence
    du caractère en conflit, plutôt que de recommencer à i+1.

    Optimisations majeures :
    - Complexité réduite à O(n) dans le meilleur cas
    - Pas de recalcul inutile des positions déjà vérifiées
    - Gestion intelligente des chevauchements

    Points techniques :
    - Mise à jour dynamique du masque binaire
    - Gestion des caractères hors [a-z] (réinitialisation complète)
    - Vérification de la validité de l'index final
    */
    size_t index = 0;
    unsigned int sous_chaine = 0;
    const size_t max_valid_index = longueur - SOUS_CHAINE_LEN;

    for (size_t i = 0; i < longueur; ++i) {
        const char c = chaine[i];
        const int shift = c - 'a';

        // Réinitialisation si caractère non valide
        if (shift < 0 || shift >= 26) {
            index = i + 1;
            sous_chaine = 0;
            continue;
        }

        // Élimination des caractères conflictuels
        while (sous_chaine & (1 << shift)) {
            const char prev_c = chaine[index++];
            const int prev_shift = prev_c - 'a';
            sous_chaine &= ~(1 << prev_shift); // Retire le caractère sortant
        }

        sous_chaine |= (1 << shift); // Ajoute le nouveau caractère

        // Vérification de la taille de la fenêtre
        if (i - index + 1 == SOUS_CHAINE_LEN) {
            if (index > max_valid_index) break; // Dernières positions impossibles
            return; // Sous-chaîne valide trouvée
        }
    }
    printf("Aucune chaîne trouvée\n");
}