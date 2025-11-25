#include <chrono>
#include <random>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "MundoJogo.h"

MundoJogo::MundoJogo( Bolinha bolinha, sf::Font fonte )
    :
    bolinhaEmArraste( nullptr ),
    gravidade( 2000 ),
    fonte( fonte ),
    gerador( std::chrono::system_clock::now().time_since_epoch().count() ) {

    this->bolinhas.push_back( bolinha );

    textoFPS.setFont( this->fonte );
    textoFPS.setCharacterSize( 20 );
    textoFPS.setFillColor( sf::Color::Black );
    textoFPS.setPosition( 10, 10 );

    textoDelta.setFont( this->fonte );
    textoDelta.setCharacterSize( 20 );
    textoDelta.setFillColor( sf::Color::Black );
    textoDelta.setPosition( 10, 30 );

    textoGravidade.setFont( this->fonte );
    textoGravidade.setCharacterSize( 20 );
    textoGravidade.setFillColor( sf::Color::Black );
    textoGravidade.setPosition( 10, 50 );

}

void MundoJogo::tratarEventos( sf::Event &event, float delta ) {

    if ( event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right ) {

        this->adicionarBolinha( 
            event.mouseButton.x, 
            event.mouseButton.y,
            20 + this->distRaio( this->gerador ), 
            sf::Color( this->distRGBA( this->gerador ), this->distRGBA( this->gerador ), this->distRGBA( this->gerador ) ),
            ( 100 + this->distVel( this->gerador ) ) * ( this->dist01( this->gerador ) == 0 ? -1 : 1 ), 
            ( 100 + this->distVel( this->gerador ) ) * ( this->dist01( this->gerador ) == 0 ? -1 : 1 )
        );
    }
    
    if ( event.type == sf::Event::MouseWheelScrolled ) {
        this->gravidade += 100 * ( event.mouseWheelScroll.delta > 0 ? -1 : 1 );
    }

    for ( int i = this->bolinhas.size() - 1; i >= 0; i-- ) {
        bolinhas[i].tratarEventos( event, this, delta );
    }

}

void MundoJogo::atualizar( float delta, sf::Window &window ) {

    for ( Bolinha &bolinha : this->bolinhas ) {
        bolinha.atualizar( delta, this->gravidade, window );
    }

    std::stringstream ss;

    ss << "FPS: " << std::fixed << std::setprecision( 2 ) << ( 1.0f / delta );
    textoFPS.setString( ss.str() );

    ss.str( "" );
    ss.clear();

    ss << "Delta: " << std::fixed << std::setprecision( 3 ) << delta;
    textoDelta.setString( ss.str() );

}

void MundoJogo::desenhar( sf::RenderWindow &window ) {

    for ( Bolinha &bolinha : this->bolinhas ) {
        bolinha.desenhar( window, this->fonte );
    }

    std::stringstream ss;
    ss << "Gravidade: " << std::fixed << std::setprecision( 2 ) << this->gravidade;
    textoGravidade.setString( ss.str() );

    window.draw( textoFPS );
    window.draw( textoDelta );
    window.draw( textoGravidade );

}

void MundoJogo::adicionarBolinha( float x, float y, float raio, sf::Color cor, float vx, float vy ) {
    this->bolinhas.emplace_back( x, y, raio, cor, vx, vy );
}

void MundoJogo::setBolinhaEmArraste( Bolinha *bolinhaEmArraste ) {
    this->bolinhaEmArraste = bolinhaEmArraste;
}

Bolinha* MundoJogo::getBolinhaEmArraste() const {
    return this->bolinhaEmArraste;
}