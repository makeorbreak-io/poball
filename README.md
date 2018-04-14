#P@o Ball

## Libraries
 - SFML
 - Box2D

## Compiling
    g++ -lsfml-window -lsfml-graphics -lsfml-system -lBox2D -o duck duck.cpp

## Status
 * Simple duck and ball generation. (Ducks are generated for every mouse click where X coordinate bigger than 100, balls for every mouse click smaller than 100)
 * Physics should be close to done, might need some adjusting to the duck circle radius.
