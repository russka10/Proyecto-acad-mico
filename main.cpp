 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 																															//
//Main actualizado 15/11/17 Eric																							//
//											 																				//
//*Mejoras en: FullScreen, menu 		  																					//
//*Faltas en: salto y el setKeyPresed, sprite personaje, array enemigos, boton del menu, creditos							//
//																															//
//Main actualizado 17/11/17 Eric																							//
//																															//
//*Mejoras boton del menu, creditos																							//
//*Faltas en: salto y el setKeyPresed, sprite personaje, array enemigos														//
//																															//
//																															//
//Main actualizado 20/11/17 Eric																							//
//																															//
//Mejoras: Cambio de carpeta, Sonido menu, posicion enemigo vuelve, game over al caer										//
//Faltas en: salto y key, sprite personaje, balas, arrays enemigos															//
// 																															//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 

#include"SFML\Graphics.hpp"
#include <SFML/Audio.hpp>


#include"Limite.h"
#include"Jugador.h"
#include"Enemigo.h"
#include"Plataforma.h"
#include"Menu.h"
#include"Balas.h"


#include <sstream>
#include<iostream> 
#include <time.h>
#include <string>
#include <windows.h> 

using namespace sf;
using namespace std;



int main(){

	//-----------------------------------------------
	//				VARIABLES	
	//-----------------------------------------------
    Event event;

    int CORRECION			= 20; 		//Es para que la colision se vea limpia, si lo saco el objeto golpea constantemente al colisionar (el var pixel hace lo mismo)
	
	const int ALTO			= 800;
	const int ANCHO			= 600;
	const int pared_izq		= 1;
    const int pared_der 	= 1023;
    const int piso	   		= 490;
    const int fps 	    	= 35;
	const float pixel   	= 10;
	float jumpSpeed			= 50;
	float moveSpeed 		= 30;
    float gravitySpeed 		= 0.81;
    
	bool escape				= true;
	bool otro_menu			= true;
    bool saltar 	   	 	= false; 
    bool IA_FULL			= true;
    bool IA_RIGHT			= false;
    bool IA_LEFT			= false;
    bool IA_JUMP			= false;
    bool pantallaCompleta	= true;
    bool piso_GO			= false;
    bool xmarciano			= false;
    bool NPOS				= false;
    
    
	//-----------------------------------------------
	//				SPRITE ANTORCHA	
	//-----------------------------------------------
   
    Clock clock; 			 
    Vector2i source  (0,0); 

	Texture antorcha;
	Texture antorcha2;
	Texture cande;
	
	Sprite antorcha_sprite;  
	Sprite antorcha2_sprite; 
	Sprite pcande;  
	
	antorcha.loadFromFile	( "img/item/antorcha.png" );
	antorcha2.loadFromFile	( "img/item/antorcha.png" );
	cande.loadFromFile		( "img/item/candelario.png" );
	
	antorcha_sprite.setTexture	( antorcha   );
	antorcha2_sprite.setTexture ( antorcha2  );
	pcande.setTexture		    ( cande      );
	
	//-----------------------------------------------
	//				SPRITE FONDO	
	//-----------------------------------------------
 
 	Texture background;  
	Sprite fondo; 
	
	Texture perdio;
	Sprite sprite_perdio;
	
	//				SPRITE GAMEOVER
	perdio.loadFromFile("img/menu/game_over.png");
	sprite_perdio.setTexture(perdio);
	
	//-----------------------------------------------
	//				SPRITE MARCIANO	
	//-----------------------------------------------

	Texture marcianito;
	Sprite pmarcianito; 
		
	marcianito.loadFromFile ( "img/marcianito.png" );
	pmarcianito.setTexture	(     marcianito 	   ); 
	pmarcianito.setColor(Color::Red);

 	//-----------------------------------------------
	//				INSTANCIA SONIDO
	//-----------------------------------------------
	SoundBuffer buffer;
	Music music;
	 
	music.openFromFile ( "sfx/marcia_recorte_wav.wav" );
	music.setVolume	   (		   5			      );
	//music.play();
	
	SoundBuffer buffer2;
	Music music2;
	music2.openFromFile ( "sfx/ovni_music.ogg" );
	music2.setVolume	(		   5		 );
	music2.play();
	music2.setLoop(true);
	 
	
	//-----------------------------------------------
	//				SCORE
	//----------------------------------------------- 
    int score = 0;
 
    sf::Font arial;
    arial.loadFromFile("fonts/fuente.ttf");
 
    ostringstream Score;
    Score << "        " << score;
 
    Text Texto;
    Texto.setCharacterSize(30);
    Texto.setPosition({ 340, 0 });
    Texto.setFont(arial);
    Texto.setString(Score.str());
	
	//-----------------------------------------------
	//				INSTANCIA VENTANA	
	//-----------------------------------------------
 
	RenderWindow window(sf::VideoMode(800, 600), "SUPER ALIEN BOX"/*Style::Fullscreen*/);
	window.setFramerateLimit(fps);
	 
    window.setKeyRepeatEnabled(false);
     
    background.loadFromFile("img/menu/bg_play.png");
    fondo.setTexture(background);
    
    //		**************************************			//
	//		*				CLASES	 			 *			//
	//		**************************************			//
	 
 	
 	//-----------------------------------------------
	//				OBJETO JUGADOR
	//-----------------------------------------------
	
 	Jugador player( { 40,  40  }, Color::Blue);
 	player.setPos ( { 400, 400  } );
    
	//-----------------------------------------------
	//				OBJETO ENEMIGO
	//-----------------------------------------------
   	
	Enemigo enemy( { 40,  40  }, Color::Red);
   	enemy.setPos ( { 200, 100  } );
   	
    vector<Enemigo> vectorEnemigo;
   	bool enemigo = false;

   	//-----------------------------------------------
	//				OBJETO BALAS
	//-----------------------------------------------

	vector<Bala> vecBalaDER;
 	vector<Bala> vecBalaIZQ;
    bool dispara = false;

    //-----------------------------------------------
	//				OBJETO LIMITE	
	//-----------------------------------------------		 
	
	Limite 
	limiteLeft ( {1,800} ), 
	limiteRight( {2,800} ), 
	limiteUp   ( {798,2} );
	
	limiteLeft.setPos ( Vector2f( 0,0 ) );
	limiteRight.setPos( Vector2f( 826,1 ) );
	limiteUp.setPos   ( Vector2f( -11,-9) );
	
  
	//-----------------------------------------------
	//				OBJETO PLATAFORMA	
	//-----------------------------------------------
    
	Plataforma 		
	
	plataformUP 		( Vector2f(425,1),		Color::Transparent ),		
	plataformDownLEFT 	( Vector2f(300,2),		Color::Transparent ),	
	plataformDownRIGHT	( Vector2f(400,2),		Color::Transparent ),
	plataformDownMID 	( Vector2f(425,1),		Color::Transparent ), 		
	plataformPincheMID  ( Vector2f(60,2),		Color::Transparent ), 
	plataformUPIZQ 		( Vector2f(290,1),		Color::Transparent ),
	plataformUPIZQDown  ( Vector2f(290,1), 		Color::Transparent ), 
	plataformUPRIGHTDown( Vector2f(290,1), 		Color::Transparent ), 
	plataformUPRIGHT 	( Vector2f(290,1), 		Color::Transparent ),
//	plataformanueva 	( Vector2f(1,800), 		Color::Blue ),  			 
	plataformaGO		( Vector2f(800,100),	Color::Transparent );	    		// Si se quiere chequear -> cambiarle la POS en Y cerca de "plataformPincheMID"	 		  

    plataformUP.setPos			(Vector2f(190,340)); 				 		// arriba
	plataformDownLEFT.setPos	(Vector2f(0,550)); 					 		// abajo izquierda
	plataformDownRIGHT.setPos	(Vector2f(496,550));		 				// abajo derecha
	plataformDownMID.setPos		(Vector2f(190,389));		 	    		// en medio 
	plataformPincheMID.setPos	(Vector2f(370,530));		 				// plataforma en pinches
	plataformUPIZQ.setPos		(Vector2f(0,199.999999));					// plataforma de arriba izquierda
	plataformUPIZQDown.setPos	(Vector2f(0,259.999999));					// choque de abajo de la plataforma izquierda arriba
	plataformUPRIGHT.setPos		(Vector2f(500,199.999999));					// plataforma de arriba derecha
	plataformUPRIGHTDown.setPos	(Vector2f(500,259.9999999));				// choque de abajo de la plataforma derecha arriba
	//plataformanueva.setPos 		(Vector2f(1000,1));						// PARA SUMAR PUNTOS SCORE
 	plataformaGO.setPos			(Vector2f(0,950));						// es la plataforma que si cae el jugador pierde
	
	//-----------------------------------------------
	//				OBJETO MENU
	//-----------------------------------------------
 	
	 music2.play(); 	// 	Musica para iniciar el sonido del menu
	Menu menu1;	   //	Instancia del objeto menu
	
	//-----------------------------------------------
	//				MENU PRINCIPAL
	//-----------------------------------------------
	
	while(!escape==false){
	
	while (window.pollEvent(event)){
             
    if (event.type == sf::Event::Closed)  
    window.close();
             

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
    window.close();
            
    }     
        
	window.clear();
	
	menu1.MenuPrincipal(window);
	 
	 
	window.display();
	 
 
	if( Keyboard::isKeyPressed(Keyboard::E) ) 
	escape=false; 						 
	else
	escape=true;
	 
	if( Keyboard::isKeyPressed(Keyboard::I) ){
	while(!otro_menu==false){
	window.clear();
	menu1.MenuInformacion(window);
	window.display();	
	if( Keyboard::isKeyPressed(Keyboard::S) ) 
	otro_menu=false; 
	}
	 
	}
	else otro_menu=true; 

}
	 
	music2.setLoop(true);		//	Para el setLoop del menu
	music2.stop(); 				//	Cancela sonido de ambiente menu
	music.play();				//	Inicia sonido de marciano	 	 

	while ( window.isOpen() ) { //	WHILE PRINCIPAL
    //cout<<"FPS: "<<fps<<endl;
   
    //-----------------------------------------------
	//				EVENTO
	//-----------------------------------------------
    while (window.pollEvent(event)){
			 		
		 		//	FUNCIONA, ES PARA HACERLO FULL SCREEN, QUITAR EL COMENTARIO DEL RENDERWINDOW PRINCIPAL Y LISTO
			 	/*case sf::Keyboard::Return:
				
				if ( true == pantallaCompleta )
				{window.create(sf::VideoMode(800, 600), "SUPER MARCIANITO BOX", sf::Style::Default);
				pantallaCompleta = false;}
				
				else
				{window.create(sf::VideoMode(800, 600), "SUPER MARCIANITO BOX", sf::Style::Fullscreen);
				pantallaCompleta = true;}	 
				break;		 
				*/	
	    if (event.type == sf::Event::Closed)  
        window.close();
             

    	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)  
		window.close(); 
}     
            
    
             
 	 
		//		******************************************			//
		//		*				LOGICAS		 			 *			//
		//		******************************************			//
		
	 
		//GRAVEDAD					 
		if ( player.getY()  && saltar == false  ) {
    	player.move( { 0, 30 } );		 
		enemy.move(	{  0, 30}  );
		 }
		  
		
		//BALAS 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
        dispara = true;	
		} 
		
		//ENEMIGO
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        enemigo = true;	
		} 
		
		//		******************************************			//
		//		*				MOVIMIENTOS 			 *			//
		//		******************************************			//
    	
		//SALTAR
    	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up )  ){
		player.move( { 0, -moveSpeed } );
     	saltar=true;							
		}	 
	 	else
	 	saltar=false;
		
		//IZQUIERDA
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    	player.move({ -10, 0 });				       
		}
    	
    	//DERECHA
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    	player.move({ 10, 0 });				        }
    	
    	//-----------------------------------------------
		//				INTELIGENCIA ART.
		//-----------------------------------------------
	 
		 
		if( IA_LEFT == true)
		enemy.move({ -5, 0 });
		
		if( IA_RIGHT == true)
		enemy.move({ 5, 0 });
		
		if(	IA_JUMP == true)
		enemy.move({ 0, -30 });
	 	
	 	if ( NPOS  == true){ // Es para setearle una posicion luego de caer
		enemy.setPos({100,100});
	 	NPOS=false;
		 }
	 
		
		  
    	///////////////////////////////////////////////////////////////////////////// 
    	////////////////////////////	COLISIONES		////////////////////////////
	 	//////////////////////////////////////////////////////////////////////////// 
	 	
	 
		
		//COLISION CON LIMITES
		
		if ( player.getX() <= ( limiteLeft.getX()  ) ){
/*		cout<<" COLISIONA: LIMITE IZQUIERDO (LimiteLeft) "<<endl; */
		player.move({moveSpeed-CORRECION,0});								
		}
	
		if ( player.getX() >= ( limiteRight.getX() ) - pixel*7 ){
		player.move({-moveSpeed+CORRECION,0});
/*		cout<<"COLISIONA: LIMITE DERECHO (LimiteRight)"<<endl;*/							 
	 	}
		 
 		if ( player.getY() < ( limiteUp.getX() ) + pixel*2 )	{
		player.move({0,moveSpeed});
/*		cout<<"COLISIONA: LIMITE SUPERIOR (LimiteUp)"<<endl; 	*/												
	 	}
		
		 
		//COLISION CON PLATAFORMA
		
/*		 if(enemy.colision2(plataformanueva)){
	 	
		if( enemy.getX() < plataformanueva.getX()){
		enemy.move({-moveSpeed+CORRECION,0});  
 		cout<<"COLISIONA: PLATAFORMA Roja (PlataformaNueva)"<<endl; 
		
		}   
	
	 
		  
		} 
		
			if(player.colision2(plataformanueva)){
	 	
		if( player.getX() < plataformanueva.getX()){
		player.move({-moveSpeed+CORRECION,0});  
 		cout<<"COLISIONA: PLATAFORMA Roja (PlataformaNueva)"<<endl; }
		score++;
                Score.str("");
                Score << "        " << score;
                Texto.setString(Score.str());
		
		  if(score == 20){
		  	player.setPos({200,200});		//SI SCORE LLEGA A 20 SE SETEA OTRA POSS
		  }
		
		} */
		 
		
		if(  player.colision2(plataformUPIZQ) || player.colision2(plataformUPRIGHT)  ){		 	     
		 
		if( ( player.getY() < plataformUPIZQ.getY() ) ){
		player.move( {0, -moveSpeed} );
	 
/*		cout<<"COLISIONA: PLATAFORMA IZQUIERDA ARRIBA (PlataformUPIZQ)"<<endl; */}
										     
		}//	COLISION JUGADOR CON PLATAFORMA INDICADA								(JUGADOR)
		
		 
		
		if( player.colision2 (plataformUP) ){		     
		 
		if( player.getY() < plataformUP.getY() ){
		player.move( {0, -moveSpeed} );
/*		cout<<"COLISIONA: PLATAFORMA MEDIO (PlataformaUP)"<<endl; */}
										     
		}//	COLISION JUGADOR CON PLATAFORMA INDICADA								(JUGADOR)
		
		 
		 
		
		if( player.colision2(plataformUPIZQDown)  || player.colision2(plataformUPRIGHTDown)){		     
		 
		if( player.getY() > plataformUPIZQDown.getY() ){
		player.move( {0, moveSpeed} );
/*		cout<<"COLISIONA: PLATAFORMA IZQUIERDA ABAJO (plataformUPIZQDown)"<<endl; */}
			saltar=false;							     
		}
		 
		
		if( player.colision2 (plataformPincheMID) ){		     
		 
		if( player.getY() <= plataformPincheMID.getY() ){
		player.move( {0, -moveSpeed} );
/*		cout<<"COLISIONA: PLATAFORMA PEQUENIA PINCHES (plataformPincheMID)"<<endl;*/ }
										     
		}	
		
		if( player.colision2(plataformDownLEFT) ){
				 
	 	if( player.getY() <= plataformDownLEFT.getY() ){
		player.move( {0, -moveSpeed} );
/*		cout<<"COLISIONA: PLATAFORMA PISO IZQUIERDA (plataformDownLEFT)"<<endl;*/ }
	 	 
		}
		
		if( player.colision2(plataformDownRIGHT) ){
				 
	 	if( player.getY() <= plataformDownRIGHT.getY() ){
		player.move( {0, -moveSpeed} );
/*		cout<<"COLISIONA: PLATAFORMA PISO DERECHO (plataformDownRIGHT)"<<endl;*/ }
	 	 
		}//	COLISION JUGADOR CON PLATAFORMA INDICADA								(JUGADOR)
		
		
		
		if( player.colision2(plataformDownMID) ){
				  
	 	if( player.getY() >  plataformDownMID.getY() ){
		player.move( {0, moveSpeed} );
/*		cout<<"COLISIONA: PLATAFORMA ABAJO MEDIO (plataformDownMID)"<<endl;*/ }
	 	  saltar=false;
		}
		
		// ----------			GAME OVER JUGADOR			--------------
		if(player.colision2(plataformaGO) || enemy.colisionEnemigo(player)){
			 piso_GO=true;
		 	
			 while(piso_GO==true ){
			  	 
			 	window.clear();
		 		window.draw(sprite_perdio);
		 		 
		 		if(Keyboard::isKeyPressed(Keyboard::X)){
		 		cout<<"\n*** FIN ***"<<endl; 
		 		return 0;
		 	 	window.close();						   }
		 	 	
		 	 	
		
				else 
				window.display();
				 
		 	
		 
		 						}
	  
	}
	
 
	 
		
		// -------------------ENEMIGO (1) COLISION IA-----------------------------//
		
		if( enemy.colision2 (plataformUP) ){		     
		 
		if( enemy.getY() < plataformUP.getY() ){
		enemy.move( {0, -moveSpeed} );
		IA_RIGHT=true;
	 
/*		cout<<"AAAAAAAAAAAA COLISIONA: PLATAFORMA MEDIO (PlataformaUP)"<<endl;*/ }
										     
		}//	COLISION ENEMIGO CON PLATAFORMA INDICADA								(ENEMIGO)
	 
		if( enemy.colision2(plataformUPIZQ) || enemy.colision2(plataformUPRIGHT) ){ 		 	
		IA_LEFT=false;
		if( ( player.getY() < plataformUPIZQ.getY() ) || ( enemy.getY() < plataformUPIZQ.getY() ) ){
		enemy.move( {0, -moveSpeed} );	
		IA_RIGHT=true;}
		
		}//	COLISION ENEMIGO CON PLATAFORMA INDICADA								(ENEMIGO)
		
		if( enemy.colision2(plataformDownRIGHT) ){
				 
	 	if( enemy.getY() < plataformDownRIGHT.getY() ){
		enemy.move( {0, -moveSpeed} );
		
		IA_LEFT=true;
		IA_RIGHT=false;
	 
		
/*		cout<<"COLISIONA: PLATAFORMA PISO DERECHO (plataformDownRIGHT)"<<endl; */ }
	 	 
		}//	COLISION ENEMIGO CON PLATAFORMA INDICADA								(ENEMIGO)    	

	 	if(enemy.colision2(plataformaGO)){
	 		NPOS=true;
		 }
	
		//		******************************************			//
		//		*				ANIMACIONES 			 *			//
		//		******************************************			//
		
		Time 	time;
        time 	= clock.getElapsedTime();		
 	 	
 	 	 
 	 	
	  if( time.asMilliseconds() >= 150  ){
             
        	// ANTORCHAS, CANDELARIO, MARCIANO
			source.x++;
        	if(source.x * 64 >= 252 ){
       		 source.x=0;
        	clock.restart();}				  }
             
			antorcha_sprite.setTextureRect	( IntRect (source.x*64,source.y*64,64,64) );
			antorcha_sprite.setScale		( 1.3,1.3 );
			antorcha_sprite.setPosition		( 65,40   );
			
	 		antorcha2_sprite.setTextureRect	( IntRect (source.x*64,source.y*64,64,64) );
	 		antorcha2_sprite.setScale		( 1.3,1.3 );			 
	 		antorcha2_sprite.setPosition	( 650,40  );
	 		
	 		pcande.setTextureRect( IntRect (source.x*64,source.y*64,64,64));
	 		pcande.setPosition	 ( 350,1  );
	 		pcande.setScale		 ( 1.5,1.5);
	 	
	  		pmarcianito.setTextureRect( IntRect (source.x*64,source.y*64,64,64) );
	 		pmarcianito.setPosition	 ( 386,80  );
	 		pmarcianito.setScale	 ( 1.2,1.2 );
            
 
   		//		******************************************			//
		//		*				DIBUJAR		 			 *			//
		//		******************************************			//
   		
   		
   		//	Posicion mouse X,Y		      
   		Vector2i position = Mouse::getPosition(window);
   	 	///cout<<"Mouse  X: "<< position.x <<"   Mouse  Y: "<< position.y <<endl; 
 
   		//	REFRESCA PANTALLA
   		window.clear();

   		//	FONDO PANTALLA
   		window.draw(fondo);
 		
		 //	UPDATEAR POSICION
 		player.update();
 		enemy.update();
 
 		//	BALAS
 		Time 	time2;
        time2 	= clock.getElapsedTime();
        
		if (dispara == true)  
		{            
		if( time2.asMilliseconds() > 100  )  
		{
			
        Bala balaDER(Vector2f(35, 35));    
        balaDER.setPos(Vector2f(player.getX(), player.getY()));   
		vecBalaDER.push_back(balaDER);	 
        //
        Bala balaIZQ(Vector2f(35,35));
        balaIZQ.setPos(Vector2f(player.getX(), player.getY()));    
        vecBalaIZQ.push_back(balaIZQ);
        
		}    
		}        
		dispara = false;              
         
        for (int i = 0; i < vecBalaDER.size(); i++)  
        {  
		vecBalaDER[i].mostrar(window);
        
		vecBalaDER[i].move({20,0});    
        }
        
       for (int j = 0; j < vecBalaIZQ.size(); j++)  
        {  
		
		vecBalaIZQ[j].mostrar(window);
        
		vecBalaIZQ[j].move({-20,0});    
        }     	 
			 
		//	ENEMIGO	 
 		
		 if (enemigo == true)  
{            
		if( time2.asMilliseconds() > 100  )  
		{
			
        Enemigo newEnemigo(Vector2f(50, 50),Color::Black);    
        newEnemigo.setPos({200,50});   
		vectorEnemigo.push_back(newEnemigo);	 
      
      
		}    
}        
enemigo = false;              
         
        for (int i = 0; i != vectorEnemigo.size(); i++)  
        {  
		vectorEnemigo[i].mostrar(window);
        
		  
        }
        
      
        
		 
         
   		//	JUGADOR
        player.mostrar(window);
        enemy.mostrar(window);
   		
   		//	ANTORCHAS
        window.draw(antorcha_sprite);
   		window.draw(antorcha2_sprite);
   		window.draw(pcande);
   		window.draw(pmarcianito);
   		
   		//	LIMITE MAPA
   		limiteLeft.mostrarLimite(window);
   		limiteRight.mostrarLimite(window);
   		limiteUp.mostrarLimite(window);
		   
  		//	PLATAFORMAS
   		plataformUP.mostrarPlataforma(window);
   		plataformUPIZQ.mostrarPlataforma(window);
   		plataformUPIZQDown.mostrarPlataforma(window);
   		plataformUPRIGHT.mostrarPlataforma(window);
   		plataformUPRIGHTDown.mostrarPlataforma(window);
   		plataformDownLEFT.mostrarPlataforma(window);
   		plataformDownRIGHT.mostrarPlataforma(window);
   		plataformDownMID.mostrarPlataforma(window);
		plataformPincheMID.mostrarPlataforma(window);
	 	//plataformanueva.mostrarPlataforma(window);
	 	plataformaGO.mostrarPlataforma(window);
   		
	 	// SCORE
        window.draw(Texto);
       
		   
		window.display();
		
	 
        
}//FIN LOOP
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}//MAIN
