// Compilar usando:
//	g++ -o tests tests.cpp Driver.cpp <lista de archivos *.cpp propios>
//	valgrind --leak-check=full ./tests

#include <string>
#include <iostream>
#include <fstream>

#include "Driver.h"
#include "mini_test_without_couts.h"

#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <math.h>

using namespace aed2;


////////////////////////////////////////////////////////////////
// ACERCA DEL MAPA
////////////////////////////////////////////////////////////////


void test_constructor_con_mapa()
{
	Conj<Coordenada> cc;
	cc.Agregar(Coordenada(0,0));
	cc.Agregar(Coordenada(0,1));
	cc.Agregar(Coordenada(0,2));
	cc.Agregar(Coordenada(1,2));
	cc.Agregar(Coordenada(10,0));
	cc.Agregar(Coordenada(1,4));
	Driver d(cc);
	ASSERT( d.mapa() == cc );
}


////////////////////////////////////////////////////////////////
// ACERCA DE POKEMONS
////////////////////////////////////////////////////////////////


void test_puedo_agregar_pokemons_1()
{
	Coordenada c0(0,0); // sector 0
	Coordenada c1(1,0); // sector 0
	Coordenada c2(2,0); // sector 0
	Coordenada c3(12,0); // sector 1
	Coordenada c4(12,1); // sector 1
	Coordenada c5(12,2); // sector 1
	Coordenada c6(120,2); // sector 2

	Conj<Coordenada> cc;
	cc.Agregar(c0);
	cc.Agregar(c1);
	cc.Agregar(c2);
	cc.Agregar(c3);
	cc.Agregar(c4);
	cc.Agregar(c5);
	cc.Agregar(c6);
	
	Driver d(cc);

	d.agregarPokemon("Squirtle", c0);
	ASSERT( d.puedoAgregarPokemon(c0) == false );
	ASSERT( d.puedoAgregarPokemon(c1) == false );
	ASSERT( d.puedoAgregarPokemon(c2) == false );
	ASSERT( d.puedoAgregarPokemon(c3) == true );
	ASSERT( d.puedoAgregarPokemon(c4) == true );
	ASSERT( d.puedoAgregarPokemon(c5) == true );
	ASSERT( d.puedoAgregarPokemon(c6) == true );

	d.agregarPokemon("Metapod", c3);
	ASSERT( d.puedoAgregarPokemon(c0) == false );
	ASSERT( d.puedoAgregarPokemon(c1) == false );
	ASSERT( d.puedoAgregarPokemon(c2) == false );
	ASSERT( d.puedoAgregarPokemon(c3) == false );
	ASSERT( d.puedoAgregarPokemon(c4) == false );
	ASSERT( d.puedoAgregarPokemon(c5) == false );
	ASSERT( d.puedoAgregarPokemon(c6) == true );

	d.agregarPokemon("Chikorita", c6);
	ASSERT( d.puedoAgregarPokemon(c0) == false );
	ASSERT( d.puedoAgregarPokemon(c1) == false );
	ASSERT( d.puedoAgregarPokemon(c2) == false );
	ASSERT( d.puedoAgregarPokemon(c3) == false );
	ASSERT( d.puedoAgregarPokemon(c4) == false );
	ASSERT( d.puedoAgregarPokemon(c5) == false );
	ASSERT( d.puedoAgregarPokemon(c6) == false );
	
}

void test_puedo_agregar_pokemons_2()
{
	Conj<Coordenada> cc;
	cc.Agregar(Coordenada(0,0));
	cc.Agregar(Coordenada(0,1));
	cc.Agregar(Coordenada(0,2));
	cc.Agregar(Coordenada(1,2));
	cc.Agregar(Coordenada(1,4));
	cc.Agregar(Coordenada(4,3));
	cc.Agregar(Coordenada(4,4));
	cc.Agregar(Coordenada(10,0));
	/*
		- X - - - - - - - -
		- - - - X - - - - -
		X X - - - - - - - -
		X - - - - - - - - -
		X - - - - - - - - X
	*/
	Driver d(cc);
	ASSERT(d.puedoAgregarPokemon(Coordenada(0,0)) == true);
	ASSERT(d.puedoAgregarPokemon(Coordenada(0,1)) == true);
	ASSERT(d.puedoAgregarPokemon(Coordenada(0,2)) == true);
	ASSERT(d.puedoAgregarPokemon(Coordenada(1,2)) == true);
	ASSERT(d.puedoAgregarPokemon(Coordenada(1,4)) == true);
	ASSERT(d.puedoAgregarPokemon(Coordenada(4,3)) == true);
	ASSERT(d.puedoAgregarPokemon(Coordenada(10,0)) == true);
	ASSERT(d.puedoAgregarPokemon(Coordenada(1,0)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(1,3)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(10,3)) == false);
	
	d.agregarPokemon("Jigglypuff", Coordenada(0,0));
	ASSERT(d.puedoAgregarPokemon(Coordenada(0,0)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(0,1)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(0,2)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(1,2)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(1,4)) == false);
	//ASSERT(d.puedoAgregarPokemon(Coordenada(4,3)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(4,4)) == true);
	ASSERT(d.puedoAgregarPokemon(Coordenada(10,0)) == true);
	ASSERT(d.puedoAgregarPokemon(Coordenada(1,0)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(1,3)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(10,3)) == false);

	d.agregarPokemon("Vaporeon", Coordenada(10,0));
	ASSERT(d.puedoAgregarPokemon(Coordenada(0,0)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(0,1)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(0,2)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(1,2)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(1,4)) == false);
	//ASSERT(d.puedoAgregarPokemon(Coordenada(4,3)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(4,4)) == true);
	ASSERT(d.puedoAgregarPokemon(Coordenada(10,0)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(1,0)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(1,3)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(10,3)) == false);

	d.agregarPokemon("Gengar", Coordenada(4,4));
	ASSERT(d.puedoAgregarPokemon(Coordenada(0,0)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(0,1)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(0,2)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(1,2)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(1,4)) == false);
	//ASSERT(d.puedoAgregarPokemon(Coordenada(4,3)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(4,4)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(10,0)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(1,0)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(1,3)) == false);
	ASSERT(d.puedoAgregarPokemon(Coordenada(10,3)) == false);
}

void test_pokemon_en_posicion()
{
	Conj<Coordenada> cc;
	cc.Agregar(Coordenada(0,0));
	cc.Agregar(Coordenada(0,1));
	cc.Agregar(Coordenada(0,2));
	cc.Agregar(Coordenada(1,2));
	cc.Agregar(Coordenada(1,4));
	cc.Agregar(Coordenada(4,3));
	cc.Agregar(Coordenada(10,0));
	Driver d(cc);
	
	d.agregarPokemon("Jigglypuff", Coordenada(0,0));
	ASSERT("Jigglypuff" == d.pokemonEnPos(Coordenada(0,0)));

	d.agregarPokemon("Vaporeon", Coordenada(10,0));
	ASSERT("Jigglypuff" == d.pokemonEnPos(Coordenada(0,0)));
	ASSERT("Vaporeon" == d.pokemonEnPos(Coordenada(10,0)));

	d.agregarPokemon("Gengar", Coordenada(4,3));
	ASSERT("Jigglypuff" == d.pokemonEnPos(Coordenada(0,0)));
	ASSERT("Vaporeon" == d.pokemonEnPos(Coordenada(10,0)));
	ASSERT("Gengar" == d.pokemonEnPos(Coordenada(4,3)));
}

void test_pos_con_pokemons()
{
	Coordenada c0(0,0); // sector 0
	Coordenada c1(1,0); // sector 0
	Coordenada c2(2,0); // sector 0
	Coordenada c3(12,0); // sector 1
	Coordenada c4(12,1); // sector 1
	Coordenada c5(12,2); // sector 1
	Coordenada c6(120,2); // sector 2

	Conj<Coordenada> cc;

	cc.Agregar(c0);
	cc.Agregar(c1);
	cc.Agregar(c2);
	cc.Agregar(c3);
	cc.Agregar(c4);
	cc.Agregar(c5);
	cc.Agregar(c6);
	
	Driver d(cc);

	Conj<Coordenada> cc_pokes;

	d.agregarPokemon("Squirtle", c0);
	ASSERT( "Squirtle" == d.pokemonEnPos(c0) );
	cc_pokes.Agregar(c0);
	ASSERT( cc_pokes == d.posConPokemons() );

	d.agregarPokemon("Metapod", c3);
	ASSERT( "Squirtle" == d.pokemonEnPos(c0) );
	ASSERT( "Metapod" == d.pokemonEnPos(c3) );
	cc_pokes.Agregar(c3);
	ASSERT( cc_pokes == d.posConPokemons() );

	d.agregarPokemon("Chikorita", c6);
	ASSERT( "Squirtle" == d.pokemonEnPos(c0) );
	ASSERT( "Metapod" == d.pokemonEnPos(c3) );
	ASSERT( "Chikorita" == d.pokemonEnPos(c6) );
	cc_pokes.Agregar(c6);
	ASSERT( cc_pokes == d.posConPokemons() );

}

void test_hay_pokemon_cercano()
{
	Conj<Coordenada> cc;
	cc.Agregar(Coordenada(0,0));
	cc.Agregar(Coordenada(0,1));
	cc.Agregar(Coordenada(0,2));
	cc.Agregar(Coordenada(0,4));
	cc.Agregar(Coordenada(0,5));
	cc.Agregar(Coordenada(1,0));
	cc.Agregar(Coordenada(1,2));
	cc.Agregar(Coordenada(1,3));
	cc.Agregar(Coordenada(1,4));
	cc.Agregar(Coordenada(4,3));
	cc.Agregar(Coordenada(5,3));
	cc.Agregar(Coordenada(10,0));
	cc.Agregar(Coordenada(10,3));
	cc.Agregar(Coordenada(99,99));

	Driver d(cc);
	ASSERT(d.hayPokemonCercano(Coordenada(0,0)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(0,1)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(0,2)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(0,4)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(0,5)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(1,0)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(1,2)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(1,3)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(1,4)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(4,3)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(5,3)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(10,0)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(10,3)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(99,99)) == false);

	d.agregarPokemon("Jigglypuff", Coordenada(0,0));
	ASSERT(d.hayPokemonCercano(Coordenada(0,0)) == true);
	ASSERT(d.hayPokemonCercano(Coordenada(0,1)) == true);
	ASSERT(d.hayPokemonCercano(Coordenada(0,2)) == true);
	ASSERT(d.hayPokemonCercano(Coordenada(0,4)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(0,5)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(1,0)) == true);
	ASSERT(d.hayPokemonCercano(Coordenada(1,2)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(1,3)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(1,4)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(4,3)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(5,3)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(10,0)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(10,3)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(99,99)) == false);

	d.agregarPokemon("Vaporeon", Coordenada(10,0));
	ASSERT(d.hayPokemonCercano(Coordenada(0,0)) == true);
	ASSERT(d.hayPokemonCercano(Coordenada(0,1)) == true);
	ASSERT(d.hayPokemonCercano(Coordenada(0,2)) == true);
	ASSERT(d.hayPokemonCercano(Coordenada(0,4)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(0,5)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(1,0)) == true);
	ASSERT(d.hayPokemonCercano(Coordenada(1,2)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(1,3)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(1,4)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(4,3)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(5,3)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(10,0)) == true);
	ASSERT(d.hayPokemonCercano(Coordenada(10,3)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(99,99)) == false);

	d.agregarPokemon("Gengar", Coordenada(4,3));
	ASSERT(d.hayPokemonCercano(Coordenada(0,0)) == true);
	ASSERT(d.hayPokemonCercano(Coordenada(0,1)) == true);
	ASSERT(d.hayPokemonCercano(Coordenada(0,2)) == true);
	ASSERT(d.hayPokemonCercano(Coordenada(0,4)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(0,5)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(1,0)) == true);
	ASSERT(d.hayPokemonCercano(Coordenada(1,2)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(1,3)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(1,4)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(4,3)) == true);
	ASSERT(d.hayPokemonCercano(Coordenada(5,3)) == true);
	ASSERT(d.hayPokemonCercano(Coordenada(10,0)) == true);
	ASSERT(d.hayPokemonCercano(Coordenada(10,3)) == false);
	ASSERT(d.hayPokemonCercano(Coordenada(99,99)) == false);
}

void test_coordenada_pokemon_cercano()
{
	Conj<Coordenada> cc;
	Coordenada c1(0,0);
	Coordenada c2(0,1);
	Coordenada c3(0,2);
	Coordenada c4(1,2);
	Coordenada c5(1,4);
	Coordenada c6(4,3);
	Coordenada c7(10,0);
	cc.Agregar(c1);
	cc.Agregar(c2);
	cc.Agregar(c3);
	cc.Agregar(c4);
	cc.Agregar(c5);
	cc.Agregar(c6);
	cc.Agregar(c7);
	/*
	- X - - - - - - - -
	- - - - X - - - - -
	X X - - - - - - - -
	X - - - - - - - - -
	X - - - - - - - - X
	*/
	Driver d(cc);

	d.agregarPokemon("Jigglypuff", c1);
	ASSERT(d.hayPokemonCercano(c1) == true);
	ASSERT(d.posPokemonCercano(c1) == c1);

	ASSERT(d.hayPokemonCercano(c2) == true);
	ASSERT(d.posPokemonCercano(c2) == c1);

	ASSERT(d.hayPokemonCercano(c3) == true);
	ASSERT(d.posPokemonCercano(c3) == c1);

	ASSERT(d.hayPokemonCercano(c4) == false);
	
	ASSERT(d.hayPokemonCercano(Coordenada(1,0)) == true);
	ASSERT(d.posPokemonCercano(Coordenada(1,0)) == c1);

	ASSERT(d.hayPokemonCercano(Coordenada(1,3)) == false);
	
	d.agregarPokemon("Vaporeon", c7);

	ASSERT(d.hayPokemonCercano(c1) == true);
	ASSERT(d.posPokemonCercano(c1) == c1);

	ASSERT(d.hayPokemonCercano(c2) == true);
	ASSERT(d.posPokemonCercano(c2) == c1);

	ASSERT(d.hayPokemonCercano(c3) == true);
	ASSERT(d.posPokemonCercano(c3) == c1);

	ASSERT(d.hayPokemonCercano(c4) == false);
	
	ASSERT(d.hayPokemonCercano(Coordenada(1,0)) == true);
	ASSERT(d.posPokemonCercano(Coordenada(1,0)) == c1);

	ASSERT(d.hayPokemonCercano(Coordenada(1,3)) == false);

	ASSERT(d.hayPokemonCercano(c7) == true);
	ASSERT(d.posPokemonCercano(c7) == c7);

	ASSERT(d.hayPokemonCercano(Coordenada(10,3)) == false);


	d.agregarPokemon("Gengar", c6);

	ASSERT(d.hayPokemonCercano(c1) == true);
	ASSERT(d.posPokemonCercano(c1) == c1);

	ASSERT(d.hayPokemonCercano(c2) == true);
	ASSERT(d.posPokemonCercano(c2) == c1);

	ASSERT(d.hayPokemonCercano(c3) == true);
	ASSERT(d.posPokemonCercano(c3) == c1);

	ASSERT(d.hayPokemonCercano(c4) == false);
	
	ASSERT(d.hayPokemonCercano(Coordenada(1,0)) == true);
	ASSERT(d.posPokemonCercano(Coordenada(1,0)) == c1);

	ASSERT(d.hayPokemonCercano(Coordenada(1,3)) == false);

	ASSERT(d.hayPokemonCercano(c7) == true);
	ASSERT(d.posPokemonCercano(c7) == c7);

	ASSERT(d.hayPokemonCercano(Coordenada(10,3)) == false);

	ASSERT(d.hayPokemonCercano(c6) == true);
	ASSERT(d.posPokemonCercano(c6) == c6);

	ASSERT(d.hayPokemonCercano(Coordenada(5,3)) == true);
	ASSERT(d.posPokemonCercano(Coordenada(5,3)) == c6);

}


////////////////////////////////////////////////////////////////
// ACERCA DE JUGADORES
////////////////////////////////////////////////////////////////


void test_agregar_jugadores()
{
	Coordenada c0(0,0); // sector 0
	Coordenada c1(1,0); // sector 0
	Coordenada c2(2,0); // sector 0
	Coordenada c3(12,0); // sector 1
	Coordenada c4(12,1); // sector 1
	Coordenada c5(12,2); // sector 1
	Coordenada c6(120,2); // sector 2

	Conj<Coordenada> cc;
	
	cc.Agregar(c0);
	cc.Agregar(c1);
	cc.Agregar(c2);
	cc.Agregar(c3);
	cc.Agregar(c4);
	cc.Agregar(c5);
	cc.Agregar(c6);

	Driver d(cc);

	Nat j0 = d.agregarJugador();
	Nat j1 = d.agregarJugador();
	Nat j2 = d.agregarJugador();
	Nat j3 = d.agregarJugador();

	Conj<Jugador> jugadores;

	jugadores.Agregar(j0);
	jugadores.Agregar(j1);
	jugadores.Agregar(j2);
	jugadores.Agregar(j3);

	Conj<Jugador> expulsados;

	ASSERT( jugadores == d.jugadores() );
	ASSERT( expulsados == d.expulsados() );

	Conj<Coordenada> cp;

	ASSERT( cp == d.posConPokemons() );

}

void test_conectar_jugadores()
{
	Conj<Coordenada> cc;
	Coordenada c1(0,0);
	Coordenada c2(0,2);
	Coordenada c3(10,0);
	cc.Agregar(c1);
	cc.Agregar(c2);
	cc.Agregar(c3);
	cc.Agregar(Coordenada(0,1));
	cc.Agregar(Coordenada(1,2));
	cc.Agregar(Coordenada(1,4));
	Driver d(cc);
	Nat j1 = d.agregarJugador();
	Nat j2 = d.agregarJugador();
	Nat j3 = d.agregarJugador();
	Nat j4 = d.agregarJugador();

	ASSERT(d.estaConectado(j1) == false);
	d.conectarse(j1, c1);
	ASSERT(d.estaConectado(j1) == true);
	ASSERT(d.estaConectado(j2) == false);
	d.conectarse(j2, c1);
	ASSERT(d.estaConectado(j2) == true);
	ASSERT(d.estaConectado(j3) == false);
	d.conectarse(j3, c2);
	ASSERT(d.estaConectado(j3) == true);
	ASSERT(d.estaConectado(j4) == false);
	d.conectarse(j4, c3);
	ASSERT(d.estaConectado(j4) == true);

	ASSERT(d.posicion(j1) == c1);
	ASSERT(d.posicion(j2) == c1);
	ASSERT(d.posicion(j3) == c2);
	ASSERT(d.posicion(j4) == c3);
}

void test_desconectar_jugadores()
{
	Conj<Coordenada> cc;
	Coordenada c1 (0,0);
	Coordenada c2 (0,2);
	Coordenada c3 (10,0);
	cc.Agregar(c1);
	cc.Agregar(c2);
	cc.Agregar(c3);
	cc.Agregar(Coordenada(0,1));
	cc.Agregar(Coordenada(1,2));
	cc.Agregar(Coordenada(1,4));
	Driver d(cc);
	Nat j1 = d.agregarJugador();
	Nat j2 = d.agregarJugador();
	Nat j3 = d.agregarJugador();
	Nat j4 = d.agregarJugador();
	d.conectarse(j1, c1);
	d.conectarse(j2, c1);
	d.conectarse(j3, c2);
	d.conectarse(j4, c3);

	ASSERT(d.estaConectado(j1) == true);
	ASSERT(d.estaConectado(j2) == true);
	ASSERT(d.estaConectado(j3) == true);
	ASSERT(d.estaConectado(j4) == true);

	d.desconectarse(j1);
	ASSERT(d.estaConectado(j1) == false);
	ASSERT(d.estaConectado(j2) == true);
	ASSERT(d.estaConectado(j3) == true);
	ASSERT(d.estaConectado(j4) == true);
	d.desconectarse(j2);
	ASSERT(d.estaConectado(j1) == false);
	ASSERT(d.estaConectado(j2) == false);
	ASSERT(d.estaConectado(j3) == true);
	ASSERT(d.estaConectado(j4) == true);
	d.conectarse(j1, c3);
	ASSERT(d.estaConectado(j1) == true);
	ASSERT(d.estaConectado(j2) == false);
	ASSERT(d.estaConectado(j3) == true);
	ASSERT(d.estaConectado(j4) == true);
}

void test_mover_jugador_asigna_correcta_coordenada()
{
	Conj<Coordenada> cc;
	Coordenada c1(0,0); // sector 0
	Coordenada c2(0,2); // sector 0
	Coordenada c3(10,0); // sector 1
	Coordenada c4(1,2); // sector 2
	Coordenada c5(0,1); // sector 0
	Coordenada c6(1,4); // sector 3
	
	cc.Agregar(c1);
	cc.Agregar(c2);
	cc.Agregar(c3);
	cc.Agregar(c4);
	cc.Agregar(c5);
	cc.Agregar(c6);
	/*
		- X - - - - - - - -
		- - - - - - - - - -
		X X - - - - - - - -
		X - - - - - - - - -
		X - - - - - - - - X
	*/
	Driver d(cc);
	Nat j1 = d.agregarJugador();
	Nat j2 = d.agregarJugador();
	Nat j3 = d.agregarJugador();
	Nat j4 = d.agregarJugador();
	d.conectarse(j1, c1);
	d.conectarse(j2, c1);
	d.conectarse(j3, c2);
	d.conectarse(j4, c5);

	d.moverse(j1, c1);
	ASSERT(d.posicion(j1) == c1);
	ASSERT(d.posicion(j2) == c1);
	ASSERT(d.posicion(j3) == c2);
	ASSERT(d.posicion(j4) == c5);

	d.moverse(j2, c4);
	ASSERT(d.posicion(j1) == c1);
	ASSERT(d.posicion(j2) == c4);
	ASSERT(d.posicion(j3) == c2);
	ASSERT(d.posicion(j4) == c5);

	d.moverse(j3, c3);
	ASSERT(d.posicion(j1) == c1);
	ASSERT(d.posicion(j2) == c4);
	ASSERT(d.posicion(j3) == c2);
	ASSERT(d.posicion(j4) == c5);

	d.moverse(j4, c1);
	ASSERT(d.posicion(j1) == c1);
	ASSERT(d.posicion(j2) == c4);
	ASSERT(d.posicion(j3) == c2);
	ASSERT(d.posicion(j4) == c1);

	d.moverse(j1, c3); // MOVIMIENTO INVÁLIDO
	ASSERT( d.posicion(j1) == c1 || d.posicion(j1) == c3 ); // CONSIDERO AMBAS IMPLEMENTACIONES
	ASSERT(d.posicion(j2) == c4);
	ASSERT(d.posicion(j3) == c2);
	ASSERT(d.posicion(j4) == c1);

	d.moverse(j1, c4);
	ASSERT(d.posicion(j1) == c4);
	ASSERT(d.posicion(j2) == c4);
	ASSERT(d.posicion(j3) == c2);
	ASSERT(d.posicion(j4) == c1);
}

void test_sanciones()
{
	Conj<Coordenada> cc;
	for (Nat i = 0; i < 100; ++i)
	{
		cc.Agregar(Coordenada(i, 5));
	}
	cc.Agregar(Coordenada(0,0));
	cc.Agregar(Coordenada(0,1));
	cc.Agregar(Coordenada(0,2));
	cc.Agregar(Coordenada(1,2));
	cc.Agregar(Coordenada(1,4));
	cc.Agregar(Coordenada(4,3));
	cc.Agregar(Coordenada(5,180));
	cc.Agregar(Coordenada(100,0));
	cc.Agregar(Coordenada(110,0));
	/*
	X X X X X X X X X	...	X
	- X - - - - - - -	...	-
	- - - - X - - - -	...	-
	X X - - - - - - -	...	-
	X - - - - - - - -	...	-
	X - - - - - - - -	...	X
	*/
	Driver d(cc);

	Nat j1 = d.agregarJugador();
	Nat j2 = d.agregarJugador();
	Nat j3 = d.agregarJugador();
	Nat j4 = d.agregarJugador();
	Nat j5 = d.agregarJugador();

	ASSERT(d.sanciones(j1) == 0);
	ASSERT(d.sanciones(j2) == 0);
	ASSERT(d.sanciones(j3) == 0);
	ASSERT(d.sanciones(j4) == 0);
	ASSERT(d.sanciones(j5) == 0);

	d.conectarse(j1, Coordenada(0,5));
	d.conectarse(j2, Coordenada(0,0));
	d.conectarse(j3, Coordenada(0,0));
	d.conectarse(j4, Coordenada(0,0));
	d.conectarse(j5, Coordenada(0,5));

	ASSERT(d.sanciones(j1) == 0);
	ASSERT(d.sanciones(j2) == 0);
	ASSERT(d.sanciones(j3) == 0);
	ASSERT(d.sanciones(j4) == 0);
	ASSERT(d.sanciones(j5) == 0);

	d.moverse(j1, Coordenada(10,5));
	d.moverse(j2, Coordenada(1,4));
	d.moverse(j3, Coordenada(1,2));
	//d.moverse(j4, Coordenada(0,0));
	d.moverse(j5, Coordenada(11,5));

	ASSERT(d.sanciones(j1) == 0 || d.sanciones(j1) == 1); // j1: (0,5) => (10,5) #conectados. CASO BORDE, ALGUNOS ALUMNOS LO IMPLEMENTARON DE UNA FORMA Y OTROS DE OTRA.
	ASSERT(d.sanciones(j2) == 1); // j2: (0,0) => (1,4) #desconectados. MOVIMIENTO INVÁLIDO. CASO 1: SE QUEDA EN 0,0, CASO 2: SE QUEDA EN 1,4
	ASSERT(d.sanciones(j3) == 0); // j3: (0,0) => (1,2) #conectados
	//ASSERT(d.sanciones(j4) == 0); // j4: (0,0) => (0,0) #conectados. SE MUEVE AL MISMO LUGAR, CASO BORDE, LO HAN IMPLEMENTADO DE DIFERENTES MANERAS.
	ASSERT(d.sanciones(j5) == 1); // j5: (0,5) => (11,5) #conectados. MOVIMIENTO INVÁLIDO.

	d.moverse(j3, Coordenada(0,2));
	ASSERT(d.sanciones(j3) == 0); // j3: (1,2) => (0,2) #conectados

	d.moverse(j3, Coordenada(0,1));
	ASSERT(d.sanciones(j3) == 0); // j3: (0,2) => (0,1) #conectados

	d.moverse(j3, Coordenada(0,0));
	ASSERT(d.sanciones(j3) == 0); // j3: (0,1) => (0,0) #conectados

	d.moverse(j2, Coordenada(5, 180));
	ASSERT(d.sanciones(j2) == 2); // j2: (0,0) => (5,180) ó (1,4) => (5,180)  #desconectados. MOVIMIENTO INVÁLIDO.
}

void test_expulsion()
{
	Coordenada c0(0,0); // sector 0
	Coordenada c1(1,0); // sector 0
	Coordenada c2(2,0); // sector 0

	Coordenada c3(12,0); // sector 1
	Coordenada c4(12,1); // sector 1
	Coordenada c5(12,2); // sector 1

	Coordenada c6(120,2); // sector 2

	Coordenada c7(60,0); // sector 3
	Coordenada c8(60,2); // sector 4
	Coordenada c9(60,4); // sector 5
	Coordenada c10(60,6); // sector 6
	Coordenada c11(60,8); // sector 7

	Conj<Coordenada> cc;
	cc.Agregar(c0);
	cc.Agregar(c1);
	cc.Agregar(c2);
	cc.Agregar(c3);
	cc.Agregar(c4);
	cc.Agregar(c5);
	cc.Agregar(c6);
	cc.Agregar(c7);
	cc.Agregar(c8);
	cc.Agregar(c9);
	cc.Agregar(c10);
	cc.Agregar(c11);
	
	Driver d(cc);

	Nat j1 = d.agregarJugador();
	Nat j2 = d.agregarJugador();

	ASSERT(d.sanciones(j1) == 0);
	ASSERT(d.sanciones(j2) == 0);

	Conj<Jugador> expulsados;
	ASSERT(d.expulsados() == expulsados);

	d.conectarse(j1, c6);
	d.conectarse(j2, c5);
	
	ASSERT(d.expulsados() == expulsados);

	d.moverse(j1, c7); // MOVIMIENTO INVÁLIDO
	d.moverse(j1, c8); // MOVIMIENTO INVÁLIDO 
	d.moverse(j1, c9); // MOVIMIENTO INVÁLIDO 
	d.moverse(j1, c10); // MOVIMIENTO INVÁLIDO 
	d.moverse(j1, c11); // MOVIMIENTO INVÁLIDO 
	
	ASSERT((d.sanciones(j1) == 5) || (d.sanciones(j1) == 4)); // CASO BORDE, HAY ALUMNOS QUE LO IMPLEMENTARON DE UNA MANERA Y OTROS DE OTRA
	ASSERT(d.sanciones(j2) == 0);

	expulsados.Agregar(j1);
	ASSERT(d.expulsados() == expulsados);

	d.moverse(j2, c11);
	d.moverse(j2, c10);
	d.moverse(j2, c9);
	d.moverse(j2, c8);
	d.moverse(j2, c7);

	ASSERT((d.sanciones(j1) == 5) || (d.sanciones(j1) == 4)); // CASO BORDE, HAY ALUMNOS QUE LO IMPLEMENTARON DE UNA MANERA Y OTROS DE OTRA
	ASSERT((d.sanciones(j2) == 5) || (d.sanciones(j2) == 4)); // CASO BORDE, HAY ALUMNOS QUE LO IMPLEMENTARON DE UNA MANERA Y OTROS DE OTRA
	
	expulsados.Agregar(j2);
	ASSERT(d.expulsados() == expulsados);

}

////////////////////////////////////////////////////////////////
// ACERCA DE POKEMONS Y JUGADORES
////////////////////////////////////////////////////////////////


void test_agregar_pokemones_y_jugadores()
{
	Coordenada c0(0,0); // sector 0
	Coordenada c1(1,0); // sector 0
	Coordenada c2(2,0); // sector 0
	Coordenada c3(12,0); // sector 1
	Coordenada c4(12,1); // sector 1
	Coordenada c5(12,2); // sector 1
	Coordenada c6(120,2); // sector 2

	Conj<Coordenada> cc;
	
	cc.Agregar(c0);
	cc.Agregar(c1);
	cc.Agregar(c2);
	cc.Agregar(c3);
	cc.Agregar(c4);
	cc.Agregar(c5);
	cc.Agregar(c6);

	Driver d(cc);

	d.agregarPokemon("Squirtle", c0);
	d.agregarPokemon("Metapod", c3);
	d.agregarPokemon("Chikorita", c6);

	Nat j0 = d.agregarJugador();
	Nat j1 = d.agregarJugador();

	d.conectarse(j0, c3);
	d.conectarse(j1, c0);

	Conj<Nat> jugadores;

	jugadores.Agregar(j0);
	jugadores.Agregar(j1);

	Conj<Nat> expulsados;

	ASSERT( jugadores == d.jugadores() );
	ASSERT( expulsados == d.expulsados() );

	Conj<Coordenada> cc_pokes;
	cc_pokes.Agregar(c0);
	cc_pokes.Agregar(c3);
	cc_pokes.Agregar(c6);

	ASSERT( cc_pokes == d.posConPokemons() );

}

void test_cantidad_de_movimientos_para_captura()
{

	Coordenada c0(0,0); // sector 0
	Coordenada c1(1,0); // sector 0
	Coordenada c2(2,0); // sector 0
	Coordenada c3(3,0); // sector 0

	Coordenada c4(12,0); // sector 1
	Coordenada c5(12,1); // sector 1
	Coordenada c6(12,2); // sector 1

	Coordenada c7(120,2); // sector 2

	Conj<Coordenada> cc;
	cc.Agregar(c0); // sector 0
	cc.Agregar(c1); // sector 0
	cc.Agregar(c2); // sector 0
	cc.Agregar(c3); // sector 0
	cc.Agregar(c4); // sector 1
	cc.Agregar(c5); // sector 1
	cc.Agregar(c6); // sector 1
	cc.Agregar(c7); // sector 2

	Driver d(cc);

	d.agregarPokemon("Squirtle", c0);
	ASSERT(d.cantMovimientosParaCaptura(c0) == 0);
	d.agregarPokemon("Squirtle", c7);
	ASSERT(d.cantMovimientosParaCaptura(c7) == 0);

	Nat j1 = d.agregarJugador();
	Nat j2 = d.agregarJugador();
	Nat j3 = d.agregarJugador();

	d.conectarse(j1, c4);
	ASSERT(d.cantMovimientosParaCaptura(c0) == 0);	
	ASSERT(d.cantMovimientosParaCaptura(c7) == 0);

	d.conectarse(j2, c0);
	ASSERT(d.cantMovimientosParaCaptura(c0) == 0);	
	ASSERT(d.cantMovimientosParaCaptura(c7) == 0);

	d.conectarse(j3, c7);
	ASSERT(d.cantMovimientosParaCaptura(c0) == 0);
	ASSERT(d.cantMovimientosParaCaptura(c7) == 0);

	// j1 se mueve fuera del área del pokémon en c0 y en c7
	// de forma automática se acumulan movimientos

	d.moverse(j1, Coordenada(12,1));
	ASSERT(d.cantMovimientosParaCaptura(c0) == 1);
	ASSERT(d.cantMovimientosParaCaptura(c7) == 1);

	d.moverse(j1, Coordenada(12,2));
	ASSERT(d.cantMovimientosParaCaptura(c0) == 2);
	ASSERT(d.cantMovimientosParaCaptura(c7) == 2);

	d.moverse(j1, Coordenada(12,1));
	ASSERT(d.cantMovimientosParaCaptura(c0) == 3);
	ASSERT(d.cantMovimientosParaCaptura(c7) == 3);

	
	d.moverse(j1, c0); // MOVIMIENTO INVÁLIDO
	ASSERT(d.cantMovimientosParaCaptura(c0) == 3 || d.cantMovimientosParaCaptura(c0) == 4); // SE CONSIDERAN AMBAS IMPLEMENTACIONES
	ASSERT(d.cantMovimientosParaCaptura(c7) == 3 || d.cantMovimientosParaCaptura(c7) == 4); // SE CONSIDERAN AMBAS IMPLEMENTACIONES
	
	// j2 entra al área del pokemon en c0, reiniciando la cantidad de movimientos

	d.moverse(j2, Coordenada(3,0));
	d.moverse(j2, Coordenada(1,0));

	ASSERT(d.cantMovimientosParaCaptura(c0) == 0);
	ASSERT(d.cantMovimientosParaCaptura(c7) == 4 || d.cantMovimientosParaCaptura(c7) == 5); // SE CONSIDERAN AMBAS IMPLEMENTACIONES

	// j1 vuelve a moverse fuera del área del pokemon c0 y c7,
	// aumentando la cantidad de movimientos

	d.moverse(j1, Coordenada(12,2)); // MOVIMIENTO PUEDE SER VÁLIDO O NO, EN AMBOS CASOS SUMA MOV. PARA CAPTURA
	ASSERT(d.cantMovimientosParaCaptura(c0) == 1);
	ASSERT(d.cantMovimientosParaCaptura(c7) == 5 || d.cantMovimientosParaCaptura(c7) == 6); // SE CONSIDERAN AMBAS IMPLEMENTACIONES

}


void test_entrenadores_posibles()
{
	Conj<Coordenada> cc;
	cc.Agregar(Coordenada(0,0));
	cc.Agregar(Coordenada(1,0));
	cc.Agregar(Coordenada(2,0));
	cc.Agregar(Coordenada(3,0));
	cc.Agregar(Coordenada(12,0));
	cc.Agregar(Coordenada(12,1));
	cc.Agregar(Coordenada(12,2));
	cc.Agregar(Coordenada(120,2));

	Driver d(cc);
	Conj<Jugador> vacio;

	d.agregarPokemon("Squirtle", Coordenada(0,0));
	ASSERT(d.entrenadoresPosibles(Coordenada(0,0)) == vacio);

	Nat j1 = d.agregarJugador();
	Nat j2 = d.agregarJugador();
	Nat j3 = d.agregarJugador();
	Conj<Jugador> todos;
	todos.Agregar(j1);
	todos.Agregar(j2);
	todos.Agregar(j3);

	d.conectarse(j1, Coordenada(12,0));
	ASSERT(d.entrenadoresPosibles(Coordenada(0,0)) == vacio);

	Conj<Jugador> entrenadores;
	entrenadores.Agregar(j2);
	d.conectarse(j2, Coordenada(0,0));
	ASSERT(d.entrenadoresPosibles(Coordenada(0,0)) == entrenadores);

	d.desconectarse(j2);
	d.conectarse(j2, Coordenada(12,0));
	ASSERT(d.entrenadoresPosibles(Coordenada(0,0)) == vacio);

	d.moverse(j2, Coordenada(120,2)); // MOVIMIENTO INVÁLIDO
	ASSERT(d.entrenadoresPosibles(Coordenada(0,0)) == vacio);

	d.conectarse(j3, Coordenada(120,2));
	ASSERT(d.entrenadoresPosibles(Coordenada(0,0)) == vacio);

	d.moverse(j1, Coordenada(12,1));
	ASSERT(d.entrenadoresPosibles(Coordenada(0,0)) == vacio);

	Conj<Jugador> entrenadores2;
	entrenadores2.Agregar(j1);
	d.desconectarse(j1);
	d.conectarse(j1, Coordenada(1,0));
	ASSERT(d.entrenadoresPosibles(Coordenada(0,0)) == entrenadores2);

	d.moverse(j1, Coordenada(0,0));
	ASSERT(d.entrenadoresPosibles(Coordenada(0,0)) == entrenadores2);
}


void test_atrapar_pokemon_test_simple()
{
	Conj<Coordenada> cc;
	cc.Agregar(Coordenada(0,0));
	cc.Agregar(Coordenada(1,0));
	cc.Agregar(Coordenada(2,0));
	cc.Agregar(Coordenada(3,0));
	cc.Agregar(Coordenada(10,0));
	cc.Agregar(Coordenada(11,0));

	Driver d(cc);

	d.agregarPokemon("Squirtle", Coordenada(0,0));

	Nat j1 = d.agregarJugador();
	Nat j2 = d.agregarJugador();

	d.conectarse(j1, Coordenada(2,0));
	d.conectarse(j2, Coordenada(10,0));

	Dicc< Pokemon , Nat > pokemons;
	ASSERT( d.pokemons(j1) == pokemons );
	ASSERT( d.pokemons(j2) == pokemons );

	d.moverse(j2, Coordenada(11,0));
	d.moverse(j2, Coordenada(10,0));
	d.moverse(j2, Coordenada(11,0));
	d.moverse(j2, Coordenada(10,0));
	d.moverse(j2, Coordenada(11,0));
	d.moverse(j2, Coordenada(10,0));
	d.moverse(j2, Coordenada(11,0));
	d.moverse(j2, Coordenada(10,0));
	d.moverse(j2, Coordenada(11,0));
	d.moverse(j2, Coordenada(10,0));
	d.moverse(j2, Coordenada(11,0));
	d.moverse(j2, Coordenada(10,0));

	ASSERT( d.pokemons(j2) == pokemons );
	pokemons.Definir("Squirtle",1);
	ASSERT( d.pokemons(j1) == pokemons );

}

void test_cantidad_de_pokemons_totales_usando_mover()
{
	Conj<Coordenada> cc;
	cc.Agregar(Coordenada(0,0));
	cc.Agregar(Coordenada(1,0));
	cc.Agregar(Coordenada(2,0));
        
	cc.Agregar(Coordenada(12,0));
	cc.Agregar(Coordenada(12,1));
	cc.Agregar(Coordenada(12,2));
        
	cc.Agregar(Coordenada(120,2));
	cc.Agregar(Coordenada(120,3));

	Driver d(cc);

	ASSERT(d.cantPokemonsTotales() == 0);
	d.agregarPokemon("Squirtle", Coordenada(0,0));
	ASSERT(d.cantPokemonsTotales() == 1);
	d.agregarPokemon("Rattata", Coordenada(12,0));
	ASSERT(d.cantPokemonsTotales() == 2);

	Nat j1 = d.agregarJugador();
	Nat j2 = d.agregarJugador();
	Nat j3 = d.agregarJugador();
	
	d.conectarse(j1, Coordenada(12,0));
	d.conectarse(j2, Coordenada(0,0));

	d.moverse(j2, Coordenada(12,0)); // Movimiento no válido, se teletransporta, se sanciona. sanciones(j2) = 1
	d.moverse(j2, Coordenada(120,2)); // Movimiento no válido, se teletransporta, se sanciona. sanciones(j2) = 2

	d.conectarse(j3, Coordenada(120,2));

	d.moverse(j1, Coordenada(12,1)); // Movimiento válido
	d.moverse(j1, Coordenada(120,3)); // Movimiento no válido, se teletransporta, se sanciona. sanciones(j1) = 1
	d.moverse(j1, Coordenada(0,0)); // Movimiento no válido, se teletransporta, se sanciona. sanciones(j1) = 2


	ASSERT(d.cantPokemonsTotales() == 2);
            
	for (int i = 0; i < 11; ++i)
	{
		d.moverse(j3, Coordenada(120,2)); // Movimiento válido
		d.moverse(j3, Coordenada(120,3)); // Movimiento válido
	}
	
	ASSERT(d.pokemons(j1).CantClaves() == 1);
	ASSERT(d.pokemons(j2).CantClaves() == 0 || d.pokemons(j2).CantClaves() == 1); // SE CONSIDERAN AMBAS IMPLEMENTACIONES
	ASSERT(d.cantPokemonsTotales() == 2);

	d.moverse(j1, Coordenada(120,2)); // Movimiento no válido, se teletransporta, se sanciona. sanciones(j1) = 3
	d.moverse(j1, Coordenada(0,0)); // Movimiento no válido, se teletransporta, se sanciona. sanciones(j1) = 4
	d.moverse(j1, Coordenada(120,2)); // Movimiento no válido, se teletransporta, se sanciona. sanciones(j1) = 5

	ASSERT(d.cantPokemonsTotales() == 1);

}

void test_cantidad_misma_especie_usando_mover()
{
	Conj< Coordenada > cc;
	cc.Agregar(Coordenada(0,0));
	cc.Agregar(Coordenada(1,0));
	cc.Agregar(Coordenada(2,0));
	cc.Agregar(Coordenada(12,0));
	cc.Agregar(Coordenada(12,1));
	cc.Agregar(Coordenada(12,2));
	cc.Agregar(Coordenada(120,2));
	cc.Agregar(Coordenada(120,3));

	Driver d(cc);

	d.agregarPokemon("Squirtle", Coordenada(0,0));
	d.agregarPokemon("Rattata", Coordenada(12,0));
	d.agregarPokemon("Squirtle", Coordenada(120,2));

	ASSERT(d.cantMismaEspecie("Squirtle") == 2);
	ASSERT(d.cantMismaEspecie("Rattata") == 1);

	Nat j1 = d.agregarJugador();
	Nat j2 = d.agregarJugador();
	Nat j3 = d.agregarJugador();

	d.conectarse(j1, Coordenada(12,0));
	d.conectarse(j2, Coordenada(0,0));

	d.moverse(j2, Coordenada(12,0)); // MOVIMIENTO INVÁLIDO
	d.moverse(j2, Coordenada(120,2)); // MOVIMIENTO INVÁLIDO
	d.moverse(j2, Coordenada(0,0)); // MOVIMIENTO INVÁLIDO O NO

	d.conectarse(j3, Coordenada(120,2));

	d.moverse(j1, Coordenada(12,1));
	d.moverse(j1, Coordenada(120,2));  // MOVIMIENTO INVÁLIDO
	d.moverse(j1, Coordenada(12,0)); // MOVIMIENTO INVÁLIDO O NO

	for (int i = 0; i < 10; ++i)
	{
		d.moverse(j3, Coordenada(120,3));
		d.moverse(j3, Coordenada(120,2));
	}

	ASSERT(d.pokemons(j1).CantClaves() == 1);
	ASSERT(d.pokemons(j2).CantClaves() == 1);
	ASSERT(d.pokemons(j3).CantClaves() == 0);
	ASSERT(d.cantPokemonsTotales() == 3);

	ASSERT(d.cantMismaEspecie("Squirtle") == 2);	
	ASSERT(d.cantMismaEspecie("Rattata") == 1);

}

void test_indice_de_rareza_usando_mover()
{
	//100 - (100 × cantMismaEspecie(p, j) / cantPokémonsTotales(j))
	Conj<Coordenada> cc;
	cc.Agregar(Coordenada(0,0));
	cc.Agregar(Coordenada(1,0));
	cc.Agregar(Coordenada(2,0));
	    
	cc.Agregar(Coordenada(12,0));
	cc.Agregar(Coordenada(12,1));
	cc.Agregar(Coordenada(12,2));
	    
	cc.Agregar(Coordenada(120,2));

	Driver d(cc);

	d.agregarPokemon("Squirtle", Coordenada(0,0));
	ASSERT(d.indiceRareza("Squirtle") == 0);
	    
	d.agregarPokemon("Rattata", Coordenada(12,0));
	ASSERT(d.indiceRareza("Squirtle") == 50);
	    
	ASSERT(d.indiceRareza("Rattata") ==	50);
	d.agregarPokemon("Squirtle", Coordenada(120,2));
	    
	Nat rarezaS = 100 - 200/3;
	ASSERT(d.indiceRareza("Squirtle") == rarezaS);
	    
	Nat rarezaR = 100 - 100/3;
	ASSERT(d.indiceRareza("Rattata") == rarezaR);

	Nat j1 = d.agregarJugador();
	Nat j2 = d.agregarJugador();
	Nat j3 = d.agregarJugador();

	d.conectarse(j1, Coordenada(12,0));
	d.conectarse(j2, Coordenada(0,0));
	d.conectarse(j3, Coordenada(120,2));

	d.moverse(j1, Coordenada(12,1));
	d.moverse(j1, Coordenada(12,0));
	d.moverse(j1, Coordenada(12,1));
	d.moverse(j1, Coordenada(12,0));
	d.moverse(j1, Coordenada(12,1));
	d.moverse(j1, Coordenada(12,0));
	d.moverse(j1, Coordenada(12,1));
	d.moverse(j1, Coordenada(12,0));
	d.moverse(j1, Coordenada(12,1));
	d.moverse(j1, Coordenada(12,0));
	d.moverse(j1, Coordenada(12,1));
	d.moverse(j1, Coordenada(12,0));

	ASSERT(d.indiceRareza("Squirtle") == rarezaS);
	ASSERT(d.indiceRareza("Rattata") == rarezaR);

	d.moverse(j2, Coordenada(120,2)); // MOVIMIENTO INVÁLIDO
	d.moverse(j2, Coordenada(12,0)); // MOVIMIENTO INVÁLIDO
	d.moverse(j2, Coordenada(120,2)); // MOVIMIENTO INVÁLIDO
	d.moverse(j2, Coordenada(12,0)); // MOVIMIENTO INVÁLIDO
	d.moverse(j2, Coordenada(120,2)); // MOVIMIENTO INVÁLIDO
	    
	ASSERT(d.indiceRareza("Squirtle") == 50);
	ASSERT(d.indiceRareza("Rattata") == 50);
}

////////////////////////////////////////////////////////////////
// ACERCA DE LA COMPLEJIDAD TEMPORAL
////////////////////////////////////////////////////////////////

void plotAgregarPokemon(int * xvals, double * yvals, double * yvals_ori, int nro_experimentos, double c1, double c2)
{
	//std::string plot_comand = "plot \"Agregar-Pokemon-Plot.dat\" using 1:2 t \"Mediciones del algoritmo\", \"Agregar-Pokemon-Plot.dat\" using 1:3 with lines t \""+ std::to_string(c1) +" * P + "+ std::to_string(c2) +" * EC log(EC)\" ";
	char plot_comand[200];
	sprintf(plot_comand, "plot \"Agregar-Pokemon-Plot.dat\" using 1:2 t \"Mediciones del algoritmo\", \"Agregar-Pokemon-Plot.dat\" using 1:3 with lines t \" %f * P + %f * EC log(EC)\" ", c1, c2);
	char * commandsForGnuplot[] = {	 "set title \"Complejidad temporal: agregarPokemon\"", 
											 "set xlabel \"Tamaño de la entrada: P + EC\"", 
											 "set ylabel \"Tiempo [us]\"", 
											 // "plot \"Agregar-Pokemon-Plot.dat\" using 1:2 t \"Mediciones del algoritmo\",
											 //  \"Agregar-Pokemon-Plot.dat\" using 1:3 with lines t \"Curva esperada\" ",
											 plot_comand,
											 "set term png",
											 "set output \"Agregar-Pokemon-Plot.png\"",
											 "replot",
											 "set term x11"};
 	FILE * temp = fopen("Agregar-Pokemon-Plot.dat", "w");	 
	FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
	int i;
	for (i=0; i < nro_experimentos; i++)
	{
		fprintf(temp, "%d %lf %lf\n", xvals[i], yvals[i], yvals_ori[i]); //Write the data to a temporary file
	}
	for (i=0; i < 8; i++)
	{
		fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
	}
}

void scatterAgregarPokemon(std::string title, std::string filename, int * ECs, int * Ps, double * yvals, int nro_experimentos)
{
	char * commandsForGnuplot[] = {  "set title \"Complejidad temporal: agregarPokemon\"", 
									 "set xlabel \"EC\"", 
									 "set ylabel \"P\"", 
									 "plot \"Agregar-Pokemon-Scatter.dat\" using 1:2:3 with points palette pointsize 3 pointtype 7 title \"Tiempo [us]\"",
									 "set term png",
									 "set output \"Agregar-Pokemon-Scatter.png\"",
									 "replot",
									 "set term x11"};
	FILE * temp = fopen("Agregar-Pokemon-Scatter.dat", "w");	 
	FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
	int i,j;
	for (i=0; i < nro_experimentos; i++)
	{
		fprintf(temp, "%d %d %lf \n", ECs[i], Ps[i], yvals[i]); //Write the data to a temporary file
	}
	for (i=0; i < 8; i++)
	{
		fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
	}
}

bool calc_curva_esperada(double mediciones_esperadas[], double mediciones[], int n_max, int m_max, int nro_experimentos, double & c_1, double & c_2)
{
	long double umbral_ok = 1;
	double c1_max = 2;
	double c2_max = 2;
	int delta_n = n_max / ( nro_experimentos - 1 );
	int delta_m = m_max / ( nro_experimentos - 1 );
	long double min_max_error = 100000000.;
	long double max_error = -1;
	bool res = false;

	double c1_max_error = -1;
	double c2_max_error = -1;

	double c1_min_max_error = -1;
	double c2_min_max_error = -1;

	for(double c1 = 0.001; c1 < c1_max; c1+=0.001)
	{
		for(double c2 = 0.001; c2 < c2_max; c2+=0.001)
		{
			max_error = -1;
			for( int i = 0; i < nro_experimentos; i++ )
			{
				double n = delta_n * ( i + 1 );
				double m = delta_m * ( i + 1 );
				long double aux = fabs( c1 * n + c2 * m * log(m) - mediciones[i] );
				//output_file << c1 * n + c2 * m * log(m) << "," << mediciones[i] << std::endl;
				if( max_error < aux )
				{
					max_error = aux;
					c1_max_error = c1;
					c2_max_error = c2;
				}
				//output_file << "for: max_error:" << max_error << std::endl;
			}
			//output_file << "fuera del for: max_error:" << max_error << std::endl;

			if( min_max_error > max_error )
			{
				min_max_error = max_error;
				c1_min_max_error = c1_max_error;
				c2_min_max_error = c2_max_error;
			}
		}
	}


	for(int l = 0; l < nro_experimentos; l++)
	{
		double n = delta_n * ( l + 1 );
		double m = delta_m * ( l + 1 );
		mediciones_esperadas[l] = ( c1_min_max_error * n + c2_min_max_error * m * log(m) );
	}

	c_1 = c1_min_max_error;
	c_2 = c2_min_max_error;

}

void test_complejidad_agregarPokemon()
{
	// Se pretende complejidad: O( |P| + EC * log(EC) )
	// Donde |P| es el nombre más largo para un pokémon en el d.
	// EC es la máxima cantidad de jugadores esperando para atrapar un pokémon

	int P_max = 500;
	int EC_max = 700;

	double cant_proms = 30.; 

	int nro_experimentos = 40;
	int delta_P = P_max / ( nro_experimentos - 1 );
	int delta_EC = EC_max / ( nro_experimentos - 1 );

	double mediciones[nro_experimentos];
	double mediciones_esperadas[nro_experimentos];
	int ECs[nro_experimentos];
	int Ps[nro_experimentos];
	int entrada[nro_experimentos];

	double ti,tf;
	struct timeval tp;
	int rtn;

	Conj<Coordenada> cc;
	cc.Agregar(Coordenada(0,0));
	cc.Agregar(Coordenada(10,10));

	cout << "Test de complejidad en agregarPokemon: " ;

	for(int l = 0; l < nro_experimentos; l++)
	{
		cout << l * 100./nro_experimentos << "%... " ;

		// Calculo el tamaño de las entradas
		int P = delta_P * (l + 1);
		int EC = delta_EC * (l + 1);

		// Genero el nombre del pokemon de tamaño P
		Pokemon nombre;
		for(int i = 0; i < P; i++)
		{
			nombre = nombre + 'a';
		}

		double sum = 0.;
		for(int j = 0; j < cant_proms; j++)
		{

			// Creo un driver
			Driver d(cc);

			// Agrego un pokemon
			d.agregarPokemon(nombre, Coordenada(0,0));

			// Agrego los EC jugadores
			for(int i = 0; i < EC; i++)
			{
				int j = d.agregarJugador();
				d.conectarse(j, Coordenada(0,0));
			}
		
			rtn = gettimeofday(&tp, NULL);
			ti = (long double)tp.tv_sec+(1.e-6)*tp.tv_usec;

			d.agregarPokemon(nombre, Coordenada(10,10));
			
			rtn = gettimeofday(&tp, NULL);
			tf = (long double)tp.tv_sec+(1.e-6)*tp.tv_usec;

			sum += (tf - ti);

		}

		ECs[l] = EC;
		Ps[l] = P;
		entrada[l] = P + EC;
		mediciones[l] = 1.e6 * ( sum / cant_proms );
	}

	double c1, c2;
	calc_curva_esperada(mediciones_esperadas,mediciones,P_max,EC_max,nro_experimentos, c1, c2);
	plotAgregarPokemon(entrada,mediciones,mediciones_esperadas,nro_experimentos, c1, c2);
	scatterAgregarPokemon("Complejidad temporal: agregarPokemon","Agregar-Pokemon-Scatter",ECs,Ps,mediciones,nro_experimentos);

}

int main(int argc, char **argv)
{

	std::ofstream output_file;
	output_file.open("safe_output.log", std::ofstream::out | std::ofstream::app);

	// Acerca del mapa
	output_file << ">> Acerca del mapa: \n";
	output_file.flush();

	RUN_TEST(test_constructor_con_mapa);
	output_file << "\n";
	output_file.flush();

	// Acerca de los pokemons
	output_file << ">> Acerca de los pokemons: \n";
	output_file.flush();

	RUN_TEST(test_puedo_agregar_pokemons_1);
	output_file.flush();

	RUN_TEST(test_puedo_agregar_pokemons_2);
	output_file.flush();

	RUN_TEST(test_pokemon_en_posicion);
	output_file.flush();

	RUN_TEST(test_pos_con_pokemons);
	output_file.flush();

	RUN_TEST(test_hay_pokemon_cercano);
	output_file.flush();

	RUN_TEST(test_coordenada_pokemon_cercano);
	output_file << "\n";
	output_file.flush();

	// Acerca de los jugadores
	output_file << ">> Acerca de los jugadores: \n";
	output_file.flush();

	RUN_TEST(test_agregar_jugadores);
	output_file.flush();

	RUN_TEST(test_conectar_jugadores);
	output_file.flush();

	RUN_TEST(test_desconectar_jugadores);
	output_file.flush();

	RUN_TEST(test_mover_jugador_asigna_correcta_coordenada);
	output_file.flush();

	RUN_TEST(test_sanciones);
	output_file.flush();

	RUN_TEST(test_expulsion);
	output_file << "\n";
	output_file.flush();

	// Acerca de pokemons y jugadores
	output_file << ">> Acerca de los jugadores y los pokemons: \n";
	output_file.flush();

	RUN_TEST(test_agregar_pokemones_y_jugadores);
	output_file.flush();

	RUN_TEST(test_cantidad_de_movimientos_para_captura);
	output_file.flush();

	RUN_TEST(test_entrenadores_posibles);
	output_file.flush();

	RUN_TEST(test_atrapar_pokemon_test_simple);
	output_file.flush();

	RUN_TEST(test_cantidad_de_pokemons_totales_usando_mover);
	output_file.flush();

	RUN_TEST(test_cantidad_misma_especie_usando_mover);
	output_file.flush();

	RUN_TEST(test_indice_de_rareza_usando_mover);
	output_file << " \n";
	output_file.flush();
	
	// Acerca de la complejidad temporal
	output_file << ">> Acerca de la complejidad temporal (en experimentación):  \n";
	RUN_TEST(test_complejidad_agregarPokemon);
	output_file << " \n";
		
	output_file.close();
	
	return 0;
}
