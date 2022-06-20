#include "AegisMain.h"
#include "checkML.h" //BASURA

int main() {
	// Agrega checkML.h al proyecto e inclúyelo en todos los módulos del proyecto 
	// Escribe el siguiente comando al inicio de la función main
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // DEBUG	 

	AegisMain a;
	a.Init();

	return 0;
}