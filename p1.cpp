#include"p1.h"
#include"config.h"
#include"window.h"
#include"mirror.h"

p1::p1(){
	man::man();
	load();
}


p1::p1(int a,int b,int c){
	man:man();
	x=a;face=c;
	load();
}
p1::~p1()
{
	
}
void p1::draw(){
	SDL_Rect pos;
	pos.x = x;
	pos.y = y +MAN_HEIGHT-stick_man[state]->h*2 ;
	pos.w = MAN_WIDTH;
	pos.h = MAN_HEIGHT;
	if(FACE_RIGHT == face){
		
		Window::Drawx(Window::RemoveBackground(stick_man[state],MAN_BACK),pos,&clips[state][(int)(frame)]);
		
	}
	else{
		
		int ctr = -1;
		switch(state){
		case RUN:
			numframes[RUN] = RUN_INDEX;
			ctr = RUN_INDEX;break;
		case REST:
			numframes[REST] = REST_INDEX;
			ctr = REST_INDEX;break;
		case ATTACK:
			numframes[ATTACK] = ATTACK_INDEX;
			ctr = ATTACK_INDEX;break;
		case JUMP:
			numframes[JUMP] = JUMP_INDEX;
			ctr = JUMP_INDEX;break;
		case HURTED:
			numframes[HURTED] = HURTED_INDEX;
			ctr = HURTED_INDEX;break;
		case DEATH:
			numframes[DEATH] = DEATH_INDEX;
			ctr = DEATH_INDEX;break;
		case FALL:
			numframes[FALL] = FALL_INDEX;
			ctr = FALL_INDEX;break;
		case U:
			numframes[U] = U_INDEX;
			ctr = U_INDEX2;break;
		case S_U:
			numframes[S_U] = S_U_INDEX;
			ctr = S_U_INDEX;break;
		case WIN:
			numframes[WIN] = WIN_INDEX;
			ctr = WIN_INDEX;break;
		case DASH:
			numframes[DASH] = DASH_INDEX;
			ctr = DASH_INDEX;break;
		case W_J:
			numframes[W_J] = W_J_INDEX;
			ctr = W_J_INDEX;break;
		case I:
			numframes[I] = I_INDEX;
			ctr = I_INDEX;break;
		case DEFENCE:
			numframes[DEFENCE] = DEFENCE_INDEX;
			ctr = DEFENCE_INDEX;break;
		case S_J:
			numframes[S_J] = S_J_INDEX;
			ctr = S_J_INDEX;break;
		}
		SDL_Rect pos1;
		pos1.x = 100;
		pos1.y = 100;
		pos1.w = 200;
		pos1.h = 50;
		Window::Drawx( Window::RemoveBackground(MirrorSurfaceY(stick_man[state]),MAN_BACK),pos,&clips[state][ctr-1-(int)(frame)]);
	}
	if(s != NULL){
		(*s).draw();
	}
}

void p1::nextframe(man& role){
	if(atking == true){
		frame += FRAME_STEP;
	}
	else{
		frame += FRAME_STEP;
	}

	//人物技能碰撞检测
	SDL_Rect a ={x+face*MAN_WIDTH/2,y,MAN_WIDTH,MAN_HEIGHT},
				b = {role.x,role.y,MAN_WIDTH,MAN_HEIGHT};
	

	//动作一轮结束后
	if(frame >numframes[this->state]){
		if(this->life<=0){
			state = DEATH;
			frame = numframes[this->state]-1;

			role.state = WIN;
			return;
		}
		if(state == HURTED||state == S_U||state == S_J||state == I){
			atking = false;
			state = REST;
			frame = 0;
		}
		else if(state == ATTACK){

			//攻击碰撞检测
			SDL_Rect a ={x+MAN_WIDTH/2,y,MAN_WIDTH,MAN_HEIGHT},
				b = {role.x,role.y,MAN_WIDTH,MAN_HEIGHT};
			if(check_collision(a,b)){
				role.hit(ATTACK_DAMAGE);
			}
			state = REST;
			atking = false;
			frame = 0;

			
		}
		else if(state == U){
			s = new skill(skills[0],s_clips[0],0.3,3,x,y+MAN_HEIGHT/2,20,20,face*50,0);
			state = REST;
			atking = false;
			frame = 0;
		}
		else if(state == I){
			state = REST;
			atking = false;
			frame = 0;
		}
		else if(state == W_J){
			a.x = x;
			a.y = y-MAN_HEIGHT;
			a.w = 4*MAN_WIDTH;
			a.h = 3*MAN_WIDTH;
			if(check_collision(a,b)){
				if(role.x<x+2*MAN_WIDTH)
					role.super_hit(S_J_DAMAGE,(-1)*20);
				else
					role.super_hit(S_J_DAMAGE,20);
			}
			state = JUMP;
			jumping = true;atking = false;
			frame = JUMP_INDEX/2;
		}
		else if(state == S_U){
			a.w = MAN_HEIGHT*3;
			x = x+face*40;
			
			if(check_collision(a,b)){
				s = new skill(skills[1],s_clips[1],0.1,4,role.x,role.y,40,40,0,0);
			
			}
		}
		else{
			frame = 0;
			atking = false;
		}

	}


	//特效部分
	if(s!=NULL){
		SDL_Rect aa ={(*s).x,(*s).y,(*s).w,(*s).h},
			bb = {role.x,role.y,MAN_WIDTH,MAN_HEIGHT};
		if(check_collision(aa,bb)){
			delete s;
			s = NULL;
			if(state == I){
				role.super_hit(I_DAMAGE,0);
			}
			else{
				role.super_hit(ATTACK_DAMAGE,this->face*30);
			}
		}
		if(s!=NULL && !(*s).move()){
			delete s;
			s = NULL;
		}
		
	}
}
void p1::load(){
	try{
		stick_man[RUN] = Window::Loadimage("naroto//run.png");
		stick_man[REST] = Window::Loadimage("naroto//rest.png");
		stick_man[JUMP] = Window::Loadimage("naroto//jump.png");
		stick_man[ATTACK] = Window::Loadimage("naroto//attack.png");
		stick_man[HURTED] = Window::Loadimage("naroto//hurted.png");
		stick_man[WIN] = Window::Loadimage("naroto//win.png");
		stick_man[FALL] = Window::Loadimage("naroto//fall.png");
		stick_man[U] = Window::Loadimage("naroto//u.png");
		stick_man[W_J] = Window::Loadimage("naroto//w_j.png");
		stick_man[DEATH] = Window::Loadimage("naroto//death.png");
		stick_man[DASH] = Window::Loadimage("naroto//dash.png");
		stick_man[DEFENCE] = Window::Loadimage("naroto//defence.png");
		stick_man[I] = Window::Loadimage("naroto//i.png");
		stick_man[S_U] = Window::Loadimage("naroto//s_u.png");
		stick_man[S_J] = Window::Loadimage("naroto//rest.png");
	}
	catch (const std::runtime_error &e){
        std::cout << e.what() << std::endl;
		SDL_Delay(10000);
        Window::Quit();
        return;
    }

	for(int i=0; i<NUMSTATES;i++){
		int ctr = -1;
		switch(i){
		case RUN:
			numframes[RUN] = RUN_INDEX;
			ctr = RUN_INDEX;break;
		case REST:
			numframes[REST] = REST_INDEX;
			ctr = REST_INDEX;break;
		case ATTACK:
			numframes[ATTACK] = ATTACK_INDEX;
			ctr = ATTACK_INDEX;break;
		case JUMP:
			numframes[JUMP] = JUMP_INDEX;
			ctr = JUMP_INDEX;break;
		case HURTED:
			numframes[HURTED] = HURTED_INDEX;
			ctr = HURTED_INDEX;break;
		case DEATH:
			numframes[DEATH] = DEATH_INDEX;
			ctr = DEATH_INDEX;break;
		case FALL:
			numframes[FALL] = FALL_INDEX;
			ctr = FALL_INDEX;break;
		case U:
			numframes[U] = U_INDEX;
			ctr = U_INDEX;break;
		case S_U:
			numframes[S_U] = S_U_INDEX;
			ctr = S_U_INDEX;break;
		case WIN:
			numframes[WIN] = WIN_INDEX;
			ctr = WIN_INDEX;break;
		case DASH:
			numframes[DASH] = DASH_INDEX;
			ctr = DASH_INDEX;break;
		case W_J:
			numframes[W_J] = W_J_INDEX;
			ctr = W_J_INDEX;break;
		case I:
			numframes[I] = I_INDEX;
			ctr = I_INDEX;break;
		case DEFENCE:
			numframes[DEFENCE] = DEFENCE_INDEX;
			ctr = DEFENCE_INDEX;break;
		case S_J:
			numframes[S_J] = S_J_INDEX;
			ctr = S_J_INDEX;break;
		}

		int w,h,pw;
		w = stick_man[i]->w;
		h = stick_man[i]->h;
		pw = w/ctr;
		SDL_Rect* tmpptr = new SDL_Rect[ctr];
		for(int x = 0; x < ctr; ++x) {
			SDL_Rect tmp;
			tmp.x = x * pw;
			tmp.y = 0;
			tmp.w = pw;
			tmp.h = h;
			tmpptr[x] = tmp;
		}
    clips[i] = tmpptr;
	}

	//技能图片的载入
	

	skills[0] = Window::Loadimage("naroto//u_skill.png");
	skills[1] = Window::Loadimage("naroto//i_skill.png");

	int pw1 = (skills[0]->w)/9;
	SDL_Rect* tmp1 = new SDL_Rect[9],*tt = new SDL_Rect[14];
	
	for(int i=0;i<9;i++){
		tmp1[i].x= i*pw1;tmp1[i].y= 0;tmp1[i].w= pw1;tmp1[i].h= skills[0]->h;
	}

	s_clips[0] = tmp1;

	pw1 = skills[1]->w/11;
	for(int i=0;i<14;i++){
		tt[i].x= i*pw1;tt[i].y= 0;tt[i].w= pw1;tt[i].h= skills[0]->h;
	}

	s_clips[1] = tt;
}

void p1::handleKeys(const bool keys[]){
	bool moved = false;
	bool dfc = false;

	if(state == DEATH||state == HURTED||state == ATTACK||state == U||state == S_U||state == W_J||state == WIN||state== I)
		return;
	
	if(!jumping){
		if(keys[SDL_SCANCODE_K]) {
			state = JUMP;
			frame = 0;
			jumping = true;
			v_y = Y_VELOCITY_STEP;
			y += Y_VELOCITY_STEP;
			moved = true;
		}
		else if(keys[SDL_SCANCODE_J]&&!keys[SDL_SCANCODE_W]&&state!=ATTACK) {
			state = ATTACK;
			
			atking = true;
			frame = 0;
		}
		else if(keys[SDL_SCANCODE_J]&&keys[SDL_SCANCODE_W]&&state!=ATTACK) {
			state = W_J;
			atking = true;
			frame = 0;
		}
		else if(keys[SDL_SCANCODE_S]&&!keys[SDL_SCANCODE_U]){
			state = DEFENCE;
			dfc = true;
			atking = true;
			frame = 0;
		}
		else if(keys[SDL_SCANCODE_S]&&keys[SDL_SCANCODE_U]){
			state = S_U;
			atking = true;
			frame = 0;
		}
		else if(keys[SDL_SCANCODE_U]&&state != DEFENCE) {
			state = U;
			atking = true;
			frame = 0;
		}
		else if(keys[SDL_SCANCODE_I]){
			state = I;
			atking = true;
			frame = 0;
		}
	}
	else{
		moved = true;
		
		if(y + v_y < HEIGHT - MAN_HEIGHT) {
			y = y + v_y;
			x = x + v_x; 
			v_y = v_y + GRAVITY;
			
		} else {
			jumping = false;
			moved = false;
			atking = false;
			v_y = 0;
			v_x = 0;
			y = HEIGHT - MAN_HEIGHT;
		}
	}
	if(keys[SDL_SCANCODE_D]&&!dfc) {
		x += MAN_STEP;
		moved = true;
		face = FACE_RIGHT;
	}
	if(keys[SDL_SCANCODE_A]&&!dfc) {
		x -= MAN_STEP;
		moved = true;
		face = FACE_LEFT;
	  }
   
	 if(moved && keys[SDL_SCANCODE_L]&&!dashing){
		 state = DASH;
		 x += face*MAN_DASH;
		 dashing = true;
	 }
	 else if( !keys[SDL_SCANCODE_L]){
		 dashing = false;
	 }
	
	 
	if(moved && !jumping && !atking) {
		state = RUN;
	}
  
	 if(!moved &&!dfc && !atking) {
		state = REST;
	 }
	 
}
