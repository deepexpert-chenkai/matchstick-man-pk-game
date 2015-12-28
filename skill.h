#include"SDL.h"
#include<vector>


class skill{
public:
	int x,y;//位置
	int w,h;//碰撞域
	int v_x,v_y;//速度
	int num_clip;
	SDL_Rect *clip;
	double frame;
	double s_step;

	SDL_Surface* pic;
	//dx,dy等于0代表无碰撞域图片（爆炸特效），vx、vy等于0即位置不变
	skill(SDL_Surface* p,SDL_Rect *r,double step,int num,int xx,int yy,int dx=0,int dy=0,int vx=0,int vy=0);

	bool move();
	void draw();
};
