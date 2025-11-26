#include <chrono>
#include <random>
#include <iostream>
#include <format>
#include <SFML/Graphics.hpp>

#include "MundoJogo.h"

MundoJogo::MundoJogo( Bolinha bolinha, sf::Font fonte )
    :
    bolinhaEmArraste( nullptr ),
    delta( 0 ),
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

void MundoJogo::tratarEventos( sf::Event &event ) {

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
        this->gravidade += 100 * event.mouseWheelScroll.delta;
    }

    for ( int i = this->bolinhas.size() - 1; i >= 0; i-- ) {
        bolinhas[i].tratarEventos( event, this );
    }

}

void MundoJogo::atualizar( float delta, sf::Window &window ) {

    this->delta = delta;

    for ( Bolinha &bolinha : this->bolinhas ) {
        bolinha.atualizar( delta, this->gravidade, window );
    }

    textoFPS.setString( std::format( "FPS: {:.2f}", 1.0f / delta ) );
    textoDelta.setString( std::format( "Delta: {:.3f}", delta ) );
    textoGravidade.setString( std::format( "Gravidade: {:.2f}", this->gravidade ) );

}

void MundoJogo::desenhar( sf::RenderWindow &window ) {

    for ( Bolinha &bolinha : this->bolinhas ) {
        bolinha.desenhar( window, this->fonte );
    }

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

float MundoJogo::getDelta() {
    return this->delta;
}