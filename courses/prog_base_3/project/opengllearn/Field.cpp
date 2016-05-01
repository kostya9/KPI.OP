#include "Field.h"

Field::Field(Loader * loader, GLuint size, glm::vec3 position) : GameObject()
{
	if (size % 2 != 1)
		throw new invalid_argument("Expected an odd number");

	this->size = size;
	this->position = position;
	enum SIDE { TOP, RIGHT, BOTTOM, LEFT };
	SIDE side = TOP;
	vector<TexturedModel> models = loader->objToModel(fieldPath);
	int sides = 1;
	int curElement = 0;
	for (int i = 0; i < size*size; i++)
	{
		int sideLength = sides / 4;
		if (i == 0)
		{
			for (TexturedModel model : models)
				entities.push_back(Entity(model, position, 0.0f, 0.0f, 0.0f, 1.0f));
			sides = 8;
			continue;
		}
		GLfloat x;
		GLfloat z;
		int offset = sides / 8;
		switch (side)
		{
		case TOP:
		{
			x = position.x - offset + curElement % sideLength;
			z = position.z - offset;
		}break;
		case RIGHT:
		{
			x = position.x + offset;
			z = position.z - offset + curElement % sideLength;
		}break;
		case BOTTOM:
		{
			x = position.x + offset - curElement % sideLength;
			z = position.z + offset;
		}break;
		case LEFT:
		{
			x = position.x - offset;
			z = position.z + offset - curElement % sideLength;
		}break;
		}
		for (TexturedModel model : models)
			entities.push_back(Entity(model, glm::vec3(x, 0.0f, z), 0.0f, 0.0f, 0.0f, 1.0f));
		// Changing sides
		if (side == TOP && curElement == (sideLength - 1))
			side = RIGHT;
		else if (side == RIGHT && curElement == (2 * sideLength - 1))
			side = BOTTOM;
		else if (side == BOTTOM && curElement == (3 * sideLength - 1))
			side = LEFT;
		curElement++;
		// Resetting after a circle
		if (curElement == sides)
		{
			sides = sides + 8;
			curElement = 0;
			side = TOP;
		}

	}
}

bool Field::isInField(glm::fvec2 position)
{
	bool xInvalidPos = glm::abs(position.x - this->position.x) > size/2.0f;
	bool zInvalidPos = glm::abs(position.y - this->position.z) > size/2.0f;
	if (xInvalidPos || zInvalidPos)
		return false;
	else
		return true;
}

GLuint Field::getSize()
{
	return size;
}
