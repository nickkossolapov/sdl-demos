#ifndef NOUGHTS_AND_CROSSES_TEXTTEXTURE_H
#define NOUGHTS_AND_CROSSES_TEXTTEXTURE_H

#include <SDL.h>
#include <SDL_ttf.h>

class TextTexture {
public:
    TextTexture(TTF_Font *font);

    ~TextTexture();

    void free();

    void setText(SDL_Renderer* renderer, char* text, SDL_Color color);

    void render(SDL_Renderer *renderer, SDL_Point topLeft);

    int getWidth();

private:
    int mWidth;
    int mHeight;

    TTF_Font *mFont;
    SDL_Texture *mTexture;
};

#endif //NOUGHTS_AND_CROSSES_TEXTTEXTURE_H
