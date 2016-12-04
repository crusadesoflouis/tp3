#include <iostream>
#include "mini_test.h"
#include "Juego.h"

Coordenada c_0_0(0,0);
Coordenada c_0_1(0,1);
Coordenada c_0_2(0,2);
Coordenada c_0_3(0,3);
Coordenada c_1_0(1,0);
Coordenada c_1_1(1,1);
Coordenada c_1_2(1,2);
Coordenada c_1_3(1,3);
Coordenada c_2_0(2,0);
Coordenada c_2_1(2,1);
Coordenada c_2_2(2,2);
Coordenada c_2_3(2,3);
Coordenada c_3_0(3,0);
Coordenada c_3_1(3,1);
Coordenada c_3_2(3,2);
Coordenada c_3_3(3,3);
Coordenada c_4_4(4,4);
Coordenada c_6_6(6,6);
Coordenada c_6_7(6,7);
Coordenada c_7_2(7,2);
Coordenada c_8_8(8,8);
Coordenada c_10_10(10,10);
Coordenada c_11_11(11,11);
Coordenada c_12_12(12,12);
Coordenada c_20_20(20,20);
Coordenada c_50_50(50,50);



void testVacio(){
  Mapa m;
  ASSERT_EQ(m.Vacia(),true);
}



void testAgregarCoordenada(){
  Mapa m;
  ASSERT_EQ(m.Vacia(),true);
  m.AgregarCoord(c_10_10);
  m.AgregarCoord(c_1_1);
  m.AgregarCoord(c_2_2);
  m.AgregarCoord(c_1_0);
  m.AgregarCoord(c_3_3);
  m.AgregarCoord(c_6_6);
  m.AgregarCoord(c_8_8);
  ASSERT_EQ(m.Vacia(),false);
  ASSERT_EQ(m.PosExistente(c_1_1),true);
  Juego j(m);
  ASSERT_EQ(j.PosExistente(c_1_1),true);

//  ASSERT_EQ(m.HayCamino(c_1_1,c_3_3),false);
/*
Conj<Coordenada> a = j.ObtenerPosicionesCercanas(c_1_0);
ASSERT_EQ(a.Pertenece(c_1_0),true);
ASSERT_EQ(a.Pertenece(c_8_8),false);
ASSERT_EQ(a.Pertenece(c_1_1),true);
ASSERT_EQ(a.Pertenece(c_2_2),false);
*/
}

void testsAgregarBasico(){
  Mapa m;
  Pokemon Abra = "Abra";
  m.AgregarCoord(c_10_10);
  m.AgregarCoord(c_1_1);
  m.AgregarCoord(c_1_2);
  Juego j(m);
  j.AgregarPokemon(c_1_1,Abra);
  ASSERT_EQ(j.HayPokemonCercano(c_1_2),true);
  std::cout << "latitud: " <<j.PosPokemonCercano(c_1_2).latitud() <<std::endl;
  std::cout << "longitud: " <<j.PosPokemonCercano(c_1_2).longitud() <<std::endl;

}

void testAgregarPokemon(){
  Mapa m;
  Pokemon Pikachu = "Pikachu";
  Pokemon Abra = "Abra";
  m.AgregarCoord(c_11_11);
  m.AgregarCoord(c_1_1);
  m.AgregarCoord(c_6_6);
  m.AgregarCoord(c_3_3);
  m.AgregarCoord(c_2_2);
  m.AgregarCoord(c_3_1);
  m.AgregarCoord(c_2_2);
  m.AgregarCoord(c_4_4);
  m.AgregarCoord(c_1_2);
  m.AgregarCoord(c_2_2);
  m.AgregarCoord(c_3_0);
  m.AgregarCoord(c_10_10);

  Juego j(m);
//  std::cout << "agregar abra" << std::endl;
  j.AgregarPokemon(c_1_1,Abra);
//  std::cout << "puedo agregar 3 0 " << std::endl;
//  ASSERT_EQ(j.PuedoAgregarPokemon(c_3_0),false);
  ASSERT_EQ(j.PuedoAgregarPokemon(c_10_10),true);
  j.AgregarPokemon(c_10_10,Pikachu);
//  std::cout << "puedo agregar 50 50 " << std::endl;
//  ASSERT_EQ(j.PuedoAgregarPokemon(c_50_50),true);

  }

void testcompleto(){
  Mapa m;
  Pokemon Pikachu = "Pikachu";
  Pokemon Abra = "Abra";
  m.AgregarCoord(c_10_10);
  m.AgregarCoord(c_1_1);
  m.AgregarCoord(c_6_6);
  m.AgregarCoord(c_3_3);
  m.AgregarCoord(c_2_2);
  m.AgregarCoord(c_3_1);
  ASSERT_EQ(m.PosExistente(c_1_1),true);
  Juego j(m);
  Jugador manolo = j.AgregarJugador();
  Jugador pepe = j.AgregarJugador();
  j.AgregarPokemon(c_1_1,Abra);
  j.AgregarPokemon(c_6_6,Abra);
  ASSERT_EQ(j.EstaConectado(pepe),false);
  j.Conectarse(c_1_1,pepe);
  ASSERT_EQ(m.PosExistente(c_1_1),true);
  ASSERT_EQ(m.PosExistente(c_6_6),true);
  ASSERT_EQ(m.PosExistente(c_12_12),false);
  ASSERT_EQ(j.EstaConectado(manolo),false);
  ASSERT_EQ(j.EstaConectado(pepe),true);
  ASSERT_EQ(j.Sanciones(manolo),0);
  ASSERT_EQ(j.Sanciones(pepe),0);
  ASSERT_EQ(j.PokemonEnPos(c_1_1),Abra);
  ASSERT_EQ(j.cantMismaEspecie(Abra),2);
  ASSERT_EQ(j.IndiceRareza(Abra),100);
  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),10);
}


void testConectar() {
  Mapa m;
  Pokemon Pikachu = "Pikachu";
  Pokemon Abra = "Abra";
  m.AgregarCoord(c_20_20);
  m.AgregarCoord(c_1_2);
  m.AgregarCoord(c_1_1);
  m.AgregarCoord(c_6_6);
  Juego j(m);
  Jugador manolo = j.AgregarJugador();
  Jugador pepe = j.AgregarJugador();
  j.AgregarPokemon(c_1_1,Abra);
  j.Conectarse(c_1_1,manolo);
  j.Conectarse(c_6_6,pepe);
  ASSERT_EQ(j.EstaConectado(manolo),true);
  ASSERT_EQ(j.EstaConectado(pepe),true);
  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),10);
  ASSERT_EQ(j.Sanciones(manolo),0);
  j.Desconectarse(manolo);
  std::cout << "latitud: " <<j.PosPokemonCercano(c_1_2).latitud() <<std::endl;
  std::cout << "longitud: " <<j.PosPokemonCercano(c_1_2).longitud() <<std::endl;
  ASSERT_EQ(j.EstaConectado(manolo),false);
  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),10);
}

void testMover(){
  Mapa m;
  Pokemon Pikachu = "Pikachu";
  Pokemon Abra = "Abra";
  m.AgregarCoord(c_20_20);
  m.AgregarCoord(c_1_2);
  m.AgregarCoord(c_1_1);
  m.AgregarCoord(c_6_6);
  m.AgregarCoord(c_6_7);
  Juego j(m);
  Jugador manolo = j.AgregarJugador();
  Jugador pepe = j.AgregarJugador();
  j.AgregarPokemon(c_1_1,Abra);
  j.Conectarse(c_1_1,manolo);
  j.Conectarse(c_6_6,pepe);
  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),10);
  j.Moverse(c_6_7,pepe);
  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),9);
  ASSERT_EQ(j.Sanciones(pepe),0);
  j.Moverse(c_20_20,pepe);
  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),8);
  ASSERT_EQ(j.Sanciones(pepe),1);
  j.Moverse(c_1_1,pepe);
  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),10);
  ASSERT_EQ(j.Sanciones(pepe),2);
  j.Moverse(c_6_6,pepe);
  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),9);
  ASSERT_EQ(j.Sanciones(pepe),3);
}

int main(){
  RUN_TEST(testVacio);
  RUN_TEST(testAgregarCoordenada);
  RUN_TEST(testAgregarPokemon);
  RUN_TEST(testsAgregarBasico);
  RUN_TEST(testcompleto);
  RUN_TEST(testConectar);

}
