#include"man.h"
#include"config.h"
#include"window.h"
#include"mirror.h"

void man::sethead(std::string a)
{
	head=a;
}
man::man(){
	name = "no_1";
	x=250;
	y= HEIGHT - MAN_HEIGHT; 
	v_x =0;
	v_y =0;
	life = 253;
	energy = 0;
	frame = 0;
	face = FACE_RIGHT;
	jumping = dashing = atking = false;
	s = NULL;
	state = REST;
}

man::man(int a,int b,int f){
	name = "no_1";
	x=a;
	y= b; 
	v_x =0;
	v_y =0;
	life = 253;
	energy = 0;
	frame = 0;
	face = f;
	jumping = dashing = false;
	s = NULL;
	state = REST;
}

void man::draw(){
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	pos.w = MAN_WIDTH;
	pos.h = MAN_HEIGHT;
	if(FACE_RIGHT == face)
		Window::Draw(Window::RemoveBackground(stick_man[state],MAN_BACK),pos,&clips[state][(int)(frame)]);
	else{
		
		int ctr = -1;
		switch(state){
		case RUN:
			numframes[RUN] = RUN_INDEX2;
			ctr = RUN_INDEX2;break;
		case REST:
			numframes[REST] = REST_INDEX2;
			ctr = REST_INDEX2;break;
		case ATTACK:
			numframes[ATTACK] = ATTACK_INDEX2;
			ctr = ATTACK_INDEX2;break;
		case JUMP:
			numframes[JUMP] = JUMP_INDEX2;
			ctr = JUMP_INDEX2;break;
		case HURTED:
			numframes[HURTED] = HURTED_INDEX2;
			ctr = HURTED_INDEX2;break;
		case DEATH:
			numframes[DEATH] = DEATH_INDEX2;
			ctr = DEATH_INDEX2;break;
		case FALL:
			numframes[FALL] = FALL_INDEX2;
			ctr = FALL_INDEX2;break;
		case U:
			numframes[U] = U_INDEX2;
			ctr = U_INDEX2;break;
		case S_U:
			numframes[S_U] = S_U_INDEX2;
			ctr = S_U_INDEX2;break;
		case WIN:
			numframes[WIN] = WIN_INDEX2;
			ctr = WIN_INDEX2;break;
		case DASH:
			numframes[DASH] = DASH_INDEX2;
			ctr = DASH_INDEX2;break;
		case W_J:
			numframes[S_U] = W_J_INDEX2;
			ctr = W_J_INDEX2;break;
		case I:
			numframes[S_U] = I_INDEX2;
			ctr = I_INDEX2;break;
		case DEFENCE:
			numframes[S_U] = DEFENCE_INDEX2;
			ctr = DEFENCE_INDEX2;break;
		}
		SDL_Rect pos1;
		pos1.x = 100;
		pos1.y = 100;
		pos1.w = 200;
		pos1.h = 50;
		Window::Draw( Window::RemoveBackground(MirrorSurfaceY(stick_man[state]),MAN_BACK),pos,&clips[state][ctr-1-(int)(frame)]);
	}
	if(s != NULL){
		(*s).draw();
	}
}

void man::nextframe(man& role){
	
	frame += FRAME_STEP; 
	if(frame >numframes[this->state]){
		if(life<= 0){
		life = 0;
		state = DEATH;
		frame = 0;
	}

		if(state == DEATH)
			frame -= 1;
		else if(state == DEATH||state == HURTED||state == S_U||state == W_J){
			state = REST;
			frame = 0;
		}
		else if(state == ATTACK){

			//攻击碰撞检测
			/*SDL_Rect a ={x+MAN_WIDTH/2,y,MAN_WIDTH,MAN_HEIGHT},
				b = {role.x,role.y,MAN_WIDTH,MAN_HEIGHT};
			if(check_collision(a,b)){
				role.hit(ATTACK_DAMAGE);
			}
			state = REST;
			frame = 0;*/

			s = new skill(skills[0],s_clips[0],8,x,y,20,20,face*50,0);
			state = REST;
			frame = 0;
		}
		
		else
			frame = 0;

	}
	if(s!=NULL){
		SDL_Rect a ={(*s).x,(*s).y,(*s).w,(*s).h},
			b = {role.x,role.y,MAN_WIDTH,MAN_HEIGHT};
		if(check_collision(a,b)){
			delete s;
			s = NULL;
			role.super_hit(ATTACK_DAMAGE,10);
		}
		if(s!=NULL && !(*s).move()){
			delete s;
			s = NULL;
		}
		
	}
	
}

void man::hit(int damage){
	life -= damage;
	state = HURTED;
	frame = 0;
	x = x -20;
	
}

void man::super_hit(int damage,int vx){
	jumping = true;
	life -= damage;
	state = FALL;
	frame = 0;
	v_x = vx;
	v_y = Y_VELOCITY_STEP/2.0;
	
}

bool man::check_collision( SDL_Rect A, SDL_Rect B ){

    //矩形的各边
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
 
    //计算矩形A的各边
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
        
    //计算矩形B的各边
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;
	 //如果矩形A的任意一条边都在矩形B外
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //如果没有一条边在矩形B外
    return true;
}
