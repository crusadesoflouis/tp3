#include <iostream>
#include "mini_test.h"
#include "mapa.h"

using namespace ::std;
 
void diccmatriz(){
  //inicializacion de datos
  Mapa m;
  Coordenada c_1_1(1,1);
  Coordenada c_3_3(3,3);
  Coordenada c_3_1(3,1);
  Coordenada c_3_2(3,2);
  Coordenada c_7_2(7,2);
  Coordenada c_2_2(2,2);

  ASSERT_EQ(m.Vacio(),true);
  m.AgregarCoord(c_1_1);
  ASSERT_EQ(m.Vacio(),false);
  ASSERT_EQ(m.PosExistente(c_3_3),false);
  ASSERT_EQ(m.PosExistente(c_1_1),true);
  m.AgregarCoord(c_3_3);
  m.AgregarCoord(c_3_1);
  m.AgregarCoord(c_3_2);
  m.AgregarCoord(c_7_2);
  m.AgregarCoord(c_2_2);
  ASSERT_EQ(m.Haycamino(c_1_1,c_1_1),true);
  ASSERT_EQ(m.Haycamino(c_3_3,c_2_1),true);
  ASSERT_EQ(m.Haycamino(c_2_1,c_3_3),true);
  ASSERT_EQ(m.Haycamino(c_1_1,c_3_3),false);
  }

int main() {

RUN_TEST(diccmatriz);

  return 0;
}
