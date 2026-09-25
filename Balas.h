#pragma once

#include <SFML/Graphics.hpp>
 
using namespace sf;

class Bala {
	
	private:
    
	RectangleShape bala;
	RectangleShape balon;
    
    public:
    	
	Bala();
    Bala(Vector2f size);
	void Balon(Color color);
    int getRight();
    int getLeft();
    void move(Vector2f distance);
  	void fire(int speed);
    void mostrar(RenderWindow &window);
 	void setPos(Vector2f newPos);
 	void setSize(Vector2f size2);
    
};


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
 	Texture tbala;
 	tbala.loadFromFile("img/bala.png");
     
	bala.setTexture(&tbala);
    
	window.draw(bala);

}

void Bala::setPos(Vector2f newPos){

    bala.setPosition(newPos);

}
