//Gameobject.tpp

template <class T>
T* GameObject::GetComponent(EComponentType t)
{
	std::map<EComponentType, Component*>::iterator it = m_Components.find(t);

	if (it != m_Components.end())
	{
		return static_cast<T*> (it->second);
	}
	else
	{
		return nullptr;
	}
}