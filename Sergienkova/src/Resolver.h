#pragma once
#include <iostream>
#include <vector>
#include "Tile.h"

class Resolver // решает задачу
{
	std::vector<Tile> m_Result;	// результат работы
	std::vector<Tile> m_Tiles;	// список для перебора раскладок
	int m_N;					// размер стола
	int m_Div;					// во сколько раз уменьшились при вычислениях результата
	int** m_Data;				// двумерный массив занятых клеток
	int m_SumS;					// суммарная полщадь
	unsigned int m_Operations;	// количество операций при вичислении

	bool CanAdd(Tile tile);		// возвращает истину, если в текущую раскладку можно добавить указанный тайл
	void Add(Tile tile);		// добавляет в раскладку указанный тайл
	void Remove();				// удаляет последний тайл из раскладки
	bool Scan(Tile tile);		// попытка найти результат, начиная с добавления указанного тайла. Истина, если с этим тайлом скан возможен
	Position FindEmpty();		// возвращает первое попавшееся пустое место
	void Resolve2();			// возвращает решение для четного n
public:

	void Resolve(int n);
	friend std::ostream& operator<<(std::ostream& os, Resolver& resolver);
};

