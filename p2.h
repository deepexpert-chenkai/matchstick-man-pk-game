#ifndef _P2_H_
#define _P2_H_

#include<vector>
#include<string>
#include"SDL.h"
#include"man.h"
#include"mirror.h"

class p2:public man{
public:
	p2();
	p2(int a,int b,int c);
	~p2();
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
