#pragma once
#include <cereal/archives/xml.hpp>
#include <cereal/types/memory.hpp>
#include <sstream>
#include <fstream>
#include <Core/GameObject.h>

namespace cereal {
	template <> struct LoadAndConstruct<GameObject>
	{
		template <class Archive>
		static void load_and__construct(Archive& ar, cereal::construct<GameObject>& construct)
		{

		}
	};
}

namespace Serialization {

	void SerializeScene(std::shared_ptr<GameObject> gObject)
	{
		std::ofstream outputFile("Scene.xml");
		cereal::XMLOutputArchive archive(outputFile);
		serialize(archive, gObject);
	}


	template<class Archive>
	void serialize(Archive & archive, std::shared_ptr<GameObject> & gObject)
	{
		archive(gObject->m_depth, 
			gObject->m_children, 
			gObject->m_components,
			gObject->m_parent,
			gObject->m_transform,
			gObject->m_name);
	}


}
