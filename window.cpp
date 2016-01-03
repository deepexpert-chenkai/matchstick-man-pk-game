#include <string>
#include <stdexcept>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "window.h"
#include"config.h"


//Initialize the unique_ptr's deleters here
std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> Window::mWindow 
	= std::unique_ptr<SDL_Window, void (*)(SDL_Window*)>(nullptr, SDL_DestroyWindow);
std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> Window::mRenderer
	= std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>(nullptr, SDL_DestroyRenderer);
//Other static members
SDL_Rect Window::mBox;

void Window::Init(std::string title){
    //initialize all SDL subsystems
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw std::runtime_error("SDL Init Failed");
    if (TTF_Init() == -1)
		throw std::runtime_error("TTF Init Failed");

    //Setup our window size
    mBox.x = 0;
    mBox.y = 0;
    mBox.w = WIDTH;
    mBox.h = HEIGHT;
    //Create our window
    mWindow.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        mBox.w, mBox.h, SDL_WINDOW_SHOWN));
    //Make sure it created ok
    if (mWindow == nullptr)
        throw std::runtime_error("Failed to create window");

    //Create the renderer
    mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    //Make sure it created ok
    if (mRenderer == nullptr)
        throw std::runtime_error("Failed to create renderer");
	SDL_SetRenderDrawColor(mRenderer.get(),255, 251, 240,SDL_ALPHA_OPAQUE);
}
void Window::Quit(){
    TTF_Quit();
    SDL_Quit();
}
void Window::Draw(SDL_Surface *tex, SDL_Rect &dstRect, SDL_Rect *clip, float angle, 
                  int xPivot, int yPivot, SDL_RendererFlip flip)
{	

	SDL_Point pivot = { xPivot, yPivot };
	//int *w = &dstRect.w,*h = &dstRect.h;
	//SDL_QueryTexture(tex,NULL,NULL,w,h);
	SDL_Texture *x;
	x = SDL_CreateTextureFromSurface(mRenderer.get(),tex);
	SDL_RenderCopyEx(mRenderer.get(), x, clip, &dstRect, angle, &pivot, flip);
	SDL_DestroyTexture(x);
    //Draw the texture
}

void Window::SDL_QuerySurface(SDL_Surface* s,int *w,int *h){
	SDL_Texture *x;
	x = SDL_CreateTextureFromSurface(mRenderer.get(),s);
	SDL_QueryTexture(x,NULL,NULL,w,h);
	SDL_DestroyTexture(x);
}
SDL_Surface* Window::Loadimage(const std::string &file){
    SDL_Surface* tex = nullptr;
    tex = IMG_Load(file.c_str());
    if (tex == nullptr)
        throw std::runtime_error("Failed to load image: " + file + IMG_GetError());
    return tex;
}
SDL_Texture* Window::RenderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize){
    //Open the font
    TTF_Font *font = nullptr;
    font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (font == nullptr)
        throw std::runtime_error("Failed to load font: " + fontFile + TTF_GetError());
	
    //Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns
    SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer.get(), surf);
    //Clean up unneeded stuff    SDL_FreeSurface(surf);
    TTF_CloseFont(font);

    return texture;
}
void Window::Clear(){
    SDL_RenderClear(mRenderer.get());
}
void Window::Present(){
    SDL_RenderPresent(mRenderer.get());
}
SDL_Rect Window::Box(){
    //Update mBox to match the current window size
    SDL_GetWindowSize(mWindow.get(), &mBox.w, &mBox.h);
    return mBox;
}
void Window::Draw1(SDL_Surface *tex, SDL_Rect &dstRect, SDL_Rect *clip, float angle, 
                  int xPivot, int yPivot, SDL_RendererFlip flip)
{	
	SDL_Point pivot = { xPivot, yPivot };
	if(clip != NULL){
		dstRect.w = clip->w;
		dstRect.h = clip->h;
	}else{
		dstRect.w = tex->w;
		dstRect.h = tex->h;
	}
	SDL_Texture *x;
	x = SDL_CreateTextureFromSurface(mRenderer.get(),tex);
	SDL_RenderCopyEx(mRenderer.get(), x, clip, &dstRect, angle, &pivot, flip);
	SDL_DestroyTexture(x);
    //Draw the texture
}
void Window::Drawx(SDL_Surface *tex, SDL_Rect &dstRect, SDL_Rect *clip, float angle, 
                  int xPivot, int yPivot, SDL_RendererFlip flip)
{	
	SDL_Point pivot = { xPivot, yPivot };
	if(clip != NULL){
		dstRect.w = clip->w*2;
		dstRect.h = clip->h*2;
	}else{
		dstRect.w = tex->w*2;
		dstRect.h = tex->h*2;
	}
	SDL_Texture *x;
	x = SDL_CreateTextureFromSurface(mRenderer.get(),tex);
	SDL_RenderCopyEx(mRenderer.get(), x, clip, &dstRect, angle, &pivot, flip);
	SDL_DestroyTexture(x);
    //Draw the texture
}

SDL_Surface* Window::RemoveBackground(SDL_Surface *im,int a,int b,int c) {
  Uint32 colorkey = SDL_MapRGB(im->format, a,b,c);
  SDL_SetColorKey(im, SDL_TRUE, colorkey);
  return im;
}
