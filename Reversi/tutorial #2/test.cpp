#include "pch.h"
#include "../Reversi/Tablero.h"

class TableroReversiPruebas : public ::testing::Test
{
protected:
	/*DATOS COMUNES A CASOS DE PRUEBA*/
	Tablero tbl;

	Tablero tblAnulado; //Se anulan las posiciones del estado inicial para facilitar otras pruebas.

	//Constructor inicialiador del suite de pruebas.
	TableroReversiPruebas();

	//Destructor del suite de pruebas.
	~TableroReversiPruebas();

	/*INICIALIZACION DE LAS PRUEBAS, puede eliminarse si no se usa.*/
	//Se invoca al iniciar cada prueba del accesorio.
	void SetUp() override;

	/*FINALIZACION DE LAS PRUEBAS, puede eliminarse si no se usa.*/
	//Se invoca al finalizar cada prueba del accesorio.
	void TearDown() override;
};

/*DEFINICION DE LOS METODOS BASICOS DEL ACCESORIO*/

TableroReversiPruebas::TableroReversiPruebas()
{

}
TableroReversiPruebas::~TableroReversiPruebas()
{

}
void TableroReversiPruebas::SetUp()
{
	//Se invoca despues del constructor, antes de cada caso de prueba.
	tblAnulado.colocarSimple(3, 3, Tablero::Ficha::nula);
	tblAnulado.colocarSimple(4, 4, Tablero::Ficha::nula);
	tblAnulado.colocarSimple(4, 3, Tablero::Ficha::nula);
	tblAnulado.colocarSimple(3, 4, Tablero::Ficha::nula);
	tblAnulado.casillasDisponibles = 63;
}
void TableroReversiPruebas::TearDown()
{

}

/*CASOS DE PRUEBA*/

//EFE: valida la inicializacion correcta que hace el constructor del TableroReversi.
//	Ademas, indirectamente valida el metodo verFicaEn().
TEST_F(TableroReversiPruebas, InicializacionCorrecta)
{
	ASSERT_EQ(tbl.verFichaEn(3, 3), Tablero::Ficha::blanca);
	ASSERT_EQ(tbl.verFichaEn(4, 4), Tablero::Ficha::blanca);
	ASSERT_EQ(tbl.verFichaEn(3, 4), Tablero::Ficha::negra);
	ASSERT_EQ(tbl.verFichaEn(4, 3), Tablero::Ficha::negra);
	for (int f = 0; f < 8; f++)
		for (int c = 0; c < 8; c++)
			if (!((f == 3) && (c == 3)) && !((f == 3) && (c == 4)) &&
				!((f == 4) && (c == 3)) && !((f == 4) && c == 4))
				ASSERT_EQ(tbl.verFichaEn(f, c), Tablero::Ficha::nula);
}
//EFE: Valida la colocacion correcta de fichas negras, blancas asi como anulacion,
//	en pocisiones seleccionadas del tablero.
TEST_F(TableroReversiPruebas, ColocacionFichaCorrecta)
{
	tbl.colocarSimple(0, 0, Tablero::Ficha::negra);
	tbl.colocarSimple(7, 7, Tablero::Ficha::blanca);
	tbl.colocarSimple(0, 7, Tablero::Ficha::nula);
	tbl.colocarSimple(7, 0, Tablero::Ficha::nula);
	EXPECT_EQ(tbl.verFichaEn(0, 0), Tablero::Ficha::negra);
	EXPECT_EQ(tbl.verFichaEn(7, 7), Tablero::Ficha::blanca);
	EXPECT_EQ(tbl.verFichaEn(0, 7), Tablero::Ficha::nula);
	EXPECT_EQ(tbl.verFichaEn(7, 0), Tablero::Ficha::nula);
}
//EFE: Prueba verFlanqueaFilas(), variante #1 - true.
TEST_F(TableroReversiPruebas, FlanqueaFilas_1_t)
{
	//Se coloca la posición con excepción de la jugada que se intenta validar positivamente (4,6,blanca).
	tblAnulado.colocarSimple(4, 0, Tablero::Ficha::blanca);
	tblAnulado.colocarSimple(4, 1, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 2, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 3, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 4, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 5, Tablero::Ficha::negra);
	//La (4,6) es la que se intenta validar.
	EXPECT_TRUE(tblAnulado.verFlanqueaFila(4, 6, Tablero::blanca));
}
//EFE: Prueba verFlanqueaFilas(), variante #1 - false.
TEST_F(TableroReversiPruebas, FlanqueaFilas_1_f)
{
	//Se coloca la posición con excepción de la jugada que se intenta validar positivamente (4,7,blanca).
	tblAnulado.colocarSimple(4, 0, Tablero::Ficha::blanca);
	tblAnulado.colocarSimple(4, 1, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 2, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 3, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 4, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 5, Tablero::Ficha::negra);
	//La (4,6) se deja nula.
	//La (4,7) es la que se intenta validar.
	EXPECT_FALSE(tblAnulado.verFlanqueaFila(4, 7, Tablero::blanca));
}
//EFE: Prueba verFlanqueaFilas(), variante #2 - true.
TEST_F(TableroReversiPruebas, FlanqueaFilas_2_t)
{
	//Se coloca la posición con excepción de la jugada que se intenta validar positivamente (4,3,blanca).
	tblAnulado.colocarSimple(4, 0, Tablero::Ficha::blanca);
	tblAnulado.colocarSimple(4, 1, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 2, Tablero::Ficha::negra);
	//La (4,3, blanca) es la que se intenta validar. 
	tblAnulado.colocarSimple(4, 4, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 5, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 5, Tablero::Ficha::blanca);

	EXPECT_TRUE(tblAnulado.verFlanqueaFila(4, 3, Tablero::blanca));
}
//EFE: Prueba verFlanqueaFilas(), variante #2 - false.
TEST_F(TableroReversiPruebas, FlanqueaFilas_2_f)
{
	//Se coloca la posición con excepción de la jugada que se intenta validar positivamente (4,7,blanca).
	tblAnulado.colocarSimple(4, 0, Tablero::Ficha::blanca);
	tblAnulado.colocarSimple(4, 1, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 2, Tablero::Ficha::negra);
	//La (4,3) se deja nula.
	tblAnulado.colocarSimple(4, 4, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 5, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 6, Tablero::Ficha::blanca);
	//La (4,7) es la que se intenta validar.
	EXPECT_FALSE(tblAnulado.verFlanqueaFila(4, 7, Tablero::blanca));
}
//EFE: Prueba verFlanqueaColumnas(), variante #1 - true.
TEST_F(TableroReversiPruebas, FlanqueaColumnas_1_t)
{
	//Se coloca la posición con excepción de la jugada que se intenta validar positivamente (6,0,blanca).
	tblAnulado.colocarSimple(1, 0, Tablero::Ficha::blanca);
	tblAnulado.colocarSimple(2, 0, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(3, 0, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 0, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(5, 0, Tablero::Ficha::negra);
	//La (6,0) es la que se intenta validar.
	EXPECT_TRUE(tblAnulado.verFlanqueaColumna(6, 0, Tablero::blanca));
}
//EFE: Prueba verFlanqueaColumnas(), variante #1 - false.
TEST_F(TableroReversiPruebas, FlanqueaColumnas_1_f)
{
	//Se coloca la posición con excepción de la jugada que se intenta validar positivamente (6,0,blanca).
	tblAnulado.colocarSimple(1, 0, Tablero::Ficha::blanca);
	tblAnulado.colocarSimple(2, 0, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(3, 0, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 0, Tablero::Ficha::negra);
	//La (5,0) se deja nula.
	//La (6,0) es la que se intenta validar.
	EXPECT_FALSE(tblAnulado.verFlanqueaColumna(6, 0, Tablero::blanca));
}
//EFE: Prueba verFlanqueaColumnas(), variante #2 - true.
TEST_F(TableroReversiPruebas, FlanqueaColumnas_2_t)
{
	//Se coloca la posición con excepción de la jugada que se intenta validar positivamente (3,0,blanca).
	tblAnulado.colocarSimple(1, 0, Tablero::Ficha::blanca);
	tblAnulado.colocarSimple(2, 0, Tablero::Ficha::negra);
	//La (3,0, blanca) es la que se intenta validar. 
	tblAnulado.colocarSimple(4, 0, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(5, 0, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(6, 0, Tablero::Ficha::blanca);

	EXPECT_TRUE(tblAnulado.verFlanqueaColumna(3, 0, Tablero::blanca));
}
//EFE: Prueba verFlanqueaColumnas(), variante #2 - false.
TEST_F(TableroReversiPruebas, FlanqueaColumnas_2_f)
{
	//Se coloca la posición con excepción de la jugada que se intenta validar positivamente (7,0,blanca).
	tblAnulado.colocarSimple(1, 0, Tablero::Ficha::blanca);
	tblAnulado.colocarSimple(2, 0, Tablero::Ficha::negra);
	//La (3,0) se deja nula.
	tblAnulado.colocarSimple(4, 0, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(5, 0, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(6, 0, Tablero::Ficha::blanca);
	//La (7,0) es la que se intenta validar.
	EXPECT_FALSE(tblAnulado.verFlanqueaColumna(7, 0, Tablero::blanca));
}
//Prueba verFlanqueaDigagonalAscendente(), variante #1-true.
TEST_F(TableroReversiPruebas, verFlanqueaDiagAsc_1_t)
{
	tblAnulado.colocarSimple(2, 0, Tablero::blanca);
	tblAnulado.colocarSimple(1, 1, Tablero::negra);
	//(0,2, blanca) es la que se quiere validar.
	EXPECT_TRUE(tblAnulado.verFlanqueaDiagonalAscendente(0, 2, Tablero::blanca));
}
//Prueba verFlanqueaDigagonalAscendente(), variante #1-false.
TEST_F(TableroReversiPruebas, verFlanqueaDiagAsc_1_f)
{
	tblAnulado.colocarSimple(3, 0, Tablero::blanca);
	tblAnulado.colocarSimple(2, 1, Tablero::negra);
	tblAnulado.colocarSimple(1, 2, Tablero::negra);
	//(0,3) se deja nula, se quiere validar (0,2, blanca)
	EXPECT_FALSE(tblAnulado.verFlanqueaDiagonalAscendente(0, 2, Tablero::blanca));
}
//Prueba verFlanqueaDigagonalAscendente(), variante #2-true.
TEST_F(TableroReversiPruebas, verFlanqueaDiagAsc_2_t)
{
	tblAnulado.colocarSimple(3, 0, Tablero::blanca);
	tblAnulado.colocarSimple(2, 1, Tablero::negra);
	tblAnulado.colocarSimple(1, 2, Tablero::negra);
	//(0,3, blanca) es la que se quiere validar.
	EXPECT_TRUE(tblAnulado.verFlanqueaDiagonalAscendente(0, 3, Tablero::blanca));
}
//Prueba verFlanqueaDigagonalAscendente(), variante #2-false.
TEST_F(TableroReversiPruebas, verFlanqueaDiagAsc_2_f)
{
	tblAnulado.colocarSimple(3, 0, Tablero::blanca);
	//(2,1) se deja nula, se intenta validar (1,2)
	tblAnulado.colocarSimple(0, 3, Tablero::negra);
	EXPECT_FALSE(tblAnulado.verFlanqueaDiagonalAscendente(1, 2, Tablero::blanca));
}
//Prueba verFlanqueaDigagonalAscendente(), variante #3-true.
TEST_F(TableroReversiPruebas, verFlanqueaDiagAsc_3_t)
{
	tblAnulado.colocarSimple(4, 0, Tablero::blanca);
	tblAnulado.colocarSimple(3, 1, Tablero::negra);
	tblAnulado.colocarSimple(2, 2, Tablero::negra);
	tblAnulado.colocarSimple(1, 3, Tablero::negra);
	//(0,4, blanca) es la que se quiere validar.
	EXPECT_TRUE(tblAnulado.verFlanqueaDiagonalAscendente(0, 4, Tablero::blanca));
}
//Prueba verFlanqueaDigagonalAscendente(), variante #3-false.
TEST_F(TableroReversiPruebas, verFlanqueaDiagAsc_3_f)
{
	tblAnulado.colocarSimple(4, 0, Tablero::blanca);
	tblAnulado.colocarSimple(3, 1, Tablero::negra);
	tblAnulado.colocarSimple(2, 2, Tablero::negra);
	//(1,3) se deja nula, se intenta validar (0,4)
	EXPECT_FALSE(tblAnulado.verFlanqueaDiagonalAscendente(0, 4, Tablero::blanca));
}
//Prueba verFlanqueaDigagonalAscendente(), variante #4-true.
TEST_F(TableroReversiPruebas, verFlanqueaDiagAsc_4_t)
{
	tblAnulado.colocarSimple(4, 0, Tablero::blanca);
	tblAnulado.colocarSimple(3, 1, Tablero::negra);
	//se intenta validar (2,2).
	tblAnulado.colocarSimple(1, 3, Tablero::negra);
	tblAnulado.colocarSimple(0, 4, Tablero::blanca);
	EXPECT_TRUE(tblAnulado.verFlanqueaDiagonalAscendente(2, 2, Tablero::blanca));
}
//Prueba verFlanqueaDigagonalAscendente(), variante #4-false.
TEST_F(TableroReversiPruebas, verFlanqueaDiagAsc_4_f)
{
	tblAnulado.colocarSimple(4, 0, Tablero::blanca);
	tblAnulado.colocarSimple(3, 1, Tablero::negra);
	//(2,2) se deja nula, se intenta validar (1,3)
	tblAnulado.colocarSimple(0, 4, Tablero::negra);
	EXPECT_FALSE(tblAnulado.verFlanqueaDiagonalAscendente(1, 3, Tablero::blanca));
}
//Prueba verFlanqueaDigagonalDescendente(), variante #1-true.
TEST_F(TableroReversiPruebas, verFlanqueaDiagDsc_1_t)
{
	tblAnulado.colocarSimple(0, 0, Tablero::blanca);
	tblAnulado.colocarSimple(1, 1, Tablero::negra);
	//(2,2, blanca) es la que se quiere validar.
	EXPECT_TRUE(tblAnulado.verFlanqueaDiagonalDescendente(2, 2, Tablero::blanca));
}
//Prueba verFlanqueaDigagonalDescendente(), variante #1-false.
TEST_F(TableroReversiPruebas, verFlanqueaDiagDsc_1_f)
{
	tblAnulado.colocarSimple(0, 0, Tablero::blanca);
	tblAnulado.colocarSimple(1, 1, Tablero::negra);
	tblAnulado.colocarSimple(2, 2, Tablero::negra);
	//(3,3) se deja nula, se quiere validar (3,2, blanca)
	EXPECT_FALSE(tblAnulado.verFlanqueaDiagonalDescendente(3, 2, Tablero::blanca));
}
//Prueba verFlanqueaDigagonalDescendente(), variante #2-true.
TEST_F(TableroReversiPruebas, verFlanqueaDiagDsc_2_t)
{
	tblAnulado.colocarSimple(0, 0, Tablero::blanca);
	tblAnulado.colocarSimple(1, 1, Tablero::negra);
	tblAnulado.colocarSimple(2, 2, Tablero::negra);
	//(3,3, blanca) es la que se quiere validar.
	EXPECT_TRUE(tblAnulado.verFlanqueaDiagonalDescendente(3, 3, Tablero::blanca));
}
//Prueba verFlanqueaDigagonalDescendente(), variante #2-false.
TEST_F(TableroReversiPruebas, verFlanqueaDiagDsc_2_f)
{
	tblAnulado.colocarSimple(0, 0, Tablero::blanca);
	//(1,1) se deja nula, se intenta validar (2,2)
	tblAnulado.colocarSimple(3, 3, Tablero::negra);
	EXPECT_FALSE(tblAnulado.verFlanqueaDiagonalDescendente(2, 2, Tablero::blanca));
}
//Prueba verFlanqueaDigagonalDescendente(), variante #3-true.
TEST_F(TableroReversiPruebas, verFlanqueaDiagDsc_3_t)
{
	tblAnulado.colocarSimple(0, 0, Tablero::blanca);
	tblAnulado.colocarSimple(1, 1, Tablero::negra);
	tblAnulado.colocarSimple(2, 2, Tablero::negra);
	tblAnulado.colocarSimple(3, 3, Tablero::negra);
	//(4,4, blanca) es la que se quiere validar.
	EXPECT_TRUE(tblAnulado.verFlanqueaDiagonalDescendente(4, 4, Tablero::blanca));
}
//Prueba verFlanqueaDigagonalDescendente(), variante #3-false.
TEST_F(TableroReversiPruebas, verFlanqueaDiagDsc_3_f)
{
	tblAnulado.colocarSimple(0, 0, Tablero::blanca);
	tblAnulado.colocarSimple(1, 1, Tablero::negra);
	tblAnulado.colocarSimple(2, 2, Tablero::negra);
	//(3,3) se deja nula, se intenta validar (4,4)
	EXPECT_FALSE(tblAnulado.verFlanqueaDiagonalDescendente(4, 4, Tablero::blanca));
}
//Prueba verFlanqueaDigagonalDescendente(), variante #4-true.
TEST_F(TableroReversiPruebas, verFlanqueaDiagDsc_4_t)
{
	tblAnulado.colocarSimple(0, 0, Tablero::blanca);
	tblAnulado.colocarSimple(1, 1, Tablero::negra);
	//se intenta validar (2,2).
	tblAnulado.colocarSimple(3, 3, Tablero::negra);
	tblAnulado.colocarSimple(4, 4, Tablero::blanca);
	EXPECT_TRUE(tblAnulado.verFlanqueaDiagonalDescendente(2, 2, Tablero::blanca));
}
//Prueba verFlanqueaDigagonalDescendente(), variante #4-false.
TEST_F(TableroReversiPruebas, verFlanqueaDiagDsc_4_f)
{
	tblAnulado.colocarSimple(0, 0, Tablero::blanca);
	tblAnulado.colocarSimple(1, 1, Tablero::negra);
	//(2,2) se deja nula, se intenta validar (3,3)
	tblAnulado.colocarSimple(4, 4, Tablero::negra);
	EXPECT_FALSE(tblAnulado.verFlanqueaDiagonalDescendente(3, 3, Tablero::blanca));
}
//Prueba validarJugada(), variante #1-true.
TEST_F(TableroReversiPruebas, validarJugada_1_t)
{
	//Se intenta probar (4,4, blanca).
	//Aqui se rellena una diagonal.
	tblAnulado.colocarSimple(7, 1, Tablero::blanca);
	tblAnulado.colocarSimple(6, 2, Tablero::negra);
	tblAnulado.colocarSimple(5, 3, Tablero::negra);
	tblAnulado.colocarSimple(3, 5, Tablero::negra);
	tblAnulado.colocarSimple(2, 6, Tablero::negra);
	tblAnulado.colocarSimple(1, 7, Tablero::blanca);
	//Aqui se rellena una columna.
	tblAnulado.colocarSimple(0, 4, Tablero::blanca);
	tblAnulado.colocarSimple(1, 4, Tablero::negra);
	tblAnulado.colocarSimple(2, 4, Tablero::negra);
	tblAnulado.colocarSimple(3, 4, Tablero::negra);
	tblAnulado.colocarSimple(5, 4, Tablero::negra);
	tblAnulado.colocarSimple(6, 4, Tablero::negra);
	tblAnulado.colocarSimple(7, 4, Tablero::blanca);
	EXPECT_TRUE(tblAnulado.validarJugada(4, 4, Tablero::blanca));
}
//Prueba validarJugada(), variante #1-false.
TEST_F(TableroReversiPruebas, validarJugada_1_f)
{
	//Se intenta probar (4,4, blanca).
	//Aqui se rellena una diagonal.
	tblAnulado.colocarSimple(7, 1, Tablero::blanca);
	tblAnulado.colocarSimple(6, 2, Tablero::negra);
	//(5,3) se deja nula.
	tblAnulado.colocarSimple(3, 5, Tablero::negra);
	tblAnulado.colocarSimple(2, 6, Tablero::negra);
	tblAnulado.colocarSimple(1, 7, Tablero::negra);
	//Aqui se rellena una columna.
	tblAnulado.colocarSimple(0, 4, Tablero::negra);
	tblAnulado.colocarSimple(1, 4, Tablero::negra);
	tblAnulado.colocarSimple(2, 4, Tablero::negra);
	tblAnulado.colocarSimple(3, 4, Tablero::negra);
	tblAnulado.colocarSimple(5, 4, Tablero::negra);
	//(6,4) se deja nula.
	tblAnulado.colocarSimple(7, 4, Tablero::blanca);
	EXPECT_FALSE(tblAnulado.validarJugada(4, 4, Tablero::blanca));
}
//Prueba validarJugada(), variante #2-true.
TEST_F(TableroReversiPruebas, validarJugada_2_t)
{
	//Se intenta probar (4,4, blanca).
	//Aqui se rellena una diagonal.
	tblAnulado.colocarSimple(7, 7, Tablero::blanca);
	tblAnulado.colocarSimple(6, 6, Tablero::negra);
	tblAnulado.colocarSimple(5, 5, Tablero::negra);
	tblAnulado.colocarSimple(3, 3, Tablero::negra);
	tblAnulado.colocarSimple(2, 2, Tablero::negra);
	tblAnulado.colocarSimple(1, 1, Tablero::blanca);
	//Aqui se rellena una columna.
	tblAnulado.colocarSimple(0, 4, Tablero::blanca);
	tblAnulado.colocarSimple(1, 4, Tablero::negra);
	tblAnulado.colocarSimple(2, 4, Tablero::negra);
	tblAnulado.colocarSimple(3, 4, Tablero::negra);
	tblAnulado.colocarSimple(5, 4, Tablero::negra);
	tblAnulado.colocarSimple(6, 4, Tablero::negra);
	tblAnulado.colocarSimple(7, 4, Tablero::blanca);
	EXPECT_TRUE(tblAnulado.validarJugada(4, 4, Tablero::blanca));
}
//Prueba validarJugada(), variante #2-false.
TEST_F(TableroReversiPruebas, validarJugada_2_f)
{
	//Se intenta probar (4,4, blanca).
	//Aqui se rellena una diagonal.
	tblAnulado.colocarSimple(7, 7, Tablero::blanca);
	tblAnulado.colocarSimple(6, 6, Tablero::negra);
	//(5,5) se deja nula.
	tblAnulado.colocarSimple(3, 3, Tablero::negra);
	tblAnulado.colocarSimple(2, 2, Tablero::negra);
	tblAnulado.colocarSimple(1, 1, Tablero::negra);
	//Aqui se rellena una columna.
	tblAnulado.colocarSimple(0, 4, Tablero::negra);
	tblAnulado.colocarSimple(1, 4, Tablero::negra);
	tblAnulado.colocarSimple(2, 4, Tablero::negra);
	tblAnulado.colocarSimple(3, 4, Tablero::negra);
	tblAnulado.colocarSimple(5, 4, Tablero::negra);
	//(6,4) se deja nula.
	tblAnulado.colocarSimple(7, 4, Tablero::blanca);
	EXPECT_FALSE(tblAnulado.validarJugada(4, 4, Tablero::blanca));
}
//Prueba validarJugada(), variante #3-true.
TEST_F(TableroReversiPruebas, validarJugada_3_t)
{
	//Se intenta probar (4,4, blanca).
	//Aqui se rellena una diagonal.
	tblAnulado.colocarSimple(7, 1, Tablero::blanca);
	tblAnulado.colocarSimple(6, 2, Tablero::negra);
	tblAnulado.colocarSimple(5, 3, Tablero::negra);
	tblAnulado.colocarSimple(3, 5, Tablero::negra);
	tblAnulado.colocarSimple(2, 6, Tablero::negra);
	tblAnulado.colocarSimple(1, 7, Tablero::blanca);
	//Aqui se rellena una fila.
	tblAnulado.colocarSimple(4, 0, Tablero::blanca);
	tblAnulado.colocarSimple(4, 1, Tablero::negra);
	tblAnulado.colocarSimple(4, 2, Tablero::negra);
	tblAnulado.colocarSimple(4, 3, Tablero::negra);
	tblAnulado.colocarSimple(4, 5, Tablero::negra);
	tblAnulado.colocarSimple(4, 6, Tablero::negra);
	tblAnulado.colocarSimple(4, 7, Tablero::blanca);
	EXPECT_TRUE(tblAnulado.validarJugada(4, 4, Tablero::blanca));
}
//Prueba validarJugada(), variante #3-false.
TEST_F(TableroReversiPruebas, validarJugada_3_f)
{
	//Se intenta probar (4,4, blanca).
	//Aqui se rellena una diagonal.
	tblAnulado.colocarSimple(7, 1, Tablero::blanca);
	tblAnulado.colocarSimple(6, 2, Tablero::negra);
	//(5,3) se deja nula.
	tblAnulado.colocarSimple(3, 5, Tablero::negra);
	tblAnulado.colocarSimple(2, 6, Tablero::negra);
	tblAnulado.colocarSimple(1, 7, Tablero::negra);
	//Aqui se rellena una fila.
	tblAnulado.colocarSimple(4, 0, Tablero::negra);
	tblAnulado.colocarSimple(4, 1, Tablero::negra);
	tblAnulado.colocarSimple(4, 2, Tablero::negra);
	tblAnulado.colocarSimple(4, 3, Tablero::negra);
	tblAnulado.colocarSimple(4, 5, Tablero::negra);
	//(4,6) se deja nula.
	tblAnulado.colocarSimple(4, 7, Tablero::blanca);
	EXPECT_FALSE(tblAnulado.validarJugada(4, 4, Tablero::blanca));
}
//Prueba validarJugada(), variante #4-true.
TEST_F(TableroReversiPruebas, validarJugada_4_t)
{
	//Se intenta probar (4,4, blanca).
	//Aqui se rellena una diagonal.
	tblAnulado.colocarSimple(7, 7, Tablero::blanca);
	tblAnulado.colocarSimple(6, 6, Tablero::negra);
	tblAnulado.colocarSimple(5, 5, Tablero::negra);
	tblAnulado.colocarSimple(3, 3, Tablero::negra);
	tblAnulado.colocarSimple(2, 2, Tablero::negra);
	tblAnulado.colocarSimple(1, 1, Tablero::blanca);
	//Aqui se rellena una fila.
	tblAnulado.colocarSimple(4, 0, Tablero::blanca);
	tblAnulado.colocarSimple(4, 1, Tablero::negra);
	tblAnulado.colocarSimple(4, 2, Tablero::negra);
	tblAnulado.colocarSimple(4, 3, Tablero::negra);
	tblAnulado.colocarSimple(4, 5, Tablero::negra);
	tblAnulado.colocarSimple(4, 6, Tablero::negra);
	tblAnulado.colocarSimple(4, 7, Tablero::blanca);
	EXPECT_TRUE(tblAnulado.validarJugada(4, 4, Tablero::blanca));
}
//Prueba validarJugada(), variante #4-false.
TEST_F(TableroReversiPruebas, validarJugada_4_f)
{
	//Se intenta probar (4,4, blanca).
	//Aqui se rellena una diagonal.
	tblAnulado.colocarSimple(7, 7, Tablero::blanca);
	tblAnulado.colocarSimple(6, 6, Tablero::negra);
	//(5,5) se deja nula.
	tblAnulado.colocarSimple(3, 3, Tablero::negra);
	tblAnulado.colocarSimple(2, 2, Tablero::negra);
	tblAnulado.colocarSimple(1, 1, Tablero::negra);
	//Aqui se rellena una fila.
	tblAnulado.colocarSimple(4, 0, Tablero::blanca);
	//(4,1) se deja nula.
	tblAnulado.colocarSimple(4, 2, Tablero::negra);
	tblAnulado.colocarSimple(4, 3, Tablero::negra);
	tblAnulado.colocarSimple(4, 5, Tablero::negra);
	tblAnulado.colocarSimple(4, 6, Tablero::negra);
	tblAnulado.colocarSimple(4, 7, Tablero::negra);
	EXPECT_FALSE(tblAnulado.validarJugada(4, 4, Tablero::blanca));
}
//Prueba verFin().
TEST_F(TableroReversiPruebas, verFin)
{
	//Se llena todo el tablero.
	for (int f = 0; f < 8; f++)
		for (int c = 0; c < 8; c++)
			tblAnulado.colocarSimple(f, c, Tablero::negra);
	EXPECT_TRUE(tblAnulado.verFin());
}
// Prueba flanqueaFila(), variante #1
TEST_F(TableroReversiPruebas, flanqueaFila_1)
{
	// Se coloca la posición con excepción de la jugada que se intenta validar positivamente (4,6,blanca).
	tblAnulado.colocarSimple(4, 0, Tablero::Ficha::blanca);
	tblAnulado.colocarSimple(4, 1, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 2, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 3, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 4, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 5, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 6, Tablero::Ficha::blanca);
	tblAnulado.flanqueaFila(4, 6, Tablero::Ficha::blanca); // se flanquea la fila
	EXPECT_FALSE(tblAnulado.verFlanqueaFila(4, 6, Tablero::Ficha::blanca));
}

TEST_F(TableroReversiPruebas, flanqueaColumna_1)
{
	// Se coloca la posición con excepción de la jugada que se intenta validar positivamente (6,1,blanca).
	tblAnulado.colocarSimple(0, 1, Tablero::Ficha::blanca);
	tblAnulado.colocarSimple(1, 1, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(2, 1, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(3, 1, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(4, 1, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(5, 1, Tablero::Ficha::negra);
	tblAnulado.colocarSimple(6, 1, Tablero::Ficha::blanca);
	tblAnulado.flanqueaColumna(6, 1, Tablero::Ficha::blanca);
	EXPECT_FALSE(tblAnulado.verFlanqueaFila(6, 1, Tablero::Ficha::blanca));
}

TEST_F(TableroReversiPruebas, flanqueaDiagAsc_1)
{
	tblAnulado.colocarSimple(4, 0, Tablero::blanca);
	tblAnulado.colocarSimple(3, 1, Tablero::negra);
	tblAnulado.colocarSimple(2, 2, Tablero::negra);
	tblAnulado.colocarSimple(1, 3, Tablero::negra);
	tblAnulado.colocarSimple(0, 4, Tablero::blanca);
	tblAnulado.flanqueaDiagonalAscendente(0, 4, Tablero::blanca);
	EXPECT_FALSE(tblAnulado.verFlanqueaDiagonalAscendente(0, 4, Tablero::Ficha::blanca));
}

TEST_F(TableroReversiPruebas, flanqueaDiagDesc_1)
{
	tblAnulado.colocarSimple(0, 0, Tablero::blanca);
	tblAnulado.colocarSimple(1, 1, Tablero::negra);
	tblAnulado.colocarSimple(2, 2, Tablero::negra);
	tblAnulado.colocarSimple(3, 3, Tablero::negra);
	tblAnulado.colocarSimple(4, 4, Tablero::blanca);
	tblAnulado.flanqueaDiagonalDescendente(4, 4, Tablero::blanca);
	EXPECT_FALSE(tblAnulado.verFlanqueaDiagonalDescendente(4, 4, Tablero::Ficha::blanca));
}
