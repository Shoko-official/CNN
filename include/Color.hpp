#pragma once
#include <string_view>
using namespace std;

namespace ConsoleColor {
    constexpr string_view NOIR    = "\033[30m";
    constexpr string_view ROUGE   = "\033[31m";
    constexpr string_view VERT    = "\033[32m";
    constexpr string_view JAUNE   = "\033[33m";
    constexpr string_view BLEU    = "\033[34m";
    constexpr string_view MAGENTA = "\033[35m";
    constexpr string_view CYAN    = "\033[36m";
    constexpr string_view BLANC   = "\033[37m";

    constexpr string_view NOIR_CLAIR    = "\033[90m";
    constexpr string_view ROUGE_CLAIR   = "\033[91m";
    constexpr string_view VERT_CLAIR    = "\033[92m";
    constexpr string_view JAUNE_CLAIR   = "\033[93m";
    constexpr string_view BLEU_CLAIR    = "\033[94m";
    constexpr string_view MAGENTA_CLAIR = "\033[95m";
    constexpr string_view CYAN_CLAIR    = "\033[96m";
    constexpr string_view BLANC_CLAIR   = "\033[97m";

    constexpr string_view RESET      = "\033[0m";
    constexpr string_view GRAS       = "\033[1m";
    constexpr string_view FAIBLE     = "\033[2m";
    constexpr string_view ITALIQUE   = "\033[3m";
    constexpr string_view SOULIGNE   = "\033[4m";
    constexpr string_view CLIGNOTANT = "\033[5m";
    constexpr string_view INVERSE    = "\033[7m";
    constexpr string_view CACHE      = "\033[8m";
    constexpr string_view BARRE      = "\033[9m";

    constexpr string_view FOND_NOIR    = "\033[40m";
    constexpr string_view FOND_ROUGE   = "\033[41m";
    constexpr string_view FOND_VERT    = "\033[42m";
    constexpr string_view FOND_JAUNE   = "\033[43m";
    constexpr string_view FOND_BLEU    = "\033[44m";
    constexpr string_view FOND_MAGENTA = "\033[45m";
    constexpr string_view FOND_CYAN    = "\033[46m";
    constexpr string_view FOND_BLANC   = "\033[47m";

    constexpr string_view FOND_NOIR_CLAIR    = "\033[100m";
    constexpr string_view FOND_ROUGE_CLAIR   = "\033[101m";
    constexpr string_view FOND_VERT_CLAIR    = "\033[102m";
    constexpr string_view FOND_JAUNE_CLAIR   = "\033[103m";
    constexpr string_view FOND_BLEU_CLAIR    = "\033[104m";
    constexpr string_view FOND_MAGENTA_CLAIR = "\033[105m";
    constexpr string_view FOND_CYAN_CLAIR    = "\033[106m";
    constexpr string_view FOND_BLANC_CLAIR   = "\033[107m";
}
