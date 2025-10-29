CC = g++
CFLAGS = -I./include -Wall -Wextra -std=c++11
SRCDIR = src
BUILDIR = build
OBJDIR = $(BUILDIR)/obj
TARGET = $(BUILDIR)/alexnet

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPS := $(OBJECTS:.o=.d)

# Cibles par défaut
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(OBJECTS) | $(BUILDIR)
	$(CC) $(OBJECTS) -o $(TARGET)

# Compilation des fichiers objets avec génération des dépendances
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Création automatique des dossiers
$(BUILDIR) $(OBJDIR):
	mkdir -p $@

# Nettoyage
clean:
	rm -rf $(BUILDIR)

# Debug
debug: CFLAGS += -g
debug: clean all

# Lancer le programme
run: $(TARGET)
	./$(TARGET)

# Inclusion automatique des fichiers de dépendances
-include $(DEPS)

.PHONY: all clean run debug