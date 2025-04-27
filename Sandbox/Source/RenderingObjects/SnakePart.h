#pragma once

#include <LearningEngine.h>
#include <glm/glm.hpp>

enum class SnakePartMoveType : uint8_t
{
	Forward = 0,
	Backward,
	Left,
	Right
};

struct SnakePartMove
{
	glm::mat4 Translation;
	SnakePartMoveType MoveType;
};

class SnakePart : public LE::RenderingObject
{
public:

	SnakePart(SnakePartMoveType MovementDir, const glm::mat4& OwnerTranslation, std::vector<SnakePartMove> CachedMoves);
	virtual ~SnakePart();

	void AddMove(const SnakePartMove& NewMove);
	inline const std::vector<SnakePartMove>& GetCachedMoves() const { return m_CachedMoves; }

	void ExecuteMovement();
	void CheckAndExecuteMoves();

	SnakePartMoveType GetMovementDir() const { return m_MovementDir; }

private:

	SnakePartMoveType m_MovementDir;
	std::vector<SnakePartMove> m_CachedMoves;
};