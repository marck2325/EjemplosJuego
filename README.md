# Turbo Racing
Descripción del Juego de Carreras

El juego es un simulador de carreras en tercera persona. El jugador controla un auto que puede moverse de izquierda a derecha para evitar obstáculos y recolectar bidones de gasolina. Hay tres tipos de obstáculos:

      Bidones de gasolina: sumarán 20 puntos al puntaje cada vez que los toques.
      Carros azules: restarán 20 puntos al puntaje si los chocas.
      Carros rojos: te harán perder la partida al chocar con ellos.
Cuando pierdes, aparecerá un mensaje de "Game Over" y podrás reiniciar la partida presionando la tecla R.                                      

                                        ¡Buena suerte en tu carrera!

El proyecto esta desarrollado sobre MinGW64 utilizando Msys2
y como editor se esta utilizando Visual Studio Code

## Como ejecutar el juego:

Instalar todas las dependencias descritas abajo y dentro de una terminal de vscode ejecutar:

> make run

## Programas necesarios

### Visual estudio code
Descargar e instalar vscode en el siguiente [Enlace.](https://code.visualstudio.com/)

### MSYS2 (Windows)

Instalar Msys2 usando el siguiente [Enlace.](https://github.com/msys2/msys2-installer/releases/download/2023-05-26/msys2-x86_64-20230526.exe)

No modificar ningua opcion al momento de intalacion o podrian variar las configuraciones.

Una vez instalado es necesario agregar los siguientes directorios al path de windows y reiniciar.

> C:\msys64\mingw64\bin

> C:\msys64\usr\bin

### Github Desktop
Cliente de escritorio para clonar el repositorio, descargar usando el siguiente [enlace](https://desktop.github.com/).

### Git
Para poder realizar commits de vscode es necesario tener instalado Git, descargarlo del siguiente [enlace](https://git-scm.com/).


## Librerias utilizadas (Msys2)

Ejecutar los siguientes comandos en la terminal de msys2 para instalar las dependencias necesarias

### DevTools
Compiladores y herramientas necesarias para el desarrollo.

https://code.visualstudio.com/docs/cpp/config-mingw
> pacman -S --needed base-devel mingw-w64-x86_64-toolchain

### SFML
https://packages.msys2.org/package/mingw-w64-x86_64-sfml
> pacman -S mingw-w64-x86_64-sfml

### Box2D simulaciones de fisica - C++
https://box2d.org/documentation/
https://packages.msys2.org/package/mingw-w64-x86_64-box2d?repo=mingw64
pacman -S mingw-w64-x86_64-box2d

## Complementos necesarios VSCode

- Material Icon
- C/C++
- PlantUML
- GitGraph
![gameOver.png](assets/images/gameOverturbo.png)
