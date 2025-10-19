// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MyDinoValdoAnimation.h"
#include "Monster/MyDinoValdo.h"

AMyDinoValdo* UMyDinoValdoAnimation::GetDinovaldo() const
{
	return Cast<AMyDinoValdo>(TryGetPawnOwner());
}
