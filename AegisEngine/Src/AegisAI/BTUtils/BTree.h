#pragma once 

#ifndef _BTREE
#define _BTREE

#include <../BTNodes/Root.h>

class BTree {
	
	private:
		Root mRoot;
	
	public:
		BTree() = default;
		~BTree() = default;
		Root * GetRoot() { return &mRoot; };
};