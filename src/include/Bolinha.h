#pragma once 

#include <SFML/Graphics.hpp>

class MundoJogo;

class Bolinha {

    float x;
    float y;
    float raio;

    sf::Color cor;

    float vx;
    float vy;
    float atrito;
    float elasticidade;
    bool arrastando;

    float xa;
    float ya;
    float xOffset;
    float yOffset;

public:
    Bolinha( float x, float y, float raio, sf::Color cor, float vx, float vy );
    void tratarEventos( sf::Event &event, MundoJogo *mj, float delta );
    void atualizar( float delta, float gravidade, sf::Window &window );
    void desenhar( sf::RenderWindow &window, sf::Font &fonte );
    
};