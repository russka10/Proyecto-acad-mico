#include"Enemigo.h"
#include"Jugador.h"

Enemigo::Enemigo(){
	
}

Enemigo::~Enemigo(){
	
	 
} 

/*void Enemigo::checkColl(Bullet bullet) {
        if (bullet.getRight() > enemy.getPosition().x &&
            bullet.getTop() < enemy.getPosition().y + enemy.getSize().y
            && bullet.getBottom() > enemy.getPosition().y) {
            enemy.setPosition(sf::Vector2f(4234432, 4234423));
        }
    }*/

bool Enemigo::colisionEnemigo(Jugador ju1){

return enemy.getGlobalBounds().intersects(ju1.coli());

}

Enemigo::Enemigo(Vector2f tam, sf::Color color){ 

enemy.setSize(tam);
enemy.setFillColor(color);

}

void Enemigo::mostrar(RenderWindow &window){

window.draw(enemy);

}

void Enemigo::move(Vector2f distance){

enemy.move(distance);

}

void Enemigo::setPos(Vector2f newPos){

enemy.setPosition(newPos);

}

int Enemigo::getY(){

return enemy.getPosition().y;

}

int Enemigo::getX(){

return enemy.getPosition().x;

}

int Enemigo::getSizeY(){
	
return enemy.getSize().y;

}

void Enemigo::setOrigin(Vector2f _origin){

enemy.setOrigin(_origin);

}

void Enemigo::update(){
	
enemy.setPosition(enemy.getPosition());

}
 

FloatRect Enemigo::coliE(){

return enemy.getGlobalBounds(); 
	
}

bool Enemigo::colision2(Plataforma p2){

return enemy.getGlobalBounds().intersects(p2.pcoli());

}
 
