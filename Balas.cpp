#include"Balas.h"

void Bala::Balon(Color color){
	bala.setFillColor(color);
}


Bala::Bala(Vector2f size) {
  
    bala.setSize(size);
     

} 

void Bala::setSize(Vector2f size2){
	bala.setSize(size2);
}
 
void Bala::move(Vector2f distance){

bala.move(distance);

}

int Bala::getRight(){
 
 	return bala.getPosition().x + bala.getSize().x;

}
    
int Bala::getLeft(){

    return bala.getPosition().x;

}
    
void Bala::mostrar(RenderWindow &window){
 	Texture hola;
 	hola.loadFromFile("img/bala.png");
     
	bala.setTexture(&hola);
    
	window.draw(bala);

}

void Bala::setPos(Vector2f newPos){

    bala.setPosition(newPos);

}
