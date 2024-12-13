# Directorios de origen y destino
SRC_DIR := src
BIN_DIR := bin
INCLUDE_DIR := include

# Librerías de SFML
SFML := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d

# Archivos fuente y objeto
CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(CPP_FILES:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)

# Nombre del ejecutable final
EXEC := $(BIN_DIR)/juego

# Crear el directorio de binarios si no existe
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Regla para compilar los archivos .cpp en archivos .o
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BIN_DIR)
	g++ -c $< -o $@ -I$(INCLUDE_DIR)

# Regla para enlazar los archivos .o y generar el ejecutable
$(EXEC): $(OBJ_FILES)
	g++ $^ -o $@ $(SFML)

# Regla para compilar todo el proyecto
all: $(EXEC)

# Regla para ejecutar el ejecutable
run: $(EXEC)
	./$(EXEC)

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJ_FILES) $(EXEC)

.PHONY: all clean run
