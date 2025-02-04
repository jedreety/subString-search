/*
    Projet de Recherche de sous-cha�nes
    Auteur : Mehdi Mazouz
    Date : 2024

    Ce projet a pour but de r�aliser une recherche optimis�e de sous-cha�nes sans doublons de lettres dans une cha�ne de caract�res donn�e.

    L'objectif de ce projet est de d�velopper un programme en langage C capable de parcourir une cha�ne de caract�res tr�s longue et de trouver,
    de la mani�re la plus optimis�e possible, toutes les sous-cha�nes de longueur 14 qui ne contiennent aucun doublon de lettres.
    Autrement dit, chaque lettre dans la sous-cha�ne doit �tre unique.

    Petite conclusion, un projet assez fun mais qui a demand� beaucoup de r�flexion mais qui s'implemente rapidement.
    Il se peut qu'il existe des m�thodes plus optimis�es

    Ce projet m'a permis d'approfondir mes connaissances sur les bits et les op�rations bit � bit et les structures de donn�es.
	Et de prendre en main la programmation ceci �tant mon premier projet.
    Fun : 7/10
    Difficult� : 5/10 (en programmation sans prendre en compte la reflexion)
    Utilit� : 9/10
*/

#include <stdio.h>
#include <string.h>
#include <time.h>

enum { SOUS_CHAINE_LEN = 14, NB_METHOD = 3, ITERATIONS = 100000 };

typedef enum { false, true } bool;

// M�thode 1 que j'ai impl�ment�e � chaud une sorte de fonction de reference
void method1(const char* chaine, size_t longueur);

// M�thode 2 avec une reflexion plus pouss�e
void method2(const char* chaine, size_t longueur);

// M�thode 3 est une am�lioration de la m�thode 2 un approfondissement de celle-ci
void method3(const char* chaine, size_t longueur);

int main() {

    printf("\n");

    const char chaine[] = "qvllndllhzhfzhhdzhddhjdjggvnvhvccmffwllqgqmmfjfqfhhtrrzczjczzlplddfpptqqfbqffmnmjnnqppfjfccgnnmqqsvvdbbgppjvpjvpjjctjjttwtrrdldlcddrvddqndqnqwqwzwfwwzczggcppgzpzhpzhppprfffbhhwmhhtftstrsrvsrvsrvvshvssnwwpllhfhnnfflcltlblzlqlvqlvlcldcccpptggtdgdjdbbrggmbmnncscbssqrrjddvcvgvfflpppgpvphvphhpcpzpzvvctvctvthtwtfwwbrrhhlplmlwwlqlnlhhtmhmmqlqplllrvrgvrvrffzfgfjfjtjmjvmjmwmvvjffmpfphfhvfvmfvmmhpphhltthgttgccqggpzpfpqpcpvcpvcvvqtqvqbbrlrtllmrmllhmhvmhhvzhvzvrrrzjzbbtvvbgvbbfnnqndqnnpnbnbnlnggwqggmgmqmgmbbmccgqcqbccpvcvnnhvvrvlrrcwrcwrcwrwbrwwzbwbdbfddpttntzzjszsnznbndnzngzgccjrcjchcffmlmqqlrqqzsqzzsbsnsttzpztpzpggzrrttbqqplpqlqjjqcqvccdzdccthccvfcvvqvhqhfhhzwzpzwppgpttntssflfjjrwrqrjrppptlltptpvttpfpwpswpppzzsrzssqllbnlljpllrjllsrlrhrdrmdrmrrpsrprnrffgrffdqdhdqhhrhggwqqlddsbsqbqtqdtdhdvhhbdhdzhdhhtrrppzddgfgzgpzpvpfpnpptggltggbnbppqffzfrzzzsbsrrdgrddwsdsqddhpdpbpvpfvppfsfgfngffzmzbzlblclsccvqvqmmjtjqtjjlcjllsddjqddhldlvlrrbgbrgbrrdzzpfpggqnqbqrrqbbgjgppqgpgwgqqndncndnpdnnbvbnvnwnjjgppzlplqqdgqghqgqzggjssqmmwwcfcpptrpprggrppgbplmzwmdtnpqwzcrthqbppwbgcvgqrpfpnbscnhvrllpvpqwnsslcjrqtvdccprvqfrpswtpvzdzlgtmmvppdmhgdbbsmrbqpqspdhpqgfjznqzphrnggcbzhdqrgvzcfzrhtrlssgmjjghqsjtghhnwjffqrrfslfnsvvdvfjqbfpffrrstdhggvbfwtfpfgswqlfdrnjpjmwzptlbmwgghgwqrphcrvfmhrplllgbnjlprllmjwccphsflntgpnbmdbfqcdsbgvrnfznfrlcfvswqfrqvdnbjsflnsmlcrdstzppmcvbgdtcvgztbdzqbwhmwcfvbwjjcdgbnwjwzrrdqhpgscwtnztjsfstzfwftcldjgvdvwbzrlbdslwttbqpnlwbjcjwqgtrgcglsgtdqbqbnqznptzzbwffwlwzvvtdpcjbvhnswzptclpbndcdvsfmcrmwwgzdfsszqjjdztmtsqgfqzjpctfdpwnzbpnzzwngqnghntblndfrnjzdrmgbqmzbdqfzctrgshwqgfgqssqjltrqlzjswjhmpgwwjdwcjpnsvgrvbfpmlmmwzmbdjwsrjthppfrccjgnmwlvqlprgslbwtbbzlqbznczmsmhsfdcqnwblprcpbzzwfllbnldvpjcwsdhglrzjsptmsjdjqzsmgvhjfjrrtvvbjlmzjsntnrggwbpjlrjggfgqzvswtggthzfmfjnmrzrttbzqpwpsnmdtnbfblpfgslgcmjlbdpshnnrbhvwsbrnvdmjqhvhdjhbfzjmqrmqmdthhzvnrmqcnbtwcdjdqfvdgvmfbhrfqnmdncrddggtcppjlznbsnntppjtnsqsrjwvfrzpnzqcrzhhdflfmmtmwcvtpzbqhdwsczffcqhtdbdjblmgnrmhlqcsvcpgghhvwqhdtzpzlpfllchzltqgcwgfqnbzhgzmdwqdlwnvhqmpqjqnjbhjctslghdqvctdmjfwdfpdjnhdndzwsfjzlmsbmfmzvnvpqgqhtngvgqmlrrzsfmwlcwsscvghjvrzjjqbnplnjzqswpblwzwczhwbhhnjmctnmwlbqqfmnlwdcrptlmfjpjrnpcvmhffjhwhmntdzpdjzwzhrrsdvmjlwdtcpvjfmfzfsrgjghhlvmjjjczgmhvrfpgqbnhldwbrjgzmnszzbssfzcggrwmdfvddwsdmnwtwfwlfnwlvzlctfblbtrjvcwjjdljplcrjhwqslppwwtvfqwsjlfmdznmcdzdmgvmmsrfcclcvhtrhlsjzrbjwrjlfnvqhqvmpzmdttnbhfcvnqlrqbcsvtvwfccjstjpmhqgwlnrzjjmfdszflmglrdbpqhqhqsdfzrcljbdvvnlcqfllmnqcjfzjppdsjwshfschzqbnwfqnpwhqnmwsjbtcgvrljsrtzvcvghcjjlqsngglcggqpntrrhbjpbfhmvpltmnfmfdtwnczwfbvjcqnhvppjftwvwsrlhvvcjtsfptpqgrmrqwwddnqmnmfgrlnphbpqhhhvglqgtwvnwvnbssftmwttmfrffwtzhrpqspclvgchwqwcsgwqwwvpgcwngrcfmhbhflwfbfchlphdzdcrflfmfclsngtlwrqcrsgrdzcpdsvvcdbhgtljmbntbbcqgjqfsbfwzlfsnljpjdcnmjlqrwpmlvwgdlrrdgfhdqhzgltmclzgzzhmrbggsmgtpqdrgmjtlzwstrwbpvhppvsmdqvvwwglzjgdswjszqmrdbmshbhhcstpcsjdbvgjnvcmvhbtclrlmlgnvppgvncsrfchdbqjrclwwlnchmcgvshfsbsvvcvjrsgjlnsfqtqmgntffwnqjtldcqbcqhsgztllstswwqnfrswpchqhnfzzzszqjztzfrgrbjdbjlpvqfqrlrmmpbfbbcclrgmnlzwqrjhqrstswjpgsrtnlwsbqthzpvdzllzqmdmbvvtcztftvlwphhjzbfnrvccfmhmvmzlbrzlnppfzcsffjvjmbgpvlwgwszpztjpsrbnftqtdrbnljtbrjzzbwlsvtwtlwptdtnmtncvcblcmdngjzmctlqtzchncccnwjzrrmmmnllbhrnhwtqjsnvcslrqjfbfndqvdlrjshdzmlprtzbtnhthdqhplwzdbnjmgzlzrbzrvrqnflwfmsmbssqnbcddnvdpltpmplpdzvtjrslcdcnrdplwtjtvctwfzhlvwwqqtbqcjjwhhnpmvgzhqmqfgthwbphrmrtdghchsmwghdqjgjgmpddbrtngtvhqgjfrplrdgpbnhqvswrmqhcmsqvsqmqsgwjndwjrbrhvrctmmrmfwpsgfgdlrzpslpflgvwrgcthgcrnhgrzsmqdgdssjgspfhmqfmjfpmwqhnfjdvqzhpndvnbmqglbrjmdrwgmgctrgzpsdvfbmcstcslblmvnprphntgslmlrqwthrndrhtbccgzzfsglhgqztcsnqjwfzbzlvrpbvswbhrwdsrhrrpnrmsbvbvjccbdsdcfrrzpgwjtnnnvjwlcppwzdqsbdzpfjplrlfgvjpsmbzwpwlghnvqgddfjvrsztrpzlfgmqqzrfcgglghndbhgbmldglclhldljjdslvhzshshtqwhqnbzhvqrcmwdmcmhjcrmdmhrwnwcbhvbbrwrbtfdnztwnbpdfjfhgrmcpngftsvbsmsptnwcvvllnmbnsntbzmwnhfdptbtzswtjzdqwjdhprnjwvhzpscjvlsgrhdrmmrmhzhwwtslzdjqmzfncnmgplhnmwrvqhslvchtjcmpzpjpnpfbjptvvwcsmhgdjtsqrjlfpnfdncpqqmpgpvtlvwljlsqbnhtsqgfwlsmdjpgtvgjvjcrnnzmbllqzlrfdnlffgmtphhhgbcjgdlpzqpwmjwtcmdrsmtnmddftwczbsddtppsptbwfvpnfnsqmsgcfqfmnzffzqgcdvwzrgdwhmnzmrlhcdpdsltnsmjzdqwmmpwvjqbbwsrfgzh";
    const size_t chaine_len = strlen(chaine);
    clock_t times[NB_METHOD];

    // M�thode 1
    times[0] = clock();
    for (int i = 0; i < ITERATIONS; ++i) {
        method1(chaine, chaine_len);
    }
    times[0] = clock() - times[0];

    printf("Temps d'execution pour la methode 1 : %f secondes\n", (double)times[0] / CLOCKS_PER_SEC);

    // M�thode 2
    times[1] = clock();
    for (int i = 0; i < ITERATIONS; ++i) {
        method2(chaine, chaine_len);
    }
    times[1] = clock() - times[1];

    printf("Temps d'execution pour la methode 2 : %f secondes\n", (double)times[1] / CLOCKS_PER_SEC);

    // M�thode 3
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
    M�thode 1 - Approche na�ve avec triple boucle

    Ma pens�e initiale :
    L'id�e est simple : pour chaque position dans la cha�ne, on v�rifie les 14 caract�res suivants.
    Pour chaque sous-cha�ne, on compare chaque caract�re avec tous les pr�c�dents dans la fen�tre.

    La complexit� est O(n*m�) o� m=14, donc O(n*196) ce qui est acceptable pour de petites cha�nes
    mais devient probl�matique sur de tr�s longues cha�nes (comme le montre le temps d'ex�cution).

    Points faibles :
    - Triple boucle imbriqu�e (i, j, h)
    - Recopie inutile de la sous-cha�ne
    - V�rification exhaustive m�me apr�s avoir trouv� un doublon
    */
    bool chaine_correct = false;
    char sous_chaine[SOUS_CHAINE_LEN + 1];
    const size_t max_i = longueur - SOUS_CHAINE_LEN;

    for (size_t i = 0; i <= max_i; ++i) {
        bool doublons = false;
        size_t index = 0;

        // Construction de la sous-cha�ne et v�rification des doublons
        for (size_t j = i; j < i + SOUS_CHAINE_LEN; ++j) {
            sous_chaine[index] = chaine[j];

            // Comparaison avec tous les caract�res pr�c�dents
            for (size_t h = 0; h < index; ++h) {
                if (sous_chaine[h] == sous_chaine[index]) {
                    doublons = true;
                    break; // On sort d�s qu'un doublon est trouv�
                }
            }

            if (doublons) break;
            ++index;
        }

        if (!doublons) {
            chaine_correct = true;
            break; // Sortie anticip�e si sous-cha�ne valide trouv�e
        }
    }

    if (!chaine_correct) {
        printf("Aucune cha�ne trouv�e\n");
    }
}

void method2(const char* chaine, size_t longueur) {
    /*
    M�thode 2 - Optimisation avec masque binaire

    R�volution par rapport � la m�thode 1 :
    Au lieu de comparer physiquement les caract�res, on utilise un entier comme tableau de bits
    o� chaque bit repr�sente la pr�sence d'une lettre (a=bit0, z=bit25).

    Avantages :
    - Suppression de la troisi�me boucle (h)
    - V�rification des doublons en O(1) via op�rations bit � bit
    - Complexit� r�duite � O(n*m) soit O(n*14)

    Nouveaut�s ajout�es :
    - V�rification des caract�res hors [a-z] (shift < 0 || shift >= 26)
    - Variable 'found' pour sortir rapidement en cas de doublon
    */
    const size_t max_i = longueur - SOUS_CHAINE_LEN;

    for (size_t i = 0; i <= max_i; ++i) {
        unsigned int sous_chaine = 0; // Masque de 32 bits (suffisant pour 26 lettres)
        bool found = true;

        for (size_t j = i; j < i + SOUS_CHAINE_LEN; ++j) {
            const char c = chaine[j];
            const int shift = c - 'a'; // Conversion caract�re -> index bit (0-25)

            // Protection contre les caract�res non minuscules
            if (shift < 0 || shift >= 26 || (sous_chaine & (1 << shift))) {
                found = false;
                break; // Caract�re invalide ou d�j� vu
            }
            sous_chaine |= (1 << shift); // Marque le bit correspondant au caract�re
        }

        if (found) {
            return; // Sous-cha�ne valide trouv�e, sortie imm�diate
        }
    }
    printf("Aucune cha�ne trouv�e\n");
}

void method3(const char* chaine, size_t longueur) {
    /*
    M�thode 3 - Fen�tre glissante optimis�e

    Approche radicalement diff�rente :
    Au lieu de r�initialiser la recherche � chaque position, on maintient une fen�tre dynamique.

    Principe cl� :
    Quand on trouve un doublon, on d�place le d�but de la fen�tre juste apr�s la premi�re occurrence
    du caract�re en conflit, plut�t que de recommencer � i+1.

    Optimisations majeures :
    - Complexit� r�duite � O(n) dans le meilleur cas
    - Pas de recalcul inutile des positions d�j� v�rifi�es
    - Gestion intelligente des chevauchements

    Points techniques :
    - Mise � jour dynamique du masque binaire
    - Gestion des caract�res hors [a-z] (r�initialisation compl�te)
    - V�rification de la validit� de l'index final
    */
    size_t index = 0;
    unsigned int sous_chaine = 0;
    const size_t max_valid_index = longueur - SOUS_CHAINE_LEN;

    for (size_t i = 0; i < longueur; ++i) {
        const char c = chaine[i];
        const int shift = c - 'a';

        // R�initialisation si caract�re non valide
        if (shift < 0 || shift >= 26) {
            index = i + 1;
            sous_chaine = 0;
            continue;
        }

        // �limination des caract�res conflictuels
        while (sous_chaine & (1 << shift)) {
            const char prev_c = chaine[index++];
            const int prev_shift = prev_c - 'a';
            sous_chaine &= ~(1 << prev_shift); // Retire le caract�re sortant
        }

        sous_chaine |= (1 << shift); // Ajoute le nouveau caract�re

        // V�rification de la taille de la fen�tre
        if (i - index + 1 == SOUS_CHAINE_LEN) {
            if (index > max_valid_index) break; // Derni�res positions impossibles
            return; // Sous-cha�ne valide trouv�e
        }
    }
    printf("Aucune cha�ne trouv�e\n");
}