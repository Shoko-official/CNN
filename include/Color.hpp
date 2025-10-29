#pragma once
#include <iostream>

namespace ConsoleColor {
    // Réinitialisation
    const char* RESET = "\033[0m";

    // Couleurs de base
    const char* NOIR = "\033[30m";
    const char* ROUGE = "\033[31m";
    const char* VERT = "\033[32m";
    const char*JAUNE = "\033[33m";
    const char* BLEU = "\033[34m";
    const char* MAGENTA = "\033[35m";
    const char* CYAN = "\033[36m";
    const char* BLANC = "\033[37m";

    // Couleurs claires (bright)
    const char* NOIR_CLAIR = "\033[90m";
    const char* ROUGE_CLAIR = "\033[91m";
    const char* VERT_CLAIR = "\033[92m";
    const char* JAUNE_CLAIR = "\033[93m";
    const char* BLEU_CLAIR = "\033[94m";
    const char* MAGENTA_CLAIR = "\033[95m";
    const char* CYAN_CLAIR = "\033[96m";
    const char* BLANC_CLAIR = "\033[97m";

    // Styles de texte
    const char* GRAS = "\033[1m";
    const char* FAIBLE = "\033[2m";
    const char* ITALIQUE = "\033[3m";
    const char* SOULIGNE = "\033[4m";
    const char* CLIGNOTANT = "\033[5m";
    const char* INVERSE = "\033[7m";
    const char* CACHE = "\033[8m";
    const char* BARRE = "\033[9m";

    // Couleurs de fond
    const char* FOND_NOIR = "\033[40m";
    const char* FOND_ROUGE = "\033[41m";
    const char* FOND_VERT = "\033[42m";
    const char* FOND_JAUNE = "\033[43m";
    const char* FOND_BLEU = "\033[44m";
    const char* FOND_MAGENTA = "\033[45m";
    const char* FOND_CYAN = "\033[46m";
    const char* FOND_BLANC = "\033[47m";

    // Couleurs de fond claires
    const char* FOND_NOIR_CLAIR = "\033[100m";
    const char* FOND_ROUGE_CLAIR = "\033[101m";
    const char* FOND_VERT_CLAIR = "\033[102m";
    const char* FOND_JAUNE_CLAIR = "\033[103m";
    const char* FOND_BLEU_CLAIR = "\033[104m";
    const char* FOND_MAGENTA_CLAIR = "\033[105m";
    const char* FOND_CYAN_CLAIR = "\033[106m";
    const char* FOND_BLANC_CLAIR = "\033[107m";
}