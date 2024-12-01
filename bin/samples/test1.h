#pragma once

class Test1 {
	virtual   void   toto()   =   0; // test of a function to not refactor
}

class Test2 : public Test1 {
	virtual   ~Test2();
	virtual   void   toto()   const  ;   // test of a function to refactor
}

