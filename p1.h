#ifndef _P1_H_
#define _P1_H_

#include<vector>
#include<string>
#include"SDL.h"
#include"man.h"
#include"mirror.h"
#include"p2.h"
class p1:public man{
public:
	p1();
	p1(int a,int b,int c);
	~p1();
	void draw();
	void nextframe(man& role);
	void handleKeys(const bool keys[]);

	int  getx(){ return x; }
	int  gety(){ return y; }
	void setx(int v){ x =v; }
	void sety(int v){ y=v; }
	void setxy(int v,int u){ x=v;y=u; }


	void hit(int damage = ATTACK_DAMAGE) { man::hit(damage);}
	void load();
};
#endif
