#ifndef AI_H
#define AI_H
#include <QPair>
#include "gamestate.h"

class Ai
{
public:
	static float heuristic(GameState gs)
	{
		return gs.m_points;
	}

	struct Move
	{
		Operation op;
		Number num;

		Move& operator=(const Move* other)
		{
			this->op = other->op;
			this->num = other->num;
			return *this;
		}
	};

	struct Step
	{
		std::pair<int, int> fisrtDrop;
		std::pair<int, int> secondDrop;
		Move move;

		Step& operator=(const Step& other)
		{
			this->fisrtDrop = other.fisrtDrop;
			this->secondDrop = other.secondDrop;
			this->move = other.move;
			return *this;
		}
	};

	// the function will do step over passed 'gs' variable
	// but return step for logging on the frontend
	static Step doNextStep(GameState& gs)
	{
		QVector<Operation> ops = {Multiple, Divide};
		QVector<Number> nums = {Two, Three, Four};

		Number maxNum = Two;
		Operation maxOperation = Multiple;
		float maxHeuristic = 0;

		auto firstDrop = gs.drop();
		auto secondDrop = gs.drop();

		for(auto op : ops)
		{
			for(auto num : nums)
			{
				GameState temp;
				temp = gs;

				temp.chooseOption(op, num);
				if(Ai::heuristic(temp) > maxHeuristic) {
					maxOperation = op;
					maxNum = num;
				}

			}
		}

		return {{firstDrop.first, firstDrop.second}, {secondDrop.first, secondDrop.second}, {maxOperation, maxNum}};
	}
};

#endif // AI_H
