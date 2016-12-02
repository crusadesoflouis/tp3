#include "Juego.h"

/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************FUNCIONES AUXILIARES****************************/
/**************************************************************************************************/
/**************************************************************************************************/
bool MovimientoInvalido(const coordenada &c1,const coordenada  &c2){
  return true;
}

Nat DistanciaEuclidea(const coordenada c1, const coordenada c2){
  Nat a = 0;
  Nat b = 0;
  if (c1.latitud() > c2.latitud()) {
    a = ( ( c1.latitud() - c2.latitud() ) ^ 2 );
  }
  else
    a =  ( (c2.latitud() - c1.latitud()) ^ 2 );

  if (c1.longitud() > c2.longitud())
    b =	 ( (c1.longitud() - c2.longitud()) ^ 2 );
  else
    b =  ( (c2.longitud() - c1.longitud()) ^ 2 );
  return a+b;
}

bool Juego::PuedeAtrapar (coordenada c1,const coordenada &c2){
  return DistanciaEuclidea(c1,c2) <= 4 &&  Mundo.HayCamino(c1,c2);
}


void Juego::Capturar(const coordenada &c){
 InfoJug* aux = FuturasCapturas.Obtener(c)->PosiblesEntrenadores.Tope().Iter();
 aux->EstaCazando = false;
 aux->CazaActual.EliminarSiguiente();
 Pokemon capturado = FuturasCapturas.Obtener(c)->Bicho;
 aux->Atrapados.Agregar(capturado);
 delete FuturasCapturas.Obtener(c);
 FuturasCapturas.Borrar(c);
}


void Juego::EliminarJugador(const Jugador &j){
Conj<String>::const_Iterador IT = Jugadores[j]->Atrapados.CrearIt();
  while (IT.HaySiguiente()) {
    Nat Cantidad = Jugadores[j]->Atrapados.Repeticiones(IT.Siguiente());
    Nat CanPok = Pokedex.Significado(IT.Siguiente());
    Pokedex.Borrar(IT.Siguiente());
    Nat Diferencia = CanPok - Cantidad;
    if (Diferencia != 0) {
      Pokedex.Definir(IT.Siguiente(),Diferencia);
    }
  }
}
/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************GENERADORES****************************/
/**************************************************************************************************/
/**************************************************************************************************/

Juego::Juego(Mapa &map):Mundo(map),TotalPokemones(0){}

Juego::~Juego(){
  for (Nat i = 1; i < Jugadores.Longitud(); i++) {
    delete Jugadores[i];
  }
  Conj<coordenada> C = FuturasCapturas.Claves();
  Conj<coordenada>::Iterador IT = C.CrearIt();
  while (IT.HaySiguiente()) {
     delete FuturasCapturas.Obtener(IT.Siguiente());
     IT.Avanzar();
  }
}



Jugador Juego::AgregarJugador(){
  Juego::InfoJug* nuevo = new InfoJug;
  Jugadores.AgregarAtras(nuevo);
  unsigned int ID = Jugadores.Longitud() - 1;
  return  ID;
}

void Juego::AgregarPokemon(coordenada c, const Pokemon &p){
//agrego el pokemon en el mc donde estan las pos de pokemones salvajes
PosSalvajes.AgregarRapido(c);
// si estaba definido aumento en 1 su "cardinal" sino lo defino
  if (Pokedex.Definido(p)) {
      Nat valorAnterio = Pokedex.Significado(p);
      valorAnterio++;
      Pokedex.Borrar(p);
      Pokedex.Definir(p,valorAnterio);
      //tengo que eliminarlo y redefinirlo porque no tengo funciones
      //que me permita redefinirlo...
  }
  else{
    Pokedex.Definir(p,1);
  }
// creo un puntero a InfoPos que es donde hay que gener
//un heap con todos los jugadores cercanos a donde agregue
//dicho pokemon
  InfoPos* info = new InfoPos(p);
  bool online = false;
  FuturasCapturas.Definir(c,info);

  //creo un iterador al vector donde estan todos los jugadores
  Vector<InfoJug*>::const_Iterador IT = Jugadores.CrearIt();
  Nat pos = 1;
  while (IT.HaySiguiente()) {
    online = IT.Siguiente()->Conectado;
    if (online && PuedeAtrapar(c,IT.Siguiente()->Posicion)) {
      Tupla<InfoJug*> t(Jugadores[pos],IT.Siguiente()->Atrapados.Cardinal(),pos);
      FuturasCapturas.Obtener(c)->PosiblesEntrenadores.Encolar(t);
    }
    pos++;
    IT.Avanzar();
  }

}

void Juego::Conectarse(const coordenada &c,const Jugador j){
  //assert(Jugadores[j]->Sanciones < 5);
  Jugadores[j]->Conectado = true;
  Jugadores[j]->Posicion = c;

  if (HayPokemonCercano(c)) {
      Tupla<InfoJug*> t(Jugadores[j],Jugadores[j]->Atrapados.Cardinal(),j);
      FuturasCapturas.Obtener(PosPokemonCercano(c))->PosiblesEntrenadores.Encolar(t);
  }
}


void Juego::Desconectarse(const Jugador j){
  Jugadores[j]->Conectado = false;
  if (Jugadores[j]->EstaCazando) {
    Jugadores[j]->CazaActual.EliminarSiguiente();
  }
 if (FuturasCapturas.Obtener(PosPokemonCercano(Jugadores[j]->Posicion))->PosiblesEntrenadores.esVacia()) {
   FuturasCapturas.Obtener(PosPokemonCercano(Jugadores[j]->Posicion))->Turnos = 0;
  }
}


void Juego::Moverse(const coordenada &c,const Jugador j){
  assert(Jugadores[j]->Sanciones < 5);
  bool HayPokemon = false;
  bool HayPokemonNuevo = false;
  coordenada vieja(0,0);
  coordenada nueva(0,0);

  if (MovimientoInvalido(c,Jugadores[j]->Posicion)) {
    Jugadores[j]->Sanciones++;
  }

if (Jugadores[j]->Sanciones < 5) {

    if (HayPokemonCercano(Jugadores[j]->Posicion)) {
    HayPokemon = true;
    coordenada e(PosPokemonCercano(Jugadores[j]->Posicion).latitud(),PosPokemonCercano(Jugadores[j]->Posicion).longitud());
    vieja = e;
    }

    if (HayPokemonCercano(c)) {
      HayPokemonNuevo = true;
      nueva = PosPokemonCercano(c);
    }

    if (HayPokemonNuevo && HayPokemon && vieja == nueva) {
      Conj<coordenada>::Iterador IT = PosSalvajes.CrearIt();
      while (IT.HaySiguiente()) {
        if (IT.Siguiente() != c) {
          FuturasCapturas.Obtener(IT.Siguiente())->Turnos++;
          if (FuturasCapturas.Obtener(IT.Siguiente())->Turnos == 10 && IT.Siguiente() != vieja) {
             Capturar(IT.Siguiente());
          }
        }
        IT.Avanzar();
      }
    }
    else{
      //esto implica que en la posicion nueva y vieja son distintas
      //osea puede ser que ambas sean vacias
      //o que salgo de una cola y entro a otra
      //o que de no estar en nada voy a una nueva capturas
      if (HayPokemon && HayPokemonNuevo) {
        // caso en el que salgo de una cola y entro a otra
        Jugadores[j]->CazaActual.EliminarSiguiente();
        FuturasCapturas.Obtener(vieja)->Turnos++;
        if (FuturasCapturas.Obtener(vieja)->Turnos == 10) {
           Capturar(vieja);
        }
        FuturasCapturas.Obtener(nueva)->Turnos = 0;
        Tupla<InfoJug*> t(Jugadores[j],Jugadores[j]->Atrapados.Cardinal(),j);
        FuturasCapturas.Obtener(nueva)->PosiblesEntrenadores.Encolar(t);
        Conj<coordenada>::Iterador IT = PosSalvajes.CrearIt();
        while (IT.HaySiguiente()) {
          if (IT.Siguiente()!= vieja && IT.Siguiente() != nueva) {
            FuturasCapturas.Obtener(IT.Siguiente())->Turnos++;
          }

          if (FuturasCapturas.Obtener(IT.Siguiente())->Turnos == 10) {
            ////////////////////////////////// CAPTURAR /////////////////////////
            Capturar(IT.Siguiente());
          }
          IT.Avanzar();
        }
      }
      else{
          //salgo de una posicion con pokemon a un lugar donde no hay pokemon
          if (HayPokemon) {
            Jugadores[j]->CazaActual.EliminarSiguiente();
            Conj<coordenada>::Iterador IT = PosSalvajes.CrearIt();
            while (IT.HaySiguiente()) {
              FuturasCapturas.Obtener(IT.Siguiente())->Turnos++;
              if (FuturasCapturas.Obtener(IT.Siguiente())->Turnos == 10) {
                Capturar(IT.Siguiente());
              }
              IT.Avanzar();
            }
          }
          else{
            // entro a una posición con un pokemon y lo encolado
            FuturasCapturas.Obtener(nueva)->Turnos = 0;
            Tupla<InfoJug*> t(Jugadores[j],Jugadores[j]->Atrapados.Cardinal(),j);
            FuturasCapturas.Obtener(nueva)->PosiblesEntrenadores.Encolar(t);
          }
      }
    }
  }
  else{
    EliminarJugador(j);
  }
}


/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************OBSERVADORES****************************/
/**************************************************************************************************/
/**************************************************************************************************/

Mapa Juego::MAPA(){
  return Mundo;
}

bool Juego::HayCamino(const coordenada &c1,const coordenada &c2){
  return Mundo.HayCamino(c1,c2);
}

bool Juego::PosExistente(const coordenada &c1){
  return Mundo.PosExistente(c1);
}

bool Juego::EstaConectado(const Jugador j){
  return Jugadores[j]->Conectado;
}

Nat Juego::Sanciones(const Jugador j){
  return Jugadores[j]->Sanciones;
}

coordenada Juego::Posicion(const Jugador j){
  return Jugadores[j]->Posicion;
}


coordenada Juego::PosPokemonCercano(const coordenada &c){

  Conj<coordenada> PosValidas(ObtenerPosicionesCercanas(c));

  Conj<coordenada>::Iterador IT = PosValidas.CrearIt();
  while (IT.HaySiguiente() && FuturasCapturas.Obtener(IT.Siguiente()) == NULL) {
      IT.Avanzar();
  }

  return IT.Siguiente();
}

//falta iterador a Posiciones salvajes

//falta iterador a Expulsados

/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************OTRAS OPERACIONES****************************/
/**************************************************************************************************/
/**************************************************************************************************/

Conj<coordenada> Juego::ObtenerPosicionesCercanas(const coordenada c){
  Conj<coordenada> Posiciones;
  Posiciones.Agregar(c);
   coordenada a(c.latitud()-1,c.longitud());
   Posiciones.Agregar(a);
   coordenada b(c.latitud()-2,c.longitud());
   Posiciones.Agregar(b);
   coordenada d(c.latitud()-1,c.longitud()-1);
   Posiciones.Agregar(d);
   coordenada e(c.latitud(),c.longitud()-1);
   Posiciones.Agregar(e);
   coordenada f(c.latitud(),c.longitud()-2);
   Posiciones.Agregar(f);
   coordenada g(c.latitud()+1,c.longitud()-1);
   Posiciones.Agregar(g);
   coordenada h(c.latitud()+1,c.longitud());
   Posiciones.Agregar(h);
   coordenada i(c.latitud()+2,c.longitud());
   Posiciones.Agregar(i);
   coordenada j(c.latitud()+1,c.longitud()+1);
   Posiciones.Agregar(j);
   coordenada k(c.latitud(),c.longitud()+1);
   Posiciones.Agregar(k);
   coordenada l(c.latitud(),c.longitud()+2);
   Posiciones.Agregar(l);
   coordenada m(c.latitud()-1,c.longitud()+1);
   Posiciones.Agregar(m);
   Conj<coordenada> validas;
   Conj<coordenada>::Iterador IT = Posiciones.CrearIt();
   while (IT.HaySiguiente()) {
     if (Mundo.PosExistente(IT.Siguiente())) {
       validas.Agregar(IT.Siguiente());
     }
     IT.Avanzar();
   }
   return validas;
}

Conj <Jugador> Juego::Expulsados(){
  Conj <Jugador> expulsados;
  Vector<InfoJug*>::const_Iterador IT = Jugadores.CrearIt();
  Nat player = 0;
  while (IT.HaySiguiente()) {
    if (IT.Siguiente()->Sanciones > 4) {
      expulsados.Agregar(player);
    }
  player++;
 }

return expulsados;
}




bool Juego::HayPokemonCercano( const coordenada &c){

  //TODO

  return true;
}

Nat Juego::IndiceRareza(const Pokemon &p){
  Nat TipoPokemon = Pokedex.Significado(p);
  Nat Total = TotalPokemones;
  return TipoPokemon/Total;
}


Nat Juego::CantPokemonTotales(){
  return TotalPokemones;
}



typename Conj<String>::const_Iterador Juego::Pokemons(const Jugador j){
  return Jugadores[j]->Atrapados.CrearIt();
}

Nat Juego::cantMismaEspecie(const Pokemon &p)const{
  return Pokedex.Significado(p);
}

Pokemon PokemonEnPos (const coordenada &c){
  return
}


/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************ITERADOR****************************/
/**************************************************************************************************/
/**************************************************************************************************/


typename Juego::Iterador Juego::CrearIt() {
  return Iterador(this);
}

bool Juego::Iterador::HaySiguiente(){
  unsigned int cont = Posicion;
  unsigned int sig = cont++;
  unsigned int guarda = juego->Jugadores.Longitud();
  if (Posicion > guarda) {
    return false;
  }
  else{
      while (sig < guarda && juego->Jugadores[sig]->Sanciones > 4) {
        sig++;
      }
      if (sig < guarda) {
        return true;
      }
      return false;
  }
}

void Juego::Iterador::Avanzar(){
  assert(HaySiguiente());
  while (juego->Jugadores[Posicion]->Sanciones > 4) {
    Posicion++;
  }
}

Jugador Juego::Iterador::Siguiente(){
  assert(HaySiguiente());
  return Posicion;
}


//*******************************Iterador expulsados*************************/
typename Juego::Iterador_Exp Juego::CrearIt_Exp(){
  return Iterador_Exp(this);
}

bool Juego::Iterador_Exp::HaySiguiente(){
  unsigned int cont = Posicion;
  unsigned int sig = cont++;
  unsigned int guarda = juego->Jugadores.Longitud();
  if (Posicion > guarda) {
    return false;
  }
  else{
      while (sig < guarda && juego->Jugadores[sig]->Sanciones < 4) {
        sig++;
      }
      if (sig < guarda) {
        return true;
      }
      return false;
  }
}

void Juego::Iterador_Exp::Avanzar(){
  assert(HaySiguiente());
  while (juego->Jugadores[Posicion]->Sanciones < 4) {
    Posicion++;
  }
}

Jugador Juego::Iterador_Exp::Siguiente(){
  assert(HaySiguiente());
  return Posicion;
}
