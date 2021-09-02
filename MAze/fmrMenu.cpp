#include "fmrMenu.h"
#include <ctime>
void main()
{
    srand(time(NULL));
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    MAze::MyForm1 form;
    Application::Run(% form);
}
