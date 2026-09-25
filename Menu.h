#include"SFML\Graphics.hpp"
#include <SFML/Audio.hpp>

#include<iostream> 
#include <time.h>
#include <string>

using namespace sf;
using namespace std;


class Menu{
	
	
	public:
	
		 
        
        
		Menu();
		void cargarMenu();
	//	void presionarE(RenderWindow &window);
	    void MenuPrincipal(RenderWindow &window);
		void MenuInformacion(RenderWindow &window);
	
};

Menu::Menu(){
}

void Menu::cargarMenu(){
 
	
}

void Menu::MenuPrincipal(RenderWindow &window){
	
	Texture fondo_menu;
	Sprite 	pfondo_menu;
	
	fondo_menu.loadFromFile ( "img/menu/menu.png");
	pfondo_menu.setTexture		( fondo_menu );
	window.draw(pfondo_menu);
}

void Menu::MenuInformacion(RenderWindow &window){
	
	Texture fondo_info;
	Sprite 	pfondo_info;
	
	fondo_info.loadFromFile ( "img/menu/credits.png");
	pfondo_info.setTexture		( fondo_info );
	window.draw(pfondo_info);
}

/*void Menu::presionarE(RenderWindow &window){
		
		Clock clock;		
		Vector2i boton_pres;
		bool hola=true;
		Texture presionar;
		Sprite 	ppresionar;	
		  
		 
		
		 
	presionar.loadFromFile  ( "img/boton/ppresionar.png" );
	ppresionar.setTexture		( presionar  );
	ppresionar.setPosition		(	170, 470	 );
	
	  
	 
	 
	 
	window.draw(ppresionar);
}*/
