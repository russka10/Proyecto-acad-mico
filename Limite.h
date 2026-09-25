#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

 
class Limite{

	private:
    	RectangleShape rect;
  		Vector2f _size;
   		Vector2f _pos;
   		
	
	public: 
		Limite();
    	Limite(Vector2f size);
    	
		void mostrarLimite(RenderWindow &window);
	    void setPos(Vector2f pos);
    	
    	int getX();
    	int getY();
    	int getSX();
    	int getSY();
  
		~Limite();
	
};

Limite::Limite(Vector2f size){
	rect.setSize(size);
	rect.setFillColor(Color::Blue);

}

void Limite::setPos(Vector2f newPos){
	rect.setPosition(newPos);

} 
 
Limite::~Limite(){
	
	
	
}

Limite::Limite(){

}

void Limite::mostrarLimite(RenderWindow &window){
	window.draw(rect);

}
 	 
int Limite::getX(){
	return rect.getPosition().x;

} 

int Limite::getY(){
	return rect.getPosition().y;

} 

int Limite::getSX(){
	return rect.getSize().x;

} 

int Limite::getSY(){
	return rect.getSize().y;

} 


