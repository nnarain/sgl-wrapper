
#pragma once

#ifndef STATICMODELFACTORY_H
#define STATICMODELFACTORY_H

#include "StaticModel.h"

namespace sgl{
#ifdef _MSC_VER
	class DLLEXPORT StaticModelFactory
#else
	class StaticModelFactory
#endif
	{
	public:
		StaticModelFactory();
		~StaticModelFactory();

		virtual StaticModel* createInstance() = 0;

	private:

	};
};


#endif
