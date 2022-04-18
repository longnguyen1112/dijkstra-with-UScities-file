#include <iostream>
#include "Class.h"
	
int main()
{
    Dijkstra D;
    do
    {
        system("cls");

        std::cout << "                                        WE WILL CREATE YOUR PATH TO THE FUTURE:          " << std::endl;
        std::cout << "1/ AddCity without loading: " << std::endl;
        std::cout << "2/ AddConnection without loading: " << std::endl;
        std::cout << "3/ LoadFile: " << std::endl;
        std::cout << "4/ Find Shortest Distance: " << std::endl;
        std::cout << "5/ Find Shortest Time: " << std::endl;
        std::cout << "6/ Delete Network: " << std::endl;
        std::cout << "7/ Quit: " << std::endl;

        int num,dist,min;
        std::string input;
        std::string filename;
        std::string start,stop;
        std::cin >> num;

        switch (num)
        {
        case 1:
            std::cout << "Enter a city you want to add in a map: " ;
            std::cin >> input;

            D.AddCity(input);
            break;
        case 2:
            std::cout << "Enter a connection (Start point, end point, distance, time respectively) you want to add in a map: ";
            std::cin >> start;
            std::cout << " and ";
            std::cin >> stop;
            std::cout << " and ";
            std::cin >> dist;
            std::cout << " and ";
            std::cin >> min;
            std::cout << std::endl;

            D.AddConnection(start,stop,dist,min);
            break;
        case 3:
            std::cout << "Enter file name: " << std::endl;
            std::cin >> filename;
            D.LoadFromFile(filename);
            break;
        case 4:
            std::cout << "Find the shortest distance from ";
            std::cin >> start;
            std::cout << " to ";
            std::cin >> stop;
            if (!D.FindShortestDistance(start,stop))
            {
                std::cout << "There is no such connection " << std::endl;
            }
            break;
        case 5:
            std::cout << "Find the shortest time from ";
            std::cin >> start;
            std::cout << " to ";
            std::cin >> stop;
            if (!D.FindShortestTime(start, stop))
            {
                std::cout << "There is no such connection " << std::endl;
            }
            break;
        case 6:
            D.~Dijkstra();
            std::cout << "Map has been cleared! " << std::endl;
        case 7:
            D.~Dijkstra();
            std::cout << "Bye! " << std::endl;
            exit(0);
        }
        system("pause");
    } while (true);
}

