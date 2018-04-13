#pragma once

#include <map>

#include "entity.h"
#include "types.h"

class Hunter : public Entity {
private:
	int stamina = 100;
	int kills = 0;
	orderedPair pos = orderedPair(0, 0);
		std::map<orderedPair, bool> map; // bool is true if a monster has been killed on that square
	public:
		Hunter() : Entity("Hunter", 100, 10, 4) { map[pos] = false; }

		std::string posString() { return pairText(pos); }
		bool visited(orderedPair location) { return map.find(location) != map.end(); }
		bool killedMonster() { return map[pos]; }
		void killMonster() { map[pos] = true; kills++; }

		void printStatus()
		{
			std::cout << "Location: " << pairText(pos) << "\n" <<
						 "HP: " << hp << "\n" <<
						 "Stamina: " << stamina << "\n" << 
						 "Kills: " << kills << std::endl;
		}

		bool walk(Cardinal direction)
		{
			pos += direction;
			bool v = visited(pos);
			if (!v)
				map[pos] = false;
			stamina -= 20;

			if (stamina < 0)
			{
				std::cout << "Your stamina fails you; the world fades in your vision as you collapse from exhaustion. Good job Sir Hunter, you killed " << kills <<
							 " Rathalos! When you awaken, I'm sure you'll make it back to the village in one piece." << std::endl;
				exit(0);
			}

			return v;
		}

		void lastRites()
		{
			std::cout << "You have died gloriously in battle trying to vanquish Rathalos #" << (kills + 1) << ". Go to Valhala in peace." << std::endl;
			exit(0);
		}
	};