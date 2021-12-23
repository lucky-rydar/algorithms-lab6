#include "gamestate.h"

int GameState::moves() const
{
	return m_moves;
}

void GameState::setMoves(int newMoves)
{
	m_moves = newMoves;
}

int GameState::getMoves()
{
	return m_moves;
}

GameState &GameState::operator=(const GameState &other)
{
	this->m_chooseOptionAllowed = other.m_chooseOptionAllowed;
	this->m_dropsAllowed = other.m_dropsAllowed;
	this->m_lastResult = other.m_lastResult;
	this->m_moves = other.m_moves;
	this->m_points = other.m_points;
	this->m_score = other.m_score;
	return *this;
}

void GameState::swapAllowed()
{
	this->m_chooseOptionAllowed = !this->m_chooseOptionAllowed;
}

void GameState::checkForThirteenLike()
{
	if(m_score % 13 == 0) {
		m_points += 1;
	}
}

GameState::GameState(int moves)
{
	setMoves(moves);
}

void GameState::clearState()
{
	this->m_score = 0;
	this->m_lastResult = 0;
	this->m_moves = 10;
	this->m_points = 0;
	this->m_dropsAllowed = 2;
	this->m_chooseOptionAllowed = false;
}

DiceState GameState::drop()
{
	if(m_dropsAllowed <= 0 || m_moves <= 0) {
		throw std::runtime_error("drop not allowed");
	}

	int first_i = rand() % m_firstCube.size();
	int second_i = rand() % m_secondCube.size();

	m_lastResult = m_firstCube[first_i] + m_secondCube[second_i];

	if(m_dropsAllowed == 2) {
		addToScore(m_lastResult);
		m_dropsAllowed--;
		setMoves(getMoves() - 1);
	} else if(m_dropsAllowed == 1) {
		swapAllowed();
		m_dropsAllowed--;
	}

	checkForThirteenLike();

	return {.first = m_firstCube[first_i], .second = m_secondCube[second_i]};
}

void GameState::chooseOption(Operation op, Number num)
{
	if(!m_chooseOptionAllowed || m_moves <= 0) {
		throw std::runtime_error("choose option not allowed");
	}

	int result = 0;

	switch (op) {
	case Operation::Divide:
		result = m_lastResult / num;
		break;
	case Operation::Multiple:
		result = m_lastResult * num;
		break;
	default:
		throw std::runtime_error("operation is not allowed");
	}

	addToScore(result);

	swapAllowed();
	m_dropsAllowed = 2;

	setMoves(getMoves() - 1);

	checkForThirteenLike();
}

bool GameState::dropAvailable()
{
	return m_dropsAllowed > 0;
}

void GameState::addToScore(int value)
{
	m_score += value;
}
