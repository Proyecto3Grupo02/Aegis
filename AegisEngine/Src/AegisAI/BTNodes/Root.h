#pragma once 

#ifndef _ROOT
#define _ROOT

#include <BTNode.h>


class Root: BTNode {
	public:
		Root() = default;
		~Root() = default;

		string Title() { return "Root"; }
};