#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QObject>
#include <QVector>
#include <QDebug>

struct DiceState
{
	int first;
	int second;

	int sum()
	{
		return first + second;
	}
};

enum Operation { Multiple, Divide };
enum Number { Two = 2, Three, Four };


class GameState// : public QObject
{
	//Q_OBJECT

public:
	const QVector<int> m_firstCube = {2, 3, 4, 5, 6, 7};
	const QVector<int> m_secondCube = {1, 2, 3, 4, 5, 6};

	int m_score = 0;
	int m_lastResult;
	int m_moves;
	int m_points = 0;

	int m_dropsAllowed = 2;
	bool m_chooseOptionAllowed = false;

	void swapAllowed();
	void checkForThirteenLike();
public:
	explicit GameState(int moves = 10, QObject *parent = nullptr);

	void clearState();
	DiceState drop();
	void chooseOption(Operation op, Number num);
	bool available();
	bool dropAvailable();

	void addToScore(int value);
	int moves() const;
	void setMoves(int newMoves);
	int getMoves();

//signals:
//	void scoreUpdated(int score);
//	void pointsUpdated(int points);
//	void movesChanged(int moves);
};

#endif // GAMESTATE_H
