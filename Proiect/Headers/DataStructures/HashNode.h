#pragma once
#include<string>
using std::string;

class HashNode{
public:
	string key;
	bool value;

	HashNode(string k, bool v) : key(k), value(v) {};
};

