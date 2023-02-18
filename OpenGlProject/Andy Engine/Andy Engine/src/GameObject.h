#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Componant.h"
#include <list>
#include <vector>
#include "Transform.h"
#include "GameObject.h"



class GameObject
{
public:
	Transform transform;
	//std::vector<Componant*> componants;
	std::vector<Transform> trans;
	// Functions
	GameObject();
	~GameObject();

	//void AddComponant(Componant* toAdd);
	void RemoveComponant(int toRemove);
	void Update();

private:

};

#endif // !GAMEOBJECT_H

