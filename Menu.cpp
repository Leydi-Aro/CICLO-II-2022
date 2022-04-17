#include "Controladora.h"

using namespace std;

int main()
{
    Controladora<Usuario>* c = new Controladora<Usuario>();
    c->CargarUsuarios();
    c->menu();

    getch();
    return 0;
}