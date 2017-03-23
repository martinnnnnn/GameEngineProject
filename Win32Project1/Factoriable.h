#pragma once


class Factoriable
{
public:
	Factoriable() {}
	virtual ~Factoriable() = 0;
	virtual bool operator==(const Factoriable &) = 0;
	virtual void Swap(const Factoriable &) = 0;
	virtual void Reset() = 0;

};