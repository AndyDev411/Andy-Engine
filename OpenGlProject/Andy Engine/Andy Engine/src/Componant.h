#ifndef COMPONANT_H
#define COMPONANT_H


#include"Componant.h"
#include"GameObject.h"
#include"Transform.h"


class Componant {

public:
	Transform* transform;
	virtual void Update();

	void SetTransform(Transform* toSet);
	//void SetupComponantBase(GameObject* parent);

};

#endif // !COMPONANT_H
