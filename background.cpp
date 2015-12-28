#include"background.h"
#include"SDL.h"
#include"window.h"
#include"p2.h"

background::background(){
	b = Window::Loadimage("data//bck.bmp");
	life = Window::Loadimage("data//bd1.png");
	life1 = Window::Loadimage("data//bd2.png");
	vs = Window::Loadimage("data//vs.jpg");
	life2 = Window::Loadimage("data//bd3.png");
	pos[0].x = 0;
	pos[0].y = 0;
	pos[1].x = 60;
	pos[1].y = 30;
	pos[2].x = 123;
	pos[2].y = 70;
	pos[3].x = 10;
	pos[3].y = 30;
	pos[4].x = 430;
	pos[4].y = 30;
	pos[5].x = 567;
	pos[5].y = 30;
	pos[6].x = 877;
	pos[6].y = 30;
	pos[7].x = 609;
	pos[7].y = 70;


}

void background::draw(man c1,man c2){
	SDL_Rect l1={0,0,353,99},l2={253-c1.life,0,c1.life,19},e1={0,0,353,99},e2={253-c2.life,0,c2.life,19};//每个人物设定的初始的血量全部都是253，不同的人物的血量条的显示的方式不一样。
	SDL_Surface *head1,*head2;
	head1 = Window::Loadimage(c1.head);
	head2 = Window::Loadimage(c2.head);
	Window::Draw1(b,pos[0]);
	Window::Draw1(Window::RemoveBackground(life,BG_BACK),pos[1],&l1);
	Window::Draw1(Window::RemoveBackground(head1,0xFF,0xFF,0xFF), pos[3]);
	Window::Draw1(life1,pos[2],&l2);
	Window::Draw1(Window::RemoveBackground(vs,0x00,0x00,0x00), pos[4]);
	Window::Draw1(Window::RemoveBackground(life2,BG_BACK), pos[5], &e1);//人物的头像等会放在人物类中作为一个参数传进来，临时 新建对应的sdl_surface来显示头像，这样不同的人物传进来的图片不一样，显示的头像也就不一样。
	Window::Draw1(Window::RemoveBackground(head2,0xFF,0xFF,0xFF), pos[6]);
	pos[7].x = 609 + (253-c2.life);
	Window::Draw1(life1, pos[7], &e2);

	SDL_FreeSurface(head1);
	SDL_FreeSurface(head2);
	//Window::Draw1(energe,pos[3],&e1);
	//Window::Draw1(energe,pos[4],&e2);

}
