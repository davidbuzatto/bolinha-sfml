#include <SFML/Graphics.hpp>

#include "Bolinha.h"
#include "MundoJogo.h"

Bolinha::Bolinha( float x, float y, float raio, sf::Color cor, float vx, float vy )
    : 
    x( x ), 
    y( y ), 
    raio( raio ), 
    cor( cor ),
    vx( vx ), 
    vy( vy ),
    atrito( 0.99 ),
    elasticidade( 0.9 ),
    arrastando( false ),
    xa( 0 ),
    ya( 0 ),
    xOffset( 0 ),
    yOffset( 0 ) {
    
}

void Bolinha::tratarEventos( sf::Event &event, MundoJogo *mj ) {

    if ( mj->getBolinhaEmArraste() == nullptr ) {

        if ( event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left ) {

            float x = event.mouseButton.x;
            float y = event.mouseButton.y;

            float c1 = x - this->x;
            float c2 = y - this->y;

            if ( c1 * c1 + c2 * c2 <= this->raio * this->raio ) {
                this->arrastando = true;
                this->xOffset = c1;
                this->yOffset = c2;
                mj->setBolinhaEmArraste( this );
            }

        }
        
    }

    if ( event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left ) {
        this->arrastando = false;
        mj->setBolinhaEmArraste( nullptr );
    }

    if ( event.type == sf::Event::MouseMoved ) {

        if ( this->arrastando ) {

            this->x = event.mouseMove.x - this->xOffset;
            this->y = event.mouseMove.y - this->yOffset;

            this->vx = ( this->x - this->xa ) / mj->getDelta();
            this->vy = ( this->y - this->ya ) / mj->getDelta();

            this->xa = this->x;
            this->ya = this->y;

        }

    }

}

void Bolinha::atualizar( float delta, float gravidade, sf::Window &window ) {

    if ( !this->arrastando ) {

        this->x += this->vx * delta;
        this->y += this->vy * delta;

        if ( this->x + this->raio > window.getSize().x ) {
            this->x = window.getSize().x - this->raio;
            this->vx = -this->vx * this->elasticidade;
        } else if ( this->x - this->raio < 0 ) {
            this->x = this->raio;
            this->vx = -this->vx * this->elasticidade;
        }

        if ( this->y + this->raio > window.getSize().y ) {
            this->y = window.getSize().y - this->raio;
            this->vy = -this->vy * this->elasticidade;
        } else if ( this->y - this->raio < 0 ) {
            this->y = this->raio;
            this->vy = -this->vy * this->elasticidade;
        }

        this->vx = this->vx * this->atrito;
        this->vy = this->vy * this->atrito + gravidade * delta;

    }

}

void Bolinha::desenhar( sf::RenderWindow &window, sf::Font &fonte ) {

    sf::CircleShape shape( this->raio );
    
    shape.setFillColor( this->cor );
    shape.setOrigin( this->raio, this->raio );
    shape.setPosition( this->x, this->y );

    window.draw( shape );
    
}