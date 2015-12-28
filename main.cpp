#include"config.h"
#include"man.h"
#include"p1.h"
#include"window.h"
#include"timer.h"
#include"background.h"
#include"p2.h"
#include<SDL_mixer.h>

int main(int argc, char** argv) {
	try {
        Window::Init(WINDOW_TITLE);
    }
    catch (const std::runtime_error &e){
        std::cout << e.what() << std::endl;
		SDL_Delay(10000);
        Window::Quit();
        return -1;
    }

	bool flag = true;
	SDL_Surface *ko = Window::Loadimage("data//ko.png");
	p1 p;
	p2 pp(600,500,-1);
	p.sethead("data//head1.png");
	pp.sethead("data//head2.png");
	background bbb;
	bbb.draw(p,pp);
	p.draw();
	pp.draw();
	Window::Present();

	Timer fps;
	SDL_Event e;
	bool quit = false;
	int fpss = FPS;

	//初始化SDL_mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		throw std::runtime_error("mixer Init Failed");
		//将要播放的音乐
	Mix_Music *music = NULL;
		//加载音乐
	music = Mix_LoadMUS("music//music.wav");
	Mix_PlayMusic(music, -1);


	bool keys[256];
	for(int i = 0; i < 256; ++i) {
		keys[i] = false;
	}

	while(!quit) {
		fps.start();

		while(SDL_PollEvent(&e)) {
		switch(e.type) {
			case SDL_QUIT:
			quit = true;
			break;
			case SDL_KEYDOWN:
				keys[e.key.keysym.scancode] = true;
			break;
			case SDL_KEYUP:
				keys[e.key.keysym.scancode] = false;
			break;
		}
		}
		if(p.x<0) 
			p.x = 0;
		else if(p.x >WIDTH - MAN_WIDTH)
			p.x = WIDTH - MAN_WIDTH;

		if(pp.x<0) 
			pp.x = 0;
		else if(pp.x >WIDTH - MAN_WIDTH)
			pp.x = WIDTH - MAN_WIDTH;

	
		Window::Clear();
		bbb.draw(p,pp);

		p.handleKeys(keys);
		p.nextframe(pp);
		p.draw();

		pp.handleKeys(keys);
		pp.nextframe(p);
		pp.draw();

		if(p.state == DEATH ||pp.state == DEATH)
		{

			Mix_PausedMusic();
			Mix_Chunk *ko_music = NULL;
			ko_music = Mix_LoadWAV("music//ko.wav");

			if(flag)
			{
				Mix_PlayChannel( -1, ko_music, 0 );
				flag = false;
			}

			SDL_Rect pos;
			pos.x = WIDTH/2 -100 ;
			pos.y = HEIGHT/2 - 49;
			Window::Draw1(ko,pos);
		}
		Window::Present();

		

		if(fps.getTicks() < 1000.0 / FPS) {
		SDL_Delay((1000 / FPS) - fps.getTicks());
		}
	}
	//释放音乐
	Mix_FreeMusic(music);

	//退出SDL_mixer
	Mix_CloseAudio();

	//退出SDL
	SDL_Quit();


	Window::Quit();
	return 0;
}
