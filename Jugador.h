#include"Plataforma.h"

 


#include"SFML\Graphics.hpp"
#include<iostream>


using namespace sf;
using namespace std;

class Jugador{
	
	private:
		
		RectangleShape player;
		float gravity;
    	Vector2f velocity;
    	float moveSpeed; 
		float jumpSpeed;
		bool saltar = true;
		
	public:
		
		Jugador();
		Jugador(Vector2f tam,sf::Color color);
		~Jugador();
		
		void mostrar(RenderWindow &window);
		void move(Vector2f distance);
		void setPos(Vector2f newPos);
		void setOrigin(Vector2f _origin);
		void update();
		void show();
		
		//bool colision(Jugador j1);
		bool colision2(Plataforma p2);
	 	 
		FloatRect coli();
		
		int getX();
		int getSizeY(); 
		int getY();
};


 
Jugador::Jugador(){
	
}

Jugador::~Jugador(){
	
	  
} 

Jugador::Jugador(Vector2f tam, sf::Color color){ 

player.setSize(tam);
player.setFillColor(color);

}

void Jugador::mostrar(RenderWindow &window){

window.draw(player);

}

void Jugador::move(Vector2f distance){

player.move(distance);

}

void Jugador::setPos(Vector2f newPos){

player.setPosition(newPos);

}



int Jugador::getY(){

return player.getPosition().y;

}

int Jugador::getX(){

return player.getPosition().x;

}

int Jugador::getSizeY(){
	
return player.getSize().y;

}

void Jugador::setOrigin(Vector2f _origin){

player.setOrigin(_origin);

}

void Jugador::update(){
	
player.setPosition(player.getPosition());

}
 

FloatRect Jugador::coli(){

return player.getGlobalBounds(); 
	
}

bool Jugador::colision2(Plataforma p2){

return player.getGlobalBounds().intersects(p2.pcoli());

}

/*bool Jugador::colisionEnemigo(Enemigo e1){

return player.getGlobalBounds().intersects(e1.coliE());

}*/


/////////////////////////////////////////////////////////////
// 	ESTO VA EN "COLISIONES PLATAFORMAS" SUPONIENDO QUE VA A SER
// 	LA COLISION GAMEOVER DE JUGADOR A ENEMIGO, LO PONGO ACA
// 	PARA NO TENER TANTO ESPACIO EN EL MAIN, FUNCIONA OK
// 	PRECISA UNA VARIABLE BOOL GAMEOVER = FALSE; Y COLOCARLA
// 	EN EL IF DE LA COLISION, EL WHILE SE ENCARGA DE TODO
//	
//	if(player.colision2(plataformanueva)){
//	 	
//		 	if( player.getX() < plataformanueva.getX()){
//		 		player.move({-moveSpeed+CORRECION,0});  
//		 		cout<<"COLISIONA: PLATAFORMA Roja (PlataformaNueva)"<<endl;
//		 	//	hola=false;
//		 	//	chau=true;
//		 	//gameover=true;
//			 } 
//		 }
//		 
//		/* while(gameover==true){ 		GAME OVER ACTUALMENTE SIRVE
//		 	window.clear();
//		 	window.draw(sprite_perdio);
//		 	
//		 	if(Keyboard::isKeyPressed(Keyboard::C)){
//		 	 cout<<"se apaga"<<endl; 
//		 	 return 0;
//		 	 window.close();
//			 }
//		 	window.display();
//		 }*/
//
// EL BOOL HOLA Y CHAU SON LOS IA DE LOS ENEMIGOS
// HOLA= IA_IZQUIERDA (SE MUEVE SOLO A LA IZQUIERDA SI COLISIONA CON
// LA PLATAFORMA ETC.	 
/////////////////////////////////////////////////////////////
 
