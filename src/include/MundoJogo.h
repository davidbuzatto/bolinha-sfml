#pragma once

#include <chrono>
#include <random>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Bolinha.h"

class MundoJogo {

    std::vector<Bolinha> bolinhas;
    Bolinha *bolinhaEmArraste;

    float gravidade;

    sf::Font fonte;
    sf::Text textoFPS;
    sf::Text textoDelta;
    sf::Text textoGravidade;

    std::mt19937 gerador;
    std::uniform_int_distribution<int> distRaio{ 0, 30 };
    std::uniform_int_distribution<int> distVel{ 0, 100 };
    std::uniform_int_distribution<int> dist01{ 0, 1 };
    std::uniform_int_distribution<int> distRGBA{ 0, 255 };

public:
    MundoJogo( Bolinha bolinha, sf::Font fonte );
    void tratarEventos( sf::Event &event, float delta );
    void atualizar( float delta, sf::Window &window );
    void desenhar( sf::RenderWindow &window );
    void adicionarBolinha( float x, float y, float raio, sf::Color cor, float vx, float vy );
    void setBolinhaEmArraste( Bolinha *bolinhaEmArraste );
    Bolinha* getBolinhaEmArraste() const;
    
};