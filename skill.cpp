#include"skill.h"
#include"window.h"
#include"mirror.h"
	
skill::skill(SDL_Surface* p,SDL_Rect *r,double step,int num,int xx,int yy,int dx,int dy,int vx,int vy){
	pic = p;
	x = xx;
	y = yy;
	v_x = vx;
	v_y = vy;
	w = dx;
	h = dy;
	num_clip = num;
	s_step = step;
	frame = 0;
	clip= r;
}

	
bool skill::move(){
	x += v_x;
	y += v_y;
	frame += s_step;
	if(frame >= num_clip)
		return false;
	else
		return true;
}
	
void skill::draw(){
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	Window::Draw1(pic,pos,&clip[(int)frame]);
}
