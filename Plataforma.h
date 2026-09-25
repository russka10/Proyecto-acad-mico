#pragma once

#include <SFML/Graphics.hpp>
 
using namespace sf;

 
class Plataforma{

	private:
    	
		RectangleShape rect;
  		Vector2f size;
   		Vector2i position;
	
	public: 
    	
		Plataforma();
		Plataforma(Vector2f tam, Color color);
		
    	void mostrarPlataforma(RenderWindow &window);
    	void setPos(Vector2f pos);
    	//void up();
    	//void down();
    	//void left();
    	//void right();
    	
		int getY();
    	int getX();
    	int getSX();
    	int getSY();
    	
		FloatRect pcoli();
    	
		~Plataforma();
	 
};

Plataforma::Plataforma(){
	
}

Plataforma::Plataforma(Vector2f tam, Color color){
	rect.setSize(tam);
	rect.setFillColor(color);
	
}

/*void Plataforma::up(){
	rect.setSize(Vector2f(1024,4));
	rect.setFillColor(Color::Green);
}

void Plataforma::down(){
	rect.setSize(Vector2f(1024,20));
	rect.setFillColor(Color::Green); 
	rect.setPosition(0,716);
	rect.setOrigin(0,0);
}

void Plataforma::left(){
	rect.setSize(Vector2f(4,720)); 
	rect.setFillColor(Color::Green);
	rect.setOrigin(0,0);
}

void Plataforma::right(){
	rect.setSize(Vector2f(4,720));  
	rect.setFillColor(Color::Green);
	rect.setOrigin(0,0);
	rect.setPosition(1020,0);
}*/

void Plataforma::mostrarPlataforma(RenderWindow &window){
 	window.draw(rect);
 }
 
Plataforma::~Plataforma(){
	
 
	
}

void Plataforma::setPos(Vector2f pos){

rect.setPosition(pos);

}

int Plataforma::getY(){

return rect.getPosition().y;

}

int Plataforma::getX(){
	return rect.getPosition().x;
}

int Plataforma::getSX(){
	return rect.getSize().x;
}

int Plataforma::getSY(){
	return rect.getSize().y;
}

FloatRect Plataforma::pcoli(){
	return rect.getGlobalBounds(); 
	
}
