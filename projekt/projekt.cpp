#include "pch.h"
#include <iostream>
#include "restaurant.h"
#include "newclient.h"
#include "alarm.h"
#include "event.h"

bool FindEvent(const Event* event1, const Event* event2) //sortowanie eventów po czasie, zwraca najwcześniejszy event z tablicy
{
	return event1->time_ < event2->time_;
}

int main()
{
	int mode;
	std::cout << "Wybierz tryb:" << std::endl << "1 - tryb krokowy" << std::endl << "2 - tryb ciagly" << std::endl;
	std::cout << "Wybor: ";
	std::cin >> mode;
	
	double time_system = 0;
	Client* client = new Client();
	Restaurant* restaurant = new Restaurant();
	restaurant->NewEvent(new NewClient(restaurant, client, time_system));
	restaurant->NewEvent(new Alarm(restaurant, client, time_system));

	/*//ROZKŁAD WYKŁADNICZY I NORMALNY
		std::default_random_engine generator_ = std::default_random_engine(5000000);
		std::normal_distribution<double> normal_dist_ = std::normal_distribution <double>(3700.0, 90.0);
		std::exponential_distribution<double> exponential_dist_ = std::exponential_distribution<double>(1 / 2200.0);

		std::ofstream normal, wykladniczy;
		normal.open("normalny.txt");
		wykladniczy.open("wykladniczy.txt");
		for(int i=0; i<10000; i++)
		{
			int normal_ = normal_dist_(generator_);
			normal << normal_ << std::endl;
			int wykl_ = abs(exponential_dist_(generator_));
			wykladniczy << wykl_ << std::endl;
		}
		normal.close();
		wykladniczy.close();
		

*/
		
	while (Client::GetIdOfLastClient() < 1000) //warunek końca symulacji
	{
		if (!restaurant->GetEventListEmpty())
		{
			if (mode == 1)
			{
				restaurant->GetData();
				system("pause");
			}
			std::sort(restaurant->GetEventListBegin(), restaurant->GetEventListEnd(), FindEvent);
			Event* event = restaurant->GetEvent();
			time_system = event->GetTime();
			std::cout << "Czas systemowy: " << time_system << std::endl;
			event->execute();
			delete event;
		}
	}
	delete restaurant;
	//system("pause");
	return 0;
}
