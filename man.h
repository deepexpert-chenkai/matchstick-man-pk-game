#ifndef _MAN_H_
#define _MAN_H_
#include<iostream>
#include<vector>
#include<string>
#include"SDL.h"
#include"config.h"
#include"skill.h"

enum State {RUN,REST,JUMP,ATTACK,HURTED,DEATH,WIN,FALL,DASH,DEFENCE,W_J,S_U,I,U,S_J};

class man{
public:
	std::string name;
	std::string head;
	int life;
	int energy;
	int x,y;
	double v_x,v_y;
	//当前状态的序列数，如跑的第一个动作
	double  frame;
	//当前状态：跑，跳，、、、
	State state;
	bool jumping,dashing,atking;
	int face;
	int numframes[NUMSTATES];
	SDL_Rect *clips[NUMSTATES];
	SDL_Rect *s_clips[NUMSKILLS];

	skill *s;
	SDL_Surface *stick_man[NUMSTATES];
	SDL_Surface *skills [NUMSKILLS];

	man();
	man(int a,int b,int f = FACE_RIGHT);

	void draw();
	void nextframe(man& role);


	int  getx(){ return x; }
	int  gety(){ return y; }
	void setx(int v){ x =v; }
	void sety(int v){ y=v; }
	void setxy(int v,int u){ x=v;y=u; }
	void sethead(std::string a);

	void hit(int damage = ATTACK_DAMAGE);
	void super_hit(int damage,int vx);
	bool check_collision( SDL_Rect A, SDL_Rect B );
};

#endif
