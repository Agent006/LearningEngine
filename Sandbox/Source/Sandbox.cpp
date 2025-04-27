
#include "Sandbox.h"
#include "RenderingObjects/SnakeHead.h"
#include "RenderingObjects/SnakePart.h"
#include "RenderingObjects/Fruit.h"

/* Entry Point */
#include "LE/EntryPoint.h"
/*------------------------*/

#include <random>

#include <glm/gtc/matrix_transform.hpp>

using namespace LE;

LE::Application* LE::CreateApplication()
{
	return new Sandbox();
}

Sandbox::Sandbox()
	: m_Camera(-1.6f, 1.6f, -1.2f, 1.2f )
{
	objSnakeHead.reset(new SnakeHead());

	objFruit = std::make_shared<Fruit>();
	MoveFruitToRandomLoc();
}

void Sandbox::Tick(float DeltaTime)
{
	RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
	RenderCommand::Clear();

	Renderer::BeginScene(m_Camera);

	ExecuteMovement();
	Renderer::SubmitObj(objSnakeHead);

	if (DoesHeadCollideWithFruit())
	{
		MoveFruitToRandomLoc();
		AddNewSnakePart();
	}

	Renderer::SubmitObj(objFruit);

	for (const std::shared_ptr<SnakePart>& part : objSnakeParts)
	{
		part->CheckAndExecuteMoves();
		part->ExecuteMovement();
		Renderer::SubmitObj(part);
	}

	Renderer::EndScene();
}

void Sandbox::ExecuteMovement()
{
	switch (m_MovementDir)
	{
		case MovementDir::Forward:
		{
			objSnakeHead->SetModelMatrix(glm::translate(objSnakeHead->GetModelMatrix(), glm::vec3(0.f, 1e-3, 0.f)));
			break;
		}
		case MovementDir::Backward:
		{
			objSnakeHead->SetModelMatrix(glm::translate(objSnakeHead->GetModelMatrix(), glm::vec3(0.f, -1e-3, 0.f)));
			break;
		}
		case MovementDir::Left:
		{
			objSnakeHead->SetModelMatrix(glm::translate(objSnakeHead->GetModelMatrix(), glm::vec3(-1e-3, 0.f, 0.f)));
			break;
		}
		case MovementDir::Right:
		{
			objSnakeHead->SetModelMatrix(glm::translate(objSnakeHead->GetModelMatrix(), glm::vec3(1e-3, 0.f, 0.f)));
			break;
		}
	}
}

void Sandbox::OnEvent(Event& e)
{
	Application::OnEvent(e);

	EventDispatcher dispatcher = EventDispatcher(e);

	dispatcher.Dispatch<KeyPressedEvent>(LE_BIND(this, &Sandbox::OnKeyPressedEvent));
}

bool Sandbox::OnKeyPressedEvent(const KeyPressedEvent& e)
{
	if (e.GetKeyCode() == LE_KEY_W && m_MovementDir != MovementDir::Forward && m_MovementDir != MovementDir::Backward)
	{
		SnakePartMove newMove;
		newMove.MoveType = SnakePartMoveType::Forward;
		newMove.Translation = objSnakeHead->GetModelMatrix();
		for (const std::shared_ptr<SnakePart>& part : objSnakeParts)
		{
			part->AddMove(newMove);
		}

		m_MovementDir = MovementDir::Forward;
	}
	else if (e.GetKeyCode() == LE_KEY_S && m_MovementDir != MovementDir::Backward && m_MovementDir != MovementDir::Forward)
	{
		SnakePartMove newMove;
		newMove.MoveType = SnakePartMoveType::Backward;
		newMove.Translation = objSnakeHead->GetModelMatrix();
		for (const std::shared_ptr<SnakePart>& part : objSnakeParts)
		{
			part->AddMove(newMove);
		}

		m_MovementDir = MovementDir::Backward;
	}
	else if (e.GetKeyCode() == LE_KEY_A && m_MovementDir != MovementDir::Left && m_MovementDir != MovementDir::Right)
	{
		SnakePartMove newMove;
		newMove.MoveType = SnakePartMoveType::Left;
		newMove.Translation = objSnakeHead->GetModelMatrix();
		for (const std::shared_ptr<SnakePart>& part : objSnakeParts)
		{
			part->AddMove(newMove);
		}

		m_MovementDir = MovementDir::Left;
	}
	else if (e.GetKeyCode() == LE_KEY_D && m_MovementDir != MovementDir::Right && m_MovementDir != MovementDir::Left)
	{
		SnakePartMove newMove;
		newMove.MoveType = SnakePartMoveType::Right;
		newMove.Translation = objSnakeHead->GetModelMatrix();
		for (const std::shared_ptr<SnakePart>& part : objSnakeParts)
		{
			part->AddMove(newMove);
		}

		m_MovementDir = MovementDir::Right;
	}

	return true;
}

void Sandbox::MoveFruitToRandomLoc()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distX(-1.5f, 1.5f);
	std::uniform_real_distribution<float> distY(-1.f, 1.f);

	objFruit->SetModelMatrix(glm::translate(glm::mat4(1.f), glm::vec3(distX(gen), distY(gen), 0)));
}

bool Sandbox::DoesHeadCollideWithFruit() const
{
	const glm::mat4& headM = objSnakeHead->GetModelMatrix();
	const glm::mat4& fruitM = objFruit->GetModelMatrix();

	return glm::length(headM[3] - fruitM[3]) < 0.15f;
}

void Sandbox::AddNewSnakePart()
{
	if (objSnakeParts.size() > 0)
	{
		const std::shared_ptr<SnakePart>& lastPart = objSnakeParts[objSnakeParts.size() - 1];
		objSnakeParts.push_back(std::make_shared<SnakePart>(lastPart->GetMovementDir(), lastPart->GetModelMatrix(), lastPart->GetCachedMoves()));
	}
	else
	{
		SnakePartMoveType tempMoveType;
		switch (m_MovementDir)
		{
			case MovementDir::Forward:		tempMoveType = SnakePartMoveType::Forward; break;
			case MovementDir::Backward:		tempMoveType = SnakePartMoveType::Backward; break;
			case MovementDir::Left:			tempMoveType = SnakePartMoveType::Left; break;
			case MovementDir::Right:		tempMoveType = SnakePartMoveType::Right; break;
		}

		std::vector<SnakePartMove> cachedMoves;
		objSnakeParts.push_back(std::make_shared<SnakePart>(tempMoveType, objSnakeHead->GetModelMatrix(), cachedMoves));
	}
}