
#include <iostream>
#include <stdexcept>
#include <string>
#include <pthread.h>
#include "Product/Administration.h"
#include "Product/FastDoor.h"
#include "Product/RestartDoor.h"
#include "Product/Enums.h"
#include "Product/Connection.h"



static void showMenuSluice();
static void showMenuAdministration(Administration* a);
void FillSluiceList(Administration* a, Connection* c);

int main( void )
{
    Administration administration;
    Connection c;
    FillSluiceList(&administration, &c);
    bool quit = false;
    bool sluisMenu = false;

    while (!quit)
    {
        int Port = 0;
        while (!sluisMenu)
        {

            char choice = '\0';
            showMenuAdministration(&administration);
            std::cin >> choice;
            std::cin.ignore();

            switch (choice)
            {
              case '1' :
                Port = 5555;
                c.Connect(Port);
                sluisMenu = true;
                break;
              case '2' :
                Port = 5556;
                c.Connect(Port);
                sluisMenu = true;
                break;
              case '3' :
                Port = 5557;
                c.Connect(Port);
                sluisMenu = true;
                break;
              case '4' :
                Port = 5558;
                c.Connect(Port);
                sluisMenu = true;
                break;
              case '9' :
                quit = true;
                c.Close();
                return 0;
                break;
              default:
                std::cout << "\n\nChoice not defined (" << choice << ")" << std::endl;
                break;
            }
          }
        while (sluisMenu)
        {
            char choice = '\0';
            showMenuSluice();
            std::cin >> choice;
            std::cin.ignore();

            switch (choice)
            {
              case '1' :
                administration.Start(Port);
                break;
              case '2' :
                administration.FreeEntry(Port);
                break;
              case '3' :
                administration.FreeExit(Port);
                break;
              case '4' :
                administration.Alarm(Port, left);
                administration.Alarm(Port, right);
                break;
              case '9' :
                sluisMenu = false;
                break;
              default:
                std::cout << "\n\nChoice not defined (" << choice << ")" << std::endl;
                break;
            }
        }
      };
    return 0;
}


static void showMenuSluice()
{
    std::cout << "\033[2J\033[1;1H";
    std::cout << "\n|-------------------------- |" << std::endl;
    std::cout << "|SluisProgram by Loe & Roy  |" << std::endl;
    std::cout << "|---------------------------|" << std::endl;
    std::cout << "|(1) Start                  |" << std::endl;
    std::cout << "|(2) Gereed voor Invaren    |" << std::endl;
    std::cout << "|(3) Gereed voor Uitvaren   |" << std::endl;
    std::cout << "|(4) Alarm                  |" << std::endl;
    std::cout << "|(5) Herstel                |" << std::endl;
    std::cout << "|---------------------------|" << std::endl;
    std::cout << "|(9) Vorige Pagina          |" << std::endl;
    std::cout << "|---------------------------|" << std::endl;
    std::cout << "Choice : " ;
}
static void showMenuAdministration(Administration* a)
{
    std::cout << "\033[2J\033[1;1H";
    std::cout << "\n|-------------------------- |" << std::endl;
    std::cout << "|SluisProgram by Loe & Roy  |" << std::endl;
    std::cout << "|---------------------------|" << std::endl;
    std::cout << "|Kies een sluis:            |" << std::endl;
    for(int i = 0; i<4;i++)
    {
		Sluice* s = a->GetSluiceList()[i];
		int id = s->GetSluiceID();
    std::cout << "|(" << i+1 << ") Sluice " << id << "            |" << std::endl;
	}
    std::cout << "|---------------------------|" << std::endl;
    std::cout << "|(9) QUIT                   |" << std::endl;
    std::cout << "|---------------------------|" << std::endl;
    std::cout << "Choice : " ;
  }

  void FillSluiceList(Administration* a, Connection* c)
  {
	  for(int i = 0; i < 4; i++)
	  {
      Sluice* s = new Sluice(5555 + i, low, c);
     a->Add(s);
    }
  }
