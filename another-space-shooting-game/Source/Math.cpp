#include "../Header Files/Math.h"


bool Math::checkAABBCollision(sf::FloatRect rect1, sf::FloatRect rect2)
{
	if (rect1.left + rect1.width > rect2.left &&
		rect2.left + rect2.width > rect1.left &&
		rect2.top + rect2.height > rect1.top &&
		rect1.top + rect1.height > rect2.top
		) {

		return true;
	}

	return false;
}



