#pragma once
#include <string_view>

namespace ConsoleColor {
    constexpr std::string_view NOIR    = "\033[30m";
    constexpr std::string_view ROUGE   = "\033[31m";
    constexpr std::string_view VERT    = "\033[32m";
    constexpr std::string_view JAUNE   = "\033[33m";
    constexpr std::string_view BLEU    = "\033[34m";
    constexpr std::string_view MAGENTA = "\033[35m";
    constexpr std::string_view CYAN    = "\033[36m";
    constexpr std::string_view BLANC   = "\033[37m";

    constexpr std::string_view NOIR_CLAIR    = "\033[90m";
    constexpr std::string_view ROUGE_CLAIR   = "\033[91m";
    constexpr std::string_view VERT_CLAIR    = "\033[92m";
    constexpr std::string_view JAUNE_CLAIR   = "\033[93m";
    constexpr std::string_view BLEU_CLAIR    = "\033[94m";
    constexpr std::string_view MAGENTA_CLAIR = "\033[95m";
    constexpr std::string_view CYAN_CLAIR    = "\033[96m";
    constexpr std::string_view BLANC_CLAIR   = "\033[97m";

    constexpr std::string_view RESET      = "\033[0m";
    constexpr std::string_view GRAS       = "\033[1m";
    constexpr std::string_view FAIBLE     = "\033[2m";
    constexpr std::string_view ITALIQUE   = "\033[3m";
    constexpr std::string_view SOULIGNE   = "\033[4m";
    constexpr std::string_view CLIGNOTANT = "\033[5m";
    constexpr std::string_view INVERSE    = "\033[7m";
    constexpr std::string_view CACHE      = "\033[8m";
    constexpr std::string_view BARRE      = "\033[9m";

    constexpr std::string_view FOND_NOIR    = "\033[40m";
    constexpr std::string_view FOND_ROUGE   = "\033[41m";
    constexpr std::string_view FOND_VERT    = "\033[42m";
    constexpr std::string_view FOND_JAUNE   = "\033[43m";
    constexpr std::string_view FOND_BLEU    = "\033[44m";
    constexpr std::string_view FOND_MAGENTA = "\033[45m";
    constexpr std::string_view FOND_CYAN    = "\033[46m";
    constexpr std::string_view FOND_BLANC   = "\033[47m";

    constexpr std::string_view FOND_NOIR_CLAIR    = "\033[100m";
    constexpr std::string_view FOND_ROUGE_CLAIR   = "\033[101m";
    constexpr std::string_view FOND_VERT_CLAIR    = "\033[102m";
    constexpr std::string_view FOND_JAUNE_CLAIR   = "\033[103m";
    constexpr std::string_view FOND_BLEU_CLAIR    = "\033[104m";
    constexpr std::string_view FOND_MAGENTA_CLAIR = "\033[105m";
    constexpr std::string_view FOND_CYAN_CLAIR    = "\033[106m";
    constexpr std::string_view FOND_BLANC_CLAIR   = "\033[107m";
}