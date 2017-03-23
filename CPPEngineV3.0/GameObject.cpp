#include "GameObject.h"

// TODO :: COMPONENTS
// TODO :: swap

#include "Component.h"
#include "Script.h"
#include "GameEngine.h"

using namespace GameEngineProject;
using namespace std;


//int _id;
//std::string _name;
//Tag _tag;
//std::vector<Component * const> _components;
//std::vector<Script * const> _scripts;

GameObject::GameObject() :
	_id(0),
	_name(""),
	_tag(""),
	_shotdown(false)
{

}


GameObject::~GameObject()
{
	if (!_shotdown)
	{
		Shutdown();
	}
}




void GameObject::Awake()
{
	for (int i = 0; i < _scripts.size(); ++i)
	{
		_scripts[i]->Awake();
	}
}

void GameObject::Start()
{
	for (int i = 0; i < _scripts.size(); ++i)
	{
		_scripts[i]->Start();
	}
}

void GameObject::Update()
{
	for (int i = 0; i < _scripts.size(); ++i)
	{
		_scripts[i]->Update();
	}
}

void GameObject::Shutdown()
{
	for (int i = 0; i < _scripts.size(); ++i)
	{
		_scripts[i]->Shutdown();
	}
	ClearScripts();
	_shotdown = true;
}


int GameObject::GetId() const
{
	return _id;
}


void GameObject::SetId(int id)
{
	_id = id;
}

const string& GameObject::GetName()
{
	return _name;
}

void GameObject::SetName(const string & name)
{
	_name = name;
}

Tag GameObject::GetTag()
{
	return _tag;
}

void GameObject::SetTag(Tag tag)
{
	if (_tag != "")
	{
		_tag = tag;
	}
}

bool GameObject::CompareTag(const Tag & tag)
{
	return _tag == tag;
}


bool GameObject::AddScript(Script * const script)
{
	_scripts.push_back(script);
}

bool GameObject::RemoveScript(Script * const script)
{
	for (int i = 0; i < _scripts.size(); ++i)
	{
		if (_scripts[i] == script && _scripts[i])
		{
			
			_scripts[i]->Shutdown();
			delete(_scripts[i]);
			return true;
		}
	}
	return false;
}

bool GameObject::RemoveScript(const string& scriptName)
{
	for (int i = 0; i < _scripts.size(); ++i)
	{
		if (*(_scripts[i]) == scriptName && _scripts[i])
		{
			_scripts[i]->Shutdown();
			delete(_scripts[i]);
			_scripts[i] = _scripts[_scripts.size() - 1];
			_scripts.pop_back();
			return true;
		}
	}
	return false;
}

void GameObject::ClearScripts()
{
	for (int i = 0; i < _scripts.size(); ++i)
	{
		_scripts[i]->Shutdown();
		delete(_scripts[i]);
	}
	_scripts.clear();
}


Transform * const GameObject::GetTransform()
{
	return _transform;
}

GraphicsComponent * const GameObject::GetGraphicsComponent()
{
	return _graphics;
}

PhysicsComponent * const GameObject::GetPhysicsComponent()
{
	return _physics;
}

void GameObject::SetTransform(Transform * const transform)
{
	_transform = transform;
}

void GameObject::SetGraphicsComponent(GraphicsComponent * const graphics)
{
	_graphics = graphics;
}

void GameObject::SetPhysicsComponent(PhysicsComponent * const physics)
{
	_physics = physics;
}


bool GameObject::operator==(const GameObject & obj)
{
	return (_id == obj.GetId());
}

void GameObject::Swap(const GameObject & obj)
{

}

void GameObject::Reset()
{
	_id = -1;
	_name = "";
	_tag = "";
	_shotdown = false;
}

GameEngineProject::GameObject::GameObject(const GameObject &)
{
}

const GameObject & GameEngineProject::GameObject::operator=(const GameObject &)
{
	// TODO: insert return statement here
}
