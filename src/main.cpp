/**
 * @file main.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Testes SFML - Bolinha
 * 
 * @copyright Copyright (c) 2025
 */

#include <iostream>
#include <optional>
#include <string>
#include <SFML/Graphics.hpp>

#include "Bolinha.h"
#include "MundoJogo.h"

int main() {

    sf::RenderWindow window = sf::RenderWindow( sf::VideoMode({800, 600}), "Testes SFML - Bolinha" );
    window.setFramerateLimit( 60 );

    sf::Clock clock;
    sf::Font fonte;

    if ( !fonte.loadFromFile( "resources/fonts/Consolas.ttf" ) ) {
        std::cerr << "Arquivo de fonte não encontrado!" << std::endl;
        return EXIT_FAILURE;
    }

    Bolinha bolinha{ (float) ( window.getSize().x / 2 ), (float) ( window.getSize().y / 2 ), 50, sf::Color::Blue, 200, 200 };
    MundoJogo mj( bolinha, fonte );

    while ( window.isOpen() ) {

        sf::Event event;
        float delta = clock.restart().asSeconds();

        while ( window.pollEvent( event ) ) {

            if ( event.type == sf::Event::Closed ) {
                window.close();
            }

            mj.tratarEventos( event, delta );

        }

        window.clear( sf::Color::White );

        mj.atualizar( delta, window );
        mj.desenhar( window );

        window.display();

    }

    return EXIT_SUCCESS;

}
