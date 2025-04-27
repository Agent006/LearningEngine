#pragma once

#include <LearningEngine.h>

#include <glm/glm.hpp>

class Sandbox : public LE::Application
{
private:

	enum class MovementDir : uint8_t
	{
		Forward = 0,
		Backward,
		Left,
		Right
	};

public:

	Sandbox();

	virtual void OnEvent(LE::Event& e) override;

protected:

	virtual void Tick(float DeltaTime) override;

private:

	bool OnKeyPressedEvent(const LE::KeyPressedEvent& e);
	void ExecuteMovement();
	void MoveFruitToRandomLoc();
	bool DoesHeadCollideWithFruit() const;
	void AddNewSnakePart();

private:

	std::shared_ptr<class SnakeHead> objSnakeHead = nullptr;
	std::shared_ptr<class Fruit> objFruit = nullptr;
	std::vector<std::shared_ptr<class SnakePart>> objSnakeParts;

	LE::OrthographicCamera m_Camera;

	MovementDir m_MovementDir = MovementDir::Forward;
};