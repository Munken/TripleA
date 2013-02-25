#pragma once
class Selector;
class Analyzer
{
public:
	Analyzer(void) {};
	~Analyzer(void) {};
	virtual void analyze(Selector *s) = 0;
	virtual void terminate() = 0;
};

